<?php
  //////////////////////////////////////////////////////////////////////////////
  //������ ��������� ������������ ����� �� �������
  //////////////////////////////////////////////////////////////////////////////


  //������� ���������������� ���������� �� ���������� ��������
	 unset($_SESSION["{$gl_site_name}_gl_id_user"]);
	 unset($_SESSION["{$gl_site_name}_gl_group"]);
	 setcookie("{$gl_site_name}_auth_login", '', time() - 3600);
	 setcookie("{$gl_site_name}_auth_psw",   '', time() - 3600);

  //��������� �� ������� �������� �����
	 echo "<HTML><HEAD>
	         <META HTTP-EQUIV='Refresh' CONTENT='0; URL={$gl_site}'>
	       </HEAD></HTML>";
	 exit;

?>