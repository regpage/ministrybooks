<?php
  //////////////////////////////////////////////////////////////////////////////
  error_reporting(E_ALL & ~E_NOTICE);
  session_start();

 
  preg_match("/([\a-z_-]+)bbd_auth.cfm/", $_SERVER['PHP_SELF'], $matches);
  $gl_subdir .= $matches[1];
  $_SESSION['gl_subdir'] = $gl_subdir;
  $gl_site .= $gl_subdir;

  // ,    
  preg_match("/([\a-z_-]+)bbd_auth.cfm/", $_SERVER['PHP_SELF'], $matches);

  //    
		$last = strlen($gl_site) - 1;
		if($gl_site[$last] != '/')
		  $gl_site .= '/';

  if(strpos($matches[1], '//') === false && $gl_subdir != '/')
  {
    $gl_subdir = $matches[1];

    // ,   
		  if($gl_subdir[0] == '/')
		  {
		  	 $len = strlen($gl_subdir);
		    $gl_subdir = substr($gl_subdir, 1, $len - 1);
		  }

  }
  else
    $gl_subdir = '';


  $_SESSION['gl_subdir'] = $gl_subdir;

  $gl_site .= $gl_subdir;

 
  $gl_path_to_root  = $_SERVER['DOCUMENT_ROOT'];

  $inx = strlen($gl_path_to_root) - 1;

  if($gl_path_to_root[$inx] == '/')
    $gl_path_to_root = substr($gl_path_to_root, 0, $inx);
  unset($inx);

  if($gl_subdir[0] != '/')
    $gl_subdir = '/'.$gl_subdir;
  $inx = strlen($gl_subdir) - 1;
  if($gl_subdir[$inx] != '/')
    $gl_subdir = $gl_subdir.'/';
  $gl_path_to_root .= $gl_subdir;


  /////////////////////////////////////////////////////////////////////////////
  //   
  /////////////////////////////////////////////////////////////////////////////

  //      (engine)
  if(empty($gl_path_to_engine_root))
  {
    $gl_path_to_engine_root = $_SERVER['DOCUMENT_ROOT'].$gl_subdir;
  }
  //      (engine)
  $gl_path_to_engine        = $gl_path_to_engine_root."engine/";

  /////////////////////////////////////////////////////////////////////////////
  //  
  /////////////////////////////////////////////////////////////////////////////
  include("{$gl_path_to_root}config/site_conf.inc");
  //    
  include("{$gl_path_to_engine_root}engine/common/db_func.inc");
  // 
  include("{$gl_path_to_engine_root}langfiles/pub_auth.inc");
  //  
  include("{$gl_path_to_root}config/db_connect.inc");

print "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Strict//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd'>
<html xmlns='http://www.w3.org/1999/xhtml'>
<head>
<meta http-equiv='content-type' content='text/html; charset=utf-8' />
<title></title>
<link rel='icon' href='/favicon.ico' type='image/x-icon' />
<link rel='stylesheet' href='css/auth.css' type='text/css' media='screen' />
</head>
<body class='login'>";
print "<center>";
print "<div id='login'>";
print "<table width='300'><tr><td>";
print "<div class='reg'><div class='d1'><div class='d2'><div class='d3'><div class='d4'><div class='d5'><div class='d6'>
         <table><tr><td><div class='mh'></div></td><td valign='top'><div class='pd'><div class='tlt' style='white-space:nowrap;'>$l_auth[7]</div><div>";
  /////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['auth_proceed']))
  {
    // 
       $auth_login = $_POST['auth_login'];
	   $auth_psw   = $_POST['auth_psw'];
	   $auth_login    = strtolower($auth_login);
	   $auth_psw      = strtolower($auth_psw);

	   if(!preg_match("/^[-0-9a-z_]{2,}$/i", $auth_login))
	   {
	     $error = "<div class='mege'>Ошибка логина или пароля</div>";
       return;
	   }
	   if(!preg_match("/^[-0-9a-z_]{5,}$/i", $auth_psw))
	   {
	     $error = "<div class='mege'>Ошибка логина или пароля</div>";
       //return;
	   }

    //   
	   if(empty($error))
	   {
	     $query = "SELECT id_user, name, `group`
	                 FROM {$gl_db_prefix}users
	                WHERE login = '{$auth_login}'
	                  AND psw   = md5('{$auth_psw}')";
	     $results = db_select($query);
	     if(is_array($results))
         {
        $id_user  = $results[0]['id_user'];
        $group    = $results[0]['group'];
        $name     = stripslashes($results[0]['name']);
	     } else 
				{  
				$error = "<div class='mege'>Ошибка логина или пароля</div>"; 
				//return; 
				}
	    }

    //     
	   if(empty($error))
	   {
      $_SESSION["{$gl_site_name}_gl_id_user"] = $id_user;
      $_SESSION["{$gl_site_name}_gl_group"]   = $group;
      $_SESSION["{$gl_site_name}_gl_us_name"]   = $name;

      //   
      include("{$gl_path_to_engine_root}engine/auth/auth_succ.inc");
	   }
  }
  //
  print "{$error}";
  //print "<center>";
  print "<table cellspacing='10' cellpadding='2' border='0'>";
  print "<form action = '' method = 'post'>";
  print "<tr>";
  print "<td class='text' align='right'>{$l_auth[3]}:</td>";
  print "<td><input type='text' class='inputbox' name='auth_login'></td>";
  print "</tr>";
  print "<tr>";
  print "<td class='text' align='right'>{$l_auth[4]}:</td>";
  print "<td><input type='password' class='inputbox' name='auth_psw' value=''></td>";
  print "</tr>";
  print "<tr>";
print "<td></td>";
print "<td>
               <div class = 'submit'><div><input type='submit' class='text_submit' name='auth_proceed' value={$l_auth[6]}></div></div>
             </td>";
  print "</tr>";
  print "</form>";
  print "</table>";
  //print "</center>";
  print "</td></tr></table></div></div></div></div></div></div></div>";
  print "</td></tr></table>";
  print "</center>";
print "</div>";
  print "<p id='backto'><a href='http://ministrybooks.ru/' title='Назад на сайт Публикации онлайн'>&laquo; Назад на сайт Публикации онлайн</a></p>";

  print "</body></html>";

?>