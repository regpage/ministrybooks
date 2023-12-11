
//  ============================================================================
//
//    Тут  глазам их  открылось не то  тридцать, не то  сорок ветряных  мельниц,
//  стоявших среди поля, и как скоро увидел их Дон Кихот, то обратился к своему
//  оруженосцу с такими словами:
//    — Судьба  руководит нами как нельзя лучше. Посмотри, друг Санчо Панса: вон
//  там виднеются  тридцать, если не  больше, чудовищных великанов, — я  намерен
//  вступить с ними в бой и перебить их всех до е диного, трофеи же, которые нам
//  достанутся, явятся основою  нашего  благосостояния. Это война  справедливая:
//  стереть  дурное семя с лица  земли — значит верой и  правдой послужить богу.
//    — Где вы видите великанов? — спросил Санчо Панса.
//    — Да вон они, с громадными руками, — отвечал  его господин. — У  некоторых
//  из них длина рук достигает почти двух миль.
//    — Помилуйте, сеньор, — возразил  Санчо, — то, что там виднеется,  вовсе не
//  великаны, а  ветряные мельницы;  то же, что вы  принимаете за их руки, — это
//  крылья: они кружатся от ветра и приводят в движение мельничные жернова.
//    — Сейчас видно неопытного искателя приключений, — заметил Дон Кихот, — это
//  великаны.  И  если ты  боишься, то  отъезжай в  сторону и помолись,  а я тем
//  временем вступлю с ними в жестокий и неравный бой.
//
//  ============================================================================


//  ============================================================================
//  Читайте классику, мальчики. Вместо того, чтобы Донцовых тырить :)
//  С уважением к "Великим Борцам За Вселенское Бабро", но  нет времени на
//  кудрявые головоломки для вас. Звиняйте.
//  Грибов Дмитрий aka GribUser.
//  ============================================================================


function DeFocus(){
  var Sel;
	if (window.getSelection){
		Sel=window.getSelection();
	} else if (document.getSelection){
		Sel=document.getSelection();
	} else if (document.selection){
		Sel=document.selection;
	}

	if (!Sel){return}

	if (Sel.removeAllRanges){
		Sel.removeAllRanges();
	} else if (Sel.empty){
		Sel.empty();
	}
	setTimeout ('DeFocus()', 10);
}

function InitReadField(){
  document.getElementById('rd').innerHTML = '<h2>Текст загружается…</h2><span id="rsp" style="display:none;">&#160;</span>';
}

function GetFontSizeFromCookies(){
  var Cookie = '' + document.cookie;
  var CurFnt = Cookie.match(/READFNT=(\d+)/);
  if (CurFnt && CurFnt[1]){
    return CurFnt[1];
  } else {
    return 100;
  }
}

function SaveFontSize(NewSize){
  var NewCook=''+document.cookie;
  NewCook=NewCook.replace(/READFNT=\d+(;\s+)?/,'');
  NewCook='READFNT='+NewSize+';'+NewCook;
  document.cookie=NewCook;
}


var Color='Black';
var SavedCode;
var FontSize=GetFontSizeFromCookies();

function FinaliseDoc(Code){
  Code=Code.replace(/(<a [^>]+)\/>/gi,'$1></a>');
  document.getElementById('rd').innerHTML = '<div oncontextmenu="return false" UNSELECTABLE="on" style="color:'+Color+';" id="onlineread" class="onlineread">'+Code+'</div>';
  SavedCode = Code;
  setTimeout('DeFocus()', 100);
  FontSetup(0);
	MarkElement(document.getElementById('active_read_page2'));
	document.getElementById('goog2').innerHTML=document.getElementById('goog2_loader').innerHTML;
	document.getElementById('goog2_loader').innerHTML='';
}

function YankeGoHome(Home){
  var CurLoc=''+document.location;
  if (!CurLoc.match(/http:\/\//)){
    alert('Скачать эту книгу из библиотеки невозможно.\nПриобритение книг по адресу: www.kbk.ru');
    document.location='http://';
  }
}

function FontSetup(Size){
  FontSize=FontSize*1+Size*1;
  SaveFontSize(FontSize);
  document.getElementById('onlineread').style.fontSize=FontSize+'%';
}
