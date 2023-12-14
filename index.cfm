<?php
  //error_reporting(E_NONE);  
  session_start();
  $_SESSION['gl_session_id'] = session_id();
 
  //url адрес сайта
  $gl_site = "http://".$_SERVER['SERVER_NAME'];
  $gl_subdir='';
  //определяем поддиректорию, в которую установлен сайт
  preg_match("/([\a-z_-]+)index.cfm/", $_SERVER['PHP_SELF'], $matches);


  //адрес сайта ставим конечный слэш
		$last = strlen($gl_site) - 1;
		if($gl_site[$last] != '/')
		  $gl_site .= '/';
  
  if(strpos($matches[1], '//') === false && $gl_subdir != '/')
  {
    $gl_subdir = $matches[1];

    //директория , убираем передний слэш
		  if(substr($gl_subdir, 0, 1) == '/')
		  {
		  	 $len = strlen($gl_subdir);
		    $gl_subdir = substr($gl_subdir, 1, $len - 1);
		  }

  }
  else
    $gl_subdir = '';


  $_SESSION['gl_subdir'] = $gl_subdir;

  $gl_site .= $gl_subdir;

  //определяем путь к корню сайта
  $gl_path_to_root  = $_SERVER['DOCUMENT_ROOT'];
  $inx = strlen($gl_path_to_root) - 1;

  if($gl_path_to_root[$inx] == '/')
    $gl_path_to_root = substr($gl_path_to_root, 0, $inx);
  unset($inx);

  if(substr($gl_subdir, 0, 1) != '/')
    $gl_subdir = '/'.$gl_subdir;
  $inx = strlen($gl_subdir) - 1;
  if($gl_subdir[$inx] != '/')
    $gl_subdir = $gl_subdir.'/';
  $gl_path_to_root .= $gl_subdir;

  //подключаем конфигурационный файл
  include("{$gl_path_to_root}config/site_conf.inc");

  //подключаем следующий основной узел
  include("{$gl_path_to_engine_root}main.inc");
?>
