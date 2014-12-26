<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">
    <?php
        include_once '../php/uuid.php';
        if(isset($_POST["id"])){
            $id = $_POST["id"];
        }else{
            $id = UUID::gen_s_id();
        }
        $mode = $_POST["mode"];
        echo "<meta name=\"id\" content=\"$id\">";
        echo "<meta name=\"mode\" content=\"$mode\">"
    ?>

    <title>美家秀秀·场景编辑</title>

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/sb-admin-2.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="css/font-awesome.css" rel="stylesheet" type="text/css">

    <!-- Meijia Customize css-->
    <link href="css/meijia-core.css" rel="stylesheet">
    <link href="css/meijia-scene.css" rel="stylesheet">
    <link href="css/meijia-scene-detail.css" rel="stylesheet">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
    <!--<script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
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
            <a id="mj-main-title" class="navbar-brand" href="index.php">美家秀秀·场景编辑</a>
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
                        <a class="mj-sidebar-item" href="index.php"><i class="fa fa-dashboard fa-fw"></i><span>控制台</span></a>
                    </li>
                    <li>
                        <a class="mj-sidebar-item active" href="scene.php"><i class="fa fa-th fa-fw"></i><span>场景管理</span></a>
                    </li>

                </ul>
            </div>
            <!-- /.sidebar-collapse -->
        </div>
        <!-- /.navbar-static-side -->
    </nav>

    <div id="page-wrapper">
        <div id="page-mask"></div>
        <div class="row">
            <div class="col-lg-12">
                <h1 id="page-title" class="mj-page-title page-header">场景详情</h1>
            </div>
            <!-- /.col-lg-12 -->
        </div>
        <div class="row" id="row-message">
            <?php
            if(isset($_POST['message'])){
                if($_POST['message'] == 'add-success'){
                    echo '<div class="alert alert-success tobefade" role="alert"><i class="fa fa-check"></i>成功增加场景</div>';
                }
            }
            ?>
        </div>
        <div class="row">
            <div class="col-md-6 left-panel">
                <div id="thumb-wrap" class="form-group">
                    <div id="thumb">
                        <div id="spin-thumb"></div>
                        <?php
                        if(isset($_POST['mode'])) {
                            if ($_POST['mode'] == 'new') {
                                echo '<input type="file" id="scene-upload" style="display: none">
                                    <div class="form-group">
                                        <div style="text-align: left"><label for="form-upload-filename" class="control-label">选择场景文件(.zip)</label></div>
                                        <div class="input-group">
                                            <span class="input-group-btn">
                                                <button id="form-upload-bt" class="btn btn-default" type="button"><i class="fa fa-folder-open"></i></button>
                                            </span>
                                            <input type="text" class="form-control" readonly id="form-upload-filename" placeholder="请选择文件">

                                        </div>
                                    </div>
                                    <div class="well" id="upload-info" style="display: none;text-align: left">
                                    <b>文件信息:</b>
                                    </div>
                                    <div id="progress" class="progress" style="margin-top: 10px;display: none">
                                      <div id="progress-bar" class="progress-bar progress-bar-info" role="progressbar" aria-valuenow="0" aria-valuemin="0" aria-valuemax="100" style="width: 0;">
                                      </div>
                                    </div>';
                            }
                        }
                        ?>
                    </div>
                    <button id="scene-dn-up" type="button" class="btn btn-primary">Text</button>
                </div>
            </div>
            <div class="col-md-6 right-panel">
                <div class="form-group">
                    <label for="form-scene-id">ID</label>
                    <?php
                    if(isset($_POST['mode'])){
                        if($_POST['mode'] == 'new') {
                            echo '<div class="input-group">
                                    <span class="input-group-btn">
                                        <button id="form-id-refresh" class="btn btn-default" type="button"><i class="fa fa-refresh"></i></button>
                                    </span>
                                    <input type="text" class="form-control" disabled id="form-scene-id" placeholder="场景 ID">

                                    </div>';
                        }else if($_POST['mode'] == 'modify'){
                            echo '<input type="text" class="form-control" disabled id="form-scene-id" placeholder="场景 ID">';
                        }
                    }
                    ?>

                </div>
                <div class="form-group">
                    <label class="control-label" for="form-scene-name">显示名称(在客户端中作为标题显示)</label>
                    <input type="text" class="form-control no-empty" id="form-scene-name" placeholder="场景名称">
                </div>
                <div class="form-group">
                    <label class="control-label" for="form-scene-designer">设计师(主要设计人员)</label>
                    <input type="text" class="form-control no-empty" id="form-scene-designer" placeholder="设计师" aria-describedby="designer-error">
                </div>
                <div class="form-group">
                    <label for="form-vc">视角数目</label>
                    <div class="input-group spinner">
                        <input type="text" readonly class="form-control" value="1" id="form-vc">
                        <div class="input-group-btn-vertical">
                            <button class="btn btn-default"><i class="fa fa-caret-up"></i></button>
                            <button class="btn btn-default"><i class="fa fa-caret-down"></i></button>
                        </div>
                    </div>
                </div>
                <div class="form-group">
                    <label class="control-label" for="form-desc">场景描述</label>
                    <textarea id="form-desc" class="form-control" rows="4" style="max-width: 450px"></textarea>
                </div>
                <button id="scene-submit" type="button" class="btn btn-primary">Text</button>
                <button  id="scene-delete" type="button" class="btn btn-danger">删除场景</button>
            </div>
            <!-- /.col-lg-12 -->
        </div>
        <!-- /.row -->
        <!--<div class="row" id="scene-table">

        </div>-->

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

<!-- Spin JS Plugin JavaScript -->
<script src="js/plugins/spin.js/spin.min.js"></script>


<!-- Custom Theme JavaScript -->
<script src="js/sb-admin-2.js"></script>


<!-- Meijia JS-->
<script src="js/config.js"></script>

<script src="js/scene_detail.js"></script>

</body>

</html>
