<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления ведомыми сайтами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Форма, где указываются параметры ведомого сайта.
  //Подключается в модулях sites_add.inc, sites_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $tbl_section_tpl = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //опции кодировк для select'a
  $db_enc_options = "
                     <option value='utf8'>UTF-8 Unicode</option>
                     <option value='cp1251'>Windows Cyrillic</option>
                     <option value='latin1'>cp1252 West European </option>
                     <option value='koi8r'>KOI8-R Relcom Russian</option>
	                    <option value='latin2'>ISO 8859-2 Central European</option>
	                    <option value='ascii'>US ASCII</option>
	                    <option value='hebrew'>ISO 8859-8 Hebrew</option>
	                    <option value='koi8u'>KOI8-U Ukrainian </option>
	                    <option value='greek'>ISO 8859-7 Greek </option>
	                    <option value='cp1250'>Windows Central European </option>
	                    <option value='armscii8'>ARMSCII-8 Armenian</option>
	                    <option value='cp866'>DOS Russian</option>
	                    <option value='cp1256'>Windows Arabic</option>
	                    <option value='cp1257'>Windows Baltic</option>
	                    <option value='geostd8'>GEOSTD8 Georgian</option>
                    ";

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //заголовок "Параметры сайта"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_sites[9]));

  if($gl_adm == 'sites_add')
  {
    //название сайта (англ. буквы, цифры, знак подчеркивания)
    print work_template($form_lineobl_tpl,    array("{caption}" => $l_sites[10],
                                                    "{field}" => form_create_input("s_name", $css = 'SiteFInputM', $size ='')));
  }

  //URL адрес сайта
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_sites[11],
                                                  "{field}" => form_create_input("s_url", $css = 'SiteFInputM', $size ='')));

  //Относительный путь от корня сайта ведущего к корню сайта ведомого, включая название директории сайта ведомого (с конечным слэшем):
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_sites[12],
                                                  "{field}" => form_create_input("s_path_to_root", $css = 'SiteFInputM', $size ='')));

  //Относительный путь от корня сайта ведомого к корню сайта ведущего, включая название директории сайта ведущего (с конечным слэшем)
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_sites[13],
                                                  "{field}" => form_create_input("s_path_to_engine", $css = 'SiteFInputM', $size ='')));

  //заголовок "Параметры соединения с базой"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_sites[14]));

  //имя сервера MySQL
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_sites[15],
                                                  "{field}" => form_create_input("s_db_server", $css = 'SiteFInputM', $size ='')));

  //имя базы данных
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_sites[16],
                                                  "{field}" => form_create_input("s_db_name", $css = 'SiteFInputM', $size ='')));

  //имя пользователя базы данных
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_sites[17],
                                                  "{field}" => form_create_input("s_db_user", $css = 'SiteFInputM', $size ='')));

  //пароль пользователя MySQL
  print work_template($form_line_tpl,    array("{caption}" => $l_sites[18],
                                                  "{field}" => form_create_input("s_db_psw", $css = 'SiteFInputM', $size ='')));

  //character set for database
  print work_template($form_lineobl_tpl, array("{caption}" => "Character set for database",
                                               "{field}" => form_create_select("s_db_encoding", $db_enc_options, $css = 'SiteFInputM', $size ='') ));

  //префикс таблиц
  if($gl_adm == 'sites_add')
    print work_template($form_line_tpl,    array("{caption}" => $l_sites[28],
                                                   "{field}" => form_create_input("s_db_prefix", $css = 'SiteFInputM', $size ='')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague', session_id());
  print form_create_hidden('site', $site);

  //конец формы
  print form_end();

  //info
  print $l_sites[19];
?>