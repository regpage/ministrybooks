<?php
  //////////////////////////////////////////////////////////////////////////////
  //Настройки формы запроса, модуль изменяет файл /config/query_form.inc
  //////////////////////////////////////////////////////////////////////////////


  //путь к конфигурационному файлу
  $filename = "{$gl_path_to_root}config/query_form.inc";


  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы
  //////////////////////////////////////////////////////////////////////////////


  if(!empty($_POST['save']))
  {
    //фильтрация данных формы
    $email_encoding = correct_input($_POST['email_encoding']);
    $to_email       = correct_input($_POST['to_email']);

    //формируем php-код конф. файла
    $str = "<?php\r\n";
    $str .= "  \$to_email       = '{$to_email}';\r\n";
    $str .= "  \$email_encoding = '{$email_encoding}';\r\n";
    $str .= "?>";

    //сохраняем конф. файл в директории $path
    save_in_file($filename, $str, 'w');

	   //переходим на страницу с формой
	   echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.php?mod=form'></HEAD></HTML>";
    exit;
  }


  //////////////////////////////////////////////////////////////////////////////
  //Выборка предыдущих значений формы
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    //e-mail
    if(file_exists($filename))
      include($filename);
  }


  //////////////////////////////////////////////////////////////////////////////
  //Форма
  //////////////////////////////////////////////////////////////////////////////

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
     if($email_encoding == $key)
       $enc_options .= " selected";
     $enc_options .= ">{$value}</option>";
   }


  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //заголовок
  print "<h1>{$l_form[18]}</h1><br>";

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('form', '');

  //поле e-mail
  print work_template($form_lineobl_tpl, array("{caption}" => "<span class='Mustred'>{$l_form[19]}</span>",
                                               "{field}" => form_create_input("to_email", $css = 'SiteFInputM', $size ='') ));

  //кодировка писем
  print work_template($form_lineobl_tpl,    array("{caption}" => "Character set",
                                                  "{field}" => form_create_select("email_encoding", $enc_options, $css = 'SiteFInputM', $size ='')));

 //кнопки
  print work_template($form_line_tpl, array("{caption}:" => "&nbsp;",
                                            "{field}" => form_create_submit('save', $value=$l_gen[18], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague', session_id());

  //конец формы
  print form_end();


?>