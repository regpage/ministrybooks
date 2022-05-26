<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления ведомыми сайтами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль изменяет параметры ведомого сайта
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $site = correct_input($_POST['site']);
  if(empty($site))
    $site = correct_input($_GET['site']);


  //////////////////////////////////////////////////////////////////////////////
  //выборка предыдущих значений из конф. файла
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    include("config/sites/$site");
  }


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация данных
    $s_name = correct_input($_POST['s_name']);
    $s_url = correct_input($_POST['s_url']);
    $s_path_to_root = correct_input($_POST['s_path_to_root']);
    $s_path_to_engine = correct_input($_POST['s_path_to_engine']);
    $s_db_name = correct_input($_POST['s_db_name']);
    $s_db_user = correct_input($_POST['s_db_user']);
    $s_db_psw = correct_input($_POST['s_db_psw']);
    $s_db_server = correct_input($_POST['s_db_server']);
    $s_db_encoding = correct_input($_POST['s_db_encoding']);

    //формируем конфигурационный файл сайта (sites/config)
    if(empty($errors))
    {
      $config = "<?php\r\n";
      $config .= "  \$s_name = \"{$s_name}\";\r\n";
      $config .= "  \$s_path_to_root = \"{$s_path_to_root}\";\r\n";
      $config .= "  \$s_path_to_engine = \"{$s_path_to_engine}\";\r\n";
      $config .= "  \$s_url = \"{$s_url}\";\r\n";
      $config .= "  \$s_db_name = \"{$s_db_name}\";\r\n";
      $config .= "  \$s_db_server = \"{$s_db_server}\";\r\n";
      $config .= "  \$s_db_user = \"{$s_db_user}\";\r\n";
      $config .= "  \$s_db_psw = \"{$s_db_psw}\";\r\n";
      $config .= "  \$s_db_encoding = \"{$s_db_encoding}\";\r\n";
      $config .= "?>\r\n";

      save_in_file("{$gl_path_to_root}config/sites/{$site}", $config, 'w');
    }

    //формируем файл соединения с базой
    $str = "<?php\r\n";
    $str .= "  db_connect(\"{$s_db_server}\", \"{$s_db_user}\", \"{$s_db_psw}\", \"{$s_db_name}\", \"{$s_db_encoding}\"); \r\n";
    $str .= "?>";
    save_in_file("{$s_path_to_root}config/db_connect.inc", $str, 'w');

    //переходим в список сайтов
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=sites_list'></HEAD></HTML>";
    return;
  }


  //////////////////////////////////////////////////////////////////////////////
  // Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_sites[21]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine}sites/_sites_edit.inc");

  //ссылка "назад"
  print "<p><a class='Mustgreen' href='?adm=sites_list'>{$l_sites[22]}</a></p>";

?>