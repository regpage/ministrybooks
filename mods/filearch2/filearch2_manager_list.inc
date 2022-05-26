<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Файловый менеджер, список файлов
  //////////////////////////////////////////////////////////////////////////////


  //инициализация переменных
  $id_cat = intval($_GET['id_cat']);

  //выбираем параметры категории
  $query     = "SELECT * FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat}";
  $results   = db_select($query);
  $cat_title = stripslashes($results[0]['title']);

  //директория с файлами
  $path      = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/";

  //заголовок
  print "<div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div><h4>{$cat_title} :: {$l_filearch2[71]}</h4>";

  print "<form name='form' action='' method='post'>";

  //выбираем файлы директории path в массив files
  $dr = opendir($path);
  while($file = readdir($dr))
  {
    if($file != '.' && $file !='..')
    {
      $files[] = $file;
    }
  }
  closedir($dr);

  //если файлов нет - завершаем работу скрипта
  if(!is_array($files))
  {
    print "<br /><br /><br /><p>{$l_filearch2[60]}<br /><br /><a class='chap' href='?mod=filearch2_cats_list'>{$l_filearch2[1001]}</a></p>";
    return;
  }

  sort($files);

  //таблица, шапка
  print "<table class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
  print "<tr>";
  print "<td class='SiteTblTH'><input type='checkbox' name='sel_all' onClick='var o=this.form.elements;for(var i=0;i<o.length;i++)if(o[i].type==\"checkbox\")o[i].checked=this.checked'></td>";
  print "<td class='SiteTblTH'>{$l_filearch2[73]}</td>";
  print "<td class='SiteTblTH'>{$l_filearch2[74]}</td>";
  print "</tr>";

  $cnt = count($files);
  for($i = 0; $i < $cnt; $i++)
  {    print "<tr>";
      //checkbox
      print "<td class='SiteTblCenter'><input type='checkbox' name='items[]' value='{$files[$i]}'></td>";
      //имя файла
      print "<td class='SiteTblLeft'><a class='chap' href='{$path}{$files[$i]}' target='_blank'>{$files[$i]}</a></td>";
      //опции
      print "<td class='SiteTblLeft'><a class='chap' href='?mod=filearch2_manager_del&amp;id_cat={$id_cat}&amp;file={$files[$i]}'>{$l_filearch2[75]}</a></td>";
      print "</tr>";
  }

  print "</table>";

  //кнопка удалить выделенные
  print "<p>
           <input type='submit' class='SiteFButton' style='margin-left:0; width:150px' name='delete_all' value='{$l_filearch2[76]}'>
         </p>";
  print "<input type='hidden' name='mod' value='filearch2_manager_del_all'>";

  //ссылка назад
  print "<p><a class='chap' href='?mod=filearch2_items_list&amp;id_cat={$id_cat}'>{$l_filearch2[1002]}</a></p>";

  print "</form>";
  print "<br />";
  print "<br />";

?>