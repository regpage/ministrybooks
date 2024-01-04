<!DOCTYPE html><?php include("{$gl_path_to_root}codesfragms/ban"); ?>	
<html class=" js no-touch svg inlinesvg svgclippaths no-ie8compat" lang="ru"><!--<![endif]-->
  <head>
    <!-- Google Tag Manager (noscript) ТОЛЬКО ДЛЯ САЙТА .online
    <noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-NSB4TV33"
    height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>-->
    <!-- End Google Tag Manager (noscript) -->
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <!-- Google Tag Manager 
    <script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
      new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
      j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
      'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
    })(window,document,'script','dataLayer','GTM-NSB4TV33');</script>-->
    <!-- End Google Tag Manager -->
  	<meta name="viewport" content="width=device-width, initial-scale=1.0">
    
  	 <?php setmeta($gl_page, $site_keywords, $site_descr)?>
  	<title><?php print $site_title; ?></title>
 <!-- <link rel="stylesheet" href="themes/Templ_Books/css/epub.css" type="text/css" media="screen"> -->
  
    <!-- stylesheets -->
	<link rel="stylesheet" href="themes/general/index/foundation.min.css">
    <link rel="stylesheet" href="themes/general/index/app.css">
   <link rel="stylesheet" href="themes/general/mistakes/mistakes.css">
    <link href="themes/general/index/css" rel="stylesheet" type="text/css">    
    <!-- Google Fonts -->
<link href="https://fonts.googleapis.com/css?family=Droid+Serif:400,700,400italic,700italic|Droid+Sans:400,700" rel="stylesheet" type="text/css">

<link href="https://fonts.googleapis.com/css?family=Droid+Serif" rel="stylesheet">
<style>
@import url('https://fonts.googleapis.com/css?family=Droid+Serif');
</style>
<!-- <link href="https://allfont.ru/allfont.css?fonts=droid-serif" rel="stylesheet" type="text/css" />-->


    <!-- javascript -->
    <script src="themes/general/index/jquery.min.js"></script>
    <script type="text/javascript" async src="themes/general/mistakes/mistakes.js"></script>
  	<script type="text/javascript" async src="themes/general/index/ga.js?v2"></script>
    <script src="themes/general/index/custom.modernizr.js"></script>  	
    <script src="themes/general/index/scroll-top.js"></script>
</head>
<body id="top" style="padding-top: 0px;"><a name="topofpage"></a>
<div id="header">
  <div class="row">
          <div class="large-12 columns">
               <a href="https://<?php echo $_SERVER['SERVER_NAME'];?>/"><img src="themes/general/index/lsm-logo.png" alt="Living Stream Ministry logo" class="logo"></a>
               <h1 style='font-family: DroidSerifItalic;'>Коллектор библейской книги</h1>
               <h2 style='font-family: DroidSerifItalic;'>Произведения Вочмана Ни и Уитнесса Ли онлайн</h2>
          </div>
    </div>
    <div class="row">
          <div class="large-12 columns spanish-link"> 
<a href="https://www.kbk.ru/">Посетить интернет-магазин издательства</a>        	
          </div>
    </div>    
</div>
<div class="contain-to-grid sticky">
  <nav class="top-bar">
    <ul class="title-area">
      <li class="name"></li>
      <li class="toggle-topbar menu-icon"><a href="http://<?php echo $_SERVER['SERVER_NAME'];?>/#"><span>Меню</span></a></li>
    </ul>    
  <section class="top-bar-section" style="left: 0%;">
      <ul class="left">
        <li><a href="index.cfm">Главная</a></li>
        <li><a href="/?mod=by_alphabet">Книги А-Я</a></li>
        <li><a href="/?mod=books_list">Книги по категориям</a></li>
        <li><a href="/?mod=watchman_nee_books">Книги Вочмана Ни</a></li>
        <li class="has-dropdown"><a href="/?mod=witness_lee_books">Книги Уитнесса Ли</a>
          <ul class="dropdown">
            <li><a href="/?mod=life_study">Жизнеизучения Библии</a></li>
            <li><a href="/?mod=conclnt">Заключительные сообщения к Новому Завету</a></li>
            <li><a href="/?mod=high_peak_books">Вершина божественного откровения</a></li>
          </ul>
        </li>
        <li class="has-dropdown"><a href="/?mod=kbk_websites">Cайты КБК</a>
          <ul class="dropdown">
            <li><a href="http://www.kbk.ru/">Интернет-магазин КБК</a></li>
            <li><a href="http://www.recoveryversion.ru/">Новый Завет онлайн</a></li>
            <li><a href="http://www.watchmannee.ru/">Вочман Ни</a></li>
            <li><a href="http://www.witnesslee.ru/">Уитнесс Ли</a></li>
          </ul>
        </li>
        <li><a href="/?mod=search_on_site" title="Онлайн поиск публикаций">Поиск <span aria-hidden="true" data-icon="&#xe001;"></span> </a></li>        
      </ul>
    </section></nav>
</div>

   <div class="large-12 columns">
           <?php include("{$gl_path_to_engine}public/chpt_nvg.inc"); ?>
           <?php include("{$gl_path_to_engine}public/ch_novig.inc"); ?>
       <div id="ministry-text">  
        <?php include("{$gl_path_to_engine}public/content.inc"); ?>      
       </div>
   </div>
