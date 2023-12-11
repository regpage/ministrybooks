<?php
  //////////////////////////////////////////////////////////////////////////////
  //Модуль позволяет пользователю выйти из системы
  //////////////////////////////////////////////////////////////////////////////


  //удаляем пользовательские переменные из глобальных массивов
	 unset($_SESSION["{$gl_site_name}_gl_id_user"]);
	 unset($_SESSION["{$gl_site_name}_gl_group"]);
	 setcookie("{$gl_site_name}_auth_login", '', time() - 3600);
	 setcookie("{$gl_site_name}_auth_psw",   '', time() - 3600);

  //переходим на главную страницу сайта
	 echo "<HTML><HEAD>
	         <META HTTP-EQUIV='Refresh' CONTENT='0; URL={$gl_site}'>
	       </HEAD></HTML>";
	 exit;

?>