<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive M2
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Автозагрузка файлов в категорию $id_cat
  //////////////////////////////////////////////////////////////////////////////


  //инициализация переменных
  $id_cat = intval($_GET['id_cat']);
  if(empty($id_cat))
    $id_cat = intval($_POST['id_cat']);


  //выбираем параметры категории
  $query = "SELECT * FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat}";
  $results = db_select($query);
  $cat_title = stripslashes($results[0]['title']);
  $path_rel      = "content/_filearch2/".sprintf("%03d", $id_cat)."/";
  $path          = "{$gl_path_to_root}content/_filearch2/".sprintf("%03d", $id_cat)."/";


  //////////////////////////////////////////////////////////////////////////////
  //обработчик формы, автозагрузка файлов
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //фильтрация данных формы
    $where = correct_input($_POST['where']);

    //выборка позиции первого файла
    if($where == 'in_begin')
    {
      $max_id = db_select_one("SELECT MAX(id_item) FROM {$gl_db_prefix}filearch2_items WHERE id_cat = {$id_cat}");
      if(empty($max_id)) $max_id = 0;
      $pos = 1;

    }
    if($where == 'in_end')
      $pos = db_select_one("SELECT MAX(pos) FROM {$gl_db_prefix}filearch2_items WHERE id_cat = {$id_cat}") + 1;

    //загружаем файлы
		  $dr = opendir($path);
		  while($file = readdir($dr))
		  {
		    if($file != '.' && $file !='..')
		    {
        if(!db_select_one("SELECT id_item FROM {$gl_db_prefix}filearch2_items WHERE file = '{$file}'"))
        {           $query = "INSERT INTO {$gl_db_prefix}filearch2_items
                      SET id_item = NULL,
                          title = '{$file}',
                          descr = '',
                          date = NOW(),
	                         file = '{$file}',
	                         pos     = {$pos},
	                         id_cat  = {$id_cat}";
          //mysql_query($query);
          mysqli_query(DBBYMYSQLI::$link, $query)
           or die(mysqli_error(DBBYMYSQLI::$link));
           //if(mysql_affected_rows() == 1)
          if(mysqli_affected_rows(DBBYMYSQLI::$link) == 1)
          {
            $inserted[] = $file;
            $added_count = count($inserted);
            $pos++;

          }
          else
          {
            $not_inserted[] = $file;
          }
        }

		    }
		  }
		  closedir($dr);

    //калибруем позицию остальных файлов, если файлы вставлялись в начало
    if($added_count > 0)
    {
    	 if($where == 'in_begin')
    	 {
        $query = "UPDATE {$gl_db_prefix}filearch2_items SET pos = pos + {$added_count} WHERE id_item <= {$max_id} AND id_cat = {$id_cat}";
        db_update($query);
    	 }
    }

  }


  //////////////////////////////////////////////////////////////////////////////
  // Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'><tr><td class=''></td></tr></table><div style='text-align:right'><img src='themes/file_archiv/images/file_archiv.gif'  height='40'></div><h4>{$l_filearch2[51]} \"{$cat_title}\"</h4>";

  //состояние
		if(!empty($_POST))
		{
		  //информация о добавленных файлах
		  if(is_array($inserted))
		  {
		    print "<h2>{$l_filearch2[48]}</h2>";
		    print "<p>";
		    $cnt = count($inserted);
		    for($i = 0; $i < $cnt; $i++)
		    {
		      print $inserted[$i]."<br>";
		    }
		    print "</p>";
		  } else print "<p>{$l_filearch2[50]}</p>";

		  //информация о недобавленных файлах
		  if(is_array($not_inserted))
		  {
      print "<h3>{$l_filearch2[49]}</h3>";
		    print "<p>";
		    $cnt = count($not_inserted);
		    for($i = 0; $i < $cnt; $i++)
		    {
		      print $not_inserted[$i]."<br>";
		    }
		    print "</p>";
		  }
  }

  //опции добавить в начало/конец
  //начало
  $options .= "<option value='in_begin'";
  if($field_type == 'in_begin')
    $options .= ' selected';
  $options .= ">{$l_filearch2[46]}</option>";
  //конец
  $options .= "<option value='in_end'";
  if($field_type == 'in_end')
    $options .= ' selected';
  $options .= ">{$l_filearch2[47]}</option>";

   //загружаем шаблоны
  $form_line_tpl    = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //начало формы
  print "<br />";
  print form_begin('edit_form', '', 'post', 'multipart');

  //добавить в конец или в начало?
  print work_template($form_lineobl_tpl, array("{caption}" => $l_filearch2[45],
                                               "{field}" => form_create_select("where", $options, $css = 'SiteFInputM', $size ='') ));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));
  //скрытые поля
  print form_create_hidden('id_cat', $id_cat);

  //конец формы
  print form_end();
print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'><tr><td class=''>";
  //инфо
  print "<h3>{$l_filearch2[44]}</h3>";
  print "<p>";
  $l_filearch2[42] = str_replace("{path}", $path, $l_filearch2[42]);
  print $l_filearch2[42];
  print $l_filearch2[43];
  print "</p><br /></td></tr></table>";

  //ссылка назад
  print "<p><a class='chap' href='?mod=filearch2_items_list&amp;id_cat={$id_cat}'>{$l_filearch2[1002]}</a></p>";
  print "</td></tr></table>";

?>