<?php

  //////////////////////////////////////////////////////////////////////////////
  // Выводит список e-mail адресов, на которые буудт отсылаться сообщения.
  //////////////////////////////////////////////////////////////////////////////

  //инициализация переменных
  $id_form = intval($_GET['id_form']);

  //заголовок формы
  $query = "SELECT title FROM {$gl_db_prefix}forms WHERE id_form = {$id_form}";
  $f_title = stripslashes(db_select_one($query));

  //заголовок
  print "<h1>{$l_forms[131]} :: {$f_title}</h1>";

  //меню, добавить
  print "<br><p><a class='Mustred' href='index.cfm?mod=forms_email_add&id_form={$id_form}'>{$l_forms[132]}</a></p><br>";

  //выводим список адресов
  $query = "SELECT *
              FROM {$gl_db_prefix}forms_emails_to
             WHERE id_form = {$id_form}";
  $results = db_select($query);
  if(is_array($results))
  {
    //шапка таблицы
    print "<table class='SiteTbl' width='300' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH'>{$l_forms[133]}</td>";
      print "<td class='SiteTblTH' width='90'>{$l_forms[134]}</td>";
    print "</tr>";
    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $id_email     = $results[$i]['id_email'];
      $email        = $results[$i]['email'];

      print "<tr>";
          //e-mail д
          print "<td class='SiteTblLeft'>{$email}</td>";
          print "<td class='SiteTblLeft'>";
            //параметры
            print "<a href='index.cfm?mod=forms_email_edit&id_form={$id_form}&id_email={$id_email}'>{$l_forms[135]}</a><br>";
            //удалить
            print "<a href='index.cfm?mod=forms_email_del&id_form={$id_form}&id_email={$id_email}'>{$l_forms[136]}</a><br>";
          print "</td>";
        print "</tr>";
    }
    print "</table>";
  } else print "<p>{$l_forms[137]}</p>";

  //ссылка возвращения в список форм
  print "<br><p><a class='Mustgreen' href='index.cfm?mod=forms_list'>{$l_forms[138]}</a></p>";
  //инфо
  /*print "<h2>{$l_swordfish[32]}</h2>";
  print "<p>{$l_swordfish[33]}</p>";*/

?>