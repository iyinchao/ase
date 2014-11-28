<?php
/**
 * Created by PhpStorm.
 * User: 尹超
 * Date: 2014/11/28
 * Time: 19:49
 */
include_once 'debug.php';
include_once 'db_conn.php';
include_once 'uuid.php';


echo '<br><h1>db connect</h1>';
try{
    DBConn::connect();
}catch (Exception $e){
    die($e->getMessage());
}

echo 'db_ok';

//---------------------------

echo '<br><h1>uuid</h1>';
echo 'default-namespace-magic-number:'.UUID::DEF_NS_M.'<br>';
echo 'default-namespace:'.UUID::DEF_NS.'<br>';
echo 'test-uuid:'.UUID::v5(UUID::DEF_NS, 'charles');

//---------------------------

?>