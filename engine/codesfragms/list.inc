<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ����������� ����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������� ������ ���������� ����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_codefragms[1]}</h1>";

  //����� ��������
  print "<br /><p><a class='Mustred' href='?adm=codesfragms_add'>{$l_codefragms[2]}</a></p><br />";

  //��������� ������, ���������� ������ ������ ���������� codesfragms
  $dir = opendir("{$gl_path_to_root}codesfragms");
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..' && $file != 'admin' )
      $codesfragms[] = $file;
  }
  closedir($dir);

  //������� ������ ����������
  if(is_array($codesfragms))
  {
    //����� �������
    print "<table width='650' class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>{$l_parts[6]}</td>";
      print "<td class='SiteTblTH' >{$l_codefragms[3]}</td>";
      print "<td class='SiteTblTH' width='100'>{$l_codefragms[4]}</td>";
      print "<td class='SiteTblTH' width='200'>{$l_codefragms[5]}</td>";
    print "</tr>";
    $cnt = count($codesfragms);
    for($i = 0; $i < $cnt; $i++)
    {

      print "<tr>";
      	 //���������� �����
      	 print "<td class='SiteTblLeft'>".($i + 1)."</td>";
	       //����
	       print "<td class='SiteTblLeft'>{$codesfragms[$i]}</td>";
        //���
        print "<td class='SiteTblLeft'>[CODEFR={$codesfragms[$i]}]</td>";
	       //�����
	       print "<td class='SiteTblLeft'>";
          //�������� ����
          print "<a href='?adm=codesfragms_text&file={$codesfragms[$i]}'>{$l_codefragms[6]}</a><br />";
          //�������
          print "<a href='?adm=codesfragms_del&file={$codesfragms[$i]}'>{$l_codefragms[7]}</a>";
          print "</td>";
	     print "</tr>";
    }
    print "</table>";
  } else print "<p>{$l_codefragms[8]}</p>";

  //������ "�� �������"
  //print "<p><a href='?adm=main'>{$l_adm_gen[1]}</a></p>";

  //����������
  print "<h2>{$l_adm_gen[20]}</h2>";
  print "<ol>";
    print "<li>{$l_codefragms[9]}</li>";
    print "<li>{$l_codefragms[10]}</li>";
  print "</ol>";
?>