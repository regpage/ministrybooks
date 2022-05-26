<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль выводит список зарегистрированных пользователей в админке
  //////////////////////////////////////////////////////////////////////////////


  //выбираем столбец, по которому сортируются пользователи
  $sort = $_GET['sort'];
  $sort = get_sort($sort, 'name');

  //выбираем порядок сортировки значений
  $mode = $_GET['mode'];
  $mode = get_mode($mode, 'ASC');
  $old_mode = $mode;
  if($mode == 'ASC') $mode = 'DESC'; else $mode = 'ASC';

  //заголовок
  print "<h1>{$l_user[1]}</h1>";


  //////////////////////////////////////////////////////////////////////////////
  //поиск пользователя, обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $srch_us_name = correct_input($_POST['srch_us_name']);

    $query = "SELECT id_user, login, name, `group`
	               FROM {$gl_db_prefix}users
	            WHERE name = '{$srch_us_name}'
                OR login = '{$srch_us_name}'";
    $results  = db_select($query);
  }

  //////////////////////////////////////////////////////////////////////////////
  //выборка пользователей
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
	     print "<p>{$l_user[2]}</p>";
	     return;
	   }

	   //верхний лимит запроса
	   $up_limit    = ($part - 1) * 30;

	   //количество страниц
	   $gb_pages_count = ceil($num_rows / 30);
	   if($num_rows > 30)
	     $navig = create_navigation($gb_pages_count, "?adm=users_list&part={$part}&mode={$old_mode}&sort={$sort}", $part);

    //формируем запрос на выборку пользователей
    if($sort != 'name')
      $new_sort = $sort.'`, `name';
    else
      $new_sort = $sort;
	   $query = "SELECT *, DATE_FORMAT(reg_date, '%d %b %Y %H:%i') as reg_date_frm
	               FROM {$gl_db_prefix}users
	            ORDER BY `{$new_sort}` {$mode}
	            LIMIT {$up_limit}, 30";
	   $results = db_select($query);
  } //else


  //////////////////////////////////////////////////////////////////////////////
  //форма поиска пользователя по имени
  //////////////////////////////////////////////////////////////////////////////

  print "<form name='srch_form' method='post'>";
    print "<table class='' cellspacing='0' cellpadding='0' border='0'>";
      print "<tr>";
        print "<td class='SiteFCapt'>{$l_user[3]}</td>";
        print "<td class='SiteFCapt'><input type='text' class='SiteFInputS' name='srch_us_name'></td>";
        print "<td class='SiteFCapt'><input type='submit' class='button' name='us_search' value='{$l_user[4]}'></td>";
      print "</tr>";
    print "</table>";
    print "<input type='hidden' name='adm' value='users_list'>";
  print "</form>";
          print "<a class='button_us' href='{$gl_site}?adm=users_add'>{$l_user[44]}</a><br/><br/>";
  //////////////////////////////////////////////////////////////////////////////
  //сообщение о том, что не найден ни один пользователь с таким именем
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['us_search']))
  {
  	 if(!is_array($results))
	     {
        if(!empty($srch_us_name))
          print "<p>{$l_user[5]} {$srch_us_name}. <br><a href='?adm=users_list'>{$l_adm_gen[11]}</a></a>";
        else
          print "<div class='mege'><p>{$l_user[6]} <br><a href='?adm=users_list'>{$l_adm_gen[11]}</a></p></div>";
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
  //формируем список пользователей
  //////////////////////////////////////////////////////////////////////////////

  if(is_array($results))
  {
    //постраничная навигация
    print $navig;

    //таблица пользователей
    print "<table width='650' class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    print "<form action='' method='post' name='users_list'>";
    print "<tr>";
      print "<td class='SiteTblTH'>&nbsp;</td>";
      print "<td class='SiteTblTH'>&nbsp;</td>";
      print "<td class='SiteTblTH'><a href='?adm=users_list&sort=name&mode={$mode}'>{$l_user[7]}</a></td>";
      print "<td class='SiteTblTH'><a href='?adm=users_list&sort=group&mode={$mode}'>{$l_user[8]}</a></td>";
      //выбираем доп. поля
      if(is_array($sup_fields))
      {
      	 foreach($sup_fields as $key => $value)
      	   print "<td class='SiteTblTH'><a href='?adm=users_list&sort={$key}&mode={$mode}'>{$value}</a></td>";
      }
      print "<td class='SiteTblTH'><a href='?adm=users_list&sort=reg_date&mode={$mode}'>{$l_user[40]}</a></td>";
      print "<td class='SiteTblTH' style='width:150px'>{$l_user[11]}</td>";
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

      $reg_date = stripslashes($results[$i]['reg_date_frm']);

      print "<tr>";
        print "<td class='SiteTblLeft'><input type='checkbox' name='to_del[{$results[$i]['id_user']}]' value='yes'></td>";
        print "<td class='SiteTblLeft'>".($i + 1)."</td>";
        print "<td class='SiteTblLeft'>".stripslashes($results[$i]['name'])."</td>";
        print "<td class='SiteTblLeft'>".stripslashes($results[$i]['group'])."</td>";
        if(is_array($sup_fields))
		{
		   foreach($sup_fields as $key => $value)
		    print "<td class='SiteTblLeft'>".stripslashes($results[$i][$key])."&nbsp;</td>";
		}
        print "<td class='SiteTblLeft'>{$reg_date}</td>";
        print "<td class='SiteTblLeft'>";
          //профиль
          print "<a href='{$gl_site}?adm=users_edit&part={$part}&sort={$sort}&mode={$old_mode}&id_user={$results[$i]['id_user']}'>{$l_user[12]}</a><br>";
          //поменять логин и пароль
          print "<a href='{$gl_site}?adm=users_chpsw&part={$part}&id_user={$results[$i]['id_user']}'>{$l_user[13]}</a><br>";
          //поменять группу
          print "<a href='{$gl_site}?adm=users_chgroup&part={$part}&sort={$sort}&mode={$old_mode}&id_user={$results[$i]['id_user']}'>{$l_user[14]}</a><br>";
          //удалить
          print "<a href='{$gl_site}?adm=users_del&id_user={$results[$i]['id_user']}&part={$part}&sort={$sort}&mode={$old_mode}'>{$l_user[15]}</a>";
        print "</td>";
      print "</tr>";
    }

    print "</table>";

    //кнопка удалить
    print "<table class='' cellspacing='0' cellpadding='0' border='0'>";
      print "<tr>";
        print "<td class=''><input type='submit' class='button' style='width:200px' name='del' value='{$l_user[16]}'></td>";
      print "</tr>";
    print "</table>";

    //скрытые поля
    print "<input type='hidden' name='adm' value='users_del_all'>";
    print "<input type='hidden' name='sort' value='{$sort}'>";
    print "<input type='hidden' name='mode' value='{$mode}'>";
    print "<input type='hidden' name='part' value='{$part}'>";

    print "</form>";

    //удаление неактивированных аккаунтов пользователей
    print "<br /><br /><h2>{$l_user[39]}</h2>";
    print "<form action='?act=users_del_inactivated' method='post'>";
      print "<table class='' cellspacing='0' cellpadding='0' border='0'>";
      print "<tr>";
        print "<td class='SiteFCapt'>{$l_user[38]}</td>";
        print "<td class=''><input type='submit' class='button' name='confirm' value='{$l_gen[28]}'></td>";
      print "</tr>";
    print "</table>";
    print "</form>";

    //постраничная навигация
    print $navig;
  }
?>