<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления фрагментами кода
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль выводит список фрагментов кода
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_codefragms[1]}</h1>";

  //опция добавить
  print "<br /><p><a class='Mustred' href='?adm=codesfragms_add'>{$l_codefragms[2]}</a></p><br />";

  //формируем массив, содержащий список файлов директории codesfragms
  $dir = opendir("{$gl_path_to_root}codesfragms");
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..' && $file != 'admin' )
      $codesfragms[] = $file;
  }
  closedir($dir);

  //выводим список фрагментов
  if(is_array($codesfragms))
  {
    //шапка таблицы
    print "<table width='650' class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>{$l_parts[6]}</td>";
      print "<td class='SiteTblTH' >{$l_codefragms[3]}</td>";
      print "<td class='SiteTblTH' width='100'>{$l_codefragms[4]}</td>";
      print "<td class='SiteTblTH' width='200'>{$l_codefragms[5]}</td>";
    print "</tr>";
    $cnt = count($codesfragms);
    for($i = 0; $i < $cnt; $i++)
    {

      print "<tr>";
      	 //порядковый номер
      	 print "<td class='SiteTblLeft'>".($i + 1)."</td>";
	       //файл
	       print "<td class='SiteTblLeft'>{$codesfragms[$i]}</td>";
        //код
        print "<td class='SiteTblLeft'>[CODEFR={$codesfragms[$i]}]</td>";
	       //опции
	       print "<td class='SiteTblLeft'>";
          //редактор кода
          print "<a href='?adm=codesfragms_text&file={$codesfragms[$i]}'>{$l_codefragms[6]}</a><br />";
          //удалить
          print "<a href='?adm=codesfragms_del&file={$codesfragms[$i]}'>{$l_codefragms[7]}</a>";
          print "</td>";
	     print "</tr>";
    }
    print "</table>";
  } else print "<p>{$l_codefragms[8]}</p>";

  //ссылка "на главную"
  //print "<p><a href='?adm=main'>{$l_adm_gen[1]}</a></p>";

  //информация
  print "<h2>{$l_adm_gen[20]}</h2>";
  print "<ol>";
    print "<li>{$l_codefragms[9]}</li>";
    print "<li>{$l_codefragms[10]}</li>";
  print "</ol>";
?>