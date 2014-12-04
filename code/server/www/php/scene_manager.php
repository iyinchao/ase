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
        //
        if(isset($data->search)){

        }
        if(isset($data->sort_by)){

        }

        if(isset($data->tag)){
            $tags = (array)$data->tag;
            //echo sizeof($tags);
            if(sizeof($tags) != 0){

                for($i = 0; $i < sizeof($tags); $i++){
                    $tags[$i] = mysqli_real_escape_string($db,$tags[$i]);
                }
                $_qs_tags = join(',',$tags);
            }
        }
        $page_now = mysqli_real_escape_string($db, $data->page_now);

        if(isset($_qs_tags)){
            $qs_tags = "SELECT s_id FROM bhouse.tag_scene WHERE tag IN ($_qs_tags)";
            $result = $db->query($qs_tags);
            if($row =$result->fetch_assoc()){
                echo $row['s_id'];
            }
        }

        $qs_count = "SELECT COUNT(s_id) FROM bhouse.scene";
        $qs_content = "";

        echo 'ok';

    }
}
