<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //� ������� ����� ������ ������������� ����� �������� ����� � ������
  //������������ � �������.
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
  //������� �������� ������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST))
  {
    $query = "SELECT login
                FROM {$gl_db_prefix}users
               WHERE id_user = {$id_user}";
    $results = db_select($query);
    if(is_array($results))
    {
      $login =  stripslashes($results[0]['login']);
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //������������� � ���������� ���������� �����
    $login = $_POST['login'];
    $psw   = $_POST['psw'];
    $psw_conf = $_POST['psw_conf'];
    $login = strtolower($login);
    $psw   = strtolower($psw);
    $psw_conf   = strtolower($psw_conf);

    if(!preg_match("/^[_0-9a-z]{2,}$/", $login))
      $errors[] = $l_user[24];
    if(!preg_match("/^[_0-9a-z]{5,}$/", $psw))
      $errors[] = $l_user[25];
    if($psw != $psw_conf)
      $errors[] = $l_user[26];

    //��������� ����� �� ������������
    $query = "SELECT id_user
                FROM {$gl_db_prefix}users
               WHERE login = '{$login}'
                 AND id_user != {$id_user}";
    $result = db_select_one($query);
    if(!empty($result))
      $errors[] = $l_user[27];

    if(empty($errors))
    {
      //������ ���������������� ������� � ��.
      $query = "UPDATE  {$gl_db_prefix}users
                    SET `login` = '{$login}',
                         psw    = md5('{$psw}')
                  WHERE id_user = {$id_user}";
      db_update($query);

      //��������� � ������ ������������� � �������
	     echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL={$gl_site}?adm=users_list&part={$part}&mode={$mode}&sort={$sort}'></HEAD></HTML>";
      exit;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_user[20]}</h1>";

  //�������� �������
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  $form_linewidg_tpl = file_get_contents("{$gl_path_to_templates}forms/linewidg.htm");

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print form_begin('edit_form', '');

  //���� �����
  print work_template($form_lineobl_tpl, array("{caption}" => $l_user[21],
                                               "{field}" => form_create_input("login", 'SiteFInputM', $size ='') ));

  //���� ������
  print work_template($form_lineobl_tpl, array("{caption}" => $l_user[22],
                                               "{field}" => form_create_password('psw', $css = 'SiteFInputM', $size ='') ));

  //����������� ������
  print work_template($form_lineobl_tpl, array("{caption}" => $l_user[23],
                                               "{field}" => form_create_password('psw_conf', $css = 'SiteFInputM', $size ='') ));

  //������
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
                                               "{field}" => form_create_submit('save', $value=$l_adm_gen[3], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague',  session_id());
  print form_create_hidden('id_user', $id_user);
  print form_create_hidden('sort', $sort);
  print form_create_hidden('mode', $mode);
  print form_create_hidden('part', $part);

  //����� �����
  print form_end();
?>