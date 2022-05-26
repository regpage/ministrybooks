<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль позволяет админу поменять профиль зарегистрированного пользователя
  //в панели управления
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
  //Выборка текущего профиля пользователя
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT *
                FROM {$gl_db_prefix}users
               WHERE id_user = {$id_user}";
    $results = db_select($query);
    if(is_array($results))
    {
      $us_name =  stripslashes($results[0]['name']);
      //$tel =  stripslashes($results[0]['tel']);
      $email =  stripslashes($results[0]['email']);
      //$www =  stripslashes($results[0]['www']);
      //$icq =  stripslashes($results[0]['icq']);
      //$city =  stripslashes($results[0]['city']);
      //$firm =  stripslashes($results[0]['firm']);
      $info =  stripslashes($results[0]['info']);
      $subscribe =  stripslashes($results[0]['subscribe']);
    }

    $query = "SELECT *
              FROM {$gl_db_prefix}regform_fields
             ORDER BY pos";
		  $results_fld = db_select($query);

		  if(is_array($results_fld))
		  {
		    $cnt = count($results_fld);
		    for($i = 0; $i < $cnt; $i++)
		    {
		      $field_name = $results_fld[$i]['field_name'];
  			   $type       = $results_fld[$i]['type'];
					   $params     = unserialize(stripslashes($results_fld[$i]['params']));

		      $$field_name = $results[0][$field_name];
		      $$field_name;

		      if($type == 'select' && $params['multiple'] == 'yes')
					   {
            $$field_name= explode(", ", $$field_name);

					   }

		    }
		  }
  }


  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    $us_name = strip_tags(correct_input($_POST['us_name']));
    //$tel = strip_tags(correct_input($_POST['tel']));
    $email = strip_tags(correct_input($_POST['email']));

    //$icq = strip_tags(correct_input($_POST['icq']));
    //$www = strip_tags(correct_input($_POST['www']));

    $info = strip_tags(correct_input($_POST['info']));
    //$firm = strip_tags(correct_input($_POST['firm']));
    //$city = strip_tags(correct_input($_POST['city']));

    $subscribe = $_POST['subscribe']; if($subscribe != 'yes') $subscribe = 'no';

    if(empty($us_name))
      $errors[] = $l_user[18];
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
 	              $errors[] = "{$l_users[42]} <b>{$caption}</b>.";
				          }

            	 $$field_name = $l_users[41];
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
              $errors[] = "{$l_users[42]} <b>{$caption}</b>.";
            }
          }

          if(!empty($$field_name))
          {

            $$field_name  = correct_input($$field_name);
          } else $$field_name = $l_users[41];

          $query_part .= "`{$field_name}` = '{$$field_name}',";
        }



      }
    }

    //проверяем имя пользователя на уникальность
    $query = "SELECT id_user
                FROM {$gl_db_prefix}users
               WHERE name = '{$us_name}'
                 AND id_user != {$id_user}";
    $result = db_select_one($query);
    if(!empty($result))
      $errors[] = $l_user[19];

    if(empty($errors))
    {
      //исправляем url адрес
      if(!empty($www))
      {
      	 if(strpos($www, 'http://') === false)
	         $www_tmp = 'http://'.$www;
	       else
	         $www_tmp = $www;
      }

      //меняем пользовательский профиль
      $query = "UPDATE {$gl_db_prefix}users
                   SET `name`  = '{$us_name}',
                       {$query_part}
                       `info` = '{$info}',
                       `email` = '{$email}',
                       `subscribe` = '{$subscribe}'
                WHERE id_user = {$id_user} ";
      db_update($query);

      //переходим в список пользователей (в админке)
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=users_list&part={$part}&mode={$mode}&sort={$sort}'></HEAD></HTML>";
      exit;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_user[17]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine}/users/_users_edit.inc");
?>