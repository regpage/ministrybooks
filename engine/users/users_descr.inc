<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль выводит подробную информацию о пользователе (профиль пользователя)
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //Инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $sort = correct_input($_POST['sort']);
  if(empty($sort))
    $sort = correct_input($_GET['sort']);

  $mode = correct_input($_POST['mode']);
  if(empty($mode))
    $mode = correct_input($_GET['mode']);

  $id_user = intval($_POST['id_user']);
  if(empty($id_user))
    $id_user = intval($_GET['id_user']);

  $part = intval($_POST['part']);
  if(empty($part))
    $part = intval($_GET['part']);


  //////////////////////////////////////////////////////////////////////////////
  //Выборка информации о пользователе id_user
  //////////////////////////////////////////////////////////////////////////////

  $query = "SELECT *
              FROM {$gl_db_prefix}users
             WHERE id_user = {$id_user}";
  $results = db_select($query);
  if(is_array($results))
  {
    foreach($results[0] as $key => $value)
      if(empty($value))
        $results[0][$key] = '&nbsp;';

    $us_name =  stripslashes($results[0]['name']);
    $tel =  stripslashes($results[0]['tel']);
    $email =  stripslashes($results[0]['email']);
    $www =  stripslashes($results[0]['www']);
    $icq =  stripslashes($results[0]['icq']);
    $city =  stripslashes($results[0]['city']);
    $firm =  stripslashes($results[0]['firm']);
    $info =  stripslashes($results[0]['info']);
  }


  //////////////////////////////////////////////////////////////////////////////
  //Выборка информации о пользователе id_user
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_users[28]}</h1>";

  //выводим таблицу
  print "<br /><br />";
  print "<table class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    //имя
    print "<tr>";
      print "<td class='SiteTblLeft'><b>{$l_users[29]}:</b></td>";
      print "<td class='SiteTblLeft'>{$us_name}</td>";
    print "</tr>";
    //телефон
    print "<tr>";
      print "<td class='SiteTblLeft'><b>{$l_users[30]}:</b></td>";
      print "<td class='SiteTblLeft'>{$tel}</td>";
    print "</tr>";
    //e-mail
    //print "<tr>";
    //  print "<td class='SiteTblLeft'><b>{$l_users[31]}:</b></td>";
    //  print "<td class='SiteTblLeft'>{$email}</td>";
    //print "</tr>";
    //www
    print "<tr>";
      print "<td class='SiteTblLeft'><b>{$l_users[32]}:</b></td>";
      print "<td class='SiteTblLeft'><a href='{$www}' target='_blank'>{$www}</a></td>";
    print "</tr>";
    //icq
    print "<tr>";
      print "<td class='SiteTblLeft'><b>{$l_users[33]}:</b></td>";
      print "<td class='SiteTblLeft'>{$icq}</td>";
    print "</tr>";
    //город
    print "<tr>";
      print "<td class='SiteTblLeft'><b>{$l_users[34]}:</b></td>";
      print "<td class='SiteTblLeft'>{$city}</td>";
    print "</tr>";
    //организация
    print "<tr>";
      print "<td class='SiteTblLeft'><b>{$l_users[35]}:</b></td>";
      print "<td class='SiteTblLeft'>{$firm}</td>";
    print "</tr>";
    //инфо
    print "<tr>";
      print "<td class='SiteTblLeft'><b>{$l_users[36]}:</b></td>";
      print "<td class='SiteTblLeft'>{$info}</td>";
    print "</tr>";
  print "</table>";

  //ссылка в список пользователей
  print "<br /><p><a href='?mod=users_list_pub&part={$part}&sort={$sort}&mode={$mode}'>{$l_users[37]}</a></p>";
?>