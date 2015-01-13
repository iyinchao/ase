/**
 * Created by lenovo on 2014/12/27.
 */
(function(){
    $(document).ready(function(){
        setTimeout(function(){
            $('.tobefade').fadeOut(1000);
        }, 3000);

       var id = ($("meta[name='id']")[0]).getAttribute('content');
        var mode = ($("meta[name='mode']")[0]).getAttribute('content');
        //var file_upload = null;

      //  var tag_selected = {};
        var form = new FormData();

        $('input.no-empty').on('input', function () {
            //console.log(this);
            if(this.value.trim() == ''){
                this.parentNode.classList.add('has-error');
            }else{
                this.parentNode.classList.remove('has-error');
            }
        });

        //console.log($('#form-scene-id'));
        if(mode == 'modify')      //如果是修改
        {
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

            //
            form = new FormData();
            form.append('op', 'get_one_tag');
            form.append('data', JSON.stringify(
                {
                    id:id
                }
            ));
            var xhr_form = new XMLHttpRequest();
            xhr_form.open('post', '../php/tag_api.php', true);
            xhr_form.addEventListener('readystatechange', function() {
                if (this.readyState == 4) {
                    if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                        //console.log(this.responseText);
                        var json = JSON.parse(this.responseText);
                        $('#form-tag-name')[0].value = json.name;
                        //$('#form-scene-designer')[0].value = json.designer;
                        $('#form-desc')[0].value = json.desc;
                       // $('#form-vc')[0].value = json.views_count;
                    }
                }
            });
            xhr_form.send(form);
            //console.log($('input.no-empty'));

            //$('#form-scene-id')[0].value = id;
            var submit_bt = $('#tag-submit');
            submit_bt.empty();
            submit_bt[0].innerHTML = '修改标签数据';
            submit_bt.on('click', function () {
                var error_item = $('.has-error');
                if(error_item.length != 0){
                    error_item[0].childNodes[1].focus();
                    //console.log(error_item[0]);
                }else{
                    var form = new FormData();
                    form.append('op', 'update');
                    var json = JSON.stringify(
                        {
                            id:id,
                            name:$('#form-tag-name')[0].value.trim(),
                            //designer:$('#form-scene-designer')[0].value.trim(),
                            desc:$('#form-desc')[0].value
                            //views_count:$('#form-vc')[0].value,
                            //modify_date:new Date().toMysqlFormat()
                        }
                    );
                    form.append('data', json);
                    var xhr = new XMLHttpRequest();
                    xhr.open('post', '../php/tag_api.php', true);
                    xhr.addEventListener('readystatechange', function() {
                        if (this.readyState == 4) {
                            if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                                if((JSON.parse(this.responseText)).result == 'ok'){
                                    var url = './c-tag.php';
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


            var scene_del = $('#tag-delete');
            scene_del.popover({
                title:'提示',
                content:'确认要删除该标签吗？<br><br>再次点击以删除<br>点击空白处关闭提示',
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
                    form.append('op', 'delete');
                    var json = JSON.stringify(
                        {
                            id:id
                        }
                    );
                    form.append('data', json);
                    var xhr = new XMLHttpRequest();
                    xhr.open('post', '../php/tag_api.php', true);
                    xhr.addEventListener('readystatechange', function() {
                        if (this.readyState == 4) {
                            if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                                var json = JSON.parse(this.responseText);
                                if(json['result'] == 'ok'){
                                    var url = './c-tag.php';
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


        }
        else if(mode == 'new'){
           // $('#scene-dn-up').remove();
            $('#tag-delete').remove();
            var bt_submit = $('#tag-submit');
            bt_submit.empty();
            bt_submit[0].innerHTML = '添加标签';
            bt_submit[0].classList.add('btn-success');
            bt_submit.on('click', function(){
                if($('#form-tag-name').val().trim() == ''){
                    $('#form-scene-name')[0].parentNode.classList.add('has-error');
                }
                var error_item = $('.has-error');
                if(error_item.length > 0) {
                    error_item[0].childNodes[1].focus();
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
                            name:$('#form-tag-name').val().trim(),
                            //designer:$('#form-scene-designer').val().trim(),
                           //b_id:'503d5728-fc6c-52f1-a151-537778c296a5',
                           // download_times:0,
                           // views_count:$('#form-vc').val(),
                            desc:$('#form-desc').val().trim()
                           // modify_date:new Date().toMysqlFormat()
                        }
                    );
                    form.append('data', json);
                    //form.append('file', file_upload);
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
                                if(json['result'] == 'ok'){
                                    var url = './c-tag.php';
                                    var form = $('<form action="' + url + '" method="post">' +
                                    '<input type="text" name="id" value="' + id + '" />' +
                                    '<input type="text" name="mode" value="add-success" />'+
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
                    xhr.open('post', '../php/tag_api.php', true);
                    xhr.send(form);
                }
            });
        }
    });
})();
