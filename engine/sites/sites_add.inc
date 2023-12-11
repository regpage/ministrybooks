<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления ведомыми сайтами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль создает новый ведомый сайт
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация полей формы
    $s_name = correct_input($_POST['s_name']);
    $s_url = correct_input($_POST['s_url']);
    $s_path_to_root = correct_input($_POST['s_path_to_root']);
    $s_path_to_engine = correct_input($_POST['s_path_to_engine']);
    $s_db_name = correct_input($_POST['s_db_name']);
    $s_db_user = correct_input($_POST['s_db_user']);
    $s_db_psw = correct_input($_POST['s_db_psw']);
    $s_db_server = correct_input($_POST['s_db_server']);
    $s_db_encoding = correct_input($_POST['s_db_encoding']);
    $s_db_prefix = correct_input($_POST['s_db_prefix']);

    //формируем файловую структуру сайта ведомого
    if(is_dir($s_path_to_root))
    {
      mkdir("{$s_path_to_root}/codesfragms", 0777);
      mkdir("{$s_path_to_root}/css", 0777);
      mkdir("{$s_path_to_root}/themes", 0777);
      copy_dir("{$gl_path_to_root}css/", "{$s_path_to_root}css/");
      mkdir("{$s_path_to_root}/langfiles", 0777);
      copy_dir("{$gl_path_to_root}langfiles/", "{$s_path_to_root}langfiles/");
      mkdir("{$s_path_to_root}/images", 0777);
      mkdir("{$s_path_to_root}/images/smiles", 0777);
      mkdir("{$s_path_to_root}/content", 0777);
      mkdir("{$s_path_to_root}/config", 0777);
      mkdir("{$s_path_to_root}templates/", 0777);
      copy_dir("{$gl_path_to_root}templates/", "{$s_path_to_root}templates/");
      mkdir("{$s_path_to_root}admin/", 0777);
      copy_dir("{$gl_path_to_root}admin/", "{$s_path_to_root}admin/");
      copy("{$gl_path_to_root}bbd_auth.cfm", "{$s_path_to_root}bbd_auth.cfm");
      copy("{$gl_path_to_root}index.cfm", "{$s_path_to_root}index.cfm");
      copy("{$gl_path_to_root}antispam.php", "{$s_path_to_root}antispam.php");
    } else $errors[] = $l_sites[23];

    //формируем конфигурационный файл сайта (sites/config)
    if(empty($errors))
    {
      $config = "<?php\r\n";
      $config .= "  \$s_name = \"{$s_name}\";\r\n";
      $config .= "  \$s_path_to_root = \"{$s_path_to_root}\";\r\n";
      $config .= "  \$s_path_to_engine = \"{$s_path_to_engine}\";\r\n";
      $config .= "  \$s_url         = \"{$s_url}\";\r\n";
      $config .= "  \$s_db_name     = \"{$s_db_name}\";\r\n";
      $config .= "  \$s_db_server   = \"{$s_db_server}\";\r\n";
      $config .= "  \$s_db_user     = \"{$s_db_user}\";\r\n";
      $config .= "  \$s_db_psw      = \"{$s_db_psw}\";\r\n";
      $config .= "  \$s_db_encoding = \"{$s_db_encoding}\";\r\n";
      $config .= "  \$s_db_prefix   = \"{$s_db_prefix}\";\r\n";
      $config .= "?>\r\n";
      save_in_file("config/sites/{$s_name}.inc", $config, 'w');
    }

    //создаем .htaccess в директории сайта ведомого
    $str = file_get_contents('.htaccess');
    save_in_file("{$s_path_to_root}.htaccess", $str, 'w');
    //формируем index.cfm
    /*$str = "<?php\r\n";
    $str .= "  include(\"config/site_conf.inc\");\r\n";
    $str .= "  include(\"{\$gl_path_to_engine_root}main.inc\");\r\n";
    $str .= "?>";
    save_in_file("{$s_path_to_root}index.cfm", $str, 'w');*/

    //формируем конфигурационный файл для сайта ведомого
    $str = "<?php\r\n";
    $str .= "  \$gl_site_name           = '{$s_name}';\r\n";
    $str .= "  \$gl_path_to_engine_root = '{$s_path_to_engine}';\r\n";
    $str .= "  \$gl_admin_url = '{$gl_site}';\r\n";
    $str .= "  \$gl_db_prefix = '{$s_db_prefix}';\r\n";
    $str .= "?>";
    save_in_file("{$s_path_to_root}config/site_conf.inc", $str, 'w');

    //формируем файл соединения с базой
    $str = "<?php\r\n";
    $str .= "  db_connect(\"{$s_db_server}\", \"{$s_db_user}\", \"{$s_db_psw}\", \"{$s_db_name}\", \"{$s_db_encoding}\"); \r\n";
    $str .= "?>";
    save_in_file("{$s_path_to_root}config/db_connect.inc", $str, 'w');

    //создаем базу данных
    if(empty($errors)) {
      //$db1 = mysql_connect($s_db_server, $s_db_user, $s_db_psw);
      $db1 = mysqli_connect($s_db_server, $s_db_user, $s_db_psw, "");

      mysqli_query($db1, "SET NAMES '{$s_db_encoding}'")
           or die(mysqli_error($db1));
      mysqli_query($db1, "set character_set_client='{$s_db_encoding}'")
           or die(mysqli_error($db1));
      mysqli_query($db1, "set character_set_results='{$s_db_encoding}'")
           or die(mysqli_error($db1));
      mysqli_query($db1, "set collation_connection='{$s_db_encoding}_general_ci'")
           or die(mysqli_error($db1));
     /*
      mysql_query("SET NAMES '{$s_db_encoding}'", $db1);
	     mysql_query ("set character_set_client='{$s_db_encoding}'", $db1);
      mysql_query ("set character_set_results='{$s_db_encoding}'", $db1);
	     mysql_query ("set collation_connection='{$s_db_encoding}_general_ci'", $db1);
    */
      if($db1) {
        //получаем список баз данных
        //$db_list = mysql_list_dbs($db1);
        $db_list = mysqli_query($db1, "SHOW DATABASES");
        //while ($row = mysql_fetch_object($db_list))
        while ($row = mysqli_fetch_object($db_list)) {
          $dbs[] = $row->Database;
        }

        //создаем базу, если ее нет
        if(!in_array($s_db_name, $dbs)) {
          $query = "CREATE DATABASE {$s_db_name}  DEFAULT CHARACTER SET {$s_db_encoding}";
          //$res = mysql_query($query, $db1);
          $res = mysqli_query($db1, $query)
                  or die(mysqli_error($db1));
          //if(mysql_affected_rows($db1) < 1)
          if(mysqli_affected_rows($db1) < 1)
            $errors[] = "{$l_sites[24]} {$s_db_name}.";
        }
        mysqli_select_db($db1, $s_db_name);

        //вставляем дамп
        $dump = file_get_contents("{$gl_path_to_root}config/dump/structure.inc");
        $dump = explode("#is_separator", $dump);
        $cnt = count($dump);
        for($i = 0; $i < $cnt; $i++)
        {
          if(!empty($dump[$i]))
          {
            $dump[$i] = str_replace("CREATE TABLE `", "CREATE TABLE `{$s_db_prefix}", $dump[$i]);
            $dump[$i] = str_replace("INSERT INTO `",  "INSERT INTO `{$s_db_prefix}",  $dump[$i]);

            //$res = mysql_query($dump[$i], $db1);
            $res = mysqli_query($db1, $dump[$i])
                  or die(mysqli_error($db1));
            if(!$res)
              $errors[] = "{$l_sites[25]} {$dump[$i]} <br>".mysqli_error($db1);
          }
        }

      } else "{$l_sites[26]} {$s_db_server}";
      //mysql_close($db1);
      mysqli_close($db1);

      //переходим в список сайтов
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=sites_list'></HEAD></HTML>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  // Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_sites[20]}</h1>";

  //подключаем форму
  include("{$gl_path_to_engine}sites/_sites_edit.inc");

  //ссылка "назад"
  print "<br /><p><a class='Mustgreen' href='?adm=sites_list'>{$l_sites[22]}</a></p>";

?>