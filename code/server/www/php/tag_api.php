<?php
/**
 * Created by PhpStorm.
 * User: 尹超
 * Date: 2014/12/24
 * Time: 15:42
 */

include_once 'tag_manager.php';

//default response header
header("Content-Type: application/json;charset=utf-8");

if(!isset($_POST['op'])) exit('{"status":"NO_REQ_OP"}');
switch($_POST['op']) {
    case 'get_all_tags':
        TagManager::get_all_tags();
        break;
    case 'update_tag_scene':
        if(!isset($_POST['data'])) exit('{"status":"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        TagManager::update_tag_scene($data);
        break;
    case 'get_one_scene_tags':
        if(!isset($_POST['data'])) exit('{"status":"NO_REQ_DATA"}');
        $data = json_decode($_POST['data']);
        TagManager::get_one_scene_tags($data);
        break;
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
    default:
        exit('{"status":"UNKNOWN_OP"}');
}
exit();