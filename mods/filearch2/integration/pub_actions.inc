<?php
  //////////////////////////////////////////////////////////////////////////////
  // File archive 
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Коннектор, подключается в основном узле /engine/common/actions.inc
  //Выполняет какие-либо действия или подключает модуль до вывода информации
  //в браузер.
  //////////////////////////////////////////////////////////////////////////////


  //подключаем функции
 //include("{$gl_path_to_engine_root}mods/filearch2/filearch2_func.inc");

  //инициализация переменных модуля
  if(strpos($gl_mod, 'filearch2_') !== false)
  {

    //подключение конфиг. файла
    $f_path = "{$gl_f_path_to_root}config/filearch2_config.inc";
  	 if(file_exists($f_path))
	     include($f_path);

    //шаблон сайта
    if(!empty($filearch2_id_tpl))
	     $gl_id_tpl = $filearch2_id_tpl;

	   //заголовок архива
    if(empty($filearch2_title))
      $filearch2_title =  $l_filearch2[5];

  }
  unset($f_path);

  //подключение модуля в зависимости от значения переменной $gl_act
  if(!empty($gl_act))
  {
		  switch($gl_act)
		  {
		    case 'filearch2_dwnld':     include("{$gl_path_to_engine_root}mods/filearch2/filearch2_dwnld.inc");  break;
		  }
		}


  //формируем заголовок страницы
  if(!empty($gl_mod))
  {
		  if(strpos($gl_mod, 'filearch2_') !== false)
		  {

		    switch($gl_mod)
		    {
		      case 'filearch2_cats_list':  { $site_title =  "{$site_title} :: {$filearch2_title}"; break; }
		      case 'filearch2_items_list':  {
		                                $id_cat= intval($_GET['id_cat']);
                                  $site_title .= ":: {$filearch2_title} :: ".stripslashes(db_select_one("SELECT title FROM {$gl_db_prefix}filearch2_cats WHERE id_cat = {$id_cat}"));
	                                 break;
		                              }
		    }
    }
  }


?>