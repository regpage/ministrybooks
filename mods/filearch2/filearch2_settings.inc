<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Настройки модуля
  //////////////////////////////////////////////////////////////////////////////


  //путь к файлу конфигурации
  $conf_path = "{$gl_path_to_engine_root}config/filearch2_config.inc";


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация данных формы
    $filearch2_id_tpl = intval($_POST['filearch2_id_tpl']);
    $filearch2_title = $_POST['filearch2_title'];
    if(get_magic_quotes_gpc())
      $filearch2_title = stripslashes($filearch2_title);

    //php-код конфига
    $str = "<?php\r\n";
    $str .= "  \$filearch2_id_tpl   =  {$filearch2_id_tpl};\r\n";
    $str .= "  \$filearch2_title    = '{$filearch2_title}';\r\n";
    $str .= "?>";

    //сохранение кофига
    save_in_file($conf_path, $str, 'w');

    //переходим на эту же страницу
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?mod=filearch2_settings'></HEAD></HTML>";
    exit;
  }


  //////////////////////////////////////////////////////////////////////////////
  //загрузка конфига
  //////////////////////////////////////////////////////////////////////////////

  if(file_exists($conf_path))
    include($conf_path);


  //////////////////////////////////////////////////////////////////////////////
  //форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div><h4>{$l_filearch2[1]}</h4>";

  //загружаем шаблоны
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выбираем шаблоны сайта в виде опций select'a
  $tpl_options = form_get_options_from_db("sitetpl", "id_tpl", "title", $filearch2_id_tpl);
  $tpl_options = "<option value='0'>{$l_filearch2[2]}</option>".$tpl_options;

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '', 'post', 'multipart');

  //шаблон сайта
  print work_template($form_lineobl_tpl,    array("{caption}" => $l_filearch2[3],
                                                  "{field}" => form_create_select("filearch2_id_tpl", $tpl_options, "SiteFInputM")));

  //заголовок модуля
  print work_template($form_line_tpl,    array("{caption}" => $l_filearch2[4],
                                                  "{field}" => form_create_input("filearch2_title", $css = 'SiteFInputM', $size ='')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //скрытые поля
  //print form_create_hidden('blague', session_id());

  //конец формы
  print form_end();

  //ссылка "назад"
  print "<p><a class='chap' href='?mod=filearch2_cats_list'>{$l_filearch2[1000]}</a></p>";
  print "<br />";
  print "<br />";

?>