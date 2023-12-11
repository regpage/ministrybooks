<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления пользователями
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль
  // - выводит форму "вспомнить пароль"
  // - обрабатывает ее: сохраняет пароль в таблице новых паролей
  //                    отправляет пользователю письмо с просьбой подтвердить пароль
  //////////////////////////////////////////////////////////////////////////////

  print "<h1>{$l_users[48]}</h1>";


  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    $login = preg_replace("/[^_0-9a-z-]/", '', $_POST['login']);

    //выбираем e-mail пользователя
    $email   = stripslashes(db_select_one("SELECT email FROM {$gl_db_prefix}users WHERE login = '{$login}'"));

    if(empty($email))
      $errors[] = str_replace("{login}", $login, $l_users[49]);

    if(empty($errors))
    {
      $id_user = stripslashes(db_select_one("SELECT id_user FROM {$gl_db_prefix}users WHERE login = '{$login}'"));

      //генерируем код
      $code = rand(100000000, 999999999);

      $psw = substr(md5($code), 0, 6);

      //удаляем старый новый пароль из базы новых паролей, если он есть
      db_delete("DELETE FROM {$gl_db_prefix}new_passwords WHERE id_user = {$id_user}");

      //сохраняем пароль в таблице новых паролей
      $query = "INSERT INTO {$gl_db_prefix}new_passwords
                   SET id_psw = NULL,
                       id_user = {$id_user},
                       code = {$code},
                       new_psw = md5('$psw')";
      db_insert($query);


      //отправляем пользователю сообщение с просьбой подтвердить изменение

	     //ссылка на активацию
	     $link_for_act = "{$gl_site}?mod=users_chpsw_pub2&id_user={$id_user}&code=".$code;

	     //текст письма
	     $message = file_get_contents("{$gl_path_to_engine_root}config/site_mess_pass_remember.inc");

	     //заменяем подстановки в тексте письма
	     //$message = str_replace("{user}", $gl_us_name, $message);
	     $message = str_replace("{activation}", $link_for_act, $message);
	     $message = str_replace("{new_psw}", $psw, $message);

	     //заголовки
	     $headers = "Content-type: text/plain; charset={$site_email_encoding}\r\n";
	     $headers .= "From: ".$_SERVER['SERVER_NAME']." <".$_SERVER['SERVER_ADMIN'].">\r\n";

	     //отправляем данные, переходим на страницу с формой, где выводится сообщение об успешной отправки
	     send_email($email,
	           $site_title.' :: '.$l_users[50],
	           $message,
	           $headers);

      print "<p>{$l_users[51]}</p>";
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  //Форма
  //////////////////////////////////////////////////////////////////////////////

  //сообщение об успешном изменении данных
  //if(intval($_GET['mess']) == 1)
  //  print "<p>Мы выслали на ваш e-mail ($email)</p>";

  //выбираем шаблоны полей формы
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //формируем шаблон поля формы
  $field_tpl = "<tr><td class='AuthFormCapt'>{caption}</td><td>{field}</td></tr>";

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);


  //начало формы
  print "<table cellspacing='0' cellpadding='0' border='0' class=AuthFormTbl width='100%'>";
  print "<form name='rem_f' action='' method='post'>";

  //поле имя
  print work_template($field_tpl, array("{caption}" => $l_users[52],
                                               "{field}" => form_create_input("login", $css = 'SiteFInputS')));

  //кнопки
  print work_template("<tr><td>{field}</td></tr>", array("{caption}" => "&nbsp;",
                                        "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague', session_id());


  //конец формы
  print "</form></table>";


?>