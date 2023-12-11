<?php

  //////////////////////////////////////////////////////////////////////////////
  //Модуль авторизирует пользователя через форму auth_form.inc
  //////////////////////////////////////////////////////////////////////////////


  //инициализация и фильтрация данных
  $auth_login = $_POST['login'];
  $auth_psw   = $_POST['psw'];
  $save_psw   = $_POST['save_psw'];
  if($save_psw != 'yes')
    $save_psw = 'no';
  $auth_login    = strtolower($auth_login);
  $auth_psw      = strtolower($auth_psw);
  $auth_pg    = $_POST['auth_pg'];
  $auth_pg    = preg_replace("#[^a-zA-Z0-9\/_\.?=&]#i", "", $auth_pg);

  //сообщение о неверном логине и пароле
  $message = "{$l_auth[1]} <a href='{$auth_pg}'>{$l_auth[2]}</a>";
  if(!preg_match("/^[-0-9a-z_]{2,}$/i", $auth_login))
  {
    print $message;
    exit;
  }
  if(!preg_match("/^[-0-9a-z_]{5,}$/i", $auth_psw))
  {
    print $message;
    exit;
  }

  //проверка логина и пароля
  $query = "SELECT id_user, `group`, name
              FROM {$gl_db_prefix}users
             WHERE login = '{$auth_login}'
               AND psw   = md5('{$auth_psw}')
               AND activated = 'yes'";
  $results = db_select($query);
  if(is_array($results))
  {

      $id_user   = $results[0]['id_user'];
      $group     = stripslashes($results[0]['group']);
      $name      = stripslashes($results[0]['name']);


  } else { print $message; exit; }

  //регистрация ключевых пользовательских переменных в сессии и  cookie
  $_SESSION["{$gl_site_name}_gl_id_user"] = $id_user;
  $_SESSION["{$gl_site_name}_gl_group"]   = $group;
  $_SESSION["{$gl_site_name}_gl_us_name"]   = $name;
  if($save_psw == 'yes')
  {
    setcookie ("{$gl_site_name}_auth_login", $auth_login, time()+3600*24*7*31);
    setcookie ("{$gl_site_name}_auth_psw",   md5($auth_psw),   time()+3600*24*7*31);
  }

  //сообщение об успешной авторизации
  //include("{$gl_path_to_engine}auth/auth_succ.inc");

  echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$auth_pg}'></HEAD></HTML>";
  exit;





?>