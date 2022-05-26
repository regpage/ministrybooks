<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль регистрирует нового пользователя на сайте
  //////////////////////////////////////////////////////////////////////////////


  //закрываем доступ к модулю для уже зарегистрированных пользователей
  //if(!empty($gl_id_user))
   // { print '<h1>Caution</h1><p>Извините, но вы уже заригистрированы</p>'; return;}
 //if($_SESSION['already_registered'] == 'yes')
  // { print $l_users[47]; return;}

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
  // Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //фильтрация данных формы
     
    $login      = $_POST['login'];
    $psw        = $_POST['psw'];
    $psw_conf   = $_POST['psw_conf'];
    $name      = strtolower($name);
    $login      = strtolower($login);
    $psw        = strtolower($psw);
    $psw_conf   = strtolower($psw_conf);

    $us_name = strip_tags(correct_input($_POST['us_name']));
    //$tel     = strip_tags(correct_input($_POST['tel']));
    $email   = strip_tags(correct_input($_POST['email']));

    //$icq = strip_tags(correct_input($_POST['icq']));
    //$www = strip_tags(correct_input($_POST['www']));

    $info = strip_tags(correct_input($_POST['info']));
    //$firm = strip_tags(correct_input($_POST['firm']));
    //$city = strip_tags(correct_input($_POST['city']));

    $subscribe = $_POST['subscribe']; if($subscribe != 'yes') $subscribe = 'no';

    if(empty($us_name))
      $errors[] = $l_user[18];
    if(!preg_match("/^[_0-9a-z]{2,}$/", $login))
      $errors[] = $l_user[24];
    if(!preg_match("/^[_0-9a-z]{5,}$/", $psw))
      $errors[] = $l_user[25];
    if($psw != $psw_conf)
      $errors[] = $l_user[26];
    if(empty($email))
      $errors[] = $l_user[37];

    //фильтруем значения динамических полей
    $query_part = '';
    $query = "SELECT *
   	          FROM {$gl_db_prefix}regform_fields
             ORDER BY pos";
    $results = db_select($query);
    if(is_array($results))
    {
      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $field_name = $results[$i]['field_name'];
        $caption    = stripslashes($results[$i]['caption']);
        $type       = $results[$i]['type'];
        $oblig      = $results[$i]['oblig'];
        $params     = unserialize(stripslashes($results[$i]['params']));
        //$id_field   = $results[$i]['id_field'];

        if($type == 'checkbox')
        {
          $$field_name = $_POST[$field_name];
          $yes_rep = $params['yes_rep'];
          $no_rep  = $params['no_rep'];
          if($$field_name == 'yes')
            $$field_name = $yes_rep;
          else
            $$field_name = $no_rep;
          $query_part .= "`{$field_name}` = '{$$field_name}',";
        }
        elseif($type == 'select')
        {
          $multiple = $params['multiple'];
          if($multiple == 'yes')
          {
            $options = $_POST[$field_name];
            if(is_array($options))
            {
              $$field_name = correct_input(implode(", ", $options));
            } else
            {
            	 if($oblig == 'yes')
				          {
 	              $errors[] = "{$l_user[42]} <b>{$caption}</b>.";
				          }

            	 $$field_name = $l_user[41];
            }
          }
          else
          {
            $$field_name = correct_input($_POST[$field_name]);
          }


          $query_part .= "`{$field_name}` = '{$$field_name}',";
        }
        //для типов radio, checkbox, textarea
        else
        {
          $$field_name = $_POST[$field_name];

          if($oblig == 'yes')
          {
            if(empty($$field_name))
            {
              $errors[] = "{$l_user[42]} <b>{$caption}</b>.";
            }
          }

          if(!empty($$field_name))
          {
            $$field_name  = correct_input($$field_name);
          } else $$field_name = $l_user[41];

          $query_part .= "`{$field_name}` = '{$$field_name}',";
        }



      }
    }

    //проверяем имя пользователя на уникальность
    $query = "SELECT id_user
                FROM {$gl_db_prefix}users
               WHERE name = '{$us_name}'";
    $result = db_select_one($query);
    if(!empty($result))
    {
      //$errors[] = "Имя <b>{$us_name}</b> уже используется, введите другое.";
      $tmp = $l_user[19];
      $tmp = str_replace("{us_name}", $us_name, $tmp);
      $errors[] = $tmp;
    }

    //проверяем логин на уникальность
    $query = "SELECT id_user
                FROM {$gl_db_prefix}users
               WHERE login = '{$login}'";
    $result = db_select_one($query);
    if(!empty($result))
    {
      //$errors[] = "Логин <b>{$login}</b> уже используется, введите другой.";
      $tmp = $l_user[27];
      $tmp = str_replace("{login}", $login, $tmp);
      $errors[] = $tmp;
    }

    //антифлуд по картинке
    //if(empty($errors))
    {
      if($site_img_antiflood == 'yes')
      {
        $corr_img_code = $_SESSION['corr_img_code'];
      	 $img_code = correct_input($_POST['img_code']);
	       //print "$corr_img_code - $users_img_code";
	       if($corr_img_code != $img_code)
	         $errors[] = $l_user[43];
      }
    }

    //регистрируем пользователя в базе данных
    if(empty($errors))
    {
      //фильтруем адрес
      if(!empty($www))
      {
      	 if(strpos($www, 'http://') === false)
	         $www_tmp = 'http://'.$www;
	       else
	         $www_tmp = $www;
      }

      //Нужна ли активация по e-mail?
     // if($site_users_activation == 'yes') $activated = 'no'; else $activated = 'yes';
      //добавляем пользователя в таблицу users
      $query = "INSERT INTO {$gl_db_prefix}users
                   SET id_user = NULL,
                       name  = '{$us_name}',
                       login = '{$login}',
                       psw   = md5('{$psw}'),
                       `group` = 'user',
                       {$query_part}
                       `info` = '{$info}',
                       `email` = '{$email}',
                       `reg_date` = NOW(),
                       `activated` = '{$activated}',
                       `subscribe` = '{$subscribe}'";
      db_insert($query);

      $id_user = db_insert_id();

      $_SESSION['already_registered'] = 'yes';

      //переходим на страницу, где выдается сообщение об успешной регистрации
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=users_list&part={$part}&mode={$mode}&sort={$sort}'></HEAD></HTML>";
      exit;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  // Форма регистрации
  //////////////////////////////////////////////////////////////////////////////

  //заголовок Registration Of The New Users

  print "<br/><h1>{$l_user[44]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine}/users/_users_edit.inc");
?>