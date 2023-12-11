<?php
     /*--------------------------------------------------------------------------------+
      +                                                                                +
      +                                КАТЕГОРИИ КНИГ                                  +
      +                                                                                +
      ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
print "<ul class='breadcrumbs'>
      <li><a href='index.cfm'>Главная</a></li>
      <li class='current'><a href='#'>Книги по категориям</a></li>
    </ul><h2>Книги по категориям</h2><p>Нажмите на категорию, чтобы перейти к списку книг</p>"; 

  $query = "SELECT *
            FROM {$gl_db_prefix}parts
            ORDER BY title ASC";
  $results = db_select($query);

  if(is_array($results))
 {   //  02
    $cnt = count($results);   
 print "<div class='section-container accordion' data-section='accordion' data-options='one_up: false;'>";
    for($i = 0; $i < $cnt; $i++)
    {   // 01
      $id_part = $results[$i]['id_part'];
      $query_q = "SELECT *
                	FROM {$gl_db_prefix}parts_items
               		WHERE id_part = {$id_part}
               		ORDER BY title ASC";
     $results_q = db_select($query_q);
     $cnt_q = count($results_q);

 if($cnt_q > 0)
    {    // 2
     $title = stripslashes($results[$i]['title']); 
         print "<section>
            <h5 class='title' data-section-title=''><a href='index.cfm'><span>{$title} ({$cnt_q})</span></a></h5>";
             print "<div class='content' data-section-content=''>";
                   print "<ol class='bullet'>";
                      for($q = 0; $q < $cnt_q; $q++) 
                         {     // 1
           		$id_item_q  = $results_q[$q]['id_item'];
        	       $title_q    = $results_q[$q]['title'];
        		$id_author_q    = stripslashes($results_q[$q]['id_author']);        

		$query_k = "SELECT author FROM parts_author WHERE id_author = {$id_author_q}";                
              $author_k = db_select_one($query_k);
                           //    print "<li>{$title_q}</li>"; 
          print "<li><a href='?mb={$id_item_q}'>{$title_q}</a> - {$author_k}</li>"; 
         
                          }   // 1
                    print "</ol>"; 
             print "</div>";
       }      // 2
       print "</section>";
    }     //  01
   print "</div>";
 }    // 02
   print "<br><br><br>";
?>

