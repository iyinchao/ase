/**
 * Created by 尹超 on 2014/12/13.
 */

(function(){
    var SCENE_PER_PAGE = 8;
    function load_scene(page, tags, search){
        var requ = {};
        requ.scene_per_page = SCENE_PER_PAGE;
        requ.tags = tags;
        requ.page_now = page;
        var form = new FormData();
        form.append('op', 'client_browse');
        form.append('data', JSON.stringify(requ));
        var xhr = new XMLHttpRequest();
        xhr.open('post', '../php/scene_api.php', true);
        xhr.addEventListener('readystatechange', function(e){
            if (this.readyState == 4) {
                if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                    var resp = JSON.parse(this.responseText);
                    //refresh_scene_view(resp);
                    console.log(resp);
                }
            }
        });
        xhr.send(form);
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

    load_scene(0, []);
})();