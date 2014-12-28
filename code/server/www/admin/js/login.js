/**
 * Created by 尹超 on 2014/12/27.
 */
(function () {
    //email regex,see
    //http://stackoverflow.com/questions/46155/validate-email-address-in-javascript
    var email_regex = /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    jQuery.fn.shake = function(intShakes, intDistance, intDuration) {
        this.each(function() {
            $(this).css("position","relative");
            for (var x=1; x<=intShakes; x++) {
                $(this).animate({left:(intDistance*-1)}, (((intDuration/intShakes)/4)))
                    .animate({left:intDistance}, ((intDuration/intShakes)/2))
                    .animate({left:0}, (((intDuration/intShakes)/4)));
            }
        });
        return this;
    };

    $(document).ready(function(){
        $('#panel').fadeIn(500);
        //$('#panel').shake(2, 20, 300);

        setTimeout(function(){
            $('.tobefade').fadeOut(1000);
        }, 3000);

        $('#form-email').on('input', function(){
            if(email_regex.test(this.value)){
                this.parentNode.classList.remove('has-error');
            }else{
                this.parentNode.classList.add('has-error');
            }
            //console.log(this.value);
        });

        $('#form-password').on('input', function(){
            if(this.value.trim() == ''){
                this.parentNode.classList.add('has-error');
            }else{
                this.parentNode.classList.remove('has-error');
            }
        });

        $('#form-submit').on('click', function(){
            $('#form-email').trigger('input');
            $('#form-password').trigger('input');
            var error_item = $('.has-error');
            if(error_item.length != 0){
                error_item[0].childNodes[1].focus();
            }else{
                this.classList.add('progress-bar-striped');
                $('input').attr('disabled','');
                var form = new FormData();
                form.append('op', 'client_login');
                form.append('data', JSON.stringify({
                    email:$('#form-email').val().trim(),
                    password:$('#form-password').val().trim(),
                    remember:document.getElementById("form-rem").checked
                }));
                //console.log(document.getElementById("form-rem").checked);
                var xhr = new XMLHttpRequest();
                xhr.open('post', '../php/user_api.php', true);
                xhr.addEventListener('readystatechange', function(e){
                    if (this.readyState == 4) {
                        if ((this.status >= 200 && this.status < 300) || this.status == 304) {
                            var resp = JSON.parse(this.responseText);
                            //refresh_scene_view(resp);
                            if(resp['status'] == "OK"){
                                setTimeout(function(){
                                    $('#form-submit')[0].classList.add('btn-success');
                                    $('#form-submit')[0].innerHTML = '正在跳转...';
                                }, 500);
                                setTimeout(function(){
                                    window.location.href = "./index.php";
                                }, 1200);
                            }else{
                                setTimeout(function(){
                                    $('#panel').shake(2, 20, 300);
                                    $('input').removeAttr('disabled');
                                    $('#form-submit')[0].classList.remove('progress-bar-striped');
                                    $('#form-email').focus();
                                }, 500);
                            }
                        }
                    }
                });
                xhr.send(form);
            }
        });
    });
})();