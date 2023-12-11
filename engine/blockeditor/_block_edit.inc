<?php

  //////////////////////////////////////////////////////////////////////////////
  //Форма изменения параметров блока,
  //подключается в модулях blocks_add.inc и blocks_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //установка начальных значений переменных
  if(empty($nl2br))
    $nl2br = 'yes';

  //загружаем шаблоны
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('blocks_edit_form', '', 'post', 'multipart');


  //////////////////////////////////////////////////////////////////////////////
  //поля формы текстового блока
  //////////////////////////////////////////////////////////////////////////////

  if($block_gen_type == 'text')
  {
    //текст
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[35],
                                                 "{field}"   => form_create_bbcodeeditor("{$gl_path_to_engine_root}ext_prm/bbcodeeditor/", 'small', 'text', $text, 'SiteFTextareaM', '20', "{$gl_admin_url}ext_prm/bbcodeeditor/")));

    //абзац с выравниваем по ширине
    $options .= "<option value='p_just'";
    if($block_type == 'p_just')
      $options .= " selected";
    $options .= ">{$l_blockeditor[17]}</option>";

    //абзац с выравниваем слева
    $options .= "<option value='p_left'";
    if($block_type == 'p_left')
      $options .= " selected";
    $options .= ">{$l_blockeditor[18]}</option>";

    //абзац с выравниваем справа
    $options .= "<option value='p_right'";
    if($block_type == 'p_right')
      $options .= " selected";
    $options .= ">{$l_blockeditor[20]}</option>";

    //абзац с выравниваем по центру
    $options .= "<option value='p_center'";
    if($block_type == 'p_center')
      $options .= " selected";
    $options .= ">{$l_blockeditor[19]}</option>";

    //заголовок 1
    $options .= "<option value='h1'";
    if($block_type == 'h1')
      $options .= " selected";
    $options .= ">{$l_blockeditor[14]}</option>";

    //заголовок 2
    $options .= "<option value='h2'";
    if($block_type == 'h2')
      $options .= " selected";
    $options .= ">{$l_blockeditor[15]}</option>";

    //заголовок 3
    $options .= "<option value='h3'";
    if($block_type == 'h3')
      $options .= " selected";
    $options .= ">{$l_blockeditor[16]}</option>";

    //вид блока
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[39],
                                                 "{field}" => form_create_select('block_type', $options, $css = 'SiteFInputM', $size ='') ));

    //позиция
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[36],
                                               "{field}" => form_create_input("pos", 'SiteFInputM', $size ='') ));

    //заменить перевод строки на <br>
    print work_template($form_line_tpl,    array("{caption}" => $l_blockeditor[40],
                                                  "{field}" => form_create_checkbox("nl2br", $nl2br)));
  }


  //////////////////////////////////////////////////////////////////////////////
  //поля формы для  списка
  //////////////////////////////////////////////////////////////////////////////

  if($block_gen_type == 'list')
  {
    //название
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[38],
                                                 "{field}" => form_create_input("l_name", 'SiteFInputM', $size ='') ));

    //пункты (разделяются клавишей Enter):
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[41],
                                                 "{field}"   => form_create_bbcodeeditor("{$gl_path_to_engine_root}ext_prm/bbcodeeditor/", 'small', 'text', $text, "SiteFTextareaM", "20", "{$gl_admin_url}ext_prm/bbcodeeditor/")));

    //маркированный список
    $options .= "<option value='ul_mark'";
    if($block_type == 'ul_mark')
      $options .= " selected";
    $options .= ">{$l_blockeditor[21]}</option>";

    //цифровой список
    $options .= "<option value='ol_numbers'";
    if($block_type == 'ol_numbers')
      $options .= " selected";
    $options .= ">{$l_blockeditor[23]}</option>";

    //буквенный список
    $options .= "<option value='ol_letters'";
    if($block_type == 'ol_letters')
      $options .= " selected";
    $options .= ">{$l_blockeditor[22]}</option>";

    //тип списка
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[42],
                                                 "{field}" => form_create_select('block_type', $options, $css = 'SiteFInputM', $size ='') ));

    //заменить перевод строки на <br>
    print work_template($form_line_tpl,    array("{caption}" => $l_blockeditor[43],
                                                  "{field}" => form_create_checkbox("nl2br", $nl2br)));

    //позиция
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[36],
                                               "{field}" => form_create_input("pos", 'SiteFInputM', $size ='') ));
  }


  //////////////////////////////////////////////////////////////////////////////
  //поля формы для блока с изображениями
  //////////////////////////////////////////////////////////////////////////////

  if($block_gen_type == 'images')
  {
    //название
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[38],
                                                 "{field}" => form_create_input("i_name", 'SiteFInputM', $size ='') ));

    //кол-во изображений в одном ряду
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[44],
                                                 "{field}" => form_create_input("in_row", 'SiteFInputM', $size ='') ));

    //позиция:
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[36],
                                                 "{field}" => form_create_input("pos", 'SiteFInputM', $size ='') ));

    //картинки без пояснительного текста
    $options .= "<option value='images'";
    if($block_type == 'images')
      $options .= " selected";
    $options .= ">{$l_blockeditor[32]}</option>";

    //картинки пояснительный текст справа
    $options .= "<option value='images_text_in_right'";
    if($block_type == 'images_text_on_right')
      $options .= " selected";
    $options .= ">{$l_blockeditor[33]}</option>";

    //картинки пояснительный текст снизу
    $options .= "<option value='images_text_in_bottom'";
    if($block_type == 'images_text_in_bottom')
      $options .= " selected";
    $options .= ">{$l_blockeditor[34]}</option>";

    //тип блока
    print work_template($form_lineobl_tpl, array("{caption}" =>  $l_blockeditor[45],
                                                 "{field}" => form_create_select('block_type', $options, $css = 'SiteFInputM', $size ='') ));
  }


  //////////////////////////////////////////////////////////////////////////////
  //поля формы для блока таблицы
  //////////////////////////////////////////////////////////////////////////////

  if($block_gen_type == 'table')
  {
    //название
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[38],
                                                 "{field}" => form_create_input("t_name", 'SiteFInputM', $size ='') ));

    //позиция
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[36],
                                               "{field}" => form_create_input("pos", 'SiteFInputM', $size ='') ));
    //spaw-editor
    print "</table>";
    include("{$gl_path_to_engine_root}ext_prm/spaw2/spaw.inc.php");
    $spaw1 = new SpawEditor("text", $content);
    $spaw1->show();
    print "<table class='SiteFTbl' style='margin-left:0px' cellspacing='0' cellpadding='0' border='0'>";

    print form_create_hidden('block_type', 'table');
  }


  //////////////////////////////////////////////////////////////////////////////
  //поля формы для файлового блока
  //////////////////////////////////////////////////////////////////////////////

  if($block_gen_type == 'file')
  {
     //название
     print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[72],
                                                 "{field}" => form_create_input("f_name", 'SiteFInputM', $size ='') ));

     //позиция
     print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[36],
                                                "{field}" => form_create_input("pos", 'SiteFInputM', $size ='') ));

     //файл
     print work_template($form_lineobl_tpl,    array("{caption}" => $l_blockeditor[37],
                                                  "{field}" => form_create_file("file", $css = 'SiteFInputM', $size ='64')));

     print form_create_hidden('block_type', 'file');
     print form_create_hidden('old_file', $old_file);
  }

  //////////////////////////////////////////////////////////////////////////////
  //поля формы для  списка
  //////////////////////////////////////////////////////////////////////////////

  if($block_gen_type == 'newpage')
  {
    //позиция
    print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[36],
                                               "{field}" => form_create_input("pos", 'SiteFInputM', $size ='') ));
  }

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague', session_id());
  print form_create_hidden('block_gen_type', $block_gen_type);
  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('pg', $ed_pg);
  print form_create_hidden('id_block', $id_block);

  //конец формы
  print form_end();


?>