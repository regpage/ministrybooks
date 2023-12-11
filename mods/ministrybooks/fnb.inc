<?php
$query = "SELECT *
               FROM {$gl_db_prefix}parts_items ORDER BY title ASC, pos";
    $results = db_select($query);
 if(is_array($results)) { $cnt = count($results); }
              $books = array('книга', 'книги', 'книг');
              $TotalBooksOnSite = $cnt . " " . getNumEnding($cnt, $books);

print "<div class='large-12 columns'>
    <ul class='breadcrumbs'>
      <li><a href='index.cfm'>Главная</a></li>
      <li class='current'><a href=''>Избранные издания</a></li>
    </ul>";    
print "<p><span class='gold'></span></p>";
print '<p style="text-align: justify; font-size: 19px;">Издательство <a href="http://kbk.ru">«Коллектор библейской книги»</a> предоставляет читателям полные тексты книг служения <a href="/?mod=watchman_nee_books#">Вочмана Ни</a> и <a href="/?mod=witness_lee_books#">Уитнесса Ли</a>. Мы искренне надеемся, что благодаря этому ресурсу богатство Христово широко распространится по всей земле ради пользы всех детей Господних.</p>';
print '<p style="text-align: justify; font-size: 19px;">На сайте опубликовано <a href="/?mod=by_alphabet#">' . $TotalBooksOnSite .  '</a>. Список опубликованных книг регулярно дополняется. Пожалуйста, читайте наши книги онлайн и сообщите своим знакомым о духовном богатстве, представленном на этом сайте.</p>';
print '<h2>Избранные брошюры</h2>
	<ul style="margin-left: 38px;">	
	<li><a href="?mb=308">Библия</a></li>
	<li><a href="?mb=593">Бог есть</a></li>	
	<li><a href="?mb=347">Христос есть Бог</a></li>
	<li><a href="?mb=349">Христово искупление и спасение</a></li>
	<li><a href="?mb=348">Христос есть Дух и жизнь</a></li>
	<li><a href="?mb=592">Смысл человеческой жизни</a></li>
	<li><a href="?mb=251">Уверенность в спасении, надежность и радость спасения</a></li>
	<li><a href="?mb=252">Драгоценная кровь Христа</a></li>
	</ul>';

print '<h2>Избранные книги</h2>
	<ul style="margin-left: 38px;">
	<li><a href="?mb=253">Домостроительство Божье</a></li>
	<li><a href="?mb=469">Всеобъемлющий Христос</a></li>
	<li><a class="contentpagetitle" href="?mb=453">Нормальная христианская вера</a></li>
	<li><a class="contentpagetitle" href="?mb=559">Нормальная христианская жизнь</a></li>
	<li><a href="?mb=254">Дерево жизни</a></li>
	<li><a href="?mb=495">Ключевое откровение о жизни в Писаниях</a></li>	
	<li><a class="contentpagetitle" href="?mb=419">Как познавать Библию</a></li>
	</ul>';

print '<h2>Серия брошюр «Спасение»</h2>
	<ul style="margin-left: 38px;">
	<li><a href="?mb=481">Бог хочет</a></li>
	<li><a href="?mb=480">Друг грешников</a></li>
	<li><a href="?mb=479">Надёжное спасение</a></li>
	<li><a href="?mb=483">Отделение для Господа</a></li>
	<li><a href="?mb=482">Поклоняться Богу, приближаясь к Нему</a></li>
	<li><a href="?mb=484">Праведное прощение</a></li></ul>';
print '<h2>Серия брошюр «Для новых верующих»</h2>
	<ul style="margin-left: 38px;">
	<li><a class="contentpagetitle" href="?mb=217">Крещение (1)</a></li>
	<li><a class="contentpagetitle" href="?mb=218">Уничтожение прошлого (2)</a></li>
	<li><a class="contentpagetitle" href="?mb=219">Отделение от мира (3)</a></li>
	<li><a class="contentpagetitle" href="?mb=220">Свидетельствовать (4)</a></li>
	<li><a class="contentpagetitle" href="?mb=221">Приводить людей к  Христу (5)</a></li>
	<li><a class="contentpagetitle" href="?mb=222">Если кто-нибудь согрешит (6)</a></li>
	<li><a class="contentpagetitle" href="?mb=223">Посвящение (7)</a></li>
	<li><a class="contentpagetitle" href="?mb=214">Исповедование устами (8)</a></li>
	<li><a class="contentpagetitle" href="?mb=215">Чтение Библии (9)</a></li>
	<li><a class="contentpagetitle" href="?mb=216">Собрания (10)</a></li>
	<li><a class="contentpagetitle" href="?mb=224">Молитва (11)</a></li>
	<li><a class="contentpagetitle" href="?mb=225">Раннее пробуждение (12)</a></li></ul>';
	/*<li><a class="contentpagetitle" href="?mb=226">Исповедь и возмещение (13)</a></li>
	<li><a class="contentpagetitle" href="?mb=227">Прощение и восстановление (14)</a></li>
	<li><a class="contentpagetitle" href="?mb=228">Избавление (15)</a></li>
	<li><a class="contentpagetitle" href="?mb=229">Наша жизнь (16)</a></li>
	<li><a class="contentpagetitle" href="?mb=230">Искать Божьей воли (17)</a></li>
	<li><a class="contentpagetitle" href="?mb=231">Правительственное прощение (18)</a></li>
	<li><a class="contentpagetitle" href="?mb=232">Божья воспитательная работа (19)</a></li>
	<li><a class="contentpagetitle" href="?mb=233">Воспитательная работа Святого Духа (20)</a></li>
	<li><a class="contentpagetitle" href="?mb=234">Противостойте дьяволу (21)</a></li>
	<li><a class="contentpagetitle" href="?mb=235">Любовь к братьям (22)</a></li>
	<li><a class="contentpagetitle" href="?mb=527">Священство (23)</a></li>	
	<li><a class="contentpagetitle" href="?mb=549">Тело Христово (24)</a></li>*/
print "</div>";
?>