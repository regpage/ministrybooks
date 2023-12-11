<?php
error_reporting(E_NONE);
$part = "";

if(!empty($_GET['part']))
{
$part = "<b>&nbsp;&nbsp; :: &nbsp;&nbsp;</b> {$l_pages[3]} ";  
$part .= intval($_GET['part']);
}
  if(!empty($gl_page))
  {
  if(empty($id_part_prec))
      $query = "SELECT title
                 FROM {$gl_db_prefix}parts_items
                 WHERE id_item = {$gl_page}";
      $pg_title = @db_select_one($query);
?>
<div id="toc">
<?php
    $ch_path = "{$gl_path_to_root}content/{$gl_page}/ch_{$gl_page}.inc";
    if(file_exists($ch_path))include($ch_path); 

    $path = "{$gl_path_to_root}content/{$gl_page}/{$gl_page}.inc";
    if(file_exists($path) && $_GET['part']<= $pages_count)
        include($path);
    else
    {
      
echo "</div>"; 
echo "<div class='row collapse' id='ministry'>";
        include("{$gl_path_to_engine}errors/errors.inc");    echo "</div>";   
         return;
 }
?>
</div>
<?php  
//  !!!  ВЫВОДИТ ССЫЛКУ < РЕДАКТИРОВАТЬ > НА СТРАНИЦЫ С ТЕКСТАМИ ПУБЛИКАЦИЙ   !!!  
// if($gl_group == 'editors' || $gl_group == 'admin')
if($gl_group == 'admin')
// print "<p><a href='?mod=pages_text&ed_opt=blocks_list&amp;pg={$gl_page}&amp;new_page=1' class='Mustred'>{$l_gen[25]}</a></p>";
   print "<p><a href='?adm=parts_items_pages_text&ed_opt=blocks_list&pg={$gl_page}&id_part={$part}&id_item={$gl_page}'>{$l_gen[25]}</a></p>";
  }
  if(!empty($gl_mod))
  {
    switch($gl_mod)
    {
    case 'basic':     include("{$gl_path_to_engine_root}mods/ministrybooks/basic.inc");  break;
    case 'books_list':     include("{$gl_path_to_engine_root}mods/ministrybooks/books_list.inc");  break;
    case 'by_alphabet':     include("{$gl_path_to_engine_root}mods/ministrybooks/by_alphabet.inc");  break;
    case 'by_author':     include("{$gl_path_to_engine_root}mods/ministrybooks/by_author.inc");  break;
    case 'life_study':     include("{$gl_path_to_engine_root}mods/ministrybooks/life_study.inc");  break;
    case 'conclnt':     include("{$gl_path_to_engine_root}mods/ministrybooks/conclnt.inc");  break;
    case 'high_peak_books':     include("{$gl_path_to_engine_root}mods/ministrybooks/high_peak_books.inc");  break;
    case 'selected_titles':     include("{$gl_path_to_engine_root}mods/ministrybooks/selected_titles.inc");  break;
 //-----------------------------------------------------------------------------------------------  
    case 'search_on_site':    include("{$gl_path_to_engine}search/search.inc");  break;
    case 'search_tips':     include("{$gl_path_to_engine}search/search_tips.inc");  break;
    case 'search_result':     include("{$gl_path_to_engine}search/search_result.inc");  break;
    case 's':     include("{$gl_path_to_engine}search/s.inc");  break;
    case 'dse':     include("{$gl_path_to_engine}search/dse.inc");  break;
//----------------------------------------------------------------------------------------------------
    case 'search_books':    include("{$gl_path_to_engine}fulltext_search/search.inc");  break;
    case 'search_tips_books':     include("{$gl_path_to_engine}fulltext_search/search_tips.inc");  break;
    case 'search_result_books':     include("{$gl_path_to_engine}fulltext_search/search_result.inc");  break;

//-------------------------------------------------------------------------------------------------
    case 'witness_lee_books': include("{$gl_path_to_engine_root}mods/ministrybooks/witness_lee_books.inc");  break;
    case 'kbk_websites': include("{$gl_path_to_engine_root}mods/ministrybooks/kbk_websites.inc");  break;
    case 'watchman_nee_books': include("{$gl_path_to_engine_root}mods/ministrybooks/watchman_nee_books.inc");  break;
    case 'sitemap': include("{$gl_path_to_engine_root}mods/ministrybooks/sitemap.inc");  break;
    case 'copyright_policy': include("{$gl_path_to_engine_root}mods/ministrybooks/copyright_policy.inc");  break;
    case 'kbkbooks': include("{$gl_path_to_engine_root}mods/ministrybooks/kbkbooks.inc");  break;
    case 'categories': include("{$gl_path_to_engine_root}mods/ministrybooks/books_categories.inc");  break;
    case 'fnb': include("{$gl_path_to_engine_root}mods/ministrybooks/fnb.inc");  break;

//===========  резервные переменные    books_categories.inc  ==========================================================================================

      //case 'auth':            include("{$gl_path_to_engine}auth/auth_form_on_page.inc");  break;
      //case 'users_add':       include("{$gl_path_to_engine}users/users_add.inc");  break;
      //case 'users_added':     include("{$gl_path_to_engine}users/users_added.inc");  break;
      //case 'users_descr':     include("{$gl_path_to_engine}users/users_descr.inc");  break;
      //case 'users_list_pub':      include("{$gl_path_to_engine}users/users_list_pub.inc");  break;
      //case 'users_edit_pub':      include("{$gl_path_to_engine}users/users_edit_pub.inc");  break;
      //case 'users_chpsw_pub':     include("{$gl_path_to_engine}users/users_chpsw_pub.inc");  break;
      //case 'users_chpsw_pub2':     include("{$gl_path_to_engine}users/users_chpsw_pub2.inc");  break;
      //case 'users_activation':    include("{$gl_path_to_engine}users/users_activation.inc");  break;
      //case 'users_psw_remember':    include("{$gl_path_to_engine}users/users_psw_remember.inc");  break;
      //case 'pages_text':      include("{$gl_path_to_engine}pages/pages_text.inc");  break;
      //case 'parts_page':      include("{$gl_path_to_engine}parts/parts_page.inc");  break;
      //case 'sitemap':         include("{$gl_path_to_engine}sitemap/sitemap.inc");  break;

//===========  ФАЙЛОВЫЙ АРХИВ =============================================================================================
 
 case 'filearch2_cats_list': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_cats_list.inc"); else  Header('Location: ?mod=errors'); break;
 case 'filearch2_items_list': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_list.inc"); else  Header('Location: ?mod=errors'); break; case 'filearch2_cats_add': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_cats_add.inc");  break;
 case 'filearch2_cats_edit': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_cats_edit.inc"); else  Header('Location: ?mod=errors'); break; case 'filearch2_cats_del': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_cats_del.inc");  break;
 case 'filearch2_items_add': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_add.inc"); else  Header('Location: ?mod=errors'); break; case 'filearch2_items_edit': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_edit.inc"); break;
 case 'filearch2_items_del': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_del.inc"); else  Header('Location: ?mod=errors'); break; case 'filearch2_items_del_all': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_del_all.inc");  break;
 case 'filearch2_items_autoload': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_autoload.inc"); else  Header('Location: ?mod=errors'); break; case 'filearch2_items_detstat': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_detstat.inc");  break;
 case 'filearch2_items_stat': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_items_stat.inc"); else  Header('Location: ?mod=errors'); break; case 'filearch2_manager_list': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_manager_list.inc");  break;
 case 'filearch2_manager_del': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_manager_del.inc"); else  Header('Location: ?mod=errors'); break; case 'filearch2_manager_del_all': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_manager_del_all.inc");  break;
 case 'filearch2_settings': if($gl_group == 'admin' Or $gl_group=='editors') include("{$gl_path_to_engine_root}mods/filearch2/filearch2_settings.inc"); else  Header('Location: ?mod=errors'); break;      
default:  include("{$gl_path_to_engine}errors/errors.inc");
                              //case 'errors': include("{$gl_path_to_engine}errors/errors.inc");  break;    
}
    
                              //if($gl_group == 'admin')
                              //{
                              // switch($gl_mod)
                              // {
                              //    case 'users_edit':      include("{$gl_path_to_engine}users/users_edit.inc");  break;
                              //    case 'users_del':      include("{$gl_path_to_engine}users/users_del.inc");  break;
                              //    case 'users_chgroup':      include("{$gl_path_to_engine}users/users_chgroup.inc");  break;
                              //    case 'pages_edit':      include("{$gl_path_to_engine}pages/pages_edit.inc");  break;
                              // }
                              //    include("{$gl_path_to_engine}errors/errors.inc");
                              // }

  }


  $path = "{$gl_path_to_engine_root}mods/";
  $dir = opendir($path);

  while($file = readdir($dir))
  {
    if($file != '.' && $file != '..' && is_dir("{$path}{$file}"))
    {
      if(file_exists("{$path}{$file}/integration/pub_content.inc"))
        include("{$path}{$file}/integration/pub_content.inc");
    }
  }

  closedir($dir); 
?>
