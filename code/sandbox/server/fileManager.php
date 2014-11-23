<?php
header("Content-Type: text/html;charset=utf-8");
include 'debug.php';
include 'DBConn.php';
include 'UUID.php';

switch ($_GET['op']) {
    case 'testAccess':
        $data = json_decode($_GET['data']);
        FileManager::testAccess($data);
        break;
    case 'getSize':
        $data = json_decode($_GET['data']);
        FileManager::getSize($data);
        break;
    case 'getFileList':
        $data = json_decode($_GET['data']);
        FileManager::getFileList($data);
        break;
    case 'testSave':
        $data = json_decode($_GET['data']);
        FileManager::testSave($data);
        break;
    case 'save':
        FileManager::save();
        break;
    case 'deleteFile':
        $data = json_decode($_GET['data']);
        FileManager::deleteFile($data);
        break;
    case 'share':
        $data = json_decode($_GET['data']);
        FileManager::share($data);
        break;
    case 'nshare':
        $data = json_decode($_GET['data']);
        FileManager::nshare($data);
        break;
}

class FileManager{

    const defaultFid = '804b2099-6928-5c48-b88a-51db654ca3f9';

    static public function testAccess($data){

        $db = DBConn::connect();

        if (mysqli_connect_errno()) {
            //echo "Failed to connect to MySQL: " . mysqli_connect_error();
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
            die('Failed to connet the database');
        }

        $user = mysqli_real_escape_string($db, $data->{'user'});
        $file = mysqli_real_escape_string($db, $data->{'file'});


        $query = "select * from file where id='".$file."'";
        $result = $db->query($query);

        $response = (object)array();

        if($result->num_rows == 1){
            $row = $result->fetch_assoc();
            if($row['public'] == 1 || $row['owner'] == $user){
                $response->result = 'ok';
                if($row['public'] == 1){
                    $response->public = true;
                }else{
                    $response->public = false;
                }
                if($row['owner'] == $user){
                    $response->own = true;
                }else{
                    $response->own = false;
                }

                if($row['id'] == self::defaultFid){
                    $response->default = true;
                }else{
                    $response->default = false;
                }

                $response->owner = $row['owner'];
                $response->name = $row['name'];
                $response->fid = $file;

                $query = "select * from user where id='".$row['owner']."'";
                $result = $db->query($query);

                if($result->num_rows == 1){
                    $row = $result->fetch_assoc();
                    $response->owner_info = (object)array();
                    $response->owner_info->name = $row['display_name'];
                }

            }else{
                $response->result = 'no';
            }
        }else{
            $response->result = 'error_fid';
        }

        $db->close();

        echo json_encode($response);
    }

    static public function getSize($data){
        $user = $data->{'user'};
        $file = $data->{'file'};

        $totalSize = 0;
        $response = (object)array();

        if(file_exists('../user/'.$user.'/'.$file.'/def.json')){
            $response->def_size = filesize('../user/'.$user.'/'.$file.'/def.json');
            $response->def_loc = 'user/'.$user.'/'.$file.'/def.json';
            $totalSize += filesize('../user/'.$user.'/'.$file.'/def.json');
        }else{
            $response->result = 'no';
            echo json_encode($response);
            return;
        }

        if(file_exists('../user/'.$user.'/'.$file.'/pano/0.jpg')){
            $response->pano_size = filesize('../user/'.$user.'/'.$file.'/pano/0.jpg');
            $response->pano_loc = 'user/'.$user.'/'.$file.'/pano/0.jpg';
            $totalSize += filesize('../user/'.$user.'/'.$file.'/pano/0.jpg');
        }

        $response->result = 'ok';
        $response->total_size = $totalSize;
        echo json_encode($response);
        return;
    }

    static public function getFileList($data){
        $db = DBConn::connect();

        if (mysqli_connect_errno()) {
            //echo "Failed to connect to MySQL: " . mysqli_connect_error();
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
            die('Failed to connet the database');
        }

        $user = mysqli_real_escape_string($db, $data->{'user'});
        //$file = mysqli_real_escape_string($db, $data->{'file'});

        $query = "select * from file where owner='".$user."' order by modify_time desc";
        $result = $db->query($query);

        $num_result = $result->num_rows;

        $response = (object)array();
        $response->file_num = $num_result;

        if($num_result != 0){
            $response->list = array();
            for($i = 0; $i < $num_result; $i++){
                $row = $result->fetch_assoc();
                $response->list[$i] = (object)array();
                $response->list[$i]->fid = $row['id'];
                $response->list[$i]->name = $row['name'];
                $response->list[$i]->owner = $row['owner'];
                $response->list[$i]->pub = $row['public'];
                $response->list[$i]->time = $row['modify_time'];
                if(file_exists('../user/'.$row['owner'].'/'.$row['id'].'/thumb.jpg')){
                    $response->list[$i]->thumb_loc = 'user/'.$row['owner'].'/'.$row['id'].'/thumb.jpg';
                }
                $def = json_decode(file_get_contents('../user/'.$row['owner'].'/'.$row['id'].'/def.json'));
                $response->list[$i]->name = $def->name;
                $response->list[$i]->title = $def->info->title;
            }
        }
        echo json_encode($response);

        $db->close();
    }

