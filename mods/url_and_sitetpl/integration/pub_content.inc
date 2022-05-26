<?php
  //////////////////////////////////////////////////////////////////////////////
  //Коннектор, соединяет модуль с основным узлом /engine/public/content.inc
  //Выборка текущей страницы модуля в зависимости от значения переменной $gl_mod
  //////////////////////////////////////////////////////////////////////////////


  if(!empty($gl_mod))
  {
    switch($gl_mod)
    {
      //case 'news_list':     include("{$gl_path_to_engine_root}mods/news/news_list.inc");  break;
    }

    if($gl_group == 'admin')
    {
      switch($gl_mod)
    	 {
	       case 'url_and_sitetpl_list':  include("{$gl_path_to_engine_root}mods/url_and_sitetpl/url_and_sitetpl_list.inc");  break;
	       case 'url_and_sitetpl_add':   include("{$gl_path_to_engine_root}mods/url_and_sitetpl/url_and_sitetpl_add.inc");  break;
        case 'url_and_sitetpl_edit':  include("{$gl_path_to_engine_root}mods/url_and_sitetpl/url_and_sitetpl_edit.inc");  break;
        case 'url_and_sitetpl_del':   include("{$gl_path_to_engine_root}mods/url_and_sitetpl/url_and_sitetpl_del.inc");  break;
	     }
    }
  }
?>