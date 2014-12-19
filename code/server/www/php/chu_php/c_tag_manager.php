<?php
/**
 * Created by PhpStorm.
 * User: lenovo
 * Date: 2014/12/19
 * Time: 21:24
 */
header("Content-Type: text/html;charset=utf-8");  //定义返回字符集
chdir("../");
include 'debug.php';      //出错的处理
include 'db_conn.php';    //数据库连接
include 'uuid.php';      //好像是解析user-id所需要的

switch ($_GET['op']) {
    case 'update':     //修改标签
        if(!isset($_GET['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        TagManager::update($data); //调用方法
        break;
    case 'delete':     //删除场景
        if(!isset($_GET['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        TagManager::delete($data); //调用方法
        break;
    case 'add':     //增加标签
        if(!isset($_GET['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        TagManager::add($data); //调用方法
        break;
    case 'get_tags':   //获得标签
        TagManager::get_tags();
        break;
}

class TagManager{
    const uuidNamespace = 'afc38a18-c53a-11e3-8841-1a514932ac01'; //这个要换成UUID::DEF_NS

    static public function update($data){
        //database connect
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        if(!isset($data->{'id'})){
            exit('{"status":"INVALID_DATA"}');
        }
        else { $id = mysqli_real_escape_string($db, $data->{'id'});}
        if(!isset($data->{'name'})){
            exit('{"status":"INVALID_DATA"}');
        }
        else { $name = mysqli_real_escape_string($db, $data->{'name'});}
        $query="update tag set name='$name' where id= $id";
        $result = $db->query($query);  //执行SQL
        if($result){
            $response = (object)array();
            $response->result = 'ok';
            echo json_encode($response);
        }else{
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
        }
        $db->close();  //一定记得在用完数据库后关闭！！
    }

    static public function add($data){
        //database connect
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        if(!isset($data->{'name'})){
            exit('{"status":"INVALID_DATA"}');
        }
        else { $name = mysqli_real_escape_string($db, $data->{'name'});}
        if(!isset($data->{'name'})){
            exit('{"status":"INVALID_DATA"}');
        }

        $query = "insert into tag (name) values('$name')";

        $result = $db->query($query);  //执行SQL
        if($result){
            $response = (object)array();
            $response->result = 'ok';
            echo json_encode($response);
        }else{
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
        }
        $db->close();  //一定记得在用完数据库后关闭！！
    }

    static public function delete($data){
        //database connect
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        if(!isset($data->{'id'})){
            exit('{"status":"INVALID_DATA"}');
        }
        else { $id = mysqli_real_escape_string($db, $data->{'id'});}
        $query = "delete from tag where id= $id";
        $result=$db->query($query);
        if($result)
        {
            $response = (object)array();
            $response->result = 'ok';  //这个转换到json就是 {"result":"ok"}
            echo json_encode($response);  //编码json，发回客户端
        } else{
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
        }
        $db->close();  //一定记得在用完数据库后关闭！！
    }

    static public function get_tags(){
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
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

}