<?php
  //////////////////////////////////////////////////////////////////////////////
  //��������, ��� ������ url-����� �������� � ������ $id_form
  //////////////////////////////////////////////////////////////////////////////


  //������������� ����������
  $id_form = intval($_GET['id_form']);

  //�������� �������� �����
  $query = "SELECT title FROM {$gl_db_prefix}forms WHERE id_form = {$id_form}";
  $f_title = stripslashes(db_select_one($query));

  //html-��� ��������
  print "<h1>{$l_forms[118]} {$f_title}</h1>";
  print "<br />";
  print "<p><b>{$l_forms[119]}:</a></b> <a href='index.cfm?mod=forms_get_form&id_form={$id_form}'>index.cfm?mod=forms_get_form&id_form={$id_form}</a></p>";
  print "<br />";
  print "<p><b>{$l_forms[120]}:</a></b> <a href='{$gl_site}index.cfm?mod=forms_get_form&id_form={$id_form}'>{$gl_site}index.cfm?mod=forms_get_form&id_form={$id_form}</a></p>";
  print "<br />";

  //������ "�����"
  print "<p><a class='Mustgreen' href='index.cfm?mod=forms_list'>{$l_forms[121]}</a></p>";
?>