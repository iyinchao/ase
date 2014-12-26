<?php
/**
 * Scene API
 * User: 尹超
 * Date: 2014/12/4
 * Time: 0:02
 */
include_once 'scene_manager.php';

//default response header
header("Content-Type: application/json;charset=utf-8");

//Process client post data
if(!isset($_POST['op'])) exit('{"status":"NO_REQ_OP"}');
switch($_POST['op']){
    case 'client_download':
        if(!isset($_POST['data'])) exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        SceneManager::client_download($data);
        break;
    case 'client_browse':
        if(!isset($_POST['data'])) exit('{"status":"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        SceneManager::client_browse($data);
        break;
    case 'client_get_thumb':
        if(!isset($_POST['data'])) exit('{"status":"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        SceneManager::client_get_thumb($data);
        break;
    case 'get_meta_by_id':
        if(!isset($_POST['data'])) exit('{"status":"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        SceneManager::get_meta_by_id($data);
        break;
    case 'update_one':
        if(!isset($_POST['data'])) exit('{"status":"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        SceneManager::update_one($data);
        break;
    case 'get_new_b_id':
        SceneManager::get_new_b_id();
        break;
    case 'add':     //增加场景
        /*todo: upload_max_filesize & post_max_size is needed to be set up to 64MB!*/
        if(!isset($_POST['data']))  exit('{"status:"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        SceneManager::add($data);
        break;
    case 'delete_one':
        if(!isset($_POST['data'])) exit('{"status":"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        SceneManager::delete_one($data);
        break;
}
exit();

?>