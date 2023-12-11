<?php
   //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Модуль изменяет пароль пользователя $id_user
  //////////////////////////////////////////////////////////////////////////////


  $code = intval($_GET['code']);
  $id_user = intval($_GET['id_user']);

  print "<h1>{$l_users[53]}</h1>";

  //выбираем пароль из таблицы новых паролей
  $new_psw = db_select_one("SELECT new_psw FROM {$gl_db_prefix}new_passwords WHERE id_user={$id_user} AND code = {$code}");
  if(!$new_psw)
   {  print "<p>{$l_users[54]}</p>"; return; }

  //меняем пароль
  $resrowsupdate = db_update("UPDATE {$gl_db_prefix}users SET psw = '{$new_psw}' WHERE id_user = {$id_user}");

  if($resrowsupdate > 0)
    print "<p>{$l_users[55]}</p>";
  else
    print "<p>{$l_users[56]}</p>";


?>