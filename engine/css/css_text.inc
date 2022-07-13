<?php
  //////////////////////////////////////////////////////////////////////////////
  // CSS Editor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Редактор CSS
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $file = correct_input($_GET['file']);
  if(empty($file))
    $file = correct_input($_POST['file']);

  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $css = $_POST['css'];
    if(false) //get_magic_quotes_gpc()
      $css = stripslashes($css);

    save_in_file("{$gl_path_to_root}css/{$file}", $css, 'w');
  }

  //////////////////////////////////////////////////////////////////////////////
  //Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_css[14]} :: {$file}</h1>";

  //загружаем код css-файла
  $css = file_get_contents("css/{$file}");

  //формируем шаблон
  $form_line_tpl = "<tr><td>{field}</td></tr>";

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //код формы
  print "<form action='' method='post'>";
    print "<table  cellspacing='0' cellpadding='0' border='0'>";
      print "<tr><td>";
        print "<textarea id='css' style='margin-left:10px' name='css' rows='33' class='SiteFTextareaL'>{$css}</textarea>";
      print "</td></tr>";
      print "<tr><td>";
        print "<input class='SiteFButton' type='submit' name='save' value='{$l_adm_gen[2]}'><input type='button' value='{$l_adm_gen[4]}' class='SiteFButton' onClick=\"location.href='?adm=css_list'\">";
      print "</td></tr>";
    print "</table>";


  //скрытые поля
  print form_create_hidden('file', $file);
  print "</form>";


?>