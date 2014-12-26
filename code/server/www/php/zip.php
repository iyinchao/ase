<?php
/**
 * Zip convenient functions
 * User: 尹超
 * Date: 2014/12/3
 * Time: 13:04
 */

/**
 * Class ZipCon
 */
class ZipCon{
    /**
     *see
     * http://stackoverflow.com/questions/1334613/how-to-recursively-zip-a-directory-in-php
     *
     * @param $dir
     * @param array $exclude
     * @return string
     * @throws Exception
     */
    static public function zip_dir($dir, $exclude = array()){
        if (!extension_loaded('zip') || !file_exists($dir)) {
            throw new Exception('zip_dir:dir check fail.');
        }

        $zip = new ZipArchive();
        $temp_dir = tempnam(Conf::DIR_TMP, "scene_zip");
        if (!$zip->open($temp_dir, ZIPARCHIVE::CREATE)) {
            throw new Exception('zip_dir:create temp fail.');
        }

        $source = str_replace('\\', '/', realpath($dir));

        if (is_dir($source) === true)
        {
            $files = new RecursiveIteratorIterator(new RecursiveDirectoryIterator($source), RecursiveIteratorIterator::SELF_FIRST);

            foreach ($files as $file) {
                $file = str_replace('\\', '/', $file);

                // Ignore "." and ".." folders
                if (in_array(substr($file, strrpos($file, '/') + 1), array('.', '..')))
                    continue;

                $exclude_hit = false;
                foreach($exclude as $ex){
                    if($ex == str_replace('/', '\\', $file)){
                        $exclude_hit = true;
                        break;
                    }

                }
                if($exclude_hit){
                    continue;
                }

                if (is_dir($file) === true) {
                    $zip->addEmptyDir(str_replace($source . '/', '', $file . '/'));
                } else if (is_file($file) === true) {
                    $zip->addFromString(str_replace($source . '/', '', $file), file_get_contents($file));
                }
            }
        }
        else if (is_file($source) === true)
        {
            $zip->addFromString(basename($source), file_get_contents($source));
        }

        if(!$zip->close()){
            throw new Exception('zip_dir:create zip fail.');
        }

        return $temp_dir;
    }

    static public function unzip($file_dir, $dist){
        $zip = new ZipArchive();
        $zip->open($file_dir);
        //echo $dist;
        if($zip){
            if(@($zip->extractTo($dist))){

            }else{
                throw new Exception('Error:extract to dist');
            }
        }else{
            throw new Exception('Error:open input file');
        }
    }
}