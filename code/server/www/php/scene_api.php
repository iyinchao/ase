<?php
/**
 * Scene API
 * User: 尹超
 * Date: 2014/12/4
 * Time: 0:02
 */
include_once 'scene_manager.php';

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
}
exit();

?>