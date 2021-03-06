/**
 * Created by lenovo on 2014/12/27.
 */

(function(){
   // var SCENE_PER_PAGE = -1; //get all pages
    function load_tags(){
        var requ = {};
        var form = new FormData();
        form.append('op', 'get_tags');
        var xhr = new XMLHttpRequest();
        xhr.open('post', '../php/tag_api.php', true);
        xhr.addEventListener('readystatechange', function(e){
            if (this.readyState == 4) {
                if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                    var resp = JSON.parse(this.responseText);
                    //refresh_scene_view(resp);
                    refresh_tag_table(resp);
                    //console.log(resp);
                }
            }
        });
        xhr.send(form);
    }

    function refresh_tag_table(json){
        var data = [];
        for(var i = 0;i < json.num; i++){
            var cell = json.tags[i];
            data.push(cell);
        }
        //console.log(data);
        var table = $('#tag-table').DataTable( {
            destroy:true,
            language:Config.TABLE_LANG,
            data:data,
            //autoWidth:false,
            "lengthMenu": [[5, 10, 50], [5, 10, 50]],
            //"scrollX": true,
            "columnDefs": [
               // { className:"tag-table-id-column", "targets": [ 1 ] },
                { className:"tag-table-column", "targets": [ 0,1,2] }

            ],
            columns:[
                { "data": "id" },
                { "data": "name" },
                { "data": "desc" },
            ]
        });
        //$('#container').css( 'display', 'block' );
        //console.log(table);
        table.columns.adjust().draw();

       // $('.tag-table-id-column').css('width', '30px');
        //$('.tag-table-column').css('width', '200px');
        //console.log($('.dataTables_empty')[0].parentNode);
        /*if($('.dataTables_empty').length > 0) {
         $('.dataTables_empty')[0].parentNode.style.pointerEvents = 'none';
         }*/
        /*window.addEventListener('resize', function (e) {
         table.columns.adjust().draw();
         //console.log('ok');
         });*/



    }
    /*function refresh_scene_view(json){
     $('#scene-view').empty();
     json.scene.forEach(function (element, index, array) {
     var cell_info = JSON.parse(element);
     console.log(cell_info);
     var cell = document.createElement('div');
     cell.classList.add('mj-scene-block');
     $('#scene-view').append(cell);
     var cell_mask = document.createElement('div');
     cell_mask.innerHTML='<div class="cell-digit">'+
     '<i class="fa fa-download"></i>'+
     cell_info.download_times+
     '<i class="fa fa-copy"></i>'+
     cell_info.views_count+'</div>' +
     '<div class="noselect cell-name">'+
     cell_info.name
     +'</div>';
     cell.appendChild(cell_mask);
     //cell.style.backgroundImage = "url('"+Config.FILE_SRORE+"/design/"+cell_info.s_id+"/thumb.png')";
     });
     //console.log(json.scene[0]);
     }*/

    function fill_scene_thumb(id, thumb){
    }

    $(document).ready(function(){
        setTimeout(function(){
            $('.tobefade').fadeOut(1000);
        }, 3000);

        var tag_selected = {};

        $('#tags-toggle').click(function(){
            //if(this.classList.contains('collapsed')){
            //this.classList.remove('collapsed');
            //}
            if(this.getAttribute('aria-expanded') == 'false'){
                tag_selected = {};
                this.classList.add('active');
                this.classList.add('bt-tags-expand');
                var form = new FormData();
                form.append('op', 'get_all_tags');
                var xhr = new XMLHttpRequest();
                xhr.open('post', '../php/tag_api.php', true);
                xhr.addEventListener('readystatechange', function() {
                    if (this.readyState == 4) {
                        if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                            var json = JSON.parse(this.responseText);
                            //console.log(json);
                            if(json['tags']){
                                $('#tags-panel>.well').empty();
                                (json['tags']).forEach(function(tag, i, array){
                                    var dom = document.createElement('button');
                                    dom.className = 'btn btn-default btn-tag';
                                    dom.setAttribute('meta-id',tag['id']);
                                    dom.setAttribute('meta-desc',tag['desc']);
                                    if(tag['desc'] && tag['desc'] != ''){
                                        //data-toggle="tooltip" data-placement="bottom" title="Tooltip on bottom"
                                        dom.setAttribute('data-toggle', 'tooltip');
                                        dom.setAttribute('data-placement', 'bottom');
                                        dom.setAttribute('title', tag['desc']);
                                    }
                                    dom.innerHTML = '<i class="fa fa-tag"></i>&nbsp;'+tag['name'];
                                    $('#tags-panel>.well').append(dom);
                                    dom.addEventListener('click', function(e){
                                        if(dom.classList.contains('active')){
                                            dom.classList.remove('active');
                                            dom.classList.remove('btn-warning');
                                            tag_selected[tag['id']] = false;
                                        }else{
                                            dom.classList.add('active');
                                            dom.classList.add('btn-warning');
                                            tag_selected[tag['id']] = true;
                                        }
                                        var tags = [];
                                        for (var i in tag_selected) {
                                            if (tag_selected.hasOwnProperty(i)) {
                                                if(tag_selected[i])tags.push(parseInt(i));
                                            }
                                        }
                                        load_scene(0, tags);
                                    });
                                });
                            }
                            $('[data-toggle="tooltip"]').tooltip()
                        }
                    }
                });
                xhr.send(form);
            }else{
                this.classList.remove('active');
                this.classList.remove('bt-tags-expand');
                load_scene(0, []);
            }
        });

        $('#tag-table').dataTable( {
            language:Config.TABLE_LANG
        });
        load_tags(0, []);
        $('#tag-table tbody').not($('.dataTables_empty')[0]).on('click', 'tr[role="row"]', function () {
            /* var name = $('td', this).eq(1).text();
             console.log( 'You clicked on '+name+'\'s row' );*/
            //console.log(this);
            var url = './c-tag-detail.php';
            var form = $('<form action="' + url + '" method="post">' +
            '<input type="text" name="id" value="' + $('td', this).eq(0).text() + '" />' +
            '<input type="text" name="mode" value="modify" />' +
            '</form>');
            $('body').append(form);
            form.submit();
        } );

        $('#bt-new-tag').on('click', function () {
            var url = './c-tag-detail.php';
            var form = $('<form action="' + url + '" method="post">' +
            '<input type="text" name="mode" value="new" />' +
                //'<input type="text" name="mode" value="modify" />' +
            '</form>');
            $('body').append(form);
            form.submit();
        });
        /*$('#scene-table tbody').mouseenter(function(event){
         console.log( 'enter' );
         });
         $('#scene-table').mouseout(function(event){
         console.log( 'Out' );
         });*/
    });
})();
