<?php
  //////////////////////////////////////////////////////////////////////////////
  //Коннектор, связывает модуль с основным узлом /engine/public/content.inc
  //Выбор страницы модуля в зависимости от значения get-переменной mod
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($gl_mod))
  {
    switch($gl_mod)
    {
      //case 'form':     include("{$gl_path_to_engine_root}mods/form/form.inc");  break;

    }

    if($gl_group == 'admin')
    {
    	 switch($gl_mod)
      {
        //case 'form_settings':     include("{$gl_path_to_engine_root}mods/form/form_settings.inc");  break;
      }
    }
  }
?>