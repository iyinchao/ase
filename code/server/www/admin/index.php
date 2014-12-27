<?php
include_once '../php/db_conn.php';
include_once '../php/debug.php';

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
        header("Location: http://localhost/admin/login.php");
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
                        <li><a href="#"><i class="fa fa-user fa-fw"></i><span>账户信息</span></a>
                        </li>
                        <li><a href="#"><i class="fa fa-gear fa-fw"></i><span>设置</span></a>
                        </li>
                        <li class="divider"></li>
                        <li><a href="login.php"><i class="fa fa-sign-out fa-fw"></i><span>退出登录</span></a>
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
                        <li class="sidebar-search">
                            <div class="input-group custom-search-form">
                                <input type="text" class="mj-search-placeholder form-control" placeholder="搜索一下...">
                                <span class="input-group-btn">
                                <button class="btn btn-default" type="button">
                                    <i class="fa fa-search"></i>
                                </button>
                            </span>
                            </div>
                            <!-- /input-group -->
                        </li>
                        <li>
                            <a class="mj-sidebar-item active" href="index.php"><i class="fa fa-dashboard fa-fw"></i><span>控制台</span></a>
                        </li>
                        <li>
                            <a class="mj-sidebar-item" href="scene.php"><i class="fa fa-th fa-fw"></i><span>场景管理</span></a>
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

</body>

</html>
