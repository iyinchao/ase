(function(){
    $(document).ready(function(){
        setTimeout(function(){
            $('.tobefade').fadeOut(1000);
        }, 3000);

        var id = ($("meta[name='id']")[0]).getAttribute('content');
        var mode = ($("meta[name='mode']")[0]).getAttribute('content');
        var file_upload = null;

        var tag_selected = {};
        var form = new FormData();
        form.append('op', 'get_all_tags');
        var xhr_tag = new XMLHttpRequest();
        xhr_tag.open('post', '../php/tag_api.php', true);
        xhr_tag.addEventListener('readystatechange', function() {
            if (this.readyState == 4) {
                if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                    var json = JSON.parse(this.responseText);
                    if (json['tags']) {
                        $('#tag-panel').empty();
                        (json['tags']).forEach(function (tag, i, array) {
                            var dom = document.createElement('button');
                            dom.className = 'btn btn-default btn-tag';
                            dom.setAttribute('meta-id', tag['id']);
                            dom.setAttribute('meta-desc', tag['desc']);
                            if (tag['desc'] && tag['desc'] != '') {
                                //data-toggle="tooltip" data-placement="bottom" title="Tooltip on bottom"
                                dom.setAttribute('data-toggle', 'tooltip');
                                dom.setAttribute('data-placement', 'bottom');
                                dom.setAttribute('title', tag['desc']);
                            }
                            dom.innerHTML = '<i class="fa fa-tag"></i>&nbsp;' + tag['name'];
                            $('#tag-panel').append(dom);
                            dom.addEventListener('click', function (e) {
                                if (dom.classList.contains('active')) {
                                    dom.classList.remove('active');
                                    dom.classList.remove('btn-warning');
                                    tag_selected[tag['id']] = false;
                                } else {
                                    dom.classList.add('active');
                                    dom.classList.add('btn-warning');
                                    tag_selected[tag['id']] = true;
                                }
                                var tags = [];
                                for (var i in tag_selected) {
                                    if (tag_selected.hasOwnProperty(i)) {
                                        if (tag_selected[i])tags.push(parseInt(i));
                                    }
                                }
                            });
                        });
                    }
                    $('[data-toggle="tooltip"]').tooltip()
                }
            }
        });
        xhr_tag.send(form);

        /**
         * You first need to create a formatting function to pad numbers to two digits…
         **/
        function twoDigits(d) {
            if(0 <= d && d < 10) return "0" + d.toString();
            if(-10 < d && d < 0) return "-0" + (-1*d).toString();
            return d.toString();
        }

        /**
         * …and then create the method to output the date string as desired.
         * Some people hate using prototypes this way, but if you are going
         * to apply this to more than one Date object, having it as a prototype
         * makes sense.
         **/
        Date.prototype.toMysqlFormat = function() {
            return this.getFullYear() + "-" + twoDigits(1 + this.getMonth()) + "-" + twoDigits(this.getDate()) + " " + twoDigits(this.getHours()) + ":" + twoDigits(this.getMinutes()) + ":" + twoDigits(this.getSeconds());
        };

        $('#form-scene-id')[0].value = id;

        $('.spinner .btn:first-of-type').on('click', function() {
            var spinner = $('.spinner input');
            spinner.val( parseInt(spinner.val(), 10) + 1);
        });
        $('.spinner .btn:last-of-type').on('click', function() {
            var spinner = $('.spinner input');
            var value = parseInt(spinner.val(), 10);
            if(value > 1) {
                spinner.val(parseInt(spinner.val(), 10) - 1);
            }
        });

        $('input.no-empty').on('input', function () {
            //console.log(this);
            if(this.value.trim() == ''){
                this.parentNode.classList.add('has-error');
            }else{
                this.parentNode.classList.remove('has-error');
            }
        });

        //console.log($('#form-scene-id'));

        if(mode == 'modify'){
      /*      var spin_opts = {
                lines: 13, // The number of lines to draw
                length: 20, // The length of each line
                width: 10, // The line thickness
                radius: 30, // The radius of the inner circle
                corners: 1, // Corner roundness (0..1)
                rotate: 0, // The rotation offset
                direction: 1, // 1: clockwise, -1: counterclockwise
                color: '#000', // #rgb or #rrggbb or array of colors
                speed: 1, // Rounds per second
                trail: 60, // Afterglow percentage
                shadow: false, // Whether to render a shadow
                hwaccel: false, // Whether to use hardware acceleration
                className: 'spinner', // The CSS class to assign to the spinner
                zIndex: 2e9, // The z-index (defaults to 2000000000)
                top: '50%', // Top position relative to parent
                left: '50%' // Left position relative to parent
            };*/


            form = new FormData();
            form.append('op', 'client_get_thumb');
            form.append('data', JSON.stringify(
                {
                    s_id:id
                }
            ));
            xhr = new XMLHttpRequest();
            xhr.open('post', '../php/scene_api.php', true);
            xhr.responseType = 'blob';
            xhr.addEventListener('readystatechange', function(){
                if (this.readyState == 4) {
                    if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                        //var resp = JSON.parse(this.responseText);
                        //refresh_scene_view(resp);
                        //refresh_scene_table(resp);
                        if(this.getResponseHeader('content-type') == 'image/jpeg'){
                            /*var arr = new Uint8Array(this.response);
                            var raw = String.fromCharCode.apply(null,arr);
                            var b64=btoa(raw);
                            var dataURL="data:image/jpeg;base64,"+b64;
                            console.log(b64);*/
                            var blob = new Blob([this.response], {type: 'image/jpeg'});
                            //console.log(window.URL.createObjectURL(blob));
                            var img = document.createElement('img');
                            img.src = window.URL.createObjectURL(blob);
                            //img.style.opacity = 0;
                            img.style.display = 'none';
                            img.id = 'thumb-img';
                            img.onload = function () {
                                window.URL.revokeObjectURL(img.src);
                                $("#thumb-img").fadeIn(500);
                            };
                            $('#thumb')[0].appendChild(img);
                            //$('#thumb')[0].style.backgroundImage = "url('"+window.URL.createObjectURL(blob)+"')"//"#000";//"url('data:image/jpeg;base64,"+1+'")";
                        }
                        //console.log(this.getResponseHeader('content-type'));
                    }
                }
            });
            xhr.send(form);

            //
            form = new FormData();
            form.append('op', 'get_meta_by_id');
            form.append('data', JSON.stringify(
                {
                    s_id:id
                }
            ));
            var xhr_form = new XMLHttpRequest();
            xhr_form.open('post', '../php/scene_api.php', true);
            xhr_form.addEventListener('readystatechange', function() {
                if (this.readyState == 4) {
                    if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                        //console.log(this.responseText);
                        var json = JSON.parse(this.responseText);
                        $('#form-scene-name')[0].value = json.name;
                        $('#form-scene-designer')[0].value = json.designer;
                        $('#form-desc')[0].value = json.desc;
                        $('#form-vc')[0].value = json.views_count;
                    }
                }
            });
            xhr_form.send(form);
            //console.log($('input.no-empty'));

            //$('#form-scene-id')[0].value = id;
            var submit_bt = $('#scene-submit');
            submit_bt.empty();
            submit_bt[0].innerHTML = '修改场景元数据';
            submit_bt.on('click', function () {
                var error_item = $('.has-error');
                if(error_item.length != 0){
                    error_item[0].childNodes[1].focus();
                    //console.log(error_item[0]);
                }else{
                    var form = new FormData();
                    form.append('op', 'update_one');
                    var json = JSON.stringify(
                        {
                            s_id:id,
                            name:$('#form-scene-name')[0].value.trim(),
                            designer:$('#form-scene-designer')[0].value.trim(),
                            desc:$('#form-desc')[0].value,
                            views_count:$('#form-vc')[0].value,
                            modify_date:new Date().toMysqlFormat()
                        }
                    );
                    form.append('data', json);
                    var xhr = new XMLHttpRequest();
                    xhr.open('post', '../php/scene_api.php', true);
                    xhr.addEventListener('readystatechange', function() {
                        if (this.readyState == 4) {
                            if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                                if((JSON.parse(this.responseText)).status == 'OK'){
                                    var url = './scene.php';
                                    var form = $('<form action="' + url + '" method="post">' +
                                    '<input type="text" name="mode" value="modify-success" />' +
                                        //'<input type="text" name="mode" value="modify" />' +
                                    '</form>');
                                    $('body').append(form);
                                    form.submit();
                                }
                            }
                        }
                    });
                    xhr.send(form);
                }
            });

            var scene_dn_up = $('#scene-dn-up');
            scene_dn_up[0].innerHTML = '<i class="fa fa-download"></i>下载场景文件(.zip)';
            scene_dn_up.on('click', function () {
                var url = '../php/scene_api.php';
                //var json = '{\"s_id:\""+id+"\"}";
                var form = $('<form action="' + url + '" method="post">' +
                '<input type="text" name="op" value="client_download" />' +
                '<input type="text" name="data" value="{&quot;s_id&quot;:&quot;'+id+'&quot;,&quot;admin_op&quot;:true}" />' +
                '</form>');
                $('body').append(form);
                form.submit();
                //console.log('<input type="text" name="data" value="{&quot;s_id&quot;:&quot;'+id+'&quot;,}" />');

            });

            var scene_del = $('#scene-delete');
            scene_del.popover({
                title:'提示',
                content:'确认要删除该场景吗？<br><br>再次点击以删除<br>点击空白处关闭提示',
                html:true,
                placement:'top',
                trigger:'manual'
                //container: '#scene-delete'
            });
            scene_del.on('click', function(){
                if($('div.popover:visible').length == 0) {
                    scene_del.popover('show');
                }else{
                    scene_del.popover('hide');
                    $('button').attr('disabled', '');
                    $('input').attr('disabled', '');
                    $('textarea').attr('disabled', '');

                    var form = new FormData();
                    form.append('op', 'delete_one');
                    var json = JSON.stringify(
                        {
                            s_id:id
                        }
                    );
                    form.append('data', json);
                    var xhr = new XMLHttpRequest();
                    xhr.open('post', '../php/scene_api.php', true);
                    xhr.addEventListener('readystatechange', function() {
                        if (this.readyState == 4) {
                            if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                                var json = JSON.parse(this.responseText);
                                if(json['status'] == 'OK'){
                                    var url = './scene.php';
                                    var form = $('<form action="' + url + '" method="post" style="display:none">' +
                                    '<input type="text" name="mode" value="delete-success" />' +
                                        //'<input type="text" name="mode" value="modify" />' +
                                    '</form>');
                                    $('body').append(form);
                                    form.submit();
                                }
                            }
                        }
                    });
                    xhr.send(form);
                }
            });
            scene_del.on('blur', function(){
                scene_del.popover('hide');
            })


        }else if(mode == 'new'){
            $('#scene-dn-up').remove();
            $('#scene-delete').remove();
            var bt_submit = $('#scene-submit');
            bt_submit.empty();
            bt_submit[0].innerHTML = '添加场景';
            bt_submit[0].classList.add('btn-success');
            var bt_refresh = $('#form-id-refresh');
            bt_refresh.on('click', function () {
                var form = new FormData();
                form.append('op', 'get_new_b_id');
                var xhr = new XMLHttpRequest();
                xhr.open('post', '../php/scene_api.php', true);
                xhr.addEventListener('readystatechange', function() {
                    if (this.readyState == 4) {
                        if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                            var json = JSON.parse(this.responseText);
                            $('#form-scene-id')[0].value = json['new_b_id'];
                            id = json['new_b_id'];
                        }
                    }
                });
                xhr.send(form);
            });
            $('#form-upload-bt').on('click', function(){
                $('#scene-upload').click();
            });
            $('#scene-upload').on("change" ,function(event){
                var form_fileName = $('#form-upload-filename');
                var fileList = event.target.files;
                if(fileList.length > 0){
                    form_fileName.val(fileList[0].name);
                    $('#upload-info>div').remove();
                    var form_info = $('#upload-info');
                    form_info.fadeIn(300);
                    var dom = document.createElement('div');
                    var i = 0;
                    var size = fileList[0].size;
                    while(size / 1024 > 1){
                        size /= 1024;
                        i++;
                    }
                    //console.log(i);
                    var str;
                    switch (i){
                        case 0:
                            str = 'B';
                            break;
                        case 1:
                            str = 'KB';
                            break;
                        case 2:
                            str = 'MB';
                            break;
                        case 3:
                            str = 'GB';
                            break;
                        default :
                    }
                    dom.innerHTML = '大小: '+ (fileList[0].size / Math.pow(1024, i)).toFixed(2) + ' ' + str;
                    form_info.append(dom);
                    dom = document.createElement('div');
                    var date = fileList[0].lastModifiedDate;
                    dom.innerHTML = '修改日期: '+ date.getFullYear() +'年'+date.getMonth()+'月'+date.getDay()+'日 ' +
                    date.getHours()+':'+date.getMinutes()+':'+date.getSeconds();
                    form_info.append(dom);
                    file_upload = fileList[0];
                    $('#form-upload-filename')[0].parentNode.parentNode.classList.remove('has-error');
                    //console.log(typeof(fileList[0].lastModifiedDate));
                }else{
                    form_fileName.val('');
                    $('#upload-info').fadeOut(300);
                    file_upload = null;
                }
            });
            bt_submit.on('click', function(){
                if(file_upload == null){
                    $('#form-upload-filename')[0].parentNode.parentNode.classList.add('has-error');
                }
                if($('#form-scene-name').val().trim() == ''){
                    $('#form-scene-name')[0].parentNode.classList.add('has-error');
                }
                if($('#form-scene-designer').val().trim() == ''){
                    $('#form-scene-designer')[0].parentNode.classList.add('has-error');
                }
                var error_item = $('.has-error');
                if(error_item.length > 0) {
                    if(file_upload == null){
                        $('#form-upload-filename')[0].focus();
                    }
                    else error_item[0].childNodes[1].focus();
                }else{

                    $('button').attr('disabled', '');
                    $('input').attr('disabled', '');
                    $('textarea').attr('disabled', '');
                    $('#progress').fadeIn(500);

                    var form = new FormData();
                    form.append('op', 'add');
                    var json = JSON.stringify(
                        {
                            s_id:id,
                            name:$('#form-scene-name').val().trim(),
                            designer:$('#form-scene-designer').val().trim(),
                            b_id:'503d5728-fc6c-52f1-a151-537778c296a5',
                            download_times:0,
                            views_count:$('#form-vc').val(),
                            desc:$('#form-desc').val().trim(),
                            modify_date:new Date().toMysqlFormat()
                        }
                    );
                    form.append('data', json);
                    form.append('file', file_upload);
                    var xhr = new XMLHttpRequest();
                    xhr.addEventListener('readystatechange', function() {
                        if (this.readyState == 4) {
                            if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                                try {
                                    var json = JSON.parse(this.responseText);
                                }catch(err){

                                    return;
                                }
                                //console.log(json);
                                if(json['status'] == 'OK'){
                                    /*var url = './scene.php';
                                    var form = $('<form action="' + url + '" method="post">' +
                                    '<input type="text" name="mode" value="add-success" />' +
                                        //'<input type="text" name="mode" value="modify" />' +
                                    '</form>');
                                    $('body').append(form);
                                    form.submit();*/
                                    var url = './scene_detail.php';
                                    var form = $('<form action="' + url + '" method="post">' +
                                    '<input type="text" name="id" value="' + id + '" />' +
                                    '<input type="text" name="mode" value="modify" />' +
                                    '<input type="text" name="message" value="add-success" />' +
                                        //'<input type="text" name="mode" value="modify" />' +
                                    '</form>');
                                    $('body').append(form);
                                    setTimeout(function(){
                                        form.submit();
                                    }, 2000);
                                }else{

                                }
                            }
                        }
                    }, false);
                    xhr.upload.addEventListener('progress',function(event){
                        $('#progress-bar')[0].style.width = (event.loaded / event.total)*100 + '%';
                        $('#progress-bar')[0].innerHTML = parseInt((event.loaded / event.total)*100) + '%';
                       //console.log(parseInt((event.loaded / event.total)*100));
                    }, false);
                    xhr.upload.addEventListener('load', function(event){
                        $('#progress-bar')[0].classList.add('active');
                        $('#progress-bar')[0].classList.add('progress-bar-striped');
                        $('#progress-bar')[0].innerHTML = '上传完成, 正在跳转...';
                    });
                    xhr.open('post', '../php/scene_api.php', true);
                    xhr.send(form);
                }
            });
        }
    });
})();