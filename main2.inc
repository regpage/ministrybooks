<?php

  //error_reporting(E_NONE);
  session_start();
  ////////////////////////////////////////////////////////////////////
  //������������� ���������� ����������, ������������ ������� ��������
  ////////////////////////////////////////////////////////////////////
  //������� ��������
  if(!empty($_POST['mb']))
    $gl_page = preg_replace("/[^a-z0-9-:._]/i", "", $_POST['mb']);
  elseif(!empty($_GET['mb']))
     $gl_page = preg_replace("/[^a-z0-9-:._]/i", "", $_GET['mb']);
  //������� ������ ������� �����������������
  if(!empty($_POST['adm']))
    $gl_adm = preg_replace("/[^a-z0-9_\.]/i", "", $_POST['adm']);
  elseif(!empty($_GET['adm']))
    $gl_adm = preg_replace("/[^a-z0-9_\.]/i", "", $_GET['adm']);

  //������� ������ ��� ������ ����������� ����� �����
  if(!empty($_GET['act']))
    $gl_act = preg_replace("/[^a-z0-9_\.]/i", "", $_GET['act']);
  elseif(!empty($_POST['act']))
    $gl_act = preg_replace("/[^a-z0-9_\.]/i", "", $_POST['act']);

  //������� ������ ���������������� �����
  if(!empty($_POST['mod']))
    $gl_mod = preg_replace("/[^a-z0-9_\.]/i", "", $_POST['mod']);

  elseif(!empty($_GET['mod']))
    $gl_mod = preg_replace("/[^a-z0-9_\.]/i", "", $_GET['mod']);


  /////////////////////////////////////////////////////////////////////////////
  //���������� ������ ��������� ����
  /////////////////////////////////////////////////////////////////////////////
 //���������� ������ !!!!
  $gl_site = "http://".$_SERVER['SERVER_NAME'];
  preg_match("/([\a-z_-]+)index.cfm/", $_SERVER['PHP_SELF'], $matches);
  $gl_subdir .= $matches[1];
  $_SESSION['gl_subdir'] = $gl_subdir;
  $gl_site .= $gl_subdir;
 //���������� ����� !!!!

  //���� � ��������� �������� �������� ����� (����� � �������� ������, ������ engine)
  if(empty($gl_path_to_engine_root))
  {
    $gl_path_to_engine_root = $_SERVER['DOCUMENT_ROOT'].$gl_subdir;
  }
  //���� � ����� � �������� ������ (engine)
  $gl_path_to_engine        = $gl_path_to_engine_root."engine/";
  //���� �  ����������� ��������� BbCode Editor
  $gl_path_to_widg          = "{$gl_path_to_engine_root}ext_prm/widg/";
  //�������� �����
  $gl_path_to_bbcodeeditor  = "{$gl_path_to_engine_root}ext_prm/bbcodeeditor/";
  //���� � ��������
  $gl_path_to_templates     = "{$gl_path_to_root}templates/";

  /////////////////////////////////////////////////////////////////////////////
  //���������� ��������� ������
  /////////////////////////////////////////////////////////////////////////////

  //������� ��� ��������� � ����� ������
  include("{$gl_path_to_engine}common/db_func.inc");
  //������� ���������� � ��������� ������ ����
  include("{$gl_path_to_engine}common/forms_func.inc");
  //�������, �����
  include("{$gl_path_to_engine}common/func.inc");
  //������ ������������ ����������� � ��
  if(file_exists("{$gl_path_to_root}config/db_connect.inc"))
    include("{$gl_path_to_root}config/db_connect.inc");
  else
    { print ""; return; }
  //������� ���������� ����
  include("{$gl_path_to_engine}common/menu_func.inc");
  //������� ��� ������ � utf-8
  include("{$gl_path_to_engine}common/utf8_func.inc");

  //����������� c �������������� cookie
  if(empty($_SESSION["{$gl_site_name}_gl_group"]))
  {

    if(!empty($_COOKIE["{$gl_site_name}_auth_psw"]))
      include("{$gl_path_to_engine}auth/auth_cookie.inc");
  }

  /////////////////////////////////////////////////////////////////////////////
  //������������� �����������, ������������ ������ ������������
  /////////////////////////////////////////////////////////////////////////////

  $gl_id_user = $_SESSION["{$gl_site_name}_gl_id_user"];
  $gl_group   = $_SESSION["{$gl_site_name}_gl_group"];
  $gl_us_name = $_SESSION["{$gl_site_name}_gl_us_name"];

  if(empty($gl_group))
  {
    $gl_id_user = 0;
    $gl_group   = 'unregistered';
    $gl_us_name = 'guest';
  }
  switch($gl_group)
  {
    case 'editors': $gl_id_group = 2; break;
    case 'user':    $gl_id_group = 1; break;
    case 'admin':   $gl_id_group = -1; break;
    default: $gl_id_group = 0; break;
  }

  /*if(file_exists("{$gl_path_to_engine_root}install"))
  {
    print "<h1>���������</h1>";
    print "<p>������� ����� install �� �������� ���������� �����.</p>";
    return;
  }*/


  //��������� � �������
  if(!empty($gl_adm))
  {
    include("{$gl_path_to_engine}admin/main.inc");
  }
  //��������� � ���������������� �����
  else
  {
    include("{$gl_path_to_engine}public/main.inc");
  }
?>