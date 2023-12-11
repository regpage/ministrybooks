<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Модуль выводит список зарег. пользователей в пользовательской части
  //////////////////////////////////////////////////////////////////////////////


  //определяем столбец, по которому будут сортироваться пользователи
  $sort = $_GET['sort'];
  $sort = get_sort($sort, 'name');

  //определяем порядок сортировки значений
  $mode = $_GET['mode'];
  $mode = get_mode($mode, 'ASC');
  $old_mode = $mode;
  if($mode == 'ASC') $mode = 'DESC'; else $mode = 'ASC';

  //заголовок
  print "<h1>{$l_users[1]}</h1>";


  //////////////////////////////////////////////////////////////////////////////
  // поиск пользователя, обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $srch_us_name = correct_input($_POST['srch_us_name']);

    $query = "SELECT id_user, login, name, `group`, city, firm
	               FROM {$gl_db_prefix}users
	            WHERE name = '{$srch_us_name}'
                OR login = '{$srch_us_name}'";
    $results  = db_select($query);

  }


  //////////////////////////////////////////////////////////////////////////////
  // выборка пользователей
  //////////////////////////////////////////////////////////////////////////////

  else //if(!empty($_POST['us_search']))
  {
    //формируем постраничную навигацию
    $part = intval($_GET['part']);
	   if(empty($part)) $part = 1;

	   $query = "SELECT COUNT(id_user)
	             FROM {$gl_db_prefix}users";
	   $num_rows = db_select_one($query);
	   if($num_rows == 0)
	   {
	     print "<p>{$l_users[2]}</p>";
	     return;
	   }

	   //верхний лимит запроса
	   $up_limit    = ($part - 1) * 30;

	   //количество страниц
	   $pages_count = ceil($num_rows / 30);
	   if($num_rows > 30)
	     $navig = create_navigation($pages_count, "?mod=users_list_pub&part={$part}&mode={$old_mode}&sort={$sort}", $part);

    //выбираем пользователей
    //if($sort != 'name')
    //  $new_sort = $sort.'`, `name';
    //else

    $new_sort = $sort;
	   $query = "SELECT *
	               FROM {$gl_db_prefix}users
	            ORDER BY `{$new_sort}` {$mode}
	            LIMIT {$up_limit}, 30";
	   $results = db_select($query);
  }


  //////////////////////////////////////////////////////////////////////////////
  // форма поиска пользователя по имени
  //////////////////////////////////////////////////////////////////////////////

  print "<form name='srch_form' method='post'>";
    print "<table class='SiteTbl' style='border:none' cellspacing='0' cellpadding='0' border='0'>";
      print "<tr>";
        print "<td class='SiteFCapt'>{$l_users[3]}&nbsp;</td>";
        print "<td class=''><input type='text' class='SiteFInputS' name='srch_us_name'>&nbsp;</td>";
        print "<td class=''><input type='submit' class='SiteFButton' name='us_search' value='{$l_users[4]}'></td>";
      print "</tr>";
    print "</table>";
    print "<input type='hidden' name='mod' value='users_list_pub'>";
  print "</form>";


  //////////////////////////////////////////////////////////////////////////////
  // сообщение о том, что не найден ни один пользователь с таким именем
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['us_search']))
  {
  	 if(!is_array($results))
	     {
        if(!empty($srch_us_name))
          print "<p>{$l_users[5]} {$srch_us_name}. <br><a href='?mod=users_list'>{$l_users[7]}</a><br /><br />";
        else
          print "<p>{$l_users[6]}<br><a href='?mod=users_list_pub'>{$l_users[7]}</a></p><br /><br />";
        return;
      }
  }


  //////////////////////////////////////////////////////////////////////////////
  // формируем ассоциативный массив из дополнительных полей
  //////////////////////////////////////////////////////////////////////////////

  $results_fld = db_select("SELECT * FROM {$gl_db_prefix}regform_fields WHERE in_users_list = 'yes' ORDER BY pos");
  if(is_array($results_fld))
  {
    $cnt = count($results_fld);
    for($i = 0; $i < $cnt; $i++)
    {
      $field_name = $results_fld[$i]['field_name'];
      $field_caption = stripslashes($results_fld[$i]['caption']);

      $sup_fields[$field_name] = $field_caption;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // формируем список зарегистрированных пользователей
  //////////////////////////////////////////////////////////////////////////////

  if(is_array($results))
  {
    //постраничная навигация
    print $navig;

    //шапка таблицы
    print "<table class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    print "<form action='' method='post' name='users_list'>";

    //шапка таблицы
    print "<tr>";
      print "<td class='SiteTblTH'>&nbsp;</td>";
      print "<td class='SiteTblTH'><a href='?mod=users_list_pub&sort=name&mode={$mode}'>{$l_users[8]}</a></td>";
      print "<td class='SiteTblTH'><a href='?mod=users_list_pub&sort=group&mode={$mode}'>{$l_users[9]}</a></td>";
      //выбираем доп. поля
      if(is_array($sup_fields))
      {
      	 foreach($sup_fields as $key => $value)
      	   print "<td class='SiteTblTH'><a href='?mod=users_list_pub&sort={$key}&mode={$mode}'>{$value}</a></td>";
      }
      print "<td class='SiteTblTH' style='width:150px'>{$l_users[12]}</td>";
    print "</tr>";

    $cnt = count($results);

    for($i = 0; $i < $cnt; $i++)
    {
      $city = stripslashes($results[$i]['city']);
      if(empty($city))
        $city = '&nbsp;';

      $firm = stripslashes($results[$i]['firm']);
      if(empty($firm))
        $firm = '&nbsp;';

      print "<tr>";
        //порядковый номер
        print "<td class='SiteTblLeft''>".($i + 1)."</td>";
        //имя пользователя
        print "<td class='SiteTblLeft'>".stripslashes($results[$i]['name'])."</td>";
        //группа
        print "<td class='SiteTblLeft'>".stripslashes($results[$i]['group'])."</td>";
        //доп. поля
        if(is_array($sup_fields))
		      {
		      	 foreach($sup_fields as $key => $value)
		      	   print "<td class='SiteTblLeft'>".stripslashes($results[$i][$key])."&nbsp;</td>";
		      }
        //опции
        print "<td class='SiteTblLeft'>";
          print "<a href='?mod=users_descr&part={$part}&sort={$sort}&mode={$old_mode}&id_user={$results[$i]['id_user']}'>{$l_users[13]}</a><br>";
        print "</td>";
      print "</tr>";
    }

    print "</table>";

   //скрытые поля
    print "<input type='hidden' name='sort' value='{$sort}'>";
    print "<input type='hidden' name='mode' value='{$mode}'>";
    print "<input type='hidden' name='part' value='{$part}'>";
    print "</form>";

    //постраничная навигация
    print $navig;
  }





?>