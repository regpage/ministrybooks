<?php
  //////////////////////////////////////////////////////////////////////////////
  // CSS Editor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //�������� CSS
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $file = correct_input($_GET['file']);
  if(empty($file))
    $file = correct_input($_POST['file']);

  //////////////////////////////////////////////////////////////////////////////
  //���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $css = $_POST['css'];
    if(false)
      $css = stripslashes($css);

    save_in_file("{$gl_path_to_root}css/{$file}", $css, 'w');
  }

  //////////////////////////////////////////////////////////////////////////////
  //�����
  //////////////////////////////////////////////////////////////////////////////

  //���������
  print "<h1>{$l_css[14]} :: {$file}</h1>";

  //��������� ��� css-�����
  $css = file_get_contents("css/{$file}");

  //��������� ������
  $form_line_tpl = "<tr><td>{field}</td></tr>";

  //������� ������
  if(!empty($errors))
    print form_print_errors($errors);

  //��� �����
  print "<form action='' method='post'>";
    print "<table  cellspacing='0' cellpadding='0' border='0'>";
      print "<tr><td>";
        print "<textarea id='css' style='margin-left:10px' name='css' rows='33' class='SiteFTextareaL'>{$css}</textarea>";
      print "</td></tr>";
      print "<tr><td>";
        print "<input class='SiteFButton' type='submit' name='save' value='{$l_adm_gen[2]}'><input type='button' value='{$l_adm_gen[4]}' class='SiteFButton' onClick=\"location.href='?adm=css_list'\">";
      print "</td></tr>";
    print "</table>";


  //������� ����
  print form_create_hidden('file', $file);
  print "</form>";


?>