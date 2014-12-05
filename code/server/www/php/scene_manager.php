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
    static public function client_download($data){
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
        $db->close();
        if($result->num_rows == 1){
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
                header('Content-Disposition: attachment; filename="scene.zip"');
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
        $now_page = $page_now * $scene_per_page; //Notice: page starts from 0;
        $query_count = "SELECT COUNT(s_id) AS num FROM ($query)temp";
        $query = $query." limit $scene_per_page offset $now_page";
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
                $scene[$i] = json_encode($scene_obj);
            }
        }
        $result = $db->query($query_count);
        $row = $result->fetch_assoc();
        $page_all = ceil(((int)$row['num'])/(int)$scene_per_page);

        $response = (object)array();
        $response->status = 'OK';
        $response->scene = $scene;
        $response->page_now = $page_now;
        $response->page_all = $page_all;
        echo json_encode($response);

    }
}
