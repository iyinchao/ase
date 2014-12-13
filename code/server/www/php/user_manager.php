<?php
/**
 * Created by PhpStorm.
 * User: 尹超
 * Date: 2014/12/13
 * Time: 13:52
 */
include_once 'conf.php';
include_once 'db_conn.php';
include_once 'debug.php';
include_once 'uuid.php';

/**
 * Class UserManager
 */
class UserManager{
    /**
     * @param $data
     */
    static public function client_login($data){
        if(!isset($data->s_id)){
            exit('{"status":"INVALID_DATA"}');
        }
        //create connection
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }

        //get user
    }

    static public function gen_salt(){
        return rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9);
    }
}