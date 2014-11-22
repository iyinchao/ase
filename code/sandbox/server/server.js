var http=require('http');  
var server=new http.Server();  
server.on('request',function(req,res){  
    res.writeHead(200,{'Content-Type':'text/html'});  
    res.write('<h1>Meijia</h1>');  
    res.end('<p>Server bootstrap</p>');  
});  
  
server.listen(3000);  
console.log('SERVER is LISTENING AT PORT 3000.');  