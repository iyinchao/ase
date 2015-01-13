/**
 * Created by 尹超 on 2015/1/10.
 */
(function(){
    var testProcess = {};
    var testStart = {};
    var testList = [];
    var testCur = 0;
    var testXHR;
    function listAllAPI(){
        for (var i in Config.API_LIST) {
            if (Config.API_LIST.hasOwnProperty(i)) {
                if(testStart['api_type'] == undefined){
                    testStart['api_type'] = i;
                    testProcess['api_type'] = i;
                }
                for(var j in Config.API_LIST[i]){
                    if (Config.API_LIST[i].hasOwnProperty(j)) {
                        if(testStart['api_target'] == undefined){
                            testStart['api_target'] = j;
                            testProcess['api_target'] = j;
                        }
                        testList.push({
                            api_type:i,
                            api_target:j
                        });
                        var dom = document.createElement('div');
                        dom.classList.add('list-group-item');
                        dom.classList.add('api-item');
                        dom.id = 'test-cell-' + i + j;
                        dom.innerHTML += '<i class="fa fa-question-circle"></i><span class="api-item-text">';
                        dom.innerHTML += '&nbsp;&nbsp;' + Config.API_LIST[i][j]['display_name'] + '(' + j + ')';
                        dom.innerHTML += '</span><span class="api-item-status pull-right text-muted small"><em>未测试...</em>';
                        $('#scene-api-lg').append(dom);
                    }
                }
            }
        }

    }

    function testAllAPI(){
        if(testXHR != undefined){
            testXHR.abort();
        }
        var cellIcon = $('.api-item>i');
        cellIcon.removeClass('fa-check-circle');
        cellIcon.removeClass('fa-times-circle');
        cellIcon.removeClass('fa-circle-o-notch');
        cellIcon.removeClass('fa-spin');
        cellIcon.addClass('fa-question-circle');
        var cellName = $('.api-item>.api-item-text');
        cellName.removeClass('name-error');
        var cellStatus = $('.api-item>.api-item-status');
        cellStatus.empty();
        testCur = 0;
        testOneAPI(testCur);
    }

    function testOneAPI(cur){
        var testDef = Config.API_LIST[testList[cur].api_type][testList[cur].api_target];
        var cellIcon = $('#'+'test-cell-' + testList[cur].api_type + testList[cur].api_target +'>i');
        cellIcon.removeClass('fa-question-circle');
        cellIcon.removeClass('fa-check-circle');
        cellIcon.removeClass('fa-times-circle');
        cellIcon.addClass('fa-circle-o-notch');
        cellIcon.addClass('fa-spin');
        var cellName = $('#'+'test-cell-' + testList[cur].api_type + testList[cur].api_target +'>.api-item-text');
        var cellStatus = $('#'+'test-cell-' + testList[cur].api_type + testList[cur].api_target +'>.api-item-status');
        cellStatus.empty();
        cellStatus.innerHTML = '测试中...';
        console.log(cellStatus);
        var form = new FormData();
        form.append('op', testDef['op']);
        form.append('data', testDef['data']);
        testXHR = new XMLHttpRequest();
        testXHR.open('post', '../php/tag_api.php', true);
        testXHR.addEventListener('readystatechange', function() {
            if (this.readyState == 4) {
                console.log('ok');
                if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                    cellIcon.removeClass('fa-circle-o-notch');
                    cellIcon.removeClass('fa-spin');
                    cellIcon.addClass('fa-check-circle');
                    cellStatus.empty();
                    cellStatus[0].innerHTML = '正常';
                }else{
                    cellIcon.removeClass('fa-circle-o-notch');
                    cellIcon.removeClass('fa-spin');
                    cellIcon.addClass('fa-times-circle');
                    cellStatus.empty();
                    cellStatus[0].innerHTML = '异常';
                }
                cur++;
                if(testList[cur] != undefined){
                    testOneAPI(cur);
                }
            }
        });
        testXHR.send(form);

        //console.log(def.display_name);
    }

    $(document).ready(function(){
        listAllAPI();
        $("#bt-test-all").on('click', function(){
            testAllAPI();
        });
    });
})();