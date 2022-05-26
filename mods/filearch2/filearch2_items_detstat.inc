<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Модуль выводит подробдную статистику за период $period по файлу $id_item
  //////////////////////////////////////////////////////////////////////////////


  //инициализация переменных
  $id_item = intval($_GET['id_item']);
  $id_cat  = intval($_GET['id_cat']);
  $period  = $_GET['period'];
  $period_possib = array('today', 'yest', 'month');
  if(!in_array($period, $period_possib))
    $period = 'today';

  //выбираем параметры файла
  $query   = "SELECT * FROM {$gl_db_prefix}filearch2_items WHERE id_item = {$id_item}";
  $results = db_select($query);
  $title    = stripslashes($results[0]['title']);

  $path      = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/";

  //формируем заголовок
  switch($period)
  {
  	 case 'today' :  $per_capt = $l_filearch2[66] ;  break;
  	 case 'yest'  :  $per_capt = $l_filearch2[67] ;  break;
  	 case 'month' :  $per_capt = $l_filearch2[68] ;  break;
  }

  $title    = str_replace("{file}",   $title,    $l_filearch2[65]);
  $title    = str_replace("{period}", $per_capt, $title);


  //заголовок
  print "<h3>{$title}</h3>";
  print "<br />";

  //формируем запрос на выбор ip-адресов
  if($period == 'today')
  {
    $query = "SELECT `ip`, DATE_FORMAT(date, '%d %b %Y, %H:%i') as date_ip
					           FROM {$gl_db_prefix}filearch2_stat
					          WHERE (TO_DAYS(date) BETWEEN TO_DAYS(NOW())-1 AND TO_DAYS(NOW()))
				             AND id_item = {$id_item}
		          GROUP BY ip
		          ORDER BY date";
  }

  if($period == 'yest')
  {
    $query = "SELECT `ip`, DATE_FORMAT(date, '%d %b %Y, %H:%i') as date_ip
					           FROM {$gl_db_prefix}filearch2_stat
					          WHERE (TO_DAYS(date) BETWEEN TO_DAYS(NOW())-2 AND TO_DAYS(NOW())-1)
				             AND id_item = {$id_item}
		             GROUP BY ip
		          ORDER BY date";
  }

  if($period == 'month')
  {

   $query = "SELECT `ip`, DATE_FORMAT(date, '%d %b %Y, %H:%i') as date_ip
					           FROM {$gl_db_prefix}filearch2_stat
					          WHERE now() - INTERVAL 1 MONTH < date
				             AND id_item = {$id_item}
            GROUP BY ip
		          ORDER BY date";
  }

  $results = db_select($query);

  if(is_array($results))
  {
		  $cnt = count($results);

    //шапка таблицы
    print "<table class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH'>ip</td>";
      print "<td class='SiteTblTH'>{$l_filearch2[69]}</td>";
      print "<td class='SiteTblTH'>{$l_filearch2[70]}</td>";
    print "</tr>";

		  for($i = 0; $i < $cnt; $i++)
		  {
      $ip = $results[$i]['ip'];

      if($period == 'today')
      {
		      $count = db_select_one("SELECT COUNT(id_stat)
																                  FROM {$gl_db_prefix}filearch2_stat
																                 WHERE (TO_DAYS(date) BETWEEN TO_DAYS(NOW())-1 AND TO_DAYS(NOW()))
																                   AND ip = '{$ip}'");
      }

      if($period == 'yest')
      {
		      $count = db_select_one("SELECT COUNT(id_stat)
																                  FROM {$gl_db_prefix}filearch2_stat
																                 WHERE (TO_DAYS(date) BETWEEN TO_DAYS(NOW())-2 AND TO_DAYS(NOW())-1)
																                   AND ip = '{$ip}'");
      }

      if($period == 'month')
      {
		      $count = db_select_one("SELECT COUNT(id_stat)
																                  FROM {$gl_db_prefix}filearch2_stat
																                 WHERE now() - INTERVAL 1 MONTH < date
																                   AND ip = '{$ip}'");
      }

      $date_ip = stripslashes($results[$i]['date_ip']);
      $date_ip = translate_data($date_ip, $gl_months);

      //ссылка на whois сервер
      $ip = "<a class='chap' href='http://www.ripe.net/perl/whois/?form_type=simple&full_query_string=&searchtext={$ip}&do_search=Search' target='_blank'>{$ip}</a>";

      print "<tr>";
        //ip
        print "<td class='SiteTblLeft'>{$ip}</td>";
        //количество скачиваний
        print "<td class='SiteTblCenter' width='50'>{$count}</td>";
        //дата
        print "<td class='SiteTblLeft'>{$date_ip}</td>";
      print "</tr>";
		  }

		  print "</table>";
  }

  //ссылка назад
  print "<br />";
  print "<p><a class='chap' href='?mod=filearch2_items_stat&amp;id_cat={$id_cat}&amp;id_item={$id_item}'>{$l_filearch2[1001]}</a></p>";
  print "<p><a class='chap' href='?mod=filearch2_items_list&amp;id_cat={$id_cat}'>{$l_filearch2[1002]}</a></p>";
  print "<p><a class='chap' href='?mod=filearch2_cats_list'>{$l_filearch2[1000]}</a></p>";
  print "<br />";
  print "<br />";
?>