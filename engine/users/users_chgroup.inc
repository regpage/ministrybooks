<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ������ ������� ������ ������������ � ������ ����������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $sort = correct_input($_POST['sort']);
  if(empty($sort))
    $sort = correct_input($_GET['sort']);

  $mode = correct_input($_POST['mode']);
  if(empty($mode))
    $mode = correct_input($_GET['mode']);

  $id_user = intval($_POST['id_user']);
  if(empty($id_user))
    $id_user = intval($_GET['id_user']);

  $part = intval($_POST['part']);
  if(empty($part))
    $part = intval($_GET['part']);


  //////////////////////////////////////////////////////////////////////////////
  //������ ������ ������ �������������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT `group`
                FROM {$gl_db_prefix}users
               WHERE id_user = {$id_user}";
    $group = db_select_one($query);
  }


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //���������� ������ �����
    $group = correct_input($_POST['group']);

    //������ ������
    if(empty($errors))
    {
      $query = "UPDATE  {$gl_db_prefix}users
                    SET `group` = '{$group}'
                  WHERE id_user = {$id_user}";
      db_update($query);

	     //��������� � ������ ������������� � ������
	     echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$gl_site}?adm=users_list&part={$part}&mode={$mode}&sort={$sort}'></HEAD></HTML>";
      exit;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_user[28]}</h1>";

  //�������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $form_linewidg_tpl = file_get_contents("{$gl_path_to_templates}forms/linewidg.htm");

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('edit_form', '');

  //��������� ����� � �������� ��� select'a
  $options  = "<option value='users'";
  if($group == 'users')
    $options .= " selected";
  $options .= ">{$l_user[29]}</option>";
  $options .= "<option value='admin'";
  if($group == 'admin')
    $options .= " selected";
  $options .= ">{$l_user[30]}</option>";
  $options  .= "<option value='editors'";
  if($group == 'editors')
    $options .= " selected";
  $options .= ">{$l_user[31]}</option>";

  //�������� ������
  print work_template($form_lineobl_tpl, array("{caption}" => $l_user[32],
                                               "{field}" => form_create_select("group", $options, $css = 'SiteFInputM', $size ='') ));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3],  $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague',  session_id());
  print form_create_hidden('id_user', $id_user);
  print form_create_hidden('sort', $sort);
  print form_create_hidden('mode', $mode);
  print form_create_hidden('part', $part);

  //����� �����
  print form_end();
?>