<?php
/**
 * Scene API
 * User: Charles
 * Date: 2014/12/2
 * Time: 22:16
 */
include_once 'conf.php';
include_once 'db_conn.php';
include_once 'debug.php';
include_once 'uuid.php';

//Process client post data
if(!isset($_POST['op'])) exit('{status:\'NO_REQ_OP\'}');
switch($_POST['op']){
    case 'client_download':
        if(!isset($_POST['data'])) exit('{status:\'NO_REQ_DATA\'}');
        $data = json_decode($_POST['data']);
        SceneManager::clientDownload($data);
        break;
}

class SceneManager{
    /**
     * clientDownload
     *
     * Handle client download request for a scene.
     * Response a application/zip binary stream to the clinet
     *
     * @param $data object for scene
     */
    static public function clientDownload($data){
        //test if s_id data is set
        if(!isset($data->s_id)){
            exit('{status:\'INVALID_DATA\'}');
        }
        //create connection
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }

        //prevent inject attack
        $s_id = mysqli_real_escape_string($db, $data->s_id); //TODO: special check, such as length & charset

        $qs = "SELECT * FROM scene WHERE s_id ='".$s_id."'";
        $result = $db->query($qs);
        if($result->num_rows == 1){
            $zip = new ZipArchive();

            $db->close();
            exit();
        }else{
            $db->close();
            exit('{"status":"NO_SCENE"}');
        }
        //



    }
}

?>