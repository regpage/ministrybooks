<?php
  //////////////////////////////////////////////////////////////////////////////
  // Конструктор меню
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Форма редакторивания параметров меню
  //Подключается в модуляъ menu_add.inc, menu_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //опции для select'a расположение пунктов
  $disp_opt = "<option value='vertical'";
  if($disposition == 'vertical')
    $disp_opt .= ' selected';
  $disp_opt .= ">{$l_menu[12]}</option>";
  $disp_opt .= "<option value='horizontal'";
  if($disposition == 'horizontal')
    $disp_opt .= ' selected';
  $disp_opt .= ">{$l_menu[13]}</option>";

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //название
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_menu[14],
                                                  "{field}" => form_create_input("title", $css = 'SiteFInputM', $size ='')));

  //расположение пунктов
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_menu[15],
                                                  "{field}" => form_create_select("disposition", $disp_opt, $css = 'SiteFInputM')));

  //разделитель
  print work_template($form_line_tpl,    array("{caption}" => $l_menu[16],
                                                  "{field}" => form_create_input("separator", $css = 'SiteFInputM', $size ='')));

  //позиция
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_menu[17],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague', session_id());
  print form_create_hidden('old_pos', $old_pos);

  //конец формы
  print form_end();


?>