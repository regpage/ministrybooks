<?php
  //////////////////////////////////////////////////////////////////////////////
  // CSS Editor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������� ������� ������ �� �������
  //////////////////////////////////////////////////////////////////////////////


  //������������� ����������
	 $file = correct_input($_GET['file']);
	 $state    = intval($_GET['state']);

  //���������� ���� ������������� ��������
	 if(empty($state))
	 {
    print "<h1>{$l_css[13]}</h1><br><br><br><br><br><div align='center'><br><br><a href='?adm=css_del&file={$file}&state=1'>{$l_adm_gen[5]}</a> <a href='?adm=css_list'>{$l_adm_gen[6]}</a></div>";
  }

  //������� css-file
  if($state == 1)
  {
    if(is_file("css/{$file}"))
      unlink("css/{$file}");

    //��������� � ������ css
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=css_list'></HEAD></HTML>";
    exit;
  }



?>