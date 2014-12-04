<?php
header("Content-Type: text/html;charset=utf-8");  //定义返回字符集
include '../debug.php';
include '../db_conn.php';   //需要修改
include '../uuid.php';

//取得XXX.php?op=xxx&data=xxx中的信息
//op为option，即相关操作名称，如login，logout，reg等
//data为客户端传来的json数据（json）
//试试看：实现读post数据（_POST['XXX']）中的op和data，因为感觉这样更安全
$op=$_GET['op'];
//echo $_GET['data'];
//$data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
//UserManager::login($data); //调用方法
//echo "<br/>";
switch ($op) {
    case 'login':
        $data = json_decode($_GET['data']);  //解析json（其实应该加上try/catch）
        UserManager::login($data); //调用方法
        break;
    case 'testLogin':
        UserManager::testLogin();
        break;
    case 'logout':
        UserManager::logout();
        break;
    case 'reg':
        $data = json_decode($_GET['data']);
        UserManager::register($data);
        break;
    default:
        echo "sdd";
}

class UserManager{
    const uuidNamespace = 'afc38a18-c53a-11e3-8841-1a514932ac01'; //这个要换成UUID::DEF_NS

    static public function login($data){

        $db = DBConn::connect();   //连接数据库
        //下面这一段应改成try/catch
/*        if (mysqli_connect_errno()) {
            //echo "Failed to connect to MySQL: " . mysqli_connect_error();
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
            die('Failed to connect the database');
        }*/


        // 防止注入攻击，对每个输入的数据做处理
        $email = mysqli_real_escape_string($db, $data->{'email'});  //php函数，用来预防攻击
        $pas = mysqli_real_escape_string($db, $data->{'pas'});
        //$passha1 = sha1(stripcslashes($pas));    //估计是对密码解码  不太懂，为了测试先忽略

        //首先，检查 magic_quotes_gpc 是否配置为自动转义斜线，若为on，应该调用stripslashes去掉$_REQUEST、$_GET,$_POST、$_COOKIE的转义斜线；然后，查询/写入/更新数据至mysql时，再使用mysql_real_escape_string进行字符转义。
        //http://blog.unvs.cn/archives/magic_quotes_gpc-mysql_real_escape_string-addslashes.html
        //$query = "select * from user where email='".$data->{'email'}."'and password=sha1('".$data->{'pas'}."')";
        $query = "select * from user where email='" . "$email" . "' and password='" . "$pas" . "'";
        echo $query;
        $result = $db->query($query);  //执行SQL
        if ($result->num_rows == 1) {
            session_start();  //开启php session
            $row = $result->fetch_assoc();   //取结果中的一行，如有多行可以for循环之。但是此处不需要
            $_SESSION['user_id'] = $row['id'];  //设置session cookie   表示已经登录了

            //准备回传的JSON，需按照之前写好的接口文档设置
            $response = (object)array();
            $response->result = 'ok';  //这个转换到json就是 {"result":"ok"}
            $response->sess_id = session_id();
            $response->user_id = $_SESSION['user_id'];  //不是可以直接从row【‘id’】中得到吗
            $response->email = $row['email'];
            $response->name = $row['display_name'];
            $response->gavatar = 'http://www.gravatar.com/avatar/'.md5($email).'?d=mm&s=48';  //使用外部的头像服务
            $response->sign = $row['sign'];   //用户自定义签名，我们不用

            if(isset($data->{'remember'}) && $data->{'remember'})
                setcookie('PANOCAMP_UID', $response->user_id, time()+3600*24*7, '/');//一周内免登录的cookie

            echo json_encode($response);  //编码json，发回客户端
        } else {
            //没找到该用户
            session_start();
            if(isset($_SESSION['user_id'])) unset($_SESSION['user_id']); //杀掉session
            setcookie("PANOCAMP_UID", "", time()-3600, '/');  //清空cookie
            //返回json
            $response = (object)array();
            $response->result = 'no';  //这里应该是status，反正根据接口文档做
            echo json_encode($response);
        }
        $db->close();  //一定记得在用完数据库后关闭！！
    }

    static public function testLogin(){
        session_start();
        if(!isset($_SESSION['user_id']) && !isset($_COOKIE['PANOCAMP_UID'])){
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
            return;
        }

        if(isset($_COOKIE['PANOCAMP_UID'])){
            $uid = $_COOKIE['PANOCAMP_UID'];
        }else{
            $uid = $_SESSION['user_id'];
        }


        $db = DBConn::connect();
        $query = "select * from user where id='".$uid."'";
        $result = $db->query($query);
        if ($result->num_rows == 1) {
            if(session_status() == PHP_SESSION_ACTIVE){
                session_destroy();
            }
            session_start();
            $row = $result->fetch_assoc();
            $_SESSION['user_id'] = $row['id'];

            $response = (object)array();
            $response->result = 'ok';
            $response->sess_id = session_id();
            $response->user_id = $_SESSION['user_id'];
            $response->email = $row['email'];
            $response->name = $row['display_name'];
            $response->gavatar = 'http://www.gravatar.com/avatar/'.md5($row['email']).'?d=mm&s=48';
            $response->sign = $row['sign'];

            echo json_encode($response);
        }else{
            session_start();
            if(isset($_SESSION['user_id'])) unset($_SESSION['user_id']);
            setcookie("PANOCAMP_UID", "", time()-3600, '/');
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
        }

        $db->close();
    }

    static public  function logout(){
        session_start();
        //销毁所有的 session 信息和 cookie 信息
        if(isset($_SESSION['user_id'])) unset($_SESSION['user_id']);
        setcookie("PANOCAMP_UID", "", time()-3600, '/');
        setcookie("PHPSESSID", "", time()-3600, '/');
        session_destroy();
        echo '{"result":"ok"}';
    }

    static  public function register($data){
        $db = DBConn::connect();

        if (mysqli_connect_errno()) {
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
            die('Failed to connet the database');
        }

        // escape variables for security
        $email = mysqli_real_escape_string($db, $data->{'email'});
        $name = mysqli_real_escape_string($db, $data->{'name'});
        $pas = mysqli_real_escape_string($db, $data->{'pas'});
        $sign = mysqli_real_escape_string($db, $data->{'sign'});

        $passha1 = sha1(stripcslashes($pas));

        $uid = UUID::v5(self::uuidNamespace, $email);

        $query = "INSERT INTO USER VALUES ('".$uid."','".$email."','".$passha1."','".$name."','".gmdate('Y-m-d H:i:s')."','".$sign."')";

        $result = $db->query($query);

        if($result){
            @mkdir('../user/'.$uid);
            $response = (object)array();
            $response->result = 'ok';
            echo json_encode($response);
        }else{
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
        }
        $db->close();
    }

    /*static public function isLogin($uid){
        session_start();
        if($_SESSION['user_id'] == $uid){
            return true;
        }
        if($_COOKIE['user_id'] == $uid){
            if(session_status() == PHP_SESSION_NONE){
                session_start();
                $_SESSION['user_id'] = $_COOKIE['user_id'];
            }
            return true;
        }
        return false;
    }*/
}

?>