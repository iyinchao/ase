<?php
/**
 * Created by PhpStorm.
 * User: 尹超
 * Date: 2014/11/28
 * Time: 19:49
 */
chdir("../");
include_once 'debug.php';
include_once 'db_conn.php';
include_once 'uuid.php';
include_once 'conf.php';

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
$query="insert into tag (name) values('test888999')";
$result = $db->query($query);
$query="insert into user values('8f463b03-c638-5ba4-be10-f8307dc223e7','7110eda4d09e062aa5e4a390b0a572ac0d2c0220','test4.meijia.com','test5','2014-11-26 18:45:00')";
$result = $db->query($query);
if(!$result) echo "no insert<br/>";
$query = "select * from scene where Exists(select * from tag_scene where tag_scene.s_id=scene.s_id and tag_scene.tag=1)";
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

$s_id="1630b189-4383-4a1b-a955-cfeb228ed5bc";
$dir=Conf::DIR_DESIGN_FILE.$s_id;
fun::deldir($dir);


//---------------------------

echo '<br><h1>uuid</h1>';
echo 'default-namespace-magic-number:'.UUID::DEF_NS_M.'<br>';
echo 'default-namespace:'.UUID::DEF_NS.'<br>';
echo 'test-uuid:'.UUID::v5(UUID::DEF_NS, 'charles');
class fun{
    static public  function deldir($dir) {
        //先删除目录下的文件：
        $dh=opendir($dir);
        while ($file=readdir($dh)) {
            if($file!="." && $file!="..") {
                $fullpath=$dir."/".$file;
                if(!is_dir($fullpath)) {
                    unlink($fullpath);
                } else {
                    deldir($fullpath);
                }
            }
        }

        closedir($dh);
        //删除当前文件夹：
        if(rmdir($dir)) {
            return true;
        } else {
            return false;
        }
    }
}

//---------------------------

?>
<head>
    <script type="text/javascript">
        function loadXMLDoc()
        {
            document.getElementById("myDiv").innerHTML="change";
            var xmlhttp;
            //检查浏览器是否支持 XMLHttpRequest 对象
            if (window.XMLHttpRequest)
            {// code for IE7+, Firefox, Chrome, Opera, Safari
                xmlhttp=new XMLHttpRequest();
            }
            else
            {// code for IE6, IE5
                xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
            }
            //设置response
            xmlhttp.onreadystatechange=function() {
                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                    var resopnse=eval('(' + xmlhttp.responseText + ')');
                    document.getElementById("myDiv").innerHTML=resopnse.email;
                    var result=resopnse.result;
                    if(equals(result.match,"OK")) alert("OK");   //这边有问题，不知道是什么问题
                   // document.write(resopnse.result);
                    switch (resopnse.result){          //不知道为什么是判断错误的
                        case "OK":
                            alert("login sucesses");
                            break;
                        case "No":
                            alert("fault");
                            break;
                        default :
                            alert("else");
                    }
                    //document.getElementById("myDiv").innerHTML = xmlhttp.responseText;
                }
            };
            //GET
           // xmlhttp.open("GET",'c_user_manager.php?op=login&data={ "email":"fortest@meijia.com","pas":"1234" }',true);
            //xmlhttp.send();
            //post
            xmlhttp.open("POST","c_user_manager.php",true);
            xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
            xmlhttp.send('op=login&data={ "email":"fortest@meijia.com","pas":"1234" }');
         //   var resopnse=eval('(' + xmlhttp.responseText + ')');
           // document.getElementById("myDiv").innerHTML=resopnse.result;
            //var resopnse;
            //resopnse = json_decode(xmlhttp.responseText);

        }
    </script>
</head>
<html>
<body>

<div id="myDiv"><h3>Let AJAX change this text</h3></div>
<button type="button" onclick="loadXMLDoc()">Change Content</button>

</body>
</html>