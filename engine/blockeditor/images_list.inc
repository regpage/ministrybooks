<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль выводит список изображений блока.
  //////////////////////////////////////////////////////////////////////////////


  //инициализация переменныъ
  $id_block = intval($_GET['id_block']);
  $ed_opt    = intval($_GET['ed_opt']);

  //выбираем название блока
  $query = "SELECT content
              FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
             WHERE id_block = {$id_block}";
  $block_title = stripslashes(db_select_one($query));

  //заголовок
  print "<h1>{$block_title} :: {$l_blockeditor[52]}</h1>";

  //добавить блок, ссылка
  print "<br /><p><a class='Mustred' href='{$ed_url}&amp;ed_opt=blocks_images_add&amp;pg={$ed_pg}&amp;id_block={$id_block}'>{$l_blockeditor[53]}</a></p><br />";

  //выбираем изображения
  $query = "SELECT id_img, pos, title, img_min, img_max
              FROM {$gl_db_prefix}{$ed_tbl_pref}_images
             WHERE id_block = {$id_block}
             ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    $cnt = count($results);

    //шапка таблицы
    print "<table class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH'>{$l_blockeditor[54]}</td>";
      print "<td class='SiteTblTH'>{$l_blockeditor[55]}</td>";
      print "<td class='SiteTblTH'>{$l_blockeditor[56]}</td>";
      print "<td class='SiteTblTH'>{$l_blockeditor[57]}</td>";
    print "</tr>";

   for($i = 0; $i < $cnt; $i++)
    {
      $id_img = $results[$i]['id_img'];
      $title = stripslashes($results[$i]['title']);
      $img_min = stripslashes($results[$i]['img_min']);
      $img_max = stripslashes($results[$i]['img_max']);
      $pos = $results[$i]['pos'];
      $path = $ed_path_to_img_for_url;
      $img = "<img src='{$path}{$img_min}' border='0'>";
      if(!empty($img_max))
         $img = "<a href='{$path}{$img_max}' target='_blank'><img src='{$path}{$img_min}' border='0'></a>";

      print "<tr>";
        //позиция
        print "<td class='SiteTblLeft'>{$pos}</td>";
        //заголовок
        print "<td class='SiteTblLeft'>{$title}</td>";
        //изображение
        print "<td class='SiteTblCenter'>{$img}</td>";
        print "<td class='SiteTblLeft'>";
          //параметры
          print "<a href='{$ed_url}&ed_opt=blocks_images_edit&pg={$ed_pg}&id_block={$id_block}&id_img={$id_img}'>{$l_blockeditor[58]}</a><br>";
          //удалить
          print "<a href='{$ed_url}&ed_opt=blocks_images_del&pg={$ed_pg}&id_block={$id_block}&id_img={$id_img}'>{$l_blockeditor[59]}</a>&nbsp;";
        print "</td>";
      print "</tr>";
    }
    print "</table>";
  }  else print "<p>{$l_blockeditor[60]}</p><br>";

  //ссылка "назад"
  print "<p><a class='Mustgreen' href='{$ed_url}&ed_opt=blocks_list&pg={$ed_pg}'>{$l_blockeditor[71]}</a></p>";


?>