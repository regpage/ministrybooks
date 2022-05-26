<?php
  //////////////////////////////////////////////////////////////////////////////
  // Система управления разделами и страницами
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль позволяет поменять права доступа на раздел $id_part
  //для различных групп пользователей.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //Функции
  //////////////////////////////////////////////////////////////////////////////

  //устанавливает права на раздел id_part
  //$id_part - id раздела
  //$apply_on_subparts - применить к подразделам yes/no
  //id_group - 1 - пользователи; 2 - редакторы
  //perm_action - разрешаемое/запрещаемое действие: view - просмотр, edit - редактирование
  //$action - действие: 'allow' - разрешить; 'denied' - запретить
  function set_parts_perm($id_part, $apply_on_subparts, $id_group, $perm_action, $action)
  {
    global $gl_db_prefix;

    if($action == 'denied')
    {
      $query = "SELECT id_perm FROM {$gl_db_prefix}parts_perm_den
                  WHERE id_part = {$id_part}
                   	    AND id_group = {$id_group}
	                       AND act     = '{$perm_action}'";
      $id_perm = db_select_one($query);
      if(!$id_perm)
      {
      	 $query = "INSERT INTO {$gl_db_prefix}parts_perm_den
	                    SET id_perm = NULL,
	                        id_group = {$id_group},
	                        id_part = {$id_part},
	                        act     = '{$perm_action}'";
	       db_insert($query);

      }
    }
    if($action == 'allow')
    {
      $query = "DELETE FROM {$gl_db_prefix}parts_perm_den
                 WHERE id_part = {$id_part}
                   AND id_group = {$id_group}
                   AND act     = '{$perm_action}'";
      db_insert($query);
    }

    if($apply_on_subparts == 'yes')
    {
      $query = "SELECT id_part
                  FROM {$gl_db_prefix}parts
                 WHERE id_part_prec = {$id_part}";
      $results = db_select($query);
      if(is_array($results))
      {
        $cnt = count($results);
        for($i = 0; $i < $cnt; $i++)
        {
          $chld_id_part = $results[$i]['id_part'];
          set_parts_perm($chld_id_part, 'yes', $id_group, $perm_action, $action);
        }
      }
    }
    // print $query;
  }


  //////////////////////////////////////////////////////////////////////////////
  //инициалзируем переменные
  //////////////////////////////////////////////////////////////////////////////

  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = intval($_POST['id_part_prec']);

  $id_part = intval($_GET['id_part']);
  if(empty($id_part))
      $id_part = intval($_POST['id_part']);

  //выбираем название раздела для заголовка
  /*$query = "SELECT title
              FROM parts
             WHERE id_part = {$id_part}";
  $part_title = stripslashes(db_select_one($query));*/


  //////////////////////////////////////////////////////////////////////////////
  // Обработчик формы
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //фильтрация данных формы
    $unreg_view_perm = correct_input($_POST['unreg_view_perm']);
    if($unreg_view_perm != 'yes')
      $unreg_view_perm = 'no';

    $ed_view_perm = correct_input($_POST['ed_view_perm']);
    if($ed_view_perm != 'yes')
      $ed_view_perm = 'no';

    $ed_edit_perm = correct_input($_POST['ed_edit_perm']);
    if($ed_edit_perm != 'yes')
      $ed_edit_perm = 'no';

    $us_view_perm = correct_input($_POST['us_view_perm']);
    if($us_view_perm != 'yes')
      $us_view_perm = 'no';
    //var_dump($_POST); exit;
    $apply_on_subparts = correct_input($_POST['apply_on_subparts']);
    if($apply_on_subparts != 'yes')
      $apply_on_subparts = 'no';

    //меняем права
    if($unreg_view_perm == 'no')
    {
      set_parts_perm($id_part, $apply_on_subparts, 0, 'view', 'denied');
    } else set_parts_perm($id_part, $apply_on_subparts, 0, 'view', 'allow');

    if($ed_view_perm == 'no')
    {
      set_parts_perm($id_part, $apply_on_subparts, 2, 'view', 'denied');
    } else set_parts_perm($id_part, $apply_on_subparts, 2, 'view', 'allow');

    if($ed_edit_perm == 'no')
    {
      set_parts_perm($id_part, $apply_on_subparts, 2, 'edit', 'denied');
    } else set_parts_perm($id_part, $apply_on_subparts, 2, 'edit', 'allow');

    if($us_view_perm == 'no')
    {
      set_parts_perm($id_part, $apply_on_subparts, 1, 'view', 'denied');
    } else set_parts_perm($id_part, $apply_on_subparts, 1, 'view', 'allow');
  }



  //////////////////////////////////////////////////////////////////////////////
  // Выбираем права на текущий раздел
  //////////////////////////////////////////////////////////////////////////////

  //право на просмотр для незарег. пользователей
  $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = 0
               AND act = 'view'";
  $unreg_view_perm = db_select_one($query);
  if(empty($unreg_view_perm))
    $unreg_view_perm = 'yes';

  //право на просмотр для пользователей
  $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = 1
               AND act = 'view'";
  $us_view_perm = db_select_one($query);
  if(empty($us_view_perm))
    $us_view_perm = 'yes';

  //право на просмотр для редакторов
  $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = 2
               AND act = 'view'";
  $ed_view_perm = db_select_one($query);
  if(empty($ed_view_perm))
    $ed_view_perm = 'yes';

  //право на редактирование для редакторов
  $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = 2
               AND act = 'edit'";
  $ed_edit_perm = db_select_one($query);
  if(empty($ed_edit_perm))
    $ed_edit_perm = 'yes';


  //////////////////////////////////////////////////////////////////////////////
  // Форма
  //////////////////////////////////////////////////////////////////////////////

  //заголовок
  print "<h1>{$l_parts[38]}</h1>";

  //загружаем шаблоны
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $tbl_section_tpl = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");

  //выводим ошибки
  if(!empty($errors))
    print form_print_errors($errors);

  //начало формы
  print form_begin('edit_form', '');

  //заголовок "Незарегистр. пользователи"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[39]));

  //право на просмотр
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[40],
                                                  "{field}"   => form_create_checkbox("unreg_view_perm", $unreg_view_perm)));


  //заголовок "Пользователи"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[41]));

  //право на просмотр
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[40],
                                                  "{field}"   => form_create_checkbox("us_view_perm", $us_view_perm)));

  //заголовок "Редакторы"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[42]));

  //право на просмотр
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[40],
                                                  "{field}"   => form_create_checkbox("ed_view_perm", $ed_view_perm)));

  //право на редактирование
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[43],
                                                  "{field}"   => form_create_checkbox("ed_edit_perm", $ed_edit_perm)));

  //заголовок "Настройки"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[44]));

  //Применить к подразделам
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[45],
                                                  "{field}"   => form_create_checkbox("apply_on_subparts", $apply_on_subparts)));

  //кнопки
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //скрытые поля
  print form_create_hidden('blague',  session_id());
  print form_create_hidden('id_part', $id_part);
  print form_create_hidden('id_part_prec', $id_part_prec);

  //конец формы
  print form_end();

  //ссылка назад
  print "<p><a class='Mustgreen' href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_parts[36]}</a></p>";

?>