    static public function testSave($data){
        $db = DBConn::connect();

        if (mysqli_connect_errno()) {
            //echo "Failed to connect to MySQL: " . mysqli_connect_error();
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
            die('Failed to connet the database');
        }

        $owner = mysqli_real_escape_string($db, $data->{'owner'});
        $name = mysqli_real_escape_string($db, $data->{'name'});

        $query = "select * from file where owner='".$owner."' and id='".UUID::v5($owner, $name)."'";

        $result = $db->query($query);

        $response = (object)array();

        if($result->num_rows == 0){
            $response->result = 'ok';
        }else{
            $response->result = 'no';
        }

        echo json_encode($response);

        $db->close();
    }

    static public function save(){
        $def = JSON_decode($_POST['def']);

        $db = DBConn::connect();

        if (mysqli_connect_errno()) {
            //echo "Failed to connect to MySQL: " . mysqli_connect_error();
            $response = (object)array();
            $response->result = 'no';
            echo json_encode($response);
            die('Failed to connet the database');
        }

        $owner = mysqli_real_escape_string($db, $_POST['owner']);
        $name = mysqli_real_escape_string($db, $def->name);
        $fid = UUID::v5($owner, $name);
        $dir = '../user/'.$owner;

        $query = "select * from file where owner='".$owner."' and id='".$fid."'";

        $result = $db->query($query);

        $response = (object)array();

        if($result->num_rows == 0){
            //new file
           $query = "insert into file values ('".$fid."','".$name."','".$owner."','0','".gmdate('Y-m-d H:i:s')."')";
           $insert_result = $db->query($query);
           if($insert_result){
               if(!file_exists($dir)){
                   @ mkdir($dir);
               }
               $fdir = $dir.'/'.$fid;
                @ mkdir($fdir);
                @ mkdir($fdir.'/pano');
                @ mkdir($fdir.'/pano');
                if(isset($_POST['pano'])){
                    $img = base64_decode(str_replace('data:image/jpeg;base64,', '', $_POST['pano']));
                    file_put_contents($fdir.'/pano/0.jpg', $img);
                    $img = base64_decode(str_replace('data:image/jpeg;base64,', '', $_POST['thumb']));
                    file_put_contents($fdir.'/thumb.jpg', $img);
                }
                file_put_contents($fdir.'/def.json', json_encode($def));
            }

           // echo 'new';
        }else if($result->num_rows == 1){
           //overwrite file
           // echo 'overwrite';
            $fdir = $dir.'/'.$fid;
            if(isset($_POST['pano'])){
                $img = base64_decode(str_replace('data:image/jpeg;base64,', '', $_POST['pano']));
                file_put_contents($fdir.'/pano/0.jpg', $img);
                $img = base64_decode(str_replace('data:image/jpeg;base64,', '', $_POST['thumb']));
                file_put_contents($fdir.'/thumb.jpg', $img);
            }
            file_put_contents($fdir.'/def.json', json_encode($def));

            $query = "update file set modify_time='".gmdate('Y-m-d H:i:s')."' where id='".$fid."'";
            $db->query($query);

        }else{
            $response->result = 'no';
            echo json_encode($response);
            return;
        }

        $response->result = 'ok';
        $response->fid = $fid;
        echo json_encode($response);

        $db->close();
    }

    static public function share($data){
        $fid = $data->{'fid'};
        $db = DBConn::connect();
        $query = "update file set public='1' where id='".$fid."'";
        $db->query($query);
        $db->close();
        echo '{"result":"ok","link":"http://'.$_SERVER['SERVER_NAME'].'/?'.$fid.'"}';
    }

    static public function nshare($data){
        $fid = $data->{'fid'};
        $db = DBConn::connect();
        $query = "update file set public='0' where id='".$fid."'";
        $db->query($query);
        $db->close();
        echo '{"result":"ok"}';
    }

    static public function deleteFile($data){
        session_start();
        $response = (object)array();
        if(isset($_SESSION['user_id']) && $data->{'owner'} == $_SESSION['user_id']){
            $db = DBConn::connect();

            if (mysqli_connect_errno()) {
                //echo "Failed to connect to MySQL: " . mysqli_connect_error();
                $response = (object)array();
                $response->result = 'no';
                echo json_encode($response);
                die('Failed to connet the database');
            }

            $fid = mysqli_real_escape_string($db, $data->{'fid'});

            $query = "DELETE FROM file WHERE id='".$fid."'";

            $db->query($query);

            if($db->affected_rows == 1){
                self::deleteDir('../user/'.$data->{'owner'}.'/'.$fid);
                $response->result = 'ok';
                echo json_encode($response);
                return;
            }
            $db->close();
        }
        $response->result = 'no';
        echo json_encode($response);

    }

    public static function deleteDir($dirPath) {
        if (! is_dir($dirPath)) {
            throw new InvalidArgumentException("$dirPath must be a directory");
        }
        if (substr($dirPath, strlen($dirPath) - 1, 1) != '/') {
            $dirPath .= '/';
        }
        $files = glob($dirPath . '*', GLOB_MARK);
        foreach ($files as $file) {
            if (is_dir($file)) {
                self::deleteDir($file);
            } else {
                unlink($file);
            }
        }
        rmdir($dirPath);
    }
    
}

?>