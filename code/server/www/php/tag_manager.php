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
        } else {
            $s_id = mysqli_real_escape_string($db, $data->{'s_id'});
        }
        if(!isset($data->{'tags'})){
            exit('{"status":"INVALID_DATA"}');
        }else {
            $tags = (array)$data->tags;
        }
        $no_echo = false;
        if(isset($data->{'no_echo'}) && $data->{'no_echo'} == true){
            $no_echo = true;
        }

        $response = (object)array();
        $response->status = 'OK';
        $query = "delete from tag_scene where s_id = '$s_id'";
        $result=$db->query($query);
        if (!$result) {
            if ($no_echo) {
                return false;
            } else {
                $response->status = 'ERROR_DELETE';
            }
        }
        if(sizeof($tags) != 0){
            for($i = 0; $i < sizeof($tags); $i++){
                $tag = mysqli_real_escape_string($db,$tags[$i]);
                $query = "insert into tag_scene values('$s_id',$tag)";
                $result=$db->query($query);
                if (!$result) {
                    if ($no_echo) {
                        return false;
                    } else {
                        $response->status = 'ERROR_INSERT';
                    }
                }
            }
        }

        $db->close();

        if($no_echo){
            return true;
        }else {
            echo json_encode($response);
            if($response->status != 'OK'){
                return false;
            }else{
                return true;
            }
        }
    }

    static public function get_one_scene_tags($data)  //获得场景的标签,返回的是一个数组
    {
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }

        if(!isset($data->{'s_id'})){
            exit('{"status":"INVALID_DATA"}');
        } else {
            $s_id = mysqli_real_escape_string($db, $data->{'s_id'});
        }

        $query = "select * from tag_scene where s_id='$s_id'";
        $result = $db->query($query);
        if(!$result){
            exit('{"status":"ERROR_QUERY"}');
        }else {
            $response = (object)array();
            $tags=array();
            while($row = $result->fetch_assoc()){
                array_push($tags, $row['tag']);
            }
            $response->status='OK';
            $response->tags=$tags;
            echo json_encode($response);
        }
        $db->close();
       /* $response = (object)array();
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
            $response->status='OK';
            $response->tags=$tags;
        }else{
            $response->status='no';
        }
        echo json_encode($response);
        $db->close();*/
    }
}




