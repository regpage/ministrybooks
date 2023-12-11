<?php
   $query = "SELECT *
               FROM {$gl_db_prefix}parts_items ORDER BY title ASC, pos";
    $results = db_select($query);
 if(is_array($results)) { $cnt = count($results); }
              $books = array('книга', 'книги', 'книг');
              $TotalBooksOnSite = $cnt . " " . getNumEnding($cnt, $books);
/*
echo "<ol>";
      for($i = 0; $i < $cnt; $i++)
      {
        $title    = stripslashes($results[$i]['title']);
echo "<li>" . $title . "</li>";
}
echo "</ol>";
*/
?>
		<!-- Use the ID of slider here to avoid the flash of unstyled content -->
	  	<style type="text/css">
#featured {width: 975px; height: 250px; background: #E7EDF1 url(img/ajax-loader2.gif) no-repeat center center; overflow: hidden;}	  		
	  	</style>
		
		<!-- Attach our CSS -->
	  	<link rel="stylesheet" href="orb_slide_show/orbit.css">	
	  	
		<!--[if IE]>
			<style type="text/css">
				.timer { display: none !important; }
				div.caption { background:transparent; filter:progid:DXImageTransform.Microsoft.gradient(startColorstr=#99000000,endColorstr=#99000000);zoom: 1; }
			</style>
		<![endif]-->
	  	
		<!-- Attach necessary scripts -->

		<script type="text/javascript" src="orb_slide_show/jquery.orbit.min.js"></script>
		
		<!-- Run the plugin -->
		<script type="text/javascript">
			$(window).load(function() {
				$('#featured').orbit({
					'bullets': false,
					'timer': false,
					'animation': 'fade',
                                        'directionalNav': false,
					'captions': false
				});
			});
		</script>
<!-- 
<div id="featured" class="banner-img" style="margin-top: 15px; width: 975px;">
<img style="max-width: 975px; min-width: 300px;" width="975px" src="themes/general/index/ministrybooksru.png" alt="Чтение книг Вочмана Ни и Уитнесса Ли" title="Чтение книг Вочмана Ни и Уитнесса Ли" />
<img style="max-width: 975px; min-width: 300px;"  width="975px" src="themes/general/index/slideshowministrybooks2.png" alt="Чтение книг Вочмана Ни и Уитнесса Ли" title="Чтение книг Вочмана Ни и Уитнесса Ли"  />
<img style="max-width: 975px; min-width: 300px;" width="975px" src="themes/general/index/slideshowministrybooks3.png" alt="Чтение книг Вочмана Ни и Уитнесса Ли" title="Чтение книг Вочмана Ни и Уитнесса Ли" rel="Caption1"  />
<img style="max-width: 975px; min-width: 300px;" width="975px" src="themes/general/index/ministrybooksru.jpg"  alt="Чтение и поиск книг служения Вочмана Ни и Уитнесса Ли" title="Чтение книг Вочмана Ни и Уитнесса Ли" rel="Caption2" />
</div>  -->
<span class="orbit-caption" id="Caption1">Христос должен быть вписан в каждую часть нашего внутреннего существа Духом Бога живого,</span>
<span class="orbit-caption" id="Caption2">чтобы сделать нас Своими живыми письмами с тем, чтобы Он был выражен и прочитан в нас другими.</span> 
<img class="banner-img" width="975" src="themes/general/index/ministrybooksru.png" alt="Чтение книг Вочмана Ни и Уитнесса Ли" title="Чтение книг Вочмана Ни и Уитнесса Ли" />
<h2 class="site-title" style='font-family: "LiberationSerifItalic";'>Издания «Коллектора библейской книги» онлайн</h2>
<p style="text-align: justify; font-size: 19px;">Издательство <a href="http://kbk.ru">«Коллектор библейской книги»</a> предоставляет читателям полные тексты книг служения <a href="/?mod=watchman_nee_books#">Вочмана Ни</a> и <a href="/?mod=witness_lee_books#">Уитнесса Ли</a>. Мы искренне надеемся, что благодаря этому ресурсу богатство Христово широко распространится по всей земле ради пользы всех детей Господних.</p>
<p style="text-align: justify; font-size: 19px;">На сайте опубликовано <a href="/?mod=by_alphabet#"><? echo $TotalBooksOnSite; ?></a>. Список опубликованных книг регулярно дополняется. Пожалуйста, читайте наши книги онлайн и сообщите своим знакомым о духовном богатстве, представленном на этом сайте.</p>
<p style="text-align: justify; font-size: 19px;"><strong>Для тех, кто начинает знакомиться с нашими изданиями, рекомендуем брошюры и книги, перечисленные <a href="/?mod=fnb">здесь.</a></strong></p>
<? 
 //   $search_path = "{$gl_path_to_root}/engine/search/search.inc";
 //   if(file_exists($search_path))include($search_path); 

 $query_books = "SELECT * FROM {$gl_db_prefix}parts_items WHERE dateentry > NOW() - INTERVAL 120 DAY ORDER BY id_item DESC LIMIT 10";
 $results_books = db_select($query_books);
  if(is_array($results_books))
    {
      $cnt = count($results_books);
print "<h2 style='font-family: LiberationSerifItalic;'>Недавно добавленные книги</h2><table>
            <thead>
              <tr>
                <th style='width: 15%;'>Дата</th>
		  <th>Название</th>               
              </tr>
            </thead>
            <tbody>"; 
      for($i = 0; $i < $cnt; $i++)
      {
           $title = stripslashes($results_books[$i]['title']);
           $id_item  = $results_books[$i]['id_item'];
           $date_entry = $results_books[$i]['dateentry'];
           $date_entry = strftime("%d-%m-%Y", strtotime($date_entry));
        print "<tr>";
        print "<td>{$date_entry}</td><td><a href='?mb={$id_item}'>{$title}</a></td> "; 
        print "</tr>";
      }
    }
 	print "</tbody></table>"; 
       // echo $title . ", " . ;
 ?> 
<div class="panel">
        <h3 style='font-family: "LiberationSerifItalic";'>Поиск по книгам</h3>
        <form method="POST" name="edit_form" action="/?mod=search_on_site">
          <div class="row">
            <div class="large-12 columns">
              <div class="row collapse">
                <div class="small-9 columns">
                  <input type="text" name="template" value="">
                </div>
                <div class="small-3 columns">
                  <input class="button prefix" type="submit" name="search" value="Поиск">
                </div>
                <p class="small-note">Введите слово или фразу. Учитывайте, что при поиске исключаются предлоги, местоимения, частицы и др.</p>
                <p class="text-right"><a href="/?mod=search_on_site">Расширенный поиск</a></p>
              </div>
            </div>
          </div>
          <input type="hidden" name="stype" value="S">
          <input type="hidden" name="search_by" value="All">
          <input type="hidden" name="logic" value="AND">
        </form>
</div>
<br>
<div id="notice">
      <p class="note" style="text-align: justify;"><strong>Примечание:</strong> Мы просим не копировать, не загружать и не переиздавать материалы этого сайта ни электронными, ни какими-либо другими средствами. Авторские права на все материалы принадлежат «Коллектору библейской книги» и Living Stream Ministry. Мы надеемся, что все наши посетители отнесутся к этой просьбе с уважением.</p></div>
<!-- <div class='to-top'><a href='#top' class='scroll'> В начало </a></div> -->
<div id="myModalNoise" class="reveal-modal">
 	<h2>Шумовые слова и Стоп-слова</h2>
 	<p>В работу алгоритма поисковой машины заложено отбрасывание, т.е. исключение из индексирования, определённых слов, которые часто называют "шумовыми словами" (их часто называют "стоп-слова"). Такими словами могут быть предлоги, суффиксы, причастия, междометия и частицы:</p>
	<p>а, без, более, бы, был, была, были, было, быть, в, вам, вас, весь, во, вот, все, всего, всех, вы, где, да, даже, для, до, его, ее, если, есть, ещё, же, за, здесь, и, из, из-за, или, им, их, к, как, как-то, ко, когда, кто, ли, либо, мне, может, мы, на, надо, наш, не, него, неё, нет, ни, них, но, ну, о, об, однако, он, она, они, оно, от, очень, по, под, при, с, со, так, также, такой, там, те, тем, то, того, тоже, той, только, том, ты, у, уже, хотя, чего, чей, чем, что, чтобы, чьё, чья, эта, эти, это, я</p>
 	<a class="close-reveal-modal">&#215;</a>
</div>


