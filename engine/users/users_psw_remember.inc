<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������
  // - ������� ����� "��������� ������"
  // - ������������ ��: ��������� ������ � ������� ����� �������
  //                    ���������� ������������ ������ � �������� ����������� ������
  //////////////////////////////////////////////////////////////////////////////

  print "<h1>{$l_users[48]}</h1>";


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    $login = preg_replace("/[^_0-9a-z-]/", '', $_POST['login']);

    //�������� e-mail ������������
    $email   = stripslashes(db_select_one("SELECT email FROM {$gl_db_prefix}users WHERE login = '{$login}'"));

    if(empty($email))
      $errors[] = str_replace("{login}", $login, $l_users[49]);

    if(empty($errors))
    {
      $id_user = stripslashes(db_select_one("SELECT id_user FROM {$gl_db_prefix}users WHERE login = '{$login}'"));

      //���������� ���
      $code = rand(100000000, 999999999);

      $psw = substr(md5($code), 0, 6);

      //������� ������ ����� ������ �� ���� ����� �������, ���� �� ����
      db_delete("DELETE FROM {$gl_db_prefix}new_passwords WHERE id_user = {$id_user}");

      //��������� ������ � ������� ����� �������
      $query = "INSERT INTO {$gl_db_prefix}new_passwords
                   SET id_psw = NULL,
                       id_user = {$id_user},
                       code = {$code},
                       new_psw = md5('$psw')";
      db_insert($query);


      //���������� ������������ ��������� � �������� ����������� ���������

	     //������ �� ���������
	     $link_for_act = "{$gl_site}?mod=users_chpsw_pub2&id_user={$id_user}&code=".$code;

	     //����� ������
	     $message = file_get_contents("{$gl_path_to_engine_root}config/site_mess_pass_remember.inc");

	     //�������� ����������� � ������ ������
	     //$message = str_replace("{user}", $gl_us_name, $message);
	     $message = str_replace("{activation}", $link_for_act, $message);
	     $message = str_replace("{new_psw}", $psw, $message);

	     //���������
	     $headers = "Content-type: text/plain; charset={$site_email_encoding}\r\n";
	     $headers .= "From: ".$_SERVER['SERVER_NAME']." <".$_SERVER['SERVER_ADMIN'].">\r\n";

	     //���������� ������, ��������� �� �������� � ������, ��� ��������� ��������� �� �������� ��������
	     send_email($email,
	           $site_title.' :: '.$l_users[50],
	           $message,
	           $headers);

      print "<p>{$l_users[51]}</p>";
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //��������� �� �������� ��������� ������
  //if(intval($_GET['mess']) == 1)
  //  print "<p>�� ������� �� ��� e-mail ($email)</p>";

  //�������� ������� ����� �����
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);

  //��������� ������ ���� �����
  $field_tpl = "<tr><td class='AuthFormCapt'>{caption}</td><td>{field}</td></tr>";

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);


  //������ �����
  print "<table cellspacing='0' cellpadding='0' border='0' class=AuthFormTbl width='100%'>";
  print "<form name='rem_f' action='' method='post'>";

  //���� ���
  print work_template($field_tpl, array("{caption}" => $l_users[52],
                                               "{field}" => form_create_input("login", $css = 'SiteFInputS')));

  //������
  print work_template("<tr><td>{field}</td></tr>", array("{caption}" => "&nbsp;",
                                        "{field}" => form_create_submit('save', $value=$l_gen[17], $css = 'SiteFButton')));

  //������� ����
  print form_create_hidden('blague', session_id());


  //����� �����
  print "</form></table>";


?>