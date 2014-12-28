<?php
/**
 * Created by PhpStorm.
 * User: 尹超
 * Date: 2014/12/13
 * Time: 13:51
 */
include_once 'user_manager.php';

//default response header
header("Content-Type: application/json;charset=utf-8");

//Process client post data
if(!isset($_POST['op'])) exit('{"status":"NO_REQ_OP"}');
switch($_POST['op']){
    case 'client_login':
        if(!isset($_POST['data'])) exit('{"status":"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        UserManager::client_login($data);
        break;
    case 'client_logout':
        /*if(!isset($_POST['data'])) exit('{"status":"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        SceneManager::client_browse($data);*/
    default:
        exit('{"status":"UNKNOWN_OP"}');
}
//exit();