function NewWindow(mypage, myname, w, h, scroll) {
var winl = (screen.width - w) / 2;
var wint = (screen.height - h) / 2;
winprops = 'height='+h+',width='+w+',top='+wint+',left='+winl+',scrollbars='+scroll+',resizable'
win = window.open(mypage, myname, winprops)
if (parseInt(navigator.appVersion) >= 4) { win.window.focus(); }
}
// Модальное окно c title в // мобильной версии
/*
$("sup").find("span").click(function(e){
    e.stopPropagation();
    if ($(this).attr("title")) {
    	alert($(this).attr("title"));
    }
});
*/
$("span").click(function(e){
	console.log("I am here!");
    e.stopPropagation();
    if ($(this).attr("title")) {
    	alert($(this).attr("title"));
    }
});