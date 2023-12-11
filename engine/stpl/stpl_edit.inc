<?php
  //////////////////////////////////////////////////////////////////////////////
  // �������� �������� ��������� �������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $t_file = correct_input($_GET['t_file']);
  if(empty($t_file))
    $t_file = correct_input($_POST['t_file']);


  $dir = correct_input($_GET['dir']);
  if(empty($dir))
    $dir = correct_input($_POST['dir']);
  if(empty($dir)) $dir = "forms";


  //�������� ������ ���������� ����� /templates � ������ $dirs
  $dr = opendir($gl_path_to_templates);
  while($file = readdir($dr))
  {
    if($file != '.' && $file != '..' && $file != 'site')
      $dirs[] = $file;
  }
  closedir($dr);

  //�������� ������� ����� /templates/$dir � ������ $files
  $dr = opendir($gl_path_to_templates.$dir.'/');
  while($file = readdir($dr))
  {
    if($file != '.' && $file != '..')
      $files[] = $file;
  }
  closedir($dr);
  if(empty($t_file))
    $t_file = $files[0];


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����, ���������� ���� �������
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $stpl = $_POST['stpl'];
    if(false)
      $stpl = stripslashes($stpl);

    save_in_file("{$gl_path_to_templates}{$dir}/{$t_file}", $stpl, 'w');
  }


  //////////////////////////////////////////////////////////////////////////////
  //����� ���������
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_stpl[2]}</h1>";

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //�����
  print "<form name='form' action='' method='post'>";
    print "<table class='' cellspacing='0' cellpadding='0' border='0'>";
      print "<tr>";
        print "<td class='' colspan='2'>";
          print "<table class='' cellspacing='0' cellpadding='0' border='0'>";
            print "<tr>";
              print "<td class='SiteFCapt'>{$l_stpl[1]}:</td>";
              print "<td class=''>";
                 print "<select name='dirsel' class='SiteFInputL' onChange=\"location.href='?adm=stpl_edit&dir='+document.form.dirsel.value\">";
                 $cnt = count($dirs);
                 for($i = 0; $i < $cnt; $i++)
                 {
                   if($dirs[$i] == $dir)
                     print "<option value='{$dirs[$i]}' selected>{$dirs[$i]}</option>";
                   else
                     print "<option value='{$dirs[$i]}'>{$dirs[$i]}</option>";
                 }
              print "</td>";
            print "</tr>";
          print "</table>";
        print "</td>";
      print "</tr>";
      print "<tr>";
        //�����
        print "<td class=''>";
        $cnt = count($files);
        print "<p>";
        for($i = 0; $i < $cnt; $i++)
        {
          if($files[$i] == $t_file)
            print "{$files[$i]}<br>";
          else
            print "<a href='?adm=stpl_edit&t_file={$files[$i]}&dir={$dir}'>{$files[$i]}</a><br>";
        }
        print "</p>";
        print "</td>";
        //��������
        print "<td class=''>";
          print "<table  cellspacing='0' cellpadding='0' border='0'>";
       	  print "<tr><td>";
            $stpl = file_get_contents("{$gl_path_to_templates}{$dir}/{$t_file}");
            print "<textarea style='margin-left:10px' name='stpl' id='stpl' rows='33' class='SiteFTextareaM'>{$stpl}</textarea>";
	         print "</td></tr>";
	         print "<tr><td>";
	           print "<input class='SiteFButton' type='submit' name='save' value='{$l_adm_gen[2]}'><input type='button' value='{$l_adm_gen[4]}' class='SiteFButton' onClick=\"location.href='?adm=main'\">";
	         print "</td></tr>";
	       print "</table>";
        print "</td>";
      print "</tr>";

  print "</table>";

  //������� ����
  print form_create_hidden('blague', session_id());
  print form_create_hidden('t_file', $t_file);
  print form_create_hidden('dir', $dir);

  print "</form>";


?>