<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Модуль меняет позицию нескольких блоков
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $to_del = $_POST['items'];

  if(is_array($to_del))
  {
  	 foreach($to_del as $key => $value)
  	 {
      $to_del[$key] = intval($value);
      $for_in[] = $value;
  	 }

  	 $for_in = implode(',', $for_in);
  }
  else
  {
    print "<h1>{$l_blockeditor[79]}</h1>";
    print "<p>{$l_blockeditor[80]}<br /><a href='?adm={$gl_adm}&amp;ed_opt=blocks_list&amp;pg={$ed_pg}'>{$l_adm_gen[11]}</a></p>";
    return;
  }


  //print count($to_del);
  //////////////////////////////////////////////////////////////////////////////
  //Обработчик формы, изменение позиции группы элементов
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    $begin_pos = intval($_POST['begin_pos']);

    if(empty($begin_pos))
      $errors[] = "Введите целое положительное число в поле <b>$l_blockeditor[81]</b>.";

		  if(empty($errors))
		  {
		    //меняем позицию выбранных элементов
		    $new_pos = $begin_pos;
		    foreach($to_del as $key => $id_block)
  	   {
        db_update("UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
                      SET pos = {$new_pos}
                    WHERE id_block = {$id_block}");
        $new_pos++;
  	   }

		    //калибруем позицию остальных элементов
			    $results = db_select("SELECT id_block
		                            FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
		                           WHERE id_block NOT IN ({$for_in})
		                             AND id_pg = {$ed_pg}
		                        ORDER BY pos");
		    if(is_array($results))
		    {
		      $cnt = count($results);
		      $tmp_pos = 1;

		      for($i = 0; $i < $cnt; $i++)
		      {
		        if($begin_pos == $tmp_pos) $tmp_pos = $tmp_pos + count($to_del);
		        $tmp_id_block = $results[$i]['id_block'];
		        db_update("UPDATE {$gl_db_prefix}{$ed_tbl_pref}_blocks
		                      SET pos = {$tmp_pos}
		                     WHERE id_block = {$tmp_id_block}");
		        $tmp_pos++;
		      }
		    }
		  }

		  //переходим в список блоков
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm={$gl_adm}&amp;ed_opt=blocks_list&amp;pg={$ed_pg}'></HEAD></HTML>";
    exit;
  }


  //////////////////////////////////////////////////////////////////////////////
  //Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_blockeditor[82]}</h1>";

  //выбираем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $form_linewidg_tpl = file_get_contents("{$gl_path_to_templates}forms/linewidg.htm");

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '');



  //выберите позицию первого элемента
  print work_template($form_lineobl_tpl, array("{caption}" => $l_blockeditor[81],
                                               "{field}" => form_create_input("begin_pos", $css = 'SiteFInputM')));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3],  $css = 'SiteFButton')));

  //скрытые поля
  foreach($to_del as $key => $value)
  {
    print "<input type='hidden' name='items[]' value='$value'>";

  }
  print "</p>";
  print "<input type='hidden' name='adm' value='{$gl_adm}'>";
  print "<input type='hidden' name='pg' value='{$ed_pg}'>";
  print "<input type='hidden' name='ed_opt' value='{$ed_opt}'>";

  //конец формы
  print form_end();
?>