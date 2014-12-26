<?php
/**
 * Scene Manager
 * User: Charles
 * Date: 2014/12/2
 * Time: 22:16
 */
include_once 'conf.php';
include_once 'db_conn.php';
include_once 'debug.php';
include_once 'uuid.php';
include_once 'zip.php';

class SceneManager{
    /**
     * clientDownload
     *
     * Handle client download request for a scene.
     * Response a application/zip binary stream to the client
     *
     * @param $data object for scene
     */
    public static function client_download($data){
        //test if s_id data is set
        if(!isset($data->s_id)){
            exit('{"status":"INVALID_DATA"}');
        }
        //create connection
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        //prevent inject attack
        //TODO: special check, such as length & charset
        $s_id = mysqli_real_escape_string($db, $data->s_id);

        $qs = "SELECT * FROM scene WHERE s_id ='$s_id'";
        //process query result
        $result = $db->query($qs);
        if($result->num_rows == 1){
            $row = $result->fetch_assoc();
            if(isset($data->admin_op) && $data->admin_op == true){
                $name = $row['name'];
            }else {
                $n = $row['download_times'];
                $n = $n + 1;
                $qs = "UPDATE scene set download_times = $n where s_id = '$s_id'";
                $db->query($qs);
            }
            $db->close();
            try{
                /*$exclude = array(realpath(Conf::DIR_DESIGN_FILE.$s_id.'/thumb.png'));
                echo realpath(Conf::DIR_DESIGN_FILE.$s_id.'/thumb.png');*/
                $zipdir = ZipCon::zip_dir(Conf::DIR_DESIGN_FILE.$s_id);
            }catch (Exception $e){
                exit('{"status":"ERROR_CREATE_ZIP", "err_msg":"'.$e->getMessage().'"}');
            }
            if(!isset($data->test)) {
                //form response
                header('Content-Type: application/zip');
                header('Content-Length: ' . filesize($zipdir));
                if(isset($data->admin_op) && $data->admin_op == true && isset($name)){
                    header('Content-Disposition: attachment; filename="scene-'.$name.'-'.$s_id.'.zip"');
                }else{
                    header('Content-Disposition: attachment; filename="'.$s_id.'.zip"');
                }
                readfile($zipdir);
                unlink($zipdir); //remove temp
            }else{
                echo $zipdir;
                unlink($zipdir);
            }

        }else{
            exit('{"status":"NO_SCENE"}');
        }

        //
    }

    public static function client_browse($data){
        //test if s_id data is set
        if(!isset($data->page_now) || !isset($data->scene_per_page)){
            exit('{"status":"INVALID_DATA"}');
        }
        //create connection
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        //inspect each data field & pre-process user input data
        //'must have' field
        $scene_per_page = mysqli_real_escape_string($db, $data->scene_per_page);
        $page_now = mysqli_real_escape_string($db, $data->page_now);

        $query = "select * from scene where 1=1 ";

        if(isset($data->tag)){
            $tags = (array)$data->tag;
            if(sizeof($tags) != 0){
                for($i = 0; $i < sizeof($tags); $i++){
                    $tag = mysqli_real_escape_string($db,$tags[$i]);
                    $query = $query."and Exists(select * from tag_scene where tag_scene.s_id = scene.s_id and tag_scene.tag = $tag)";
                }
            }
        }
        if(isset($data->search)){

        }
        if(isset($data->sort_by)){

        }
        if($scene_per_page >= 1) {
            $now_page = $page_now * $scene_per_page; //Notice: page starts from 0;
            $query_count = "SELECT COUNT(s_id) AS num FROM ($query)temp";
            $query = $query . " limit $scene_per_page offset $now_page";
            $result = $db->query($query_count);
            $row = $result->fetch_assoc();
            $page_all = ceil(((int)$row['num'])/(int)$scene_per_page);
        }else{
            $page_all = -1;
        }
        //echo $query;
        $result = $db->query($query);
        $scene = array();
        if(($n = $result->num_rows) > 0){
            for($i = 0; $i < $n; $i++){
                $scene_obj = (object)array();
                $row = $result->fetch_assoc();
                foreach($row as $name => $value){
                    $scene_obj->$name = $value;
                }
                /*if(file_exists(Conf::DIR_DESIGN_FILE.$row['s_id'].'/thumb.png')){
                    //$scene_obj->thumb = base64_encode(file_get_contents(Conf::DIR_DESIGN_FILE.$row['s_id'].'/thumb.png'));
                }else{
                    //$scene_obj->thumb = '';
                }*/
                $scene[$i] = $scene_obj;
            }
        }


        $response = (object)array();
        $response->status = 'OK';
        $response->scene = $scene;
        $response->page_now = $page_now;
        $response->page_all = $page_all;
        echo json_encode($response);
    }

