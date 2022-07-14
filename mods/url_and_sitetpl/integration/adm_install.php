<?php
  //////////////////////////////////////////////////////////////////////////////
  // CMS Ortus
  // File archive M1
  // 2007 (C) Fedortchenko A.A. (antf@inbox.ru, antf@pochta.ru)
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Инсталлятор модуля
  //////////////////////////////////////////////////////////////////////////////


  error_reporting(E_ALL & ~E_NOTICE);
  session_start();


  //////////////////////////////////////////////////////////////////////////////
  // подключаем модули
  //////////////////////////////////////////////////////////////////////////////

  include("../../../engine/common/func.inc");
  include("../../../engine/common/db_func.inc");
  include("../../../config/db_connect.inc");
  include("../../../config/site_conf.inc");

  //////////////////////////////////////////////////////////////////////////////
  //инсталлируем модуль для сайта ведущего
  //////////////////////////////////////////////////////////////////////////////

  //вставляем дамп
  $dump = file_get_contents("../../../mods/url_and_sitetpl/install/dump.inc");
  $dump = explode("#is_separator", $dump);
  $cnt = count($dump);
  for($i = 0; $i < $cnt; $i++)
  {
    if(!empty($dump[$i]))
    {
      $dump[$i] = str_replace("CREATE TABLE `", "CREATE TABLE `{$gl_db_prefix}", $dump[$i]);
      $dump[$i] = str_replace("INSERT INTO `",  "INSERT INTO  `{$gl_db_prefix}",  $dump[$i]);

      //$res = mysql_query($dump[$i]);
      $res = mysqli_query(DBBYMYSQLI::$link, $dump[$i]);
      if(!$res)
        print "Can't execute this query {$dump[$i]} <br>".mysqli_error(DBBYMYSQLI::$link)."<br>";
    }
  }

  //компируем директориии из корневой директории модуля в нужные места
  copy_dir("../../../mods/url_and_sitetpl/langfiles/", "../../../langfiles/");


  //////////////////////////////////////////////////////////////////////////////
  //инсталлируем модуль для всех сайтов ведомых
  //////////////////////////////////////////////////////////////////////////////

  $dir = opendir("../../../config/sites");
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..')
      $sites[] = $file;
  }
  closedir($dir);

  if(is_array($sites))
  {
    $cnt = count($sites);
    for($i = 0; $i < $cnt; $i++)
    {
      //подключаем файл с параметрами сайта
      include("../../../config/sites/{$sites[$i]}");
      //вставляем дамп
      //$db1   = mysql_connect($s_db_server, $s_db_user, $s_db_psw);
      $db1 = mysqli_connect($s_db_server, $s_db_user, $s_db_psw, $s_db_name);
      //mysql_select_db($s_db_name, $db1);
      $dump = file_get_contents("../../../mods/url_and_sitetpl/install/dump.inc");
      $dump = explode("#is_separator", $dump);

      $cnt2 = count($dump);
      for($b = 0; $b < $cnt2; $b++)
      {
        if(!empty($dump[$b]))
        {
          $dump[$b] = str_replace("CREATE TABLE `", "CREATE TABLE `{$s_db_prefix}", $dump[$b]);
          $dump[$b] = str_replace("INSERT INTO `",  "INSERT INTO  `{$s_db_prefix}", $dump[$b]);

          //$res = mysql_query($dump[$b], $db1);
          $res = mysqli_query($db1, $dump[$b]);
          if(!$res)
            print "Can't execute this query {$dump[$b]} <br>".mysqli_error($db1)."<br>";
        }
      }
      //mysql_close($db1);
      mysqli_close($db1);

      //компируем директориии из корневой директории модуля в нужные места
      copy_dir("../../../mods/url_and_sitetpl/langfiles/", "../../../{$s_path_to_root}langfiles/");
    }
  }
  print "<p><a href='../../../index.php?adm=mods_list'>Return to the modules list</a></p>";
  //echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=../../../index.php?adm=mods_list'></HEAD></HTML>";
  //return;
?>