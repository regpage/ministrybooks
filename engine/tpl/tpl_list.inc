<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� �����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������� ������ �������� �����
  //////////////////////////////////////////////////////////////////////////////


  //���������
  print "<h1>{$l_tpl[1]}</h1>";

  //������ �������� ������
  print "<br /><p><a class='Mustred' href='?adm=tpl_add'>{$l_tpl[2]}</a></p><br />";

  //������� ������
  $query = "SELECT id_tpl, maintpl, title, file, pos
              FROM {$gl_db_prefix}sitetpl
             ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    //����� �������
    print "<table width='650' class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      //�������
      print "<td class='SiteTblTH' width='20'>{$l_tpl[3]}</td>";
      //��������
      print "<td class='SiteTblTH'>{$l_tpl[4]}</td>";
      //��������
      print "<td class='SiteTblTH' width='100'>{$l_tpl[5]}</td>";
      //�����
      print "<td class='SiteTblTH' width='200'>{$l_tpl[6]}</td>";
    print "</tr>";

    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $id_tpl = $results[$i]['id_tpl'];
      $maintpl = $results[$i]['maintpl'];
      $file = $results[$i]['file'];
      $pos = $results[$i]['pos'];
      $title  = stripslashes($results[$i]['title']);

      $tpl_path = "{$gl_path_to_templates}site/{$file}.tpl";
      if(file_exists($tpl_path))
      {

        if(filesize($tpl_path) > 0)
          $tpl_caption = $l_tpl[7];
      }
      if(empty($tpl_caption))
        $tpl_caption = "<span class='Mustred'>{$l_tpl[7]}</span>";

      print "<tr>";
          //�������
          print "<td class='SiteTblLeft'>{$pos}</td>";
          //���������
          print "<td class='SiteTblLeft'>{$title}</td>";
          //�������� ��/���
          print "<td class='SiteTblCenter'>{$maintpl}</td>";
          //print "<td class='SiteTblLeft'>{$file}</td>";
          print "<td class='SiteTblLeft'>";
            //������ ������������� ������
            print "<a href='?adm=tpl_text&id_tpl={$id_tpl}'>$tpl_caption</a><br>";
            //������ ��������� �������
            print "<a href='?adm=tpl_edit&id_tpl={$id_tpl}'>{$l_tpl[8]}</a><br>";
            //������ ������� ������
            print "<a href='?adm=tpl_del&id_tpl={$id_tpl}'>{$l_tpl[9]}</a><br>";
          print "</td>";
        print "</tr>";
        $tpl_caption = '';
    }
  }
  print "</table>";

?>