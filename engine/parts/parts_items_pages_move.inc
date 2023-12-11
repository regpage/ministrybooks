<?php
  //////////////////////////////////////////////////////////////////////////////
  // —истема управлени€ разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //ћодуль переносит страницу id_item в другой раздел
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализаци€ переменных
  //////////////////////////////////////////////////////////////////////////////

  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = intval($_POST['id_part_prec']);

  $id_item = intval($_GET['id_item']);
  if(empty($id_item))
      $id_item = intval($_POST['id_item']);


  //////////////////////////////////////////////////////////////////////////////
  // ќбработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //фильтраци€ данных
    $new_id_part_prec = correct_input($_POST['new_id_part_prec']);

    //переносим страницу
    $query = "SELECT pos FROM {$gl_db_prefix}parts_items WHERE id_item = {$id_item}";
    $old_pos = db_select_one($query);

    $query = "SELECT MAX(pos) FROM {$gl_db_prefix}parts_items WHERE id_part = {$new_id_part_prec}";
    $max_pos = db_select_one($query);
    $pos = $max_pos + 1;

    //калибруем позицию остальных элементов
    $query = "UPDATE {$gl_db_prefix}parts_items
                 SET pos = pos - 1
               WHERE pos > {$old_pos}
                 AND id_part = {$id_part_prec}";
    //print $query; return;
    db_update($query);

    //формируем сообщение
    $query = "UPDATE  {$gl_db_prefix}parts_items
                    SET `id_part` = '{$new_id_part_prec}',
                        `pos`     = {$pos}
                  WHERE id_item = {$id_item}";
    db_update($query);

    //переходим в "новый" раздел
	   echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=parts_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
    exit;

  }


  //////////////////////////////////////////////////////////////////////////////
  // ‘орма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_parts[63]}</h1>";

  //установка начальных значений полей
  if(empty($new_id_cat))
    $new_id_cat = $id_cat;

  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '');

  //формирует список категорий и подкатегорий в виде опций select'a
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
          //if($cur_id_part != $id_part)
            $options .= get_parts($id_part, $cur_id_part_prec, $cur_id_part, $indent + 2);
        }
      }
    }
    return $options;
  }

  $options .= get_parts(0, $id_part_prec, $id_part, 0) ;

  //выберите раздел
  print work_template($form_lineobl_tpl, array("{caption}" => $l_parts[63],
                                               "{field}" => form_create_select("new_id_part_prec", $options, $css = 'SiteFInputM', $size ='') ));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //скрытые пол€
  print form_create_hidden('blague',  session_id());
  print form_create_hidden('id_item', $id_item);
  print form_create_hidden('id_part_prec', $id_part_prec);

  //конец формы
  print form_end();
?>