</div>
<div class="row">
  <div class="large-12 columns">
    <div id="notice"><p class="note" style="text-align: justify;"><strong>Примечание:</strong>  Мы просим не копировать, не загружать и не переиздавать материалы этого сайта ни электронными, ни какими-либо другими средствами. Авторские права на все материалы принадлежат «Коллектору библейской книги» и Living Stream Ministry. Мы надеемся, что все наши посетители отнесутся к этой просьбе с уважением.<br>* Мы будем признательны вам, если вы сообщите нам об ошибке или опечатке в тексте. Для этого достаточно выделить нужный фрагмент и нажать сочетание клавиш Ctrl+Enter</p>
      <p><strong>Загрузка этого материала, даже для личного пользования, запрещается.<br> <?php include("{$gl_path_to_root}codesfragms/ip"); ?></strong></p>         
    </div>
  </div>
</div>
<div id="footer-links">
	<div class="row">
    <div class="large-12 columns">
      <div class="row">
       	<div class="large-5 columns">
         	<h4>Другие сайты</h4>
          <ul class="vertical">
            <li><a href="https://www.rhemabooks.org/rus/Home/">Миссия «Рема»</a></li>
            <li><a href="https://bibleforall.ru/">Библия, открытая для всех</a></li>
            <li><a href="https://www.emanna.com/russian/">Emanna (электронная манна)</a></li>
            <li><a href="https://forfaith.ru/">Защищая веру</a></li>
          </ul>
       	</div>
      	<div class="large-7 columns">
        	<h4>О Коллекторе библейской книги</h4>
        	<p>«Коллектор библейской книги» — некоммерческая организация, основная задача которой — публикация служения Вочмана Ни и Уитнесса Ли на русском языке. Следуя по стопам этих двух служителей Господа Иисуса Христа, которые верно хранили наследие служения, полученного церковью от Господа, мы видим свою цель в том, чтобы распространять богатство Христово, снабжая всех верующих духовной пищей, которая даст им рост в божественной жизни ради созидания Тела Христова.</p>	
        </div>
      </div>
    </div>
  </div>
    
  <div class="row">
    <div class="large-12 columns">
      <ul class="button-group">
        <li><a href="/index.cfm" class="button tiny secondary radius">Главная</a></li>
        <li><a href="/?mod=by_alphabet" class="button tiny secondary radius">Книги А-Я</a></li>
        <li><a href="/?mod=books_list" class="button tiny secondary radius">Книги по категориям</a></li>
        <li><a href="/?mod=watchman_nee_books" class="button tiny secondary radius">Книги Вочмана Ни</a></li>
        <li><a href="/?mod=witness_lee_books" class="button tiny secondary radius">Книги Уитнесса Ли</a></li>
        <li><a href="/?mod=kbk_websites" class="button tiny secondary radius">Cайты КБК</a></li>    
       </ul>
    </div>
  </div>
  
  <div class="row">
    <div class="large-12 columns">
      <div class="button-group">
        <h4>По всем вопросам пишите по адресу <a href="mailto:books@kbk.ru" style="font-family: 'LiberationSerifRegular', DroidSerifRegular, 'Droid Serif', Georgia, Times, serif;"> books@kbk.ru</a>.</h4> <!--  kbk.books@gmail.com   books@kbk.ru-->
      </div>
      <br>
    </div>    
  </div>

<div id="footer">
	<div class="row">
   	<div class="large-9 columns">
      <p>© 1998-<? echo date('Y'); ?> Религиозная организация евангельских христиан «Коллектор библейской книги».<br>Все права защищены. Воспроизведение в целом или
частично без разрешения запрещено.</p>
    </div>
    <div class="large-3 columns">
     	<p class="right"><a href="https://kbk.ru/contact/">Контакты</a> | <a href="/?mod=sitemap">Карта сайта</a> | <a href="/?mod=copyright_policy">Политика авторского права в Интернете</a></p>
    </div>
  </div>
</div>
<!-- Yandex.Metrika counter -->
<script type="text/javascript">
    (function (d, w, c) {
        (w[c] = w[c] || []).push(function() {
            try {
                w.yaCounter7537456 = new Ya.Metrika({
                    id:7537456,
                    clickmap:true,
                    trackLinks:true,
                    accurateTrackBounce:true,
                    webvisor:true
                });
            } catch(e) { }
        });

        var n = d.getElementsByTagName("script")[0],
            s = d.createElement("script"),
            f = function () { n.parentNode.insertBefore(s, n); };
        s.type = "text/javascript";
        s.async = true;
        s.src = "https://mc.yandex.ru/metrika/watch.js";

        if (w.opera == "[object Opera]") {
            d.addEventListener("DOMContentLoaded", f, false);
        } else { f(); }
    })(document, window, "yandex_metrika_callbacks");
</script>
<noscript><div><img src="https://mc.yandex.ru/watch/7537456" style="position:absolute; left:-9999px;" alt="" /></div></noscript>
<!-- /Yandex.Metrika counter -->
<script>
  document.write('<script src=' +
   ('__proto__' in {} ? 'js/vendor/zepto' : 'js/vendor/jquery') +
   '.js><\/script>')
</script><script src="themes/general/index/zepto.js"></script>
<script>$('body').prepend('<a href="#" class="back-to-top">Back to Top</a>');var amountScrolled = 300;$(window).scroll(function() {	if ( $(window).scrollTop() > amountScrolled ) {$('a.back-to-top').fadeIn('slow');} else {$('a.back-to-top').fadeOut('slow');}});$('a.back-to-top').click(function() {$('body, html').animate({scrollTop: 0}, 700);return false;});$(document).foundation()</script>
<script src="themes/general/index/foundation.min.js"></script>



<script>
	$(document).foundation();
</script>
<script src="themes/general/index/font-size.js"></script>
<script src="themes/general/index/ios-orientationchange-fix.js"></script>



</body></html>