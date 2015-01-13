$(function() {

    $('#logout').click(function(){
        var form = new FormData();
        form.append('op', 'client_logout');
        var xhr = new XMLHttpRequest();
        xhr.open('post', '../php/user_api.php', true);
        xhr.addEventListener('readystatechange', function(e){
            if (this.readyState == 4) {
                if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                    var resp = JSON.parse(this.responseText);
                    if(resp.result=='ok') {
                        var url = './login.php';
                        var form = $('<form action="' + url + '" method="post">' +
                        '<input type="text" name="message" value="logout" />' +
                            //'<input type="text" name="mode" value="modify" />' +
                        '</form>');
                        $('body').append(form);
                        form.submit();
                    }
                }
            }
        });
        xhr.send(form);
        //console.log('ok');
    });

    $('#side-menu').metisMenu();

});

//Loads the correct sidebar on window load,
//collapses the sidebar on window resize.
// Sets the min-height of #page-wrapper to window size
$(function() {
    $(window).bind("load resize", function() {
        topOffset = 50;
        width = (this.window.innerWidth > 0) ? this.window.innerWidth : this.screen.width;
        if (width < 768) {
            $('div.navbar-collapse').addClass('collapse')
            topOffset = 100; // 2-row-menu
        } else {
            $('div.navbar-collapse').removeClass('collapse')
        }

        height = (this.window.innerHeight > 0) ? this.window.innerHeight : this.screen.height;
        height = height - topOffset;
        if (height < 1) height = 1;
        if (height > topOffset) {
            $("#page-wrapper").css("min-height", (height) + "px");
        }
    })
});

