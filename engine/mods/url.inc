<?php
  //////////////////////////////////////////////////////////////////////////////
  // ��������� ���������� ��������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ���������� ���������� url-������
  //��� ����� ������������ ��������� adm_get_url.inc, ���� ����
  //////////////////////////////////////////////////////////////////////////////


  //������������� ����������
  $mod = correct_input($_GET['mod']);

  //����������� ���������� adm_get_url.inc ���������� ������
  $path = "{$gl_path_to_engine_root}mods/{$mod}/integration/adm_get_url.inc";
  if(file_exists($path))
    include($path);

?>