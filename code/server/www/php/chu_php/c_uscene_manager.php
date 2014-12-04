<?php
/**
 * Created by PhpStorm.
 * User: lenovo
 * Date: 2014/12/3
 * Time: 18:13
 */
header("Content-Type: text/html;charset=utf-8");  //定义返回字符集
include '../debug.php';      //出错的处理
include '../db_conn.php';    //数据库连接
include '../uuid.php';      //好像是解析user-id所需要的

//取得XXX.php?op=xxx&data=xxx中的信息
//op为option，即相关操作名称，如login，logout，reg等
//data为客户端传来的json数据（json）
//试试看：实现读post数据（_POST['XXX']）中的op和data，因为感觉这样更安全
switch ($_GET['op']) {
    case 'view':     //获得场景
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        USceneManager::view($data); //调用方法
        break;
    case 'open':   //获得标签
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        USceneManager::open($data);
        break;
    case 'down':   //下载场景
        $data = json_decode($_GET['data']);
        SceneManager::down($data);
        break;
}

class USceneManager{
    const uuidNamespace = 'afc38a18-c53a-11e3-8841-1a514932ac01'; //这个要换成UUID::DEF_NS

    static public function view($data){

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
        $sea = mysqli_real_escape_string($db, $data->{'search'});  //php函数，用来预防攻击
        $tag = mysqli_real_escape_string($db, $data->{'tag'});
        $u_id = mysqli_real_escape_string($db, $data->{'u_id'});
        $page = $data->{'page_now'};
        $sort =mysqli_real_escape_string($db, $data->{'sort_by'});
        $order=mysqli_real_escape_string($db, $data->{'order'});
        //   $passha1 = sha1(stripcslashes($pas));    //估计是对密码解码

        //首先，检查 magic_quotes_gpc 是否配置为自动转义斜线，若为on，应该调用stripslashes去掉$_REQUEST、$_GET,$_POST、$_COOKIE的转义斜线；然后，查询/写入/更新数据至mysql时，再使用mysql_real_escape_string进行字符转义。
        //http://blog.unvs.cn/archives/magic_quotes_gpc-mysql_real_escape_string-addslashes.html
        //$query = "select * from user where email='".$data->{'email'}."'and password=sha1('".$data->{'pas'}."')";
        $query = "select * from user_scene where u_id= '" . "$u_id"."' and tags = "."$tag";
        if(trim($sea)!="") $query = $query ." and ". "$sea";
        if(trim($sort)!="") $query=$query." order by ".$sort;
        $result = $db->query($query);  //执行SQL
        $n=$result->num_rows;
        if($n<=($page-1)*6)
        {
            $response=(object)array();
            $response->result='no';
        }
        else {
            $i = 0;
            $scene = array();
            $k = ($page - 1) * 4;
            while ($row = $result->fetch_array()) {
                if ($i >= ($page - 1) * 4 && $i < $n && $i < $page * 4) {
                    $nn = $i - $k;
                    $term = (object)array();
                    $s_id=$row['s_id'];
                    $query="select * from scene where s_id='" . "$s_id"."'";
                    $result1 = $db->query($query);
                    $row1=$result1->fetch_assoc();
                    $term->s_id = $row['s_id'];
                    $term->b_id = $row1['b_id'];
                    $term->modify_date = $row1['modify_date'];
                    $term->designer = $row1['designer'];
                    $term->desc = $row1['desc'];
                    $term->tags = $row1['tags'];
                    $term->download_times = $row1['download_times'];
                    $term->views_count = $row1['views_count'];
                    $scene[$nn] = $term;
                }
                $i = $i + 1;
            }

            //  session_start();  //开启php session
            //  $row = $result->fetch_assoc();   //取结果中的一行，如有多行可以for循环之。但是此处不需要
            // $_SESSION['user_id'] = $row['id'];  //设置session cookie   表示已经登录了

            //准备回传的JSON，需按照之前写好的接口文档设置
            $response = (object)array();
            $response->result = 'ok';  //这个转换到json就是 {"result":"ok"}
            $response->scene=$scene;
            $response->page_now=$page;
            $response->page_all=ceil($n/6);
            // $response->sess_id = session_id();
            //$response->user_id = $_SESSION['user_id'];  //不是可以直接从row【‘id’】中得到吗
            // $response->email = $row['email'];
            // $response->name = $row['display_name'];
            //$response->gavatar = 'http://www.gravatar.com/avatar/'.md5($email).'?d=mm&s=48';  //这是什么东西
            //$response->sign = $row['sign'];

            //if(isset($data->{'remember'}) && $data->{'remember'})
            //  setcookie('PANOCAMP_UID', $response->user_id, time()+3600*24*7, '/');//一周内免登录的cookie

            echo json_encode($response);  //编码json，发回客户端
        }
        $db->close();  //一定记得在用完数据库后关闭！！
    }

    static public function get_tags(){
        $db = DBConn::connect();
        $query = "select * from tag";
        $result = $db->query($query);
        $n=$result->num_rows;
        $tags=array();
        $i=0;
        while ($row = $result->fetch_array()) {
            $term = (object)array();
            $term->id = $row['id'];
            $term->name = $row['name'];
            $tags[$i] = $term;
            $i = $i + 1;
        }

        $response = (object)array();
        $response->num = $n;
        $response->tags=$tags;
        echo json_encode($response);
        $db->close();
    }

    static  public function down($data){
        $db = DBConn::connect();
        $us_id = mysqli_real_escape_string($db, $data->{'us_id'});
        $query = "select * from user_scene where s_id='" . "$us_id"."'";
        $result = $db->query($query);
        if ($result->num_rows == 1) {
            $row=$result->fetch_assoc();
            $response=(object)array();
            $response->result='ok';
        }
        else{
            $response=(object)array();
            $response->result='no';
        }
        echo json_encode($response);
        $db->close();
    }

}

?>