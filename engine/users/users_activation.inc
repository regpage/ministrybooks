<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Модуль активации аккаунта
  //////////////////////////////////////////////////////////////////////////////

  $code = preg_replace("/[^a-z0-9]/", '', $_GET['code']);
  $id_user = intval($_GET['id_user']);

  print "<h1>{$l_users[42]}</h1>";

  $activated = db_select_one("SELECT id_user FROM {$gl_db_prefix}users WHERE id_user = {$id_user} AND activated = 'yes'");
  if($activated)
  {
  	 //Вы уже активировали свой аккаунт.
  	 print "<p>{$l_users[43]}</p>";
  	 return;
  }

  $login = stripslashes(db_select_one("SELECT login FROM {$gl_db_prefix}users WHERE  id_user={$id_user}"));
  if(md5($login) == $code)
  {
    //активируем пользователя
    db_update("UPDATE {$gl_db_prefix}users SET activated = 'yes' WHERE id_user={$id_user}");

    $login = db_select_one("SELECT login FROM {$gl_db_prefix}users WHERE id_user = {$id_user}");

    //Ваш аккаунт активирован.
    print "<p>{$l_users[44]}</p>";
  }
  else
  {  //Не удалось обнаружить запись о регистрации.
    print "<p>{$l_users[45]}</p>";
  }









?>