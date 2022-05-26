<?php

  //////////////////////////////////////////////////////////////////////////////
  //Модуль содержит форму авторизации
  //////////////////////////////////////////////////////////////////////////////


  //формируем шаблон поля формы
  $field_tpl = "<tr><td class='AuthFormCapt'>{caption}</td><td>{field}</td></tr>";

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);


  //начало формы
  print "<table cellspacing='0' cellpadding='0' border='0' class=AuthFormTbl width='100%'>";
  print "<form name='auth_form' action='' method='post'>";

  //поле имя
  print work_template($field_tpl, array("{caption}" => $l_auth[3],
                                               "{field}" => form_create_input("login", $css = 'AuthFormInput')));

  //поле логин
  print work_template($field_tpl, array("{caption}" => $l_auth[4],
                                               "{field}" => form_create_password('psw', $css = 'AuthFormInput', $size ='')));

  //поле запомнить пароль
  print work_template($field_tpl, array("{caption}" => $l_auth[5],
                                        "{field}" => form_create_checkbox('save_psw', '')));

  //кнопки
  print work_template("<tr><td>{field}</td></tr>", array("{caption}" => "&nbsp;",
                                        "{field}" => form_create_submit('enter', $value=$l_auth[6], $css = 'AuthFormButton')));

  //скрытые поля
  print form_create_hidden('blague', session_id());
  print form_create_hidden('act', "authentification");
  //if(empty($gl_auth_prec_uri)) $gl_auth_prec_uri = $gl_prec_uri;
  print form_create_hidden('auth_pg', "{$gl_prec_uri}");

  //конец формы
  print "</form></table>";

  //забыли пароль, ссылка
  //print "<p><a href='?mod=users_psw_remember'>{$l_auth[13]}</a></p>";

?>