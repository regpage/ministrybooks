<?php
  //////////////////////////////////////////////////////////////////////////////
  // »нтерфейс управлени€ модул€ми
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //ћодуль выводит список модулей директории /mods
  //////////////////////////////////////////////////////////////////////////////


  //заголовок
  print "<h1>{$l_mods[1]}</h1>";

  //формируем список модулей директории /mods
  $dir = opendir("{$gl_path_to_engine_root}mods");
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..' && $file != 'admin')
      $mods[] = $file;
  }
  closedir($dir);

  if(is_array($mods))
  {
    //шапка таблицы
    print "<br /><br />";
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>{$l_parts[6]}</td>";
      print "<td class='SiteTblTH'>{$l_mods[2]}</td>";
      print "<td class='SiteTblTH' width='200'>{$l_mods[3]}</td>";
    print "</tr>";

    $cnt = count($mods);

    $installed = false;

    for($i = 0; $i < $cnt; $i++)
    {
      //провер€ем инсталлирован ли модуль
      if(file_exists("{$gl_path_to_engine_root}mods/{$mods[$i]}/integration/adm_is_installed.inc"))
        include("{$gl_path_to_engine_root}mods/{$mods[$i]}/integration/adm_is_installed.inc");

      print "<tr>";
      	 //пор€дковый номер
      	 print "<td class='SiteTblLeft'>".($i + 1)."</td>";
	       //директори€ модул€
	       print "<td class='SiteTblLeft'>{$mods[$i]}</td>";
        //опции
	       print "<td class='SiteTblLeft'>";
          //установить
          if($gl_is_main_site == 'yes')
            if($installed != true)
            {
            	 if(file_exists("{$gl_path_to_engine_root}mods/{$mods[$i]}/integration/adm_install.php"))
	               print "<a href='mods/{$mods[$i]}/integration/adm_install.php'>{$l_mods[4]}</a><br>";
            }
          //url
          if(file_exists("{$gl_path_to_engine_root}mods/{$mods[$i]}/integration/adm_get_url.inc"))
            print "<a href='?adm=mods_url&mod={$mods[$i]}'>url</a><br>";
          //print "<a href='?adm=mods_text&file={$mods[$i]}'>info</a><br>";

        print "&nbsp;</td>";
	     print "</tr>";

      $installed = false;
    }
    print "</table>";
  } else print "<p>{$l_mods[5]}</p>";



?>