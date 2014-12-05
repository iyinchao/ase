<?php
/**
 * Created by PhpStorm.
 * User: lenovo
 * Date: 2014/12/3
 * Time: 18:13
 */
chdir("../");
header("Content-Type: text/html;charset=utf-8");  //定义返回字符集
include 'debug.php';      //出错的处理
include 'db_conn.php';    //数据库连接
include 'uuid.php';      //好像是解析user-id所需要的

//取得XXX.php?op=xxx&data=xxx中的信息
//op为option，即相关操作名称，如login，logout，reg等
//data为客户端传来的json数据（json）
//试试看：实现读post数据（_POST['XXX']）中的op和data，因为感觉这样更安全
switch ($_GET['op']) {
    case 'view':     //获得场景
        if(!isset($_GET['data'])) exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        USceneManager::view($data); //调用方法
        break;
    case 'delete':   //获得标签
        if(!isset($_GET['data'])) exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        USceneManager::delete($data);
        break;
    case 'down':   //下载场景
        $data = json_decode($_GET['data']);
        SceneManager::down($data);
        break;
}

class USceneManager{
    const uuidNamespace = 'afc38a18-c53a-11e3-8841-1a514932ac01'; //这个要换成UUID::DEF_NS

    static public function view($data){

        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        if(!isset($data->{'page_now'})){
            exit('{"status":"INVALID_DATA"}');
        }
        else { $page = $data->{'page_now'};}
        $query = "select * from user_scene where 1=1 ";
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
                $query=$query." and Exists(select * from tag_uscene where tag_uscene.us_id=user_scene.us_id and tag_uscene.tag = "."$tag".")";
            }
        }
        $u_id = mysqli_real_escape_string($db, $data->{'u_id'});  //之后利用cookie得到u_id
        $query=$query." and u_id = '".$u_id."'";
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
        $n=$page*6-6;
        $query1=$query." limit 6 offset ".$n;
        //echo $query;     //just for test
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
            while ($row = $result->fetch_array())
            {
                $term = (object)array();
                $term->us_id=$row['us_id'];
                $s_id=$row['s_id'];
                $query3="select * from scene where s_id='" . "$s_id"."'";    //get the detail of the scene
                $result1 = $db->query($query3);
                $row1=$result1->fetch_assoc();
                $term->s_id = $row['s_id'];
                $term->b_id = $row1['b_id'];
                $query2="select * from scene where s_id='" . $row1['b_id']."'";      //get the brand name
                $result2 = $db->query($query2);
                $row2=$result2->fetch_assoc();
                $term->brand=$row2['name'];
                $term->modify_date = $row1['modify_date'];
                $term->designer = $row1['designer'];
                $term->desc = $row1['desc'];
                $term->download_times = $row1['download_times'];
                $term->views_count = $row1['views_count'];
                $scene[$i] = $term;
                $i = $i + 1;
            }
            //准备回传的JSON，需按照之前写好的接口文档设置
            $response = (object)array();
            $response->result = 'ok';  //这个转换到json就是 {"result":"ok"}
            $response->scene=$scene;
            $response->page_now=$page;
            $result = $db->query($query);  //执行SQL,get page_all
            $n = $result->num_rows;
            //echo "<br/>";           //just for test
            //echo $n;
            //echo "<br/>";
            $response->page_all=ceil($n/6);
            echo json_encode($response);  //编码json，发回客户端
        }
        $db->close();  //一定记得在用完数据库后关闭！！
    }


    static  public function delete($data){
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        if(!isset($data->{'us_id'})){
            exit('{"status":"INVALID_DATA"}');
        }
        $us_id = mysqli_real_escape_string($db, $data->{'us_id'});
        $query = "delete from user_scene where us_id='" . $us_id."'";
        $result=$db->query($query);
        if($result)
        {
            $response = (object)array();
            $response->result = 'ok';  //这个转换到json就是 {"result":"ok"}
            echo json_encode($response);  //编码json，发回客户端
        }
        $db->close();
    }

}

?>