<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ����������� ����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //�������� ��������� ����
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $file = correct_input($_GET['file']);
  if(empty($file))
    $file = correct_input($_POST['file']);


  //////////////////////////////////////////////////////////////////////////////
  //���������� �����, ���������� ���� � �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $codesfragms = $_POST['codesfragms'];
    if(false)
      $codesfragms = stripslashes($codesfragms);

    $codesfragms = preg_replace("/\[CONTENT\]/i", "<?php include(\"{\$gl_path_to_engine}public/content.inc\"); ?>", $codesfragms);
    $codesfragms = preg_replace("/\[MENU=([0-9]+)\]/i", "<?php create_menu($1); ?>", $codesfragms);

    save_in_file("codesfragms/{$file}", $codesfragms, 'w');
  }


  //��������� ��� � ����������
  $codesfragms = file_get_contents("codesfragms/{$file}");


  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_codefragms[15]} :: {$file}</h1>";

  //��������� ������ ����
  //$form_line_tpl = get_tpl_from_file("{$gl_path_to_templates}forms/line1.htm");
  $form_line_tpl = "<tr><td>{field}</td></tr>";

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //������ �����
  print "<form action='' method='post'>";
    print "<table  cellspacing='0' cellpadding='0' border='0'>";
      print "<tr><td>";
        print "<textarea style='margin-left:10px' name='codesfragms' id='codesfragms' rows='33' class='SiteFTextareaL'>{$codesfragms}</textarea>";
      print "</td></tr>";
      print "<tr><td>";
        print "<input class='SiteFButton' type='submit' name='save' value='{$l_adm_gen[2]}'><input type='button' value='{$l_adm_gen[4]}' class='SiteFButton' onClick=\"location.href='?adm=codesfragms_list'\">";
      print "</td></tr>";
    print "</table>";


  //������� ����
  print form_create_hidden('file', $file);

  //������ "�����"
  //print "<p><a href='?adm=main'>{$l_adm_gen[1]}</a></p>";
  print "</form>";


?>
