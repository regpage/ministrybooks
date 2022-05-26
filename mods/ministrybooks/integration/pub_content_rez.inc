<?php
  //$gl_path_to_engine_root - путь к корневой директории сайта
  if(!empty($gl_mod))
  {
  
 switch($gl_mod)
  {

    case 'sitemap': include("{$gl_path_to_engine_root}mods/ministrybooks/sitemap.inc");  break;

  default:  include("{$gl_path_to_engine}errors/errors.inc");  break;

	}
}
?>