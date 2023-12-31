<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� � ����������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� �������� ����� ������� �� ������ $id_part
  //��� ��������� ����� �������������.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //�������
  //////////////////////////////////////////////////////////////////////////////

  //������������� ����� �� ������ id_part
  //$id_part - id �������
  //$apply_on_subparts - ��������� � ����������� yes/no
  //id_group - 1 - ������������; 2 - ���������
  //perm_action - �����������/����������� ��������: view - ��������, edit - ��������������
  //$action - ��������: 'allow' - ���������; 'denied' - ���������
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
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = intval($_POST['id_part_prec']);

  $id_part = intval($_GET['id_part']);
  if(empty($id_part))
      $id_part = intval($_POST['id_part']);

  //�������� �������� ������� ��� ���������
  /*$query = "SELECT title
              FROM parts
             WHERE id_part = {$id_part}";
  $part_title = stripslashes(db_select_one($query));*/


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //���������� ������ �����
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

    //������ �����
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
  // �������� ����� �� ������� ������
  //////////////////////////////////////////////////////////////////////////////

  //����� �� �������� ��� �������. �������������
  $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = 0
               AND act = 'view'";
  $unreg_view_perm = db_select_one($query);
  if(empty($unreg_view_perm))
    $unreg_view_perm = 'yes';

  //����� �� �������� ��� �������������
  $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = 1
               AND act = 'view'";
  $us_view_perm = db_select_one($query);
  if(empty($us_view_perm))
    $us_view_perm = 'yes';

  //����� �� �������� ��� ����������
  $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = 2
               AND act = 'view'";
  $ed_view_perm = db_select_one($query);
  if(empty($ed_view_perm))
    $ed_view_perm = 'yes';

  //����� �� �������������� ��� ����������
  $query = "SELECT id_perm
              FROM {$gl_db_prefix}parts_perm_den
             WHERE id_part = {$id_part}
               AND id_group = 2
               AND act = 'edit'";
  $ed_edit_perm = db_select_one($query);
  if(empty($ed_edit_perm))
    $ed_edit_perm = 'yes';


  //////////////////////////////////////////////////////////////////////////////
  // �����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_parts[38]}</h1>";

  //��������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $tbl_section_tpl = file_get_contents("{$gl_path_to_templates}forms/tbl_section.htm");

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('edit_form', '');

  //��������� "�����������. ������������"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[39]));

  //����� �� ��������
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[40],
                                                  "{field}"   => form_create_checkbox("unreg_view_perm", $unreg_view_perm)));


  //��������� "������������"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[41]));

  //����� �� ��������
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[40],
                                                  "{field}"   => form_create_checkbox("us_view_perm", $us_view_perm)));

  //��������� "���������"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[42]));

  //����� �� ��������
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[40],
                                                  "{field}"   => form_create_checkbox("ed_view_perm", $ed_view_perm)));

  //����� �� ��������������
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[43],
                                                  "{field}"   => form_create_checkbox("ed_edit_perm", $ed_edit_perm)));

  //��������� "���������"
  print work_template($tbl_section_tpl,    array("{caption}" => $l_parts[44]));

  //��������� � �����������
  print work_template($form_line_tpl,    array("{caption}" => $l_parts[45],
                                                  "{field}"   => form_create_checkbox("apply_on_subparts", $apply_on_subparts)));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague',  session_id());
  print form_create_hidden('id_part', $id_part);
  print form_create_hidden('id_part_prec', $id_part_prec);

  //����� �����
  print form_end();

  //������ �����
  print "<p><a class='Mustgreen' href='?adm=parts_list&id_part_prec={$id_part_prec}'>{$l_parts[36]}</a></p>";

?>