    public static function client_get_thumb($data){
        //test if required data is set
        if(!isset($data->s_id)){
            exit('{"status":"INVALID_DATA"}');
        }

        $s_id = $data->s_id;  //TODO:check the data value?

        if(file_exists(Conf::DIR_DESIGN_FILE.$s_id)){
            if(file_exists(Conf::DIR_DESIGN_FILE.$s_id.'/'.'thumb.png')) {
                $thumb = fopen(Conf::DIR_DESIGN_FILE.$s_id.'/'.'thumb.png', 'rb');
                if(!$thumb){
                    exit('{"status":"ERROR_OPEN_THUMB"}');
                }
                header('Content-Type: image/jpeg');
                header('Content-Length: ' . filesize(Conf::DIR_DESIGN_FILE . $s_id.'/'.'thumb.png'));
                fpassthru($thumb);
            }else{
                exit('{"status":"NO_THUMB"}');
            }
        }else{
            exit('{"status":"NO_SCENE"}');
        }
    }

    public static function get_meta_by_id($data){
        //test if s_id data is set
        if(!isset($data->s_id)){
            exit('{"status":"INVALID_DATA"}');
        }

        //create connection
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }
        //prevent inject attack
        //TODO: special check, such as length & charset
        $s_id = mysqli_real_escape_string($db, $data->s_id);
        $qs = "SELECT * FROM scene WHERE s_id ='$s_id'";
        $result = $db->query($qs);
        if($result->num_rows == 1){
            $scene_obj = (object)array();
            $row = $result->fetch_assoc();
            foreach($row as $name => $value){
                $scene_obj->$name = $value;
            }
            /*if(file_exists(Conf::DIR_DESIGN_FILE.$row['s_id'].'/thumb.png')){
                //$scene_obj->thumb = base64_encode(file_get_contents(Conf::DIR_DESIGN_FILE.$row['s_id'].'/thumb.png'));
            }else{
                //$scene_obj->thumb = '';
            }*/
            echo json_encode($scene_obj);
        }else{
            exit('{"status":"NO_SCENE"}');
        }

    }

    static public function update_one($data)
    {
        date_default_timezone_set('Asia/Shanghai');
        //database connect
        try {
            $db = DBConn::connect();
        } catch (Exception $e) {
            exit('{"status":"ERROR_DB_CONN","error_message:"' . $e->getMessage() . '"}');
        }
        if (!isset($data->{'s_id'})) {
            exit('{"status":"INVALID_DATA"}');
        } else {
            $s_id = mysqli_real_escape_string($db, $data->{'s_id'});
        }
        $time = date("Y-m-d H:i:s", time());
        $query = "update scene set modify_date= '" . "$time" . "' ";
        if (isset($data->{'name'})) {
            $name = mysqli_real_escape_string($db, $data->{'name'});
            $query = $query . ",name = '" . $name . "'";
        }
        if (isset($data->{'designer'})) {
            $designer = mysqli_real_escape_string($db, $data->{'designer'});
            $query = $query . ",designer = '$designer' ";
        }
        if (isset($data->{'views_count'})) {
            $views_count = mysqli_real_escape_string($db, $data->{'views_count'});
            $query = $query . ",views_count = '$views_count' ";
        }
        if (isset($data->{'desc'})) {
            $desc = mysqli_real_escape_string($db, $data->{'desc'});
            $query = $query . ",`desc` = '$desc' ";
        }
        $query = $query . " where s_id = '" . $s_id . "'";
        $result = $db->query($query);  //执行SQL
        if ($result) {
            echo('{"status":"OK"}');
        } else {
            exit('{"status":"ERROR_UPDATE"}');
        }
        $db->close();  //一定记得在用完数据库后关闭！！
    }

    public static function get_new_b_id(){
        $new_b_id = UUID::gen_b_id();
        $response = (object)array();
        $response->new_b_id = $new_b_id;
        echo (json_encode($response));
    }

    public static function add($data){
        date_default_timezone_set('Asia/Shanghai');
        //database connect
        try {
            $db = DBConn::connect();
        } catch (Exception $e) {
            exit('{"status":"ERROR_DB_CONN","error_message:"' . $e->getMessage() . '"}');
        }
        if (!isset($data->{'s_id'})) {
            exit('{"status":"INVALID_DATA"}');
        } else {
            $s_id = mysqli_real_escape_string($db, $data->{'s_id'});
        }
        if (!isset($data->{'b_id'})) {
            exit('{"status":"INVALID_DATA"}');
        } else {
            $b_id = mysqli_real_escape_string($db, $data->{'b_id'});
        }
        if (!isset($data->{'name'})) {
            exit('{"status":"INVALID_DATA"}');
        } else {
            $name = mysqli_real_escape_string($db, $data->{'name'});
        }
        if (!isset($data->{'views_count'})) {
            exit('{"status":"INVALID_DATA"}');
        } else {
            $views_count = mysqli_real_escape_string($db, $data->{'views_count'});
        }
        if (!isset($data->{'desc'})) {
            $desc = "";
        } else {
            $desc = mysqli_real_escape_string($db, $data->{'desc'});
        }
        if (!isset($data->{'designer'})) {
            $designer = "";
        } else {
            $designer = mysqli_real_escape_string($db, $data->{'designer'});
        }

        $modify_date = date("Y-m-d H:i:s", time());

        if(isset($_FILES) && isset($_FILES['file']) && $_FILES['file']['error'] != 1 && $_FILES['file']['tmp_name'] != ''){
            $file = $_FILES['file'];
        }else{
            exit('{"status":"ERROR_INVALID_FILE"}');
        }

        $query = "insert into scene values('$s_id','$b_id','$name','$modify_date','$designer','$desc',0,'$views_count')";

        $result = $db->query($query);  //执行SQL
        if ($result) {
            //move_uploaded_file();
            //move_uploaded_file($file['tmp_name'], )
            //$tmp = explode('\\',tempnam('/','unzip'));
            //echo ($tmp[count($tmp) -1]);
            //ZipCon::unzip($file['tmp_name'], Conf::DIR_TMP.$tmp[count($tmp) -1]);
            if(file_exists(Conf::DIR_DESIGN_FILE.$s_id)){
                if(is_dir(Conf::DIR_DESIGN_FILE.$s_id)){
                    $it = new RecursiveDirectoryIterator(Conf::DIR_DESIGN_FILE.$s_id, RecursiveDirectoryIterator::SKIP_DOTS);
                    $files = new RecursiveIteratorIterator($it,
                        RecursiveIteratorIterator::CHILD_FIRST);
                    foreach($files as $file) {
                        if ($file->isDir()){
                            rmdir($file->getRealPath());
                        } else {
                            unlink($file->getRealPath());
                        }
                    }
                    rmdir(Conf::DIR_DESIGN_FILE.$s_id);
                }else{
                    unlink(Conf::DIR_DESIGN_FILE.$s_id);
                }
            }
            try {
                ZipCon::unzip($file['tmp_name'], Conf::DIR_DESIGN_FILE . $s_id);
            }catch (Exception $e){
                $query = "delete from scene where s_id = '$s_id'";
                $db->query($query);
                exit('{"status":"ERROR_UNZIP"}');
            }
        }else{
            exit('{"status":"ERROR_DB_INSERT"}');
        }

        $db->close();

        $response = (object)array();
        $response->status = 'OK';
        echo (json_encode($response));
    }

    public static function delete_one($data){
        //database connect
        try {
            $db = DBConn::connect();
        } catch (Exception $e) {
            exit('{"status":"ERROR_DB_CONN","error_message:"' . $e->getMessage() . '"}');
        }
        if (!isset($data->{'s_id'})) {
            echo "ddd";
            exit('{"status":"INVALID_DATA"}');
        } else {
            $s_id = mysqli_real_escape_string($db, $data->{'s_id'});
        }

        $query = "delete from scene where s_id='" . $s_id . "'";

        $result = $db->query($query);
        if($result){
            if(file_exists(Conf::DIR_DESIGN_FILE.$s_id)){
                if(is_dir(Conf::DIR_DESIGN_FILE.$s_id)){
                    $it = new RecursiveDirectoryIterator(Conf::DIR_DESIGN_FILE.$s_id, RecursiveDirectoryIterator::SKIP_DOTS);
                    $files = new RecursiveIteratorIterator($it,
                        RecursiveIteratorIterator::CHILD_FIRST);
                    foreach($files as $file) {
                        if ($file->isDir()){
                            rmdir($file->getRealPath());
                        } else {
                            unlink($file->getRealPath());
                        }
                    }
                    rmdir(Conf::DIR_DESIGN_FILE.$s_id);
                }else{
                    unlink(Conf::DIR_DESIGN_FILE.$s_id);
                }
            }
            echo ('{"status":"OK"}');
        }else{
            echo ('{"status":"ERROR_DB_DELETE"}');
        }
    }
}
