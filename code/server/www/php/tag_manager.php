<?php
/**
 * Created by PhpStorm.
 * User: 尹超
 * Date: 2014/12/24
 * Time: 15:34
 */
include_once 'conf.php';
include_once 'db_conn.php';
include_once 'debug.php';

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
        } else {
            $id = mysqli_real_escape_string($db, $data->{'id'});
        }
        if(!isset($data->{'name'})){
            exit('{"status":"INVALID_DATA"}');
        } else {
            $name = mysqli_real_escape_string($db, $data->{'name'});
        }
        if(!isset($data->{'desc'})){
            $desc = '';
        }else{
            $desc = mysqli_real_escape_string($db, $data->{'desc'});
        }
        $query="update tag set name='$name', `desc`='$desc' where id= '$id'";
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
        $db->close();
    }

    static public function get_all_tags(){
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        $query = "select * from tag";
        $result = $db->query($query);
        $tags=array();
        while ($row = $result->fetch_array()) {
            $term = (object)array();
            $term->id = $row['id'];
            $term->name = $row['name'];
            $term->desc = $row['desc'];
            array_push($tags, $term);
        }
        $response = (object)array();
        $response->tags=$tags;
        echo json_encode($response);
        $db->close();
    }
}




