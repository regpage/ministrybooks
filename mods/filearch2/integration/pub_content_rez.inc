<?php
  //////////////////////////////////////////////////////////////////////////////
  // Файловый архив
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Коннектор, соединяет модуль с основным узлом /engine/public/content.inc
  //Выборка текущей страницы модуля в зависимости от значения переменной $gl_mod
  //////////////////////////////////////////////////////////////////////////////
   
     if(!empty($gl_mod))
  {
 if($gl_group == 'admin' Or $gl_group=='editors')
    {
      switch($gl_mod)
    	 {
      	 case 'filearch2_cats_list':       include("{$gl_path_to_engine_root}mods/filearch2/filearch2_cats_list.inc");  break;
      	 case 'filearch2_items_list':      include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_list.inc");  break;
	 case 'filearch2_cats_add':        include("{$gl_path_to_engine_root}mods/filearch2/filearch2_cats_add.inc");  break;
        case 'filearch2_cats_edit':       include("{$gl_path_to_engine_root}mods/filearch2/filearch2_cats_edit.inc"); break;
        case 'filearch2_cats_del':        include("{$gl_path_to_engine_root}mods/filearch2/filearch2_cats_del.inc");  break;
        case 'filearch2_items_add':       include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_add.inc");  break;
        case 'filearch2_items_edit':      include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_edit.inc"); break;
        case 'filearch2_items_del':       include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_del.inc");  break;
        case 'filearch2_items_del_all':   include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_del_all.inc");  break;
        case 'filearch2_items_autoload':  include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_autoload.inc");  break;
        case 'filearch2_items_detstat':   include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_detstat.inc");  break;
        case 'filearch2_items_stat':      include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_stat.inc");  break;
        case 'filearch2_manager_list':    include("{$gl_path_to_engine_root}mods/filearch2/filearch2_manager_list.inc");  break;
        case 'filearch2_manager_del':     include("{$gl_path_to_engine_root}mods/filearch2/filearch2_manager_del.inc");  break;
        case 'filearch2_manager_del_all': include("{$gl_path_to_engine_root}mods/filearch2/filearch2_manager_del_all.inc");  break;
        case 'filearch2_settings':        include("{$gl_path_to_engine_root}mods/filearch2/filearch2_settings.inc");  break;
	 }
    }
                        //switch($gl_mod)
                        //{
                        //case 'filearch2_cats_list':       include("{$gl_path_to_engine_root}mods/filearch2/filearch2_cats_list.inc");  break;
                        //case 'filearch2_items_list':      include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_list.inc");  break;
                        //}
  }
?>