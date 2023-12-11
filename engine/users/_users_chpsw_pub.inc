<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль позволяет зарегистрированному пользователю поменять
  //свой логин и пароль.
  //////////////////////////////////////////////////////////////////////////////


  //если пользователь не зарегистрирован, завершаем работу модуля
  if(empty($gl_id_user))
    { print $l_users[23]; return; }


  //////////////////////////////////////////////////////////////////////////////
  //выборка текущегол логина
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT login
                FROM {$gl_db_prefix}users
               WHERE id_user = {$gl_id_user}";
    $results = db_select($query);
    if(is_array($results))
    {
      $login =  stripslashes($results[0]['login']);

    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //инициализация и фильтрация переменных формы
    $login = $_POST['login'];
    $psw   = $_POST['psw'];
    $psw_conf = $_POST['psw_conf'];
    $login = strtolower($login);
    $psw   = strtolower($psw);
    $psw_conf   = strtolower($psw_conf);

    if(!preg_match("/^[_0-9a-z]{2,}$/", $login))
      $errors[] = $l_users[15];
    if(!preg_match("/^[_0-9a-z]{5,}$/", $psw))
      $errors[] = $l_users[16];
    if($psw != $psw_conf)
      $errors[] = $l_users[17];

    //проверяем логин на уникальность
    $query = "SELECT id_user
                FROM {$gl_db_prefix}users
               WHERE login = '{$login}'
                 AND id_user != {$gl_id_user}";
    $result = db_select_one($query);
    if(!empty($result))
    {
      //$errors[] = "Логин <b>{$login}</b> уже используется, введите другой.";
      $tmp = $l_users[19];
      $tmp = str_replace("{login}", $login, $tmp);
      $errors[] = $tmp;

    }

    if(empty($errors))
    {
      //обновляем пользовательский профиль в бд
      $query = "UPDATE  {$gl_db_prefix}users
                    SET `login` = '{$login}',
                         psw    = md5('{$psw}')
                  WHERE id_user = {$gl_id_user}";
      db_update($query);

      //переходим в список пользователей в пользовательской части
	     echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=users_chpsw_pub&mess=1'></HEAD></HTML>";
      exit;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  //Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_users[27]}</h1>";

  //сообщение об успешном изменении данных
  if(intval($_GET['mess']) == 1)
    print "<p>{$l_users[39]}</p>";

  //выбираем шаблоны полей формы
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $form_linewidg_tpl = file_get_contents("{$gl_path_to_templates}forms/linewidg.htm");

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '');

  //поле логин
  print work_template($form_lineobl_tpl, array("{caption}" => $l_users[24],
                                               "{field}" => form_create_input("login", 'SiteFInputM', $size ='') ));

  //поле пароль
  print work_template($form_lineobl_tpl, array("{caption}" => $l_users[25],
                                               "{field}" => form_create_password('psw', $css = 'SiteFInputM', $size ='') ));

  //подтвердить пароль
  print work_template($form_lineobl_tpl, array("{caption}" => $l_users[26],
                                               "{field}" => form_create_password('psw_conf', $css = 'SiteFInputM', $size ='') ));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'button')));

  //скрытые поля
  print form_create_hidden('blague',  session_id());
  print form_create_hidden('id_user', $id_user);
  print form_create_hidden('sort', $sort);
  print form_create_hidden('mode', $mode);
  print form_create_hidden('part', $part);

 //конец формы
  print form_end();
?>