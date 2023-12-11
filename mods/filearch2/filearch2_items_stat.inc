<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Страница статистики скачиваний
  //////////////////////////////////////////////////////////////////////////////


  //инициализация переменных
  $id_cat = intval($_GET['id_cat']);

  //выбираем параметры категории
		if($id_cat != 0)
		{
	$query = "SELECT * FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat} AND if_arch_user = {$gl_id_user}";
		  $results   = db_select($query);
		  $cat_title = stripslashes($results[0]['title']);
		  $cat_title = "{$cat_title} :: {$l_filearch2[60]}";
  }
  else
  {
  	 $cat_title = $l_filearch2[82];
  }

  $path      = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/";

  //заголовок
  print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'><tr><td class=''><div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div><h3>{$cat_title}</h3></td></tr></table>";


  //выбираем файлы
		if(!empty($id_cat))
		{
				$query = "SELECT *, DATE_FORMAT(date, '%d %b %Y %H:%m') as date_formatted
				            FROM {$gl_db_prefix}filearch2_items
				           WHERE id_cat = {$id_cat}
				           ORDER BY title";
  }
  else
  {
  	 $query = "SELECT *, DATE_FORMAT(date, '%d %b %Y %H:%m') as date_formatted
				            FROM {$gl_db_prefix}filearch2_items
				           ORDER BY title";
  }

  $results = db_select($query);

  if(is_array($results))
  {
    //шапка таблицы
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH'>{$l_filearch2[61]}</td>";
      print "<td class='SiteTblTH'>today</td>";
      print "<td class='SiteTblTH'>yest</td>";
      print "<td class='SiteTblTH'>month</td>";
      print "<td class='SiteTblTH'>year</td>";
      print "<td class='SiteTblTH'>total</td>";
      print "<td class='SiteTblTH'>{$l_filearch2[62]}</td>";
    print "</tr>";

    $cnt = count($results);

    for($i = 0; $i < $cnt; $i++)
    {
      $id_item = $results[$i]['id_item'];

      $title  = stripslashes($results[$i]['title']);

      $date  = translate_data($results[$i]['date_formatted'], $gl_months);

      //выбираем статистику за сегодня
      $today = db_select_one("SELECT COUNT(id_stat )
																					           FROM {$gl_db_prefix}filearch2_stat
																					           WHERE (TO_DAYS(date) BETWEEN TO_DAYS(NOW())-1 AND TO_DAYS(NOW()))
																				              AND id_item = {$id_item}");
						if(!empty($today))
						  $today = "<a class='chap' href='?mod=filearch2_items_detstat&amp;id_cat={$id_cat}&amp;id_item={$id_item}&amp;period=today'>{$today}</a>";

      //выбираем статистику за вчера
      $yest   = db_select_one("SELECT COUNT(id_stat )
																					           FROM {$gl_db_prefix}filearch2_stat
																					           WHERE (TO_DAYS(date) BETWEEN TO_DAYS(NOW())-2 AND TO_DAYS(NOW())-1)
																				              AND id_item = {$id_item}");
      if(!empty($yest))
						  $yest = "<a class='chap' href='?mod=filearch2_items_detstat&amp;id_cat={$id_cat}&amp;id_item={$id_item}&amp;period=yest'>{$yest}</a>";

						//выбираем статистику за месяц
      $month   = db_select_one("SELECT COUNT(id_stat )
																					           FROM {$gl_db_prefix}filearch2_stat
																					           WHERE now() - INTERVAL 1 MONTH < date
																				              AND id_item = {$id_item}");
      if(!empty($month))
						  $month = "<a class='chap' href='?mod=filearch2_items_detstat&amp;id_cat={$id_cat}&amp;id_item={$id_item}&amp;period=month'>{$month}</a>";

						//выбираем статистику за год
						$year   = db_select_one("SELECT COUNT(id_stat )
																					           FROM {$gl_db_prefix}filearch2_stat
																					           WHERE NOW() - INTERVAL 1 YEAR < date
																				              AND id_item = {$id_item}");

						//выбираем статистику, всего
						$total   = db_select_one("SELECT COUNT(id_stat )
																					           FROM {$gl_db_prefix}filearch2_stat
																					           WHERE id_item = {$id_item}");
      print "<tr>";
          //название файла
          print "<td class='SiteTblLeft'>{$title}</td>";
          //статистика, сегодня
          print "<td class='SiteTblCenter'><span class='Mustgreen'><b>{$today}</b></span></td>";
          //статистика, вчера
          print "<td class='SiteTblCenter'><span class='Mustgreen'><b>{$yest}</b></span></td>";
          //статистика, месяц
          print "<td class='SiteTblCenter'><span class='Mustgreen'><b>{$month}</b></span></td>";
          //статистика, год
          print "<td class='SiteTblCenter'><span class='Mustgreen'><b>{$year}</b></span></td>";
          //статистика, всего
          print "<td class='SiteTblCenter'><span class='Mustgreen'><b>{$total}</b></span></td>";
		        //дата добавления
          print "<td class='SiteTblLeft'>{$date}</td>";
        print "</tr>";
    }
    print "</table>";
                //нет ни одного файла
  } else print "<p>{$l_filearch2[50]}</p>";

  //ссылка назад

print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'><tr><td class=''>";
  if($id_cat != 0)
    print "<p>";
  print "<a class='chap' href='?mod=filearch2_items_list&amp;id_cat={$id_cat}'>{$l_filearch2[1002]}</a><br />";
  print "<a class='chap' href='?mod=filearch2_cats_list'>{$l_filearch2[1000]}</a>";
    print "</p>";

  //полезная информация
  
  print "<h3>{$l_filearch2[63]}</h3>";
  print "{$l_filearch2[64]}";
  print "</td></tr></table>";
  print "<br />";




?>