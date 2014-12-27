<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>美家秀秀·请登录</title>

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- MetisMenu CSS -->
    <link href="css/plugins/metisMenu/metisMenu.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/sb-admin-2.css" rel="stylesheet">

    <!-- Meijia Customize css-->
    <link href="css/meijia-core.css" rel="stylesheet">
    <link href="css/meijia-login.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="css/font-awesome.css" rel="stylesheet" type="text/css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body>

    <div class="container" >
        <div class="row">
            <div class="col-md-4 col-md-offset-4">
                <div style="display: none;" id="panel" class="login-panel panel panel-default">
                    <div class="panel-heading">
                        <h3 class="panel-title">美家秀秀·管理系统</h3>
                    </div>
                    <div class="panel-body">
                        <?php
                        if(isset($_POST['message'])){
                            if($_POST['message'] == 'logout'){
                                echo '<div class="alert alert-info tobefade" role="alert" style="text-align: center"><i class="fa fa-lock"></i>&nbsp;&nbsp;您已登出</div>';
                            }
                        }
                        ?>
                        <form role="form">
                            <fieldset>
                                <div class="form-group">
                                    <input id="form-email" class="form-control" placeholder="E-mail" name="email" type="email" autofocus>
                                </div>
                                <div class="form-group">
                                    <input id="form-password" class="form-control" placeholder="密码" name="password" type="password" value="">
                                </div>
                                <div class="checkbox">
                                    <label>
                                        <input id="form-rem" name="remember" type="checkbox" value="Remember Me">一周内免登录
                                    </label>
                                </div>
                                <!-- Change this to a button or input when using this as a form -->
                                <a id="form-submit" class="btn btn-lg btn-primary btn-block">登&nbsp;录</a>
                            </fieldset>
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <!-- jQuery -->
    <script src="js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="js/bootstrap.min.js"></script>

    <!-- Metis Menu Plugin JavaScript -->
    <script src="js/plugins/metisMenu/metisMenu.min.js"></script>

    <!-- Custom Theme JavaScript -->
    <script src="js/sb-admin-2.js"></script>

    <!-- Meijia JS-->
    <script src="js/config.js"></script>

    <script src="js/login.js"></script>

</body>

</html>
