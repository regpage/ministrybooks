<?php

  //////////////////////////////////////////////////////////////////////////////
  // ������� ������ ����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>Formularium :: {$l_forms[74]}</h1>";

  //����, �������� �����
  print "<br><p><a class='Mustred' href='index.cfm?mod=forms_add'>{$l_forms[88]}</a>&nbsp;|&nbsp;<a class='Mustred' href='index.cfm?mod=forms_message_list'>{$l_forms[75]}</a></p><br>";

  ///�������� ������
  $query = "SELECT *
              FROM {$gl_db_prefix}forms
             ORDER BY pos";
  $results = db_select($query);

  if(is_array($results))
  {
    //����� �������
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>pos</td>";
      print "<td class='SiteTblTH'>{$l_forms[76]}</td>";
      print "<td class='SiteTblTH' width='230'>{$l_forms[77]}</td>";
      print "<td class='SiteTblTH' width='180'>{$l_forms[78]}</td>";
    print "</tr>";

    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $id_form     = $results[$i]['id_form'];
      $pos         = $results[$i]['pos'];
      $title       = stripslashes($results[$i]['title']);

      print "<tr>";
        //�������
        print "<td class='SiteTblLeft'>{$pos}</td>";
        //���������
        print "<td class='SiteTblLeft'>{$title}</td>";
        //���
        print "<td class='SiteTblLeft'>&lt;index.cfm?mod=forms_create_form($id_form); ?&gt;</td>";
        //�����
        print "<td class='SiteTblLeft'>";
          //����
          print "<a href='index.cfm?mod=forms_fields_list&id_form={$id_form}'>{$l_forms[79]}&nbsp;&gt;&gt;</a><br>";
          //������ e-mail
          print "<a href='index.cfm?mod=forms_email_list&id_form={$id_form}'>{$l_forms[80]}&nbsp;&gt;&gt;</a><br>";
          //���������
          print "<a href='index.cfm?mod=forms_message_list&id_form={$id_form}'>{$l_forms[81]}&nbsp;&gt;&gt;</a><br>";
          //������ ���������
          print "<a href='index.cfm?mod=forms_messtpl&id_form={$id_form}'>{$l_forms[82]}</a><br>";
          //��������� �����
          print "<a href='index.cfm?mod=forms_edit&id_form={$id_form}'>{$l_forms[83]}</a><br>";
          //url-����� �����
          print "<a href='index.cfm?mod=forms_url&id_form={$id_form}'>{$l_forms[84]}</a><br>";
          //������� �����
          print "<a href='index.cfm?mod=forms_del&id_form={$id_form}'>{$l_forms[85]}</a><br>";
        print "</td>";
      print "</tr>";
    }
    print "</table>";
  } else print "<p>{$l_forms[86]}</p>";

  //����
  print $l_forms[87]
?>