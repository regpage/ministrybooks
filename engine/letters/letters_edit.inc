<?php
  //////////////////////////////////////////////////////////////////////////////
  // Настройки системы
  //////////////////////////////////////////////////////////////////////////////
  

  //путь к конф. файлам
  $site_is_locked_msg_path = "{$gl_path_to_root}config/site_is_locked_msg.inc";
  $site_activation_needed_path = "{$gl_path_to_root}config/site_activation_needed.inc";
  $site_mess_pass_remember_path = "{$gl_path_to_root}config/site_mess_pass_remember.inc";



  //////////////////////////////////////////////////////////////////////////////
  // Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $site_is_locked_msg   = stripslashes($_POST['site_is_locked_msg']);
    save_in_file($site_is_locked_msg_path, $site_is_locked_msg, 'w');

    $site_activation_needed   = stripslashes($_POST['site_activation_needed']);
    save_in_file($site_activation_needed_path, $site_activation_needed, 'w');

    $site_mess_pass_remember   = stripslashes($_POST['site_mess_pass_remember']);
    save_in_file($site_mess_pass_remember_path, $site_mess_pass_remember, 'w');
  }


  //////////////////////////////////////////////////////////////////////////////
  // Выборка текущих настроек для полей формы
  //////////////////////////////////////////////////////////////////////////////

  if(file_exists($site_is_locked_msg_path))  $site_is_locked_msg = file_get_contents($site_is_locked_msg_path);
  if(file_exists($site_activation_needed_path))  $site_activation_needed = file_get_contents($site_activation_needed_path);
  if(file_exists($site_mess_pass_remember_path))  $site_mess_pass_remember = file_get_contents($site_mess_pass_remember_path);


  //////////////////////////////////////////////////////////////////////////////
  // Выборка текущих настроек для полей формы
  //////////////////////////////////////////////////////////////////////////////
 
  
  
  //заголовок  

  print "<h1>{$l_letters_tpl[1]}</h1><br />";

  //загружаем шаблоны

  $form_line_tpl     = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl  = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

   //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');


  //сообщение, если сайт закрыт
  print work_template($form_line_tpl,    array("{caption}" => $l_letters_tpl[2],
                                                  "{field}" => form_create_textarea('site_is_locked_msg', $rows = '5', $css = 'SiteFTextareaM')));

  //Текст письма :: требуется активация аккаунта
  print work_template($form_line_tpl,    array("{caption}" => $l_letters_tpl[3],
                                                  "{field}" => form_create_textarea('site_activation_needed', $rows = '5', $css = 'SiteFTextareaM')));

  //Текст письма :: подтвердите смену пароля, высылается после ввода логина в форме "Забыли пароль"
  print work_template($form_line_tpl,    array("{caption}" => $l_letters_tpl[4],
                                                  "{field}" => form_create_textarea('site_mess_pass_remember', $rows = '5', $css = 'SiteFTextareaM')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //скрытые поля
  //print form_create_hidden('blague', session_id());

  //конец формы
  print form_end();


 ?>