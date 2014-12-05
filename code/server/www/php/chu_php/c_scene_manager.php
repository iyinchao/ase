<?php
/**
 * Created by PhpStorm.
 * User: lenovo
 * Date: 2014/12/2
 * Time: 18:00
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
        if(!isset($_GET['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        SceneManager::view($data); //调用方法
        break;
    case 'get_tags':   //获得标签
        SceneManager::get_tags();
        break;
    case 'down':   //下载场景
        $data = json_decode($_GET['data']);
        SceneManager::down($data);
        break;
}

class SceneManager{
    const uuidNamespace = 'afc38a18-c53a-11e3-8841-1a514932ac01'; //这个要换成UUID::DEF_NS

    static public function view($data){
        //database connect
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        if(!isset($data->{'page_now'})){
            echo "ddd";
            exit('{"status":"INVALID_DATA"}');
        }
        else { $page = $data->{'page_now'};}
        $query = "select * from scene where 1=1 ";
        if(isset($data->{'search'})) {
            $sea = mysqli_real_escape_string($db, $data->{'search'});  // 防止注入攻击，对每个输入的数据做处理
            $query = $query . " and " . $sea;
        }  //php函数，用来预防攻击
        if(isset($data->{'tag'}))
        {
            //$tags=array($data->tag);   //this change have some mistakes
            $tags=$data->tag;
            for($i=0;$i<sizeof($tags);$i++)
            {
                //$tag=mysql_real_escape_string($db,$tags[$i]);  //there is no need to check for it is int not string
                $tag=$tags[$i];
                $query=$query." and Exists(select * from tag_scene where tag_scene.s_id=scene.s_id and tag_scene.tag = "."$tag".")";
            }
        }
        if(isset($data->{'sort_by'}))
        {
            $sort =mysqli_real_escape_string($db, $data->{'sort_by'});
            $query=$query." order by ".$sort;
        }
        if(isset($data->{'order'}))
        {
            $order=mysqli_real_escape_string($db, $data->{'order'});
            $query=$query." ".$order;
        }
     //   $passha1 = sha1(stripcslashes($pas));    //估计是对密码解码

        //首先，检查 magic_quotes_gpc 是否配置为自动转义斜线，若为on，应该调用stripslashes去掉$_REQUEST、$_GET,$_POST、$_COOKIE的转义斜线；然后，查询/写入/更新数据至mysql时，再使用mysql_real_escape_string进行字符转义。
        //http://blog.unvs.cn/archives/magic_quotes_gpc-mysql_real_escape_string-addslashes.html
        //$query = "select * from user where email='".$data->{'email'}."'and password=sha1('".$data->{'pas'}."')";
        $n=$page*6-6;
        $query1=$query." limit 6 offset ".$n;
        $result = $db->query($query1);  //执行SQL
        $n = $result->num_rows;
        if($n==0)
        {
            $response=(object)array();
            $response->result='no';
        }
        else {
            $i = 0;
            $scene = array();
            while ($row = $result->fetch_array()) {
                $term = (object)array();
                $term->s_id = $row['s_id'];
                $term->b_id = $row['b_id'];
                $query2="select * from scene where s_id='" . $row['b_id']."'";    //get the brand name
                $result2 = $db->query($query2);
                $row2=$result2->fetch_assoc();
                $term->brand=$row2['name'];
                $term->modify_date = $row['modify_date'];
                $term->designer = $row['designer'];
                $term->desc = $row['desc'];
                //$term->tags = $row['tags'];
                $term->download_times = $row['download_times'];
                $term->views_count = $row['views_count'];
                $scene[$i] = $term;
                $i = $i + 1;
            }
            //准备回传的JSON，需按照之前写好的接口文档设置
            $response = (object)array();
            $response->result = 'ok';  //这个转换到json就是 {"result":"ok"}
            $response->scene = $scene;
            $response->page_now = $page;
            $result = $db->query($query);  //执行SQL,get page all
            $n = $result->num_rows;
            //echo "<br/>";           //just for test
            //echo $n;
            //echo "<br/>";
            $response->page_all=ceil($n/6);
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
        $s_id = mysqli_real_escape_string($db, $data->{'id'});
        echo $s_id;
        $query = "select * from scene where s_id='" . "$s_id"."'";
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