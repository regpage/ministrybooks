<?php
  //////////////////////////////////////////////////////////////////////////////
  //������ ������������ �������� ��������� $id_mess
  //////////////////////////////////////////////////////////////////////////////


  //������������� ����������
  $id_form = intval($_GET['id_form']);
  $id_mess = intval($_GET['id_mess']);
  $part    = intval($_GET['part']);

  //�������� ����� ���������
  $query = "SELECT message FROM {$gl_db_prefix}forms_messages WHERE id_mess = {$id_mess}";
  $message = stripslashes(db_select_one($query));

  //����������� ����� ���������
  $message = convert_bb_tags($message, 'forum');
  $message = nl2br($message);

  //html-��� ��������
  print "<h1>{$l_forms[105]}</h1>";
  print "<p>";
  print $message;
  print "</p>";
  print "<br /><br />";

  //������ �����
  print "<p><a class='Mustgreen' href='index.cfm?mod=forms_message_list&id_form={$id_form}&part={$part}'>{$l_forms[106]}</a></p>";



?>