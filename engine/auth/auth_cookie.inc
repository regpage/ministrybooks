<?php
  //////////////////////////////////////////////////////////////////////////////
  //Модуль авторизирует пользователя через COOKIE
  //////////////////////////////////////////////////////////////////////////////


  //инициализация и фильтрация данных
  $auth_login = $_COOKIE["{$gl_site_name}_auth_login"];
  $auth_psw   = $_COOKIE["{$gl_site_name}_auth_psw"];
  $auth_login    = strtolower($auth_login);
  $auth_psw      = strtolower($auth_psw);

  if(!preg_match("/^[-0-9a-z_]{2,}$/i", $auth_login))
  {
    return;
  }
  if(!preg_match("/^[-0-9a-z_]{5,}$/i", $auth_psw))
  {
    return;
  }

  //проверка логина и пароля
  $query = "SELECT id_user, `group`, name
              FROM {$gl_db_prefix}users
             WHERE login = '{$auth_login}'
               AND psw   = '{$auth_psw}'
               AND activated = 'yes'";
  $results = db_select($query);
  if(is_array($results))
  {

      $id_user   = $results[0]['id_user'];
      $group     = stripslashes($results[0]['group']);
      $name      = stripslashes($results[0]['name']);

  } else return;

  //регистрация важных пользовательских переменных в сессии
  $_SESSION["{$gl_site_name}_gl_id_user"] = $id_user;
  $_SESSION["{$gl_site_name}_gl_group"]   = $group;
  $_SESSION["{$gl_site_name}_gl_us_name"]   = $name;

  //регистрация важных пользовательских переменных в cookie
  setcookie ("{$gl_site_name}_auth_login", $auth_login, time()+3600*24*7*31);
  setcookie ("{$gl_site_name}_auth_psw",   $auth_psw,   time()+3600*24*7*31);

?>