<?php
  //////////////////////////////////////////////////////////////////////////////
  // CSS Editor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������� ������ ������ ���������� /css
  //////////////////////////////////////////////////////////////////////////////


  //���������
  print "<h1>{$l_css[1]}</h1>";

  //������ "�������� ������� ������"
  print "<br /><p><a class='Mustred' href='?adm=css_add'>{$l_css[2]}</a></p><br />";

  //������� ������ css-������
  $dir = opendir("{$gl_path_to_root}css");
  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..' && $file != 'admin')
      $css[] = $file;
  }
  closedir($dir);

  if(is_array($css))
  {
    //����� �������
    print "<table width='650' class='SiteTbl' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>{$l_parts[6]}</td>";
      print "<td class='SiteTblTH'>{$l_css[3]}</td>";
      print "<td class='SiteTblTH' width='200'>{$l_css[4]}</td>";
    print "</tr>";
    $cnt = count($css);
    for($i = 0; $i < $cnt; $i++)
    {

      print "<tr>";
      	 //���������� �����
      	 print "<td class='SiteTblLeft'>".($i + 1)."</td>";
        //��� �����
	       print "<td class='SiteTblLeft'>{$css[$i]}</td>";
        //�����
	       print "<td class='SiteTblLeft'>";
          //�������� ����
          print "<a href='?adm=css_text&file={$css[$i]}'>{$l_css[5]}</a><br>";
          //�������
          print "<a href='?adm=css_del&file={$css[$i]}'>{$l_css[6]}</a>";
        print "</td>";
	     print "</tr>";
    }
    print "</table>";
  } else print "<p>{$l_css[7]}</p>";

  //print "<p><a href='?adm=main'>{$l_adm_gen[1]}</a></p>";
?>