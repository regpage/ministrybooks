function resizeText(multiplier) {
    var elem = document.getElementById("ministry-text");
    var currentSize = elem.style.fontSize || 1;
    
    elem.style.fontSize = ( parseFloat(currentSize) + (multiplier * 0.2)) + "em";
	localStorage.setItem('currentSize',currentSize);
}

document.getElementById("plustext").addEventListener("click", function() {resizeText(1);});
document.getElementById("minustext").addEventListener("click", function() {resizeText(-1);});
document.getElementById("resetfontsize").addEventListener("click", function() {document.getElementById("ministry-text").style.fontSize = localStorage.getItem('5')});

window.onload = function(){
    var g = localStorage.getItem('currentSize');
    document.getElementById("ministry-text").style.fontSize = g;
}


//http://javascript.ru/forum/project/40840-jquery-plagin-dlya-uvelicheniya-umensheniya-shrifta.html
//http://ruseller.com/lessons.php?rub=32&id=748