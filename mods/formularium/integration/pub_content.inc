<?php
  //////////////////////////////////////////////////////////////////////////////
  // Bulletin Board System
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Коннектор, соединяет модуль с основным узлом /engine/public/content.inc
  //Выборка текущей страницы модуля в зависимости от значения переменной $gl_mod
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($gl_mod))
  {
    if($gl_group == 'admin')
    {
      switch($gl_mod)
    	 {
	       case 'forms_add':          include("{$gl_path_to_engine_root}mods/formularium/forms_add.inc");  break;
	       case 'forms_edit':         include("{$gl_path_to_engine_root}mods/formularium/forms_edit.inc");  break;
	       case 'forms_list':         include("{$gl_path_to_engine_root}mods/formularium/forms_list.inc");  break;
	       case 'forms_del':          include("{$gl_path_to_engine_root}mods/formularium/forms_del.inc");  break;

        case 'forms_fields_add':   include("{$gl_path_to_engine_root}mods/formularium/forms_fields_add.inc");  break;
	       case 'forms_fields_edit':  include("{$gl_path_to_engine_root}mods/formularium/forms_fields_edit.inc");  break;
	       case 'forms_fields_list':  include("{$gl_path_to_engine_root}mods/formularium/forms_fields_list.inc");  break;
	       case 'forms_fields_del':   include("{$gl_path_to_engine_root}mods/formularium/forms_fields_del.inc");  break;

        case 'forms_email_add':   include("{$gl_path_to_engine_root}mods/formularium/forms_email_add.inc");  break;
	       case 'forms_email_edit':  include("{$gl_path_to_engine_root}mods/formularium/forms_email_edit.inc");  break;
	       case 'forms_email_list':  include("{$gl_path_to_engine_root}mods/formularium/forms_email_list.inc");  break;
	       case 'forms_email_del':   include("{$gl_path_to_engine_root}mods/formularium/forms_email_del.inc");  break;

        case 'forms_message_view':   include("{$gl_path_to_engine_root}mods/formularium/forms_message_view.inc");  break;
	       case 'forms_message_del_all':  include("{$gl_path_to_engine_root}mods/formularium/forms_message_del_all.inc");  break;
	       case 'forms_message_list':  include("{$gl_path_to_engine_root}mods/formularium/forms_message_list.inc");  break;
	       case 'forms_message_del':   include("{$gl_path_to_engine_root}mods/formularium/forms_message_del.inc");  break;

        case 'forms_messtpl':      include("{$gl_path_to_engine_root}mods/formularium/forms_messtpl.inc");  break;
        case 'forms_url':      include("{$gl_path_to_engine_root}mods/formularium/forms_url.inc");  break;
  //////////////////////////////////////////////////////////////////////////////
        case 'forms_get_form':          include("{$gl_path_to_engine_root}mods/formularium/forms_get_form.inc");  break;	     
    }
        }

    switch($gl_mod)
    {
     //case 'forms_get_form':          include("{$gl_path_to_engine_root}mods/formularium/forms_get_form.inc");  break;	     
    }

  }
?>