<?php
  //////////////////////////////////////////////////////////////////////////////
  // —истема управлени€ разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //ћодуль переносит подраздел в другой раздел
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализаци€ переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = intval($_POST['id_part_prec']);

  $id_part = intval($_GET['id_part']);
  if(empty($id_part))
      $id_part = intval($_POST['id_part']);

  //////////////////////////////////////////////////////////////////////////////
  // ќбработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    $new_id_part_prec = correct_input($_POST['new_id_part_prec']);

    //переносим раздел
    if(empty($errors))
    {
      //выбираем новую (максимальную) позицию переносимого элемента
      $query = "SELECT MAX(pos) FROM {$gl_db_prefix}parts WHERE id_part_prec = {$new_id_part_prec}";
      $max_pos = db_select_one($query);
      $pos = $max_pos + 1;

      //выбираем старую позицию
      $query = "SELECT pos FROM {$gl_db_prefix}parts WHERE id_part = {$id_part}";
      $old_pos = db_select_one($query);

      //переносим элемент
      $query = "UPDATE  {$gl_db_prefix}parts
                    SET `id_part_prec` = '{$new_id_part_prec}',
                        `pos` = {$pos}
                  WHERE id_part = {$id_part}";
      db_update($query);

      //калибруем позицию остальных элементов
    	 $query = "UPDATE {$gl_db_prefix}parts
	                  SET pos = pos - 1
	                WHERE pos > {$old_pos}
	                  AND id_part_prec = {$id_part_prec}";
       db_update($query);

      //переходим в список подразделов и страниц раздела new_id_part_prec
	     echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$new_id_part_prec}'></HEAD></HTML>";
      exit;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // ‘орма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_parts[71]}</h1>";

  if(empty($new_id_cat))
    $new_id_cat = $id_cat;

  //выбираем опции
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $form_linewidg_tpl = file_get_contents("{$gl_path_to_templates}forms/linewidg.htm");

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '');

  //выборает  существующие разделы и подразделы в виде опций select
  function get_parts($id_part_prec, $cur_id_part_prec, $cur_id_part, $indent)
  {
    global $gl_db_prefix;

    $query = "SELECT id_part, title FROM {$gl_db_prefix}parts WHERE id_part_prec = {$id_part_prec}";
    $results = db_select($query);
    if(is_array($results))
    {
      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $title = stripslashes($results[$i]['title']);
        $id_part = $results[$i]['id_part'];
        if($cur_id_part != $id_part)
        {
          $options .= "<option value='{$id_part}'";
        	 if($id_part == $cur_id_part_prec)
	           $options .= " selected";
	         $options .= ">";
	         for($b = 0; $b < $indent; $b++)
	           $options .= "&nbsp;";
	         $options .= "{$title}</option>";
          if($cur_id_part != $id_part)
            $options .= get_parts($id_part, $cur_id_part_prec, $cur_id_part, $indent + 2);
        }
      }

    }
    return $options;
  }

  if($id_part_prec != 0)
    $options  = "<option value='0'>{$l_parts[72]}</option>";
  $options .= get_parts(0, $id_part_prec, $id_part, 0) ;

  //выберите раздел
  print work_template($form_lineobl_tpl, array("{caption}" => $l_parts[37],
                                               "{field}" => form_create_select("new_id_part_prec", $options, $css = 'SiteFInputM', $size ='') ));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //скрытые пол€
  print form_create_hidden('blague',  session_id());
  print form_create_hidden('id_part', $id_part);
  print form_create_hidden('id_part_prec', $id_part_prec);

  //конец формы
  print form_end();
?>