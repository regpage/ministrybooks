<?php
$id_author_prec = intval($_GET['id_author_prec']);

if(empty($id_author_prec))
{
$query = "SELECT author,id_author,about_author
                FROM {$gl_db_prefix}parts_author";
$results = db_select($query);
$cnt = count($results);
  
          //print "<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;";

for($i = 0; $i < $cnt; $i++)
      {
        $id_author  = $results[$i]['id_author'];
        $author  = $results[$i]['author'];        

          //print "<a class='contentpagetitle' href='?mod=by_author&id_author_prec={$id_author}'>{$author}</a>&nbsp;|&nbsp;";

      }

$id_author_prec=2;
}
//шапка таблицы
print "<div style='text-align:right'><a name='top'><img height='35px' src='images/books_by_witness-lee.gif' alt='Books by Witness Lee'/></a></div>";
print "<p><span class='gold'>Избранные работы Уитнесса Ли</span></p>";

    //Cначала выбераем автора, его ID
$query = "SELECT author
                FROM {$gl_db_prefix}parts_author
                WHERE id_author = {$id_author_prec}";
      $author = db_select_one($query);
//Страницы, заголовок
//print "<span class='bold'>{$author} :: СПИСОК КНИГ</span>";
  {    
    //выводим страницы подкатегории $sql = 'SELECT * FROM `parts_items` WHERE `id_author` = 2'; 
    //$query = "SELECT * FROM {$gl_db_prefix}parts_items WHERE id_author = '2' ORDER BY title";
     $query = 'SELECT * FROM `parts_items` WHERE `id_author` = 2 order by `title`';
    $results = db_select($query);
    if(is_array($results))
    {
print "<ol class='decimal'>";       
//шапка таблицы
      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $id_item  = $results[$i]['id_item'];
        //$id_parts  = $results[$i]['id_part'];
        //$type     = $results[$i]['i_type'];
        //$pos      = $results[$i]['pos'];
        $title    = stripslashes($results[$i]['title']);
        //$id_author    = stripslashes($results[$i]['id_author']);        
        //$mod_name = $results[$i]['mod_name'];
        //$params   = $results[$i]['params'];
        //$params   = unserialize(stripslashes($params));           
   
   //$number = $i + 1;
          //заголовок 
          print "<li><a class ='contentpagetitle' href='?mb={$id_item}'>{$title}</a></li>"; 

      }
          print "</ol>";
    }
  }
?>