<?php
  //////////////////////////////////////////////////////////////////////////////
  // Настройки системы
  //////////////////////////////////////////////////////////////////////////////


  //путь к конф. файлам
  //$site_is_locked_msg_path = "{$gl_path_to_root}config/site_is_locked_msg.inc";
  $conf_path = "{$gl_path_to_root}config/site_settings.inc";


  //формирует опции select'a из разделов (в optgroup) и страниц, относящихся к ним
  //$prefix - присоединяется к имени раздела спереди, содержит названия предыдущих подразделов, разделенных двоеточиями
  //$id_part_prec - ид раздела-предка
  //$begin_id_item - id (таблица parts_items) текущего начального документа
  function get_parts_and_docs($prefix, $id_part_prec, $begin_id_item)
  {
    global $gl_db_prefix;

    $query = "SELECT id_part, title, id_part_prec
                FROM {$gl_db_prefix}parts
               WHERE id_part_prec = {$id_part_prec}
              ORDER BY pos";
    $results = db_select($query);
    if(is_array($results))
    {
      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $id_part = $results[$i]['id_part'];
        $id_part_prec = $results[$i]['id_part_prec'];
        $title        = stripslashes($results[$i]['title']);
        $options .= "<optgroup label='{$prefix}{$title}'>";
        $query = "SELECT id_item, title
                    FROM {$gl_db_prefix}parts_items
                   WHERE id_part = {$id_part}
                   ORDER BY pos";
        $results_i = db_select($query);
        $cnt_i = count($results_i);
        for($b = 0; $b < $cnt_i; $b++)
        {
          $id_item = $results_i[$b]['id_item'];
          $i_title   = stripslashes($results_i[$b]['title']);
          $options .= "<option value={$id_item}";
          if($id_item == $begin_id_item)
            $options .= " selected";
          $options .= ">{$i_title}</option>";
        }
        $options .= "</optgroup>";

        $options .= get_parts_and_docs($prefix .= "{$title} -&gt; ", $id_part, $begin_id_item);
        if($id_part_prec == 0)
          $prefix = '';

      }
    }
    return($options);
  }


  //////////////////////////////////////////////////////////////////////////////
  // Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация данных
    $site_begin_id_item = intval($_POST['site_begin_id_item']);
    $site_title    = stripslashes($_POST['site_title']);
    $site_keywords      = stripslashes($_POST['site_keywords']);
    $site_descr         = stripslashes($_POST['site_descr']);
    $site_img_antiflood    = stripslashes($_POST['site_img_antiflood']);
    if($site_img_antiflood != 'yes')
      $site_img_antiflood = 'no';
    $site_users_activation    = stripslashes($_POST['site_users_activation']);
    if($site_users_activation != 'yes')
      $site_users_activation = 'no';
    //$site_is_locked_msg   = stripslashes($_POST['site_is_locked_msg']);
    $site_email_encoding   = stripslashes($_POST['site_email_encoding']);

    //формируем код конфигурационного файла
    $str = "<?php\r\n";
    $str .= "  \$site_begin_id_item      = {$site_begin_id_item};\r\n";
    $str .= "  \$site_title      = '{$site_title}';\r\n";
    $str .= "  \$site_keywords      = '{$site_keywords}';\r\n";
    $str .= "  \$site_descr     = '{$site_descr}';\r\n";
    $str .= "  \$site_img_antiflood      = '{$site_img_antiflood}';\r\n";
    $str .= "  \$site_users_activation      = '{$site_users_activation}';\r\n";
    $str .= "  \$site_email_encoding      = '{$site_email_encoding}';\r\n";
    $str .= "?>";

    save_in_file($conf_path, $str, 'w');
    //обновляем талицу settings
    /*if(empty($errors))
    {
      $query = "UPDATE {$gl_db_prefix}settings
                   SET begin_id_item = {$begin_id_item},
                       site_title    = '{$site_title}',
                       descr         = '{$descr}',
                       keywords      = '{$keywords}',
                       img_antiflood = '{$img_antiflood}'
                  WHERE id = 1";
      db_update($query);
    }*/


    ///save_in_file($site_is_locked_msg_path, $site_is_locked_msg, 'w');
  }


  //////////////////////////////////////////////////////////////////////////////
  // Выборка текущих настроек для полей формы
  //////////////////////////////////////////////////////////////////////////////

  if(file_exists($conf_path))
    include($conf_path);

  /*$query = "SELECT *
              FROM {$gl_db_prefix}settings
             WHERE id = 1";
  $results = db_select($query);
  $begin_id_item = $results[0]['begin_id_item'];
  $site_title = stripslashes($results[0]['site_title']);
  $descr = stripslashes($results[0]['descr']);
  $keywords = stripslashes($results[0]['keywords']);
  $img_antiflood = stripslashes($results[0]['img_antiflood']);
  if(file_exists($site_is_locked_msg_path))
    $site_is_locked_msg = file_get_contents($site_is_locked_msg_path);
  if(empty($site_is_locked_msg))
    $site_is_locked_msg = "This site  is temporarely locked.";*/

  //////////////////////////////////////////////////////////////////////////////
  // Выборка текущих настроек для полей формы
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_setting[1]}</h1>";

  //кодировки, ключ - название кодировки для опции select'a
  //           значение - описание кодировкиы
  $character_sets = array(   "utf-8"              =>  "Unicode / ISO 10646 UTF-8",
                             "windows-1251"            =>  "Windows Code Page 1251",
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
     if($site_email_encoding == $key)
       $enc_options .= " selected";
     $enc_options .= ">{$value}</option>";
   }

  //загружаем шаблоны
  $init_page_options = get_parts_and_docs('', 0, $site_begin_id_item);
  $form_line_tpl     = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl  = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //название сайта
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_setting[2],
                                                  "{field}"   => form_create_input("site_title", $css = 'SiteFInputM', $size ='')));

  //начальная страница
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_setting[3],
                                                   "{field}" => form_create_select('site_begin_id_item', $init_page_options, $css = 'SiteFInputM')));

  //описание
  print work_template($form_line_tpl,    array("{caption}" => $l_setting[4],
                                                  "{field}" => form_create_textarea('site_descr', $rows = '5', $css = 'SiteFTextareaM')));

  //ключевые слова
  print work_template($form_line_tpl,    array("{caption}" => $l_setting[5],
                                                  "{field}" => form_create_textarea('site_keywords', $rows = '5', $css = 'SiteFTextareaM')));

  //антифлуд по картинке
  print work_template($form_line_tpl,    array("{caption}" => $l_setting[6],
                                                  "{field}" => form_create_checkbox("site_img_antiflood", $site_img_antiflood)));

  //новый пользователь должен активировать аккаунт по e-mail
  print work_template($form_line_tpl,    array("{caption}" => $l_setting[8],
                                                  "{field}" => form_create_checkbox("site_users_activation", $site_users_activation)));

  //кодировка писем
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_setting[9],
                                                  "{field}" => form_create_select("site_email_encoding", $enc_options, $css = 'SiteFInputM', $size ='')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //скрытые поля
  //print form_create_hidden('blague', session_id());

  //конец формы
  print form_end();

 ?>