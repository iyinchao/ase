<?php
/**
 * Created by PhpStorm.
 * User: 尹超
 * Date: 2014/11/28
 * Time: 19:49
 */
include_once '../debug.php';
include_once '../db_conn.php';
include_once '../uuid.php';

//array test
$con1=(object)array();
$con1->con2="ddd";
$conn=array();
$conn[0]=(object)array();
$conn[0]->test1="test1";
$conn[0]->test2="test2";
$conn[1]="sss2";
$con1->string=$conn;
echo $con1->string[0]->test1;
echo $con1->string[0]->test2;

//database test
echo '<br><h1>db connect</h1>';
try{
    $db=DBConn::connect();
}catch (Exception $e){
    die($e->getMessage());
}
//$db=DBConn::connect();
$query = "select * from scene where 1=1 limit 4 offset 4";
$result = $db->query($query);
$n=$result->num_rows;
$i=0;
$page=1;
$string=array();
$k=($page-1)*4;
while($row = $result->fetch_array()) {
    if ($i >= ($page - 1) * 4 && $i < $n&&$i<$page*4) {
        $nn = $i - $k;
        $term = (object)array();
        $term->desc = $row['desc'];
        $term->name = $row['name'];
        $string[$nn] = $term;
    }
    $i=$i+1;
}
echo count($string);
echo "<br />";
for($i=0;$i<count($string);$i++)
{
    echo $string[$i]->name."+".$string[$i]->desc;
    echo "<br />";
}
echo 'db_ok';

//json test
$response = (object)array();
$response->result='OK';
$response->string=$string;
echo json_encode($response);
$data=json_encode($response);
$data = json_decode($data);
echo "<br />";
echo $data->result;
echo "<br />";
echo $data->string[0]->name;

//---------------------------

echo '<br><h1>uuid</h1>';
echo 'default-namespace-magic-number:'.UUID::DEF_NS_M.'<br>';
echo 'default-namespace:'.UUID::DEF_NS.'<br>';
echo 'test-uuid:'.UUID::v5(UUID::DEF_NS, 'charles');

//---------------------------

?>