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

switch ($_POST['op']) {
    case 'update':     //修改标签
        if(!isset($_POST['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']); //解析json（其实应该加上try/catch）
        TagManager::update($data); //调用方法
        break;
    case 'get_one_tag':     //根据id获得标签
        if(!isset($_POST['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']); //解析json（其实应该加上try/catch）
        TagManager::get_one_tag($data); //调用方法
        break;
    case 'delete':     //删除标签
        if(!isset($_POST['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']); //解析json（其实应该加上try/catch）
        TagManager::delete($data); //调用方法
        break;
    case 'add':     //增加标签
        if(!isset($_POST['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']); //解析json（其实应该加上try/catch）
        TagManager::add($data); //调用方法
        break;
    case 'get_tags':   //获得标签
        TagManager::get_tags();
        break;
    case 'update_tag_scene':   //更新场景的标签
        if(!isset($_POST['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']); //解析json（其实应该加上try/catch）
        TagManager::update_tag_scene($data); //调用方法
        break;
    case 'get_scene_tag':   //获得场景的标签
        if(!isset($_POST['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']); //解析json（其实应该加上try/catch）
        TagManager::get_scene_tags($data); //调用方法
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
        if(!isset($data->{'desc'})){
            exit('{"status":"INVALID_DATA"}');
        }
        else { $desc = mysqli_real_escape_string($db, $data->{'desc'});}
        $query="update tag set name='$name',`desc`='$desc' where id= $id";
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

    static public function get_one_tag($data){
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

        $query = "select * from tag where id='$id'";
        $result = $db->query($query);  //执行SQL
        $response = (object)array();
        if ($result->num_rows == 1) {
            $response = (object)array();
            $response->result = 'ok';
            $row = $result->fetch_assoc();
            $response->name=$row['name'];
            $response->desc=$row['desc'];
        }else{$response->result = 'no';}
        echo json_encode($response);
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
        if(!isset($data->{'desc'})){
            exit('{"status":"INVALID_DATA"}');
        }else { $desc = mysqli_real_escape_string($db, $data->{'desc'});}

        $query = "insert into tag (name,`desc`) values('$name','$desc')";

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
            $term->desc = $row['desc'];
            $tags[$i] = $term;
            $i = $i + 1;
        }

        $response = (object)array();
        $response->num = $n;
        $response->tags=$tags;
        echo json_encode($response);
        $db->close();
    }

    static public function update_tag_scene($data)     //更新场景标签
    {
        //database connect
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        if(!isset($data->{'s_id'})){
            exit('{"status":"INVALID_DATA"}');
        } else { $s_id = mysqli_real_escape_string($db, $data->{'s_id'});}
        if(!isset($data->{'tags'})){
            exit('{"status":"INVALID_DATA"}');
        }else {$tags = (array)$data->tags;}

        $response = (object)array();
        $response->result = 'ok';
        $query = "delete from tag_scene where s_id = '$s_id'";
        $result=$db->query($query);
        if(!$result) $response->result='no';
        if(sizeof($tags) != 0){
            for($i = 0; $i < sizeof($tags); $i++){
                $tag = mysqli_real_escape_string($db,$tags[$i]);
                $query = "insert into tag_scene values('$s_id',$tag)";
                $result=$db->query($query);
                if(!$result) $response->result='no';
            }
        }
        echo json_encode($response);
        $db->close();  //一定记得在用完数据库后关闭！！
    }

    static public function  get_scene_tags($data)  //获得场景的标签,返回的是一个数组
    {
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        if(!isset($data->{'s_id'})){
            exit('{"status":"INVALID_DATA"}');
        } else { $s_id = mysqli_real_escape_string($db, $data->{'s_id'});}
        $query = "select * from tag_scene where s_id='$s_id'";
        $tags=array();
        $result = $db->query($query);
        $response = (object)array();
        if(($n = $result->num_rows) > 0) {
            for ($i = 0; $i < $n; $i++) {
                $row = $result->fetch_assoc();
                $tags[$i] = (object)array();
                $tags[$i]->id = $row['tag'];
                $id=$row['tag'];
                $query1 = "select * from tag where id= $id";
                $result1=$db->query($query1);
                $row1=$result1->fetch_assoc();
                $tags[$i]->name=$row1['name'];
                $tags[$i]->desc=$row1['desc'];
            }
            $response->result='OK';
            $response->tags=$tags;
        }else{$response->result='no';}
        echo json_encode($response);
        $db->close();
    }

    static public function tag_delete_scene($s_id)  //删除场景的标签处理
    {
        try {
            $db = DBConn::connect();
        } catch (Exception $e) {
            exit('{"status":"ERROR_DB_CONN","error_message:"' . $e->getMessage() . '"}');
        }
        $query = "delete from tag_scene where s_id = '$s_id'";
        $result = $db->query($query);
        $db->close();
    }

    static public function tag_delete_tag($tags)   //删除标签的处理,此处的输入为数组
    {
        try {
            $db = DBConn::connect();
        } catch (Exception $e) {
            exit('{"status":"ERROR_DB_CONN","error_message:"' . $e->getMessage() . '"}');
        }
        if(sizeof($tags) != 0){
            for($i = 0; $i < sizeof($tags); $i++){
                $tag = mysqli_real_escape_string($db,$tags[$i]);
                $query = "delete from tag_scene where tag= $tag";
                $result=$db->query($query);
            }
        }
        $db->close();
    }
}
