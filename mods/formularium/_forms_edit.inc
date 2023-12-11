<?php
  //////////////////////////////////////////////////////////////////////////////
  // Форма, где указываются параметры формы
  // Подключается в модуля forms_add.inc и forms_edit.inc
  //////////////////////////////////////////////////////////////////////////////


  //загружаем шаблоны
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //кодировки, ключ - название кодировки для опции select'a
  //           значение - описание кодировкиы
  $character_sets = array(   "utf-8"             =>  "Unicode / ISO 10646 UTF-8",
                             "windows-1251"      =>  "Windows Code Page 1251",
                             "ascii"             =>  "US ASCII",
                             "british"           =>  "Britain ISO 646",
                             "bulgaria-pc"       =>  "Bulgarian PC code page",
                             "canadian-french"   =>  "Canada-French DEC NRC",
                             "cp1250"            =>  "Windows Code Page 1250",
                             "cp1252"            =>  "Windows Code Page 1252",
                             "cp437"             =>  "PC Code Page 437",
                             "cp850"             =>  "PC Code Page 850",
                             "cp852"             =>  "PC Code Page 852",
                             "cp855"             =>  "PC Code Page 855",
                             "cp858"             =>  "PC Code Page 858",
                             "cp862"             =>  "PC Code Page 862",
                             "cp866"             =>  "PC Code Page 866",
                             "cp869"             =>  "PC Code Page 869",
                             "cyrillic-iso"      =>  "ISO 8859-5 Latin/Cyrillic",
                             "danish"            =>  "Denmark/Norway ISO 646",
                             "dec-kanji"         =>  "JIS X 0208",
                             "dec-multinational" =>  "DEC Multinational",
                             "dg-international"  =>  "Data General International",
                             "dutch"             =>  "Netherlands ISO 646",
                             "elot-927"          =>  "Greece ELOT 927",
                             "elot-928"          =>  "Greece ELOT 928",
                             "euc-jp"            =>  "JIS X 0201 + 0208",
                             "finnish"           =>  "Finland ISO 646",
                             "french"            =>  "France ISO 646",
                             "german"            =>  "Germany ISO 646",
                             "greek-iso"         =>  "ISO 8859-7",
                             "hebrew-7"          =>  "DEC VT100 Hebrew",
                             "hebrew-iso"        =>  "ISO 8859-8 Latin/Hebrew",
                             "hp-roman8"         =>  "Hewlett Packard Roman-8",
                             "hungarian"         =>  "Hungary ISO 646",
                             "iso2022jp"         =>  "JIS X 0201 + 0208",
                             "italian"           =>  "Italy ISO 646",
                             "jis7-kanji"        =>  "JIS X 0201 + 0208",
                             "koi8-cyrillic"     =>  "USSR GOST KOI-8",
                             "koi8r"             =>  "Usenet KOI8 extended (Russia)",
                             "koi8u"             =>  "Usenet KOI8 extended (Ukrain)",
                             "latin1-iso"        =>  "ISO 8859-1 Latin Alphabet 1",
                             "latin2-iso"        =>  "ISO 8859-2 Latin Alphabet 2",
                             "latin9-iso"        =>  "ISO 8859-15 Latin Alphabet 9",
                             "macintosh-latin"   =>  "Apple Quickdraw / Latin-1",
                             "mazovia-pc"        =>  "Polish PC code page",
                             "next-multinational"=>  "NeXT Multinational",
                             "norwegian"         =>  "Norway/Denmark ISO 646",
                             "portuguese"        =>  "Portugal ISO 646",
                             "shift-jis"         =>  "IBM Code Page 982 Kanji",
                             "short-koi"         =>  "Short KOI Cyrillic",
                             "spanish"           =>  "Spain ISO 646",
                             "swedish"           =>  "Sweden ISO 646",
                             "swiss"             =>  "Switzerland DEC NRC",
                             "ucs2"              =>  "Unicode / ISO 10646 UCS-2",
                             );

   //формируем опции кодировок
   foreach($character_sets as $key => $value)
   {
     $enc_options .= "<option value='{$key}'";
     if($encoding == $key)
       $enc_options .= " selected";
     $enc_options .= ">{$value}</option>";
   }

  //устанавливаем начальные значения переменных
  if(empty($sended_den))
    $sended_den = "<p>{$l_forms[59]}</p>";
  if(empty($sended_mess))
    $sended_mess = "<p>{$l_forms[60]}</p>";

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('catitem_edit_form', '', 'post', 'multipart');

  //название формы
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[61],
                                                  "{field}" => form_create_input("title", $css = 'SiteFInputM', $size ='')));

  //тема сообщения
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[62],
                                                  "{field}" => form_create_input("subject", $css = 'SiteFInputM', $size ='')));

  //адрес отправителя
  print work_template($form_line_tpl,    array("{caption}" => $l_forms[63],
                                                  "{field}" => form_create_input("email_from", $css = 'SiteFInputM', $size ='')));

  //кодировка
  print work_template($form_line_tpl,    array("{caption}" => $l_forms[64],
                                                  "{field}" => form_create_select("encoding", $enc_options, $css = 'SiteFInputM', $size ='')));

  //позиция
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_forms[65],
                                                  "{field}" => form_create_input("pos", $css = 'SiteFInputM', $size ='')));

  //сообщение об успешной отправки данных
  print work_template($form_line_tpl,    array("{caption}" => $l_forms[66],
                                                   "{field}" => form_create_textarea('sended_mess', $rows = '6', $css = 'SiteFTextareaL')));

  //сообщение о том, что повторно форму использовать нельзя
  print work_template($form_line_tpl,    array("{caption}" => $l_forms[67],
                                                   "{field}" => form_create_textarea('sended_den', $rows = '6', $css = 'SiteFTextareaL')));

  //кнопки ы
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                             "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague',  session_id());
  print form_create_hidden('id_cat',  $id_cat);
  print form_create_hidden('old_pos', $old_pos);


  //конец формы
  print form_end();


?>