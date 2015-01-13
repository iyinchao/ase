<?php
include_once '../php/db_conn.php';
include_once '../php/debug.php';
include_once '../php/conf.php';

if(isset($_COOKIE['MEIJIA_UID'])){
    session_start();
    if(!isset($_SESSION['user_id'])){
        //create connection
        try{
            $db = DBConn::connect();
        }catch (Exception $e){
            exit('{"status":"ERROR_DB_CONN","error_message:"'.$e->getMessage().'"}');
        }

        $uid = $_COOKIE['MEIJIA_UID'];
        $query = "select * from user where u_id = '$uid'";
        $result = $db->query($query);  //执行SQL
        if ($result->num_rows == 1) {
            $row = $result->fetch_assoc();
            $_SESSION['user_id'] = $row['u_id'];
        }
        $db->close();
    }
}else{
    session_start();
    if(!isset($_SESSION['user_id'])){
        header("Location: ".Conf::SERVER_ADMIN_DOMAIN."login.php");
        die();
    }
}
?>
<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>美家秀秀·后台管理系统</title>

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- MetisMenu CSS -->
    <link href="css/plugins/metisMenu/metisMenu.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/sb-admin-2.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="css/font-awesome.css" rel="stylesheet" type="text/css">

    <!-- Meijia Customize css-->
    <link href="css/meijia-core.css" rel="stylesheet">
    <link href="css/meijia-index.css" rel="stylesheet">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body>

    <div id="wrapper">

        <!-- Navigation -->
        <nav class="mj-titlebar navbar navbar-default navbar-static-top" role="navigation" style="margin-bottom: 0">
            <div class=" navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a id="mj-main-title" class="navbar-brand" href="index.php">美家秀秀·后台管理系统</a>
            </div>
            <!-- /.navbar-header -->

            <ul class="nav navbar-top-links navbar-right">
                <li class="dropdown">
                    <a id="mj-dropdown-toggle" class="dropdown-toggle" data-toggle="dropdown" href="#">
                        <i class="fa fa-user fa-fw"></i>  <i class="fa fa-caret-down"></i>
                    </a>
                    <ul class="mj-sidebar-item dropdown-menu dropdown-user">
                        <!--<li><a href="#"><i class="fa fa-user fa-fw"></i><span>账户信息</span></a>
                        </li>
                        <li><a href="#"><i class="fa fa-gear fa-fw"></i><span>设置</span></a>
                        </li>
                        <li class="divider"></li>-->
                        <li><a id="logout" href="#"><i class="fa fa-sign-out fa-fw"></i><span>退出登录</span></a>
                        </li>
                    </ul>
                    <!-- /.dropdown-user -->
                </li>
                <!-- /.dropdown -->
            </ul>
            <!-- /.navbar-top-links -->

            <div class="navbar-default sidebar" role="navigation">
                <div class="sidebar-nav navbar-collapse">
                    <ul class="nav" id="side-menu">
                        <!--<li class="sidebar-search">
                            <div class="input-group custom-search-form">
                                <input type="text" class="mj-search-placeholder form-control" placeholder="搜索一下...">
                                <span class="input-group-btn">
                                <button class="btn btn-default" type="button">
                                    <i class="fa fa-search"></i>
                                </button>
                            </span>
                            </div>

                        </li>-->
                        <li>
                            <a class="mj-sidebar-item active" href="index.php"><i class="fa fa-dashboard fa-fw"></i><span>控制台</span></a>
                        </li>
                        <li>
                            <a class="mj-sidebar-item" href="scene.php"><i class="fa fa-th fa-fw"></i><span>场景管理</span></a>
                        </li>
                        <li>
                            <a class="mj-sidebar-item" href="c-tag.php"><i class="fa fa-tags"></i><span>标签管理</span></a>
                        </li>
                    </ul>
                </div>
                <!-- /.sidebar-collapse -->
            </div>
            <!-- /.navbar-static-side -->
        </nav>

        <div id="page-wrapper">
            <div class="row">
                <div class="col-lg-12">
                    <h1 class="mj-page-title page-header">控制台</h1>
                </div>
                <!-- /.col-lg-12 -->
            </div>
            <!-- /.row -->
            <div class="row">
                <div class="col-lg-8">
                    <div class="panel panel-default">
                        <div class="panel-heading">
                            全局API状态
                        </div>
                        <div class="panel-body">
                            <div style="margin-bottom: 10px;text-align: center;">
                            <button type="button" class="btn btn-primary" id="bt-test-all">
                                <i class="fa fa-cog fa-spin"></i>
                                开始测试
                            </button>
                            </div>
                            <!--<label for="scene-api-lg">场景API</label>-->
                            <div class="list-group" id="scene-api-lg">
                                <!--<div  class="list-group-item">
                                    <i class="fa fa-circle-o-notch fa-spin"></i>
                                    <i class="fa fa-question"></i>
                                    <i class="fa fa-question-circle"></i>
                                    <i class="fa fa-check-circle"></i>
                                    <i class="fa fa-times-circle"></i>
                                    <i class="fa fa-dot-circle-o"></i>
                                    [add]
                                    <span class="pull-right text-muted small"><em>测试中...</em>
                                    </span>
                                </div>
                                <div  class="list-group-item">
                                    <i class="fa fa-circle-o-notch fa-spin"></i>
                                    <i class="fa fa-question"></i>
                                    <i class="fa fa-question-circle"></i>
                                    <i class="fa fa-check-circle"></i>
                                    <i class="fa fa-times-circle"></i>
                                    <i class="fa fa-dot-circle-o"></i>
                                    [add]
                                    <span class="pull-right text-muted small"><em>测试中...</em>
                                    </span>
                                </div>
                                <div class="list-group-item">
                                    <i class="fa fa-circle-o-notch fa-spin"></i>
                                    client_download
                                    <span class="pull-right text-muted small"><em>测试中...</em>
                                    </span>
                                </div>-->
                            </div>
                        </div>
                    </div>
                </div>
                <div class="col-lg-4">
                    <div class="panel panel-default">
                        <div class="panel-heading">
                            <h3 class="panel-title">系统状态</h3>
                        </div>
                        <div class="panel-body" id="index-info-panel">
                            <?php
                            //将获取当前时间的代码放在一个函数里
                            function runtime(){
                                $times = explode(" ",microtime());
                                $nowtime = $times[1]+$times[0];
                                return $nowtime;
                            }

                            //假设这里是页面开头
                            $start_time = runtime();

                            //这里开始是的页面代码
                            //your code goes here

                            //假设这里是页面顶部
                            $end_time = runtime();
                            $cost_time = $end_time - $start_time;

                            //处理输出执行时间
                            $cost_time = round($cost_time,4);

                            //输出页面的执行时间
                            echo "页面执行时间为：".$cost_time."秒"."<br>";
                            ?>
                            <?php
                            echo "<span class=\"index-info\">脚本文件的相对路径和文件名:\"".$_SERVER["PHP_SELF"]."</span><br>";
                            echo "<span class=\"index-info\">服务器使用的CGI脚本规范:\"".$_SERVER["GATEWAY_INTERFACE"]."</span><br>";
                            echo "<span class=\"index-info\">当前运行脚本所在服务器的IP地址:\"".$_SERVER["SERVER_ADDR"]."</span><br>";
                            echo "<span class=\"index-info\">当前运行脚本服务器名称:\"".$_SERVER["SERVER_NAME"]."</span><br>";
                            echo "<span class=\"index-info\">当前运行脚本服务器标识:\"".$_SERVER["SERVER_SOFTWARE"]."</span><br>";
                            echo "<span class=\"index-info\">请求页面的通信协议的名称和版本:\"".$_SERVER["SERVER_PROTOCOL"]."</span><br>";
                            echo "<span class=\"index-info\">访问页面的请求方法:\"".$_SERVER["REQUEST_METHOD"]."</span><br>";
                            echo "<span class=\"index-info\">脚本开始运行时间:\"".$_SERVER["REQUEST_TIME"]."</span><br>";
                            echo "<span class=\"index-info\">URL问号后的字符串:\"".$_SERVER["QUERY_STRING"]."</span><br>";
                            echo "<span class=\"index-info\">当前运行脚本的文档根目录:\"".$_SERVER["DOCUMENT_ROOT"]."</span><br>";
                            echo "<span class=\"index-info\">当前Accept请求的头信息:\"".$_SERVER["HTTP_ACCEPT"]."</span><br>";
                            echo "<span class=\"index-info\">当前当前请求的Accept-Encoding头信息:\"".$_SERVER["HTTP_ACCEPT_ENCODING"]."</span><br>";
                            echo "<span class=\"index-info\">当前请求的Accept-Language头信息:\"".$_SERVER["HTTP_ACCEPT_LANGUAGE"]."</span><br>";
                            echo "<span class=\"index-info\">当前请求的Connection头信息:\"".$_SERVER["HTTP_CONNECTION"]."</span><br>";
                            echo "<span class=\"index-info\">当前请求的Host头信息:\"".$_SERVER["HTTP_HOST"]."</span><br>";
                            echo "<span class=\"index-info\">当前请求的User-Agent的头信息:\"".$_SERVER["HTTP_USER_AGENT"]."</span><br>";
                            echo "<span class=\"index-info\">浏览当前页面用户的IP地址:\"".$_SERVER["REMOTE_ADDR"]."</span><br>";
                            echo "<span class=\"index-info\">用户连接到服务器时所使用的端口:\"".$_SERVER["REMOTE_PORT"]."</span><br>";
                            echo "<span class=\"index-info\">当前执行脚本的绝对路径名:\"".$_SERVER["SCRIPT_FILENAME"]."</span><br>";
                            echo "<span class=\"index-info\">Apache配置文件中的SERVER_ADMIN参数设置情况:\"".$_SERVER["SERVER_ADMIN"]."</span><br>";
                            echo "<span class=\"index-info\">网络服务器使用的端口,默认为\"80\":\"".$_SERVER["SERVER_PORT"]."</span><br>";
                            echo "<span class=\"index-info\">服务器版本和虚拟主机名的字符串:\"".$_SERVER["SERVER_SIGNATURE"]."</span><br>";
                            echo "<span class=\"index-info\">当前脚本的路径:\"".$_SERVER["SCRIPT_NAME"]."</span><br>";
                            echo "<span class=\"index-info\">访问当前页面的URI:\"".$_SERVER["REQUEST_URI"]."</span><br>";
                            ?>
                        </div>
                    </div>
                </div>
            </div>
            <!-- /.row -->

            <!-- /.row -->
        </div>
        <!-- /#page-wrapper -->

    </div>
    <!-- /#wrapper -->

    <!-- jQuery -->
    <script src="js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="js/bootstrap.min.js"></script>

    <!-- Metis Menu Plugin JavaScript -->
    <script src="js/plugins/metisMenu/metisMenu.min.js"></script>

    <!-- Custom Theme JavaScript -->
    <script src="js/sb-admin-2.js"></script>

    <!-- Meijia index js-->
    <script src="js/config.js"></script>
    <script src="js/index.js"></script>

</body>

</html>
