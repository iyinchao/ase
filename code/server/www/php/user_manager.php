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
        if(!isset($data->email)){
            exit('{"status":"INVALID_DATA"}');
        }
        if(!isset($data->password)){
            exit('{"status":"INVALID_DATA"}');
        }
        //create connection
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }

        $email = mysqli_real_escape_string($db, $data->{'email'});  //php函数，用来预防攻击
        $pas = mysqli_real_escape_string($db, $data->{'password'});

        $pas_enc = sha1(stripcslashes($pas.'89515871'));  //TODO:real sand op

        $query = "select * from user where email='" . "$email" . "' and password='" . "$pas_enc" . "'";

        $response = (object)array();
        $result = $db->query($query);  //执行SQL
        if ($result->num_rows == 1) {
            $row = $result->fetch_assoc();

            session_start();

            $_SESSION['user_id'] = $row['u_id'];
            $response->sess_id = session_id();

            if(isset($data->{'remember'}) && $data->{'remember'})      //看是否已经登陆过
                setcookie('MEIJIA_UID', $row['u_id'], time()+3600*24*7, '/');//一周内免登录的cookie

            $response->status = 'OK';
            foreach($row as $name => $value){
                if($name == 'salt') continue;
                $response->$name = $value;
            }

        }else{
            $response->status = 'ERROR_LOGIN';
        }
        echo json_encode($response);
        $db->close();
    }

    static public function gen_salt(){
        return rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9).rand(0,9);
    }
}