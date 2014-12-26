<?php
/**
 * Created by PhpStorm.
 * User: 尹超
 * Date: 2014/12/24
 * Time: 15:34
 */

switch ($_GET['op']) {
    case 'client_update':     //修改标签
        if(!isset($_GET['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        TagManager::update($data); //调用方法
        break;
    case 'client_delete':     //删除场景
        if(!isset($_GET['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        TagManager::delete($data); //调用方法
        break;
    case 'client_add':     //增加标签
        if(!isset($_GET['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_GET['data']); //解析json（其实应该加上try/catch）
        TagManager::add($data); //调用方法
        break;
    case 'get_all_tags':   //获得标签
        TagManager::get_all();
        break;
}


class TagManager{
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
}




