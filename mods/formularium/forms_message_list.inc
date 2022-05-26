<?php
  //////////////////////////////////////////////////////////////////////////////
  // Выводит сообщения формы $id_form
  //////////////////////////////////////////////////////////////////////////////

  //нициализация переменных
  $id_form = intval($_GET['id_form']);

  //заголовок формы
  $query = "SELECT title FROM {$gl_db_prefix}forms WHERE id_form = {$id_form}";
  $f_title = stripslashes(db_select_one($query));

  //заголовок
  print "<h1>Formularium :: {$l_forms[94]} :: {$f_title}</h1>";
  print "<br />";
  print "<form name='form' action='' method='post'>";

  //формируем постраничную навигацию
  $part = intval($_GET['part']);
  if(empty($part)) $part = 1;

  if(!empty($id_form))
  {
    $query = "SELECT COUNT(id_mess)
              FROM {$gl_db_prefix}forms_messages
              WHERE id_form = {$id_form}";
  }
  else
  {
    $query = "SELECT COUNT(id_mess)
              FROM {$gl_db_prefix}forms_messages";
  }
  $num_rows = db_select_one($query);
  //if($num_rows == 0)
  //{
    //print "<p>{$l_forms[95]}</p>";
    //return;
  //}

  //верхний лимит запроса
  $up_limit    = ($part - 1) * 30;
  //количество страниц
  $gb_pages_count = ceil($num_rows / 30);
  if($num_rows > 30)
    $navig = create_navigation($gb_pages_count, "index.cfm?mod=forms_message_list&part={$part}&id_form={$id_form}", $part);

  //выводим сообщения формы id_form
  if(!empty($id_form))
  {
  	 $query = "SELECT *, DATE_FORMAT(date, '%d %b %Y %H:%i') as date_proc
	               FROM {$gl_db_prefix}forms_messages
	              WHERE id_form = {$id_form}
               ORDER BY date DESC
           LIMIT {$up_limit}, 30";
  }
  //выводим сообщения всех форм
  else
  {
    $query = "SELECT *, DATE_FORMAT(date, '%d %b %Y %H:%i') as date_proc
                FROM {$gl_db_prefix}forms_messages
               ORDER BY date DESC
               LIMIT {$up_limit}, 30";
  }
  $results = db_select($query);
  if(is_array($results))
  {
    //шапка таблицы
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'><input type='checkbox' name='sel_all' onClick='var o=this.form.elements;for(var i=0;i<o.length;i++)if(o[i].type=\"checkbox\")o[i].checked=this.checked'></td>";
      print "<td class='SiteTblTH'>{$l_forms[96]}</td>";
      print "<td class='SiteTblTH'>{$l_forms[97]}</td>";
      print "<td class='SiteTblTH' width='90'>{$l_forms[98]}</td>";
    print "</tr>";

    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $id_mess    = $results[$i]['id_mess'];
      $date        = $results[$i]['date_proc'];
      $date       = translate_data($date, $gl_months);
      $date       = str_replace(' ', '&nbsp;', $date);
      $message    = stripslashes($results[$i]['message']);
      $message    = convert_bb_tags($message, 'forum');
      if(strlen($message) > 255)
      {
        $message    = substr($message, 0, 254);
        $message    .= '...';
      }
      print "<tr>";
          //checkbox
          print "<td class='SiteTblLeft'><input type='checkbox' value='yes' name='items[{$id_mess}]'></td>";
          //дата отправки сообщения
          print "<td class='SiteTblLeft'>{$date}</td>";
          //часть текста сообщения
          print "<td class='SiteTblLeft'>{$message}</td>";
          //опции
          print "<td class='SiteTblLeft'>";
            //просмотр
            print "<a href='index.cfm?mod=forms_message_view&id_form={$id_form}&id_mess={$id_mess}&part={$part}'>{$l_forms[99]}</a><br>";
            //удалить
            print "<a href='index.cfm?mod=forms_message_del&id_form={$id_form}&id_mess={$id_mess}&part={$part}'>{$l_forms[100]}</a><br>";
          print "</td>";
        print "</tr>";
    }
    print "</table>";
    print $navig;

    //кнопка удалить все
    print "<p>{$l_forms[102]}
	            <input type='submit' class='SiteFButton' style='margin-bottom:0' name='delete_all' value='{$l_forms[103]}'>
	          </p>";

    //скрытые поля
    print "<input type='hidden' name='mod' value='forms_message_del_all'>";
 	  print "<input type='hidden' name='part' {$part}'>";
	   print "<input type='hidden' name='id_cat_prec' value='{$id_cat_prec}'>";

	   print "</form>";
  } else print "<p>{$l_forms[101]}</p>";

  //вернуться в список форм
  print "<br><p><a class='Mustgreen' href='index.cfm?mod=forms_list'>{$l_forms[104]}</a></p>";
?>