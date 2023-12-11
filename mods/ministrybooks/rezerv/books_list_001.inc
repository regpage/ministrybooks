<?php
//РАСПРЕДЕЛЕНИЕ КНИГ ПО КАТЕГОРИЯМ
	$id_part_prec = intval($_GET['id_part_prec']);   //Инициализация переменной
//Страницы, заголовок
	print "<div style='text-align:right'><a name='top'><img height='40px' src='images/category_title.gif' alt='Books By Category'/></a></div>";
	//выводим список (под)разделов
  $query = "SELECT *
            FROM {$gl_db_prefix}parts
            WHERE id_part_prec = {$id_part_prec}
            ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
      print "<ol class='decimal'>";
    $cnt = count($results);
  
    for($i = 0; $i < $cnt; $i++)
    {
    	  	  	
    	//while($tr !== 0)
    //	{
      $title = stripslashes($results[$i]['title']);
      $pos_r = $results[$i]['pos'];
      $in_site_map = $results[$i]['in_site_map'];
      $id_part = $results[$i]['id_part'];
      $id_part_prec = $results[$i]['id_part_prec'];
   	 print "<li>{$id_part} {$id_part_prec} <a href='?mod=books_list&id_part_prec={$id_part}'>{$title}</a></li>";
      
//l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;l;
        //$query_w = "SELECT *                  
            //FROM {$gl_db_prefix}parts
            //WHERE id_part_prec = {$id_part}";
            
$query_w = "SELECT id_part 
	FROM parts WHERE id_part_prec = {$id_part} UNION SELECT t1.id_part FROM parts t1 JOIN parts t2 ON t1.id_part_prec = t2.id_part 
	WHERE t2.id_part_prec = {$id_part} LIMIT 0, 30"; 
  				
  $results_w = db_select($query_w);
  if(is_array($results_w))
  {
      print "<ul class='decimal'>";
    $cnt_w = count($results_w);
    for($w = 0; $w < $cnt_w; $w++)
    {
      $title_w = stripslashes($results_w[$w]['title']);
      $pos_w = $results_w[$w]['pos'];
      $in_site_map_w = $results_w[$w]['in_site_map'];
      $id_part_w = $results_w[$w]['id_part'];
      $id_part_prec_w = $results_w[$w]['id_part_prec'];
//название категории
   	 print "<li>{$cnt_w} {$id_part_w} {$id_part_prec_w} <a class='contentpagetitle' href='?mod=books_list&id_part_prec={$id_part_w}'>{$title_w}</a></li>";
 ///////////////////////////////////////////////////////////////////////////////////////// 
  //if(!empty(id_part_w))
  //{
     $query_z = "SELECT *
                FROM {$gl_db_prefix}parts_items
               WHERE id_part = {$id_part_w}
               ORDER BY pos";
    $results_z = db_select($query_z);
    if(is_array($results_z))
       {
//шапка таблицы
print "<div style='text-align:left'><img height='40px' src='images/list_of_book.gif' alt='Books By Category'/></div>";
        print "<ol class='bullet'>";     
      $cnt_z = count($results_z);
         	for($j = 0; $j < $cnt_z; $j++)
             	{
              	$id_item_z  = $results_z[$j]['id_item'];
        		$id_parts_z  = $results_z[$j]['id_part'];
        		$type_z     = $results_z[$j]['i_type'];
        		$pos_z      = $results_z[$j]['pos'];
        		$title_z    = stripslashes($results_z[$j]['title']);
        		$id_author_z    = stripslashes($results_z[$j]['id_author']);        
        		$mod_name_z = $results_z[$j]['mod_name'];
        		$params_z   = $results_z[$j]['params'];
        		$params_z   = unserialize(stripslashes($params_z)); 
        		
			$query_k = "SELECT author
                FROM {$gl_db_prefix}parts_author
                WHERE id_author = {$id_author_z}";
      $author_k = db_select_one($query_k);        
          print "<li><a href='?mb={$id_item_z}'>{$title_z}</a> - {$author_k}</li>"; 
           		}   
      print "</ol>";
       }
   // }
  /////////////////////////////////////////////////////////////////////////////////////
     }
 	}   
  	  	
  	  print "</ul>";
	  print "</div>";     
	  print "</div>";

  
  }
//название категории

    //}
	  print "</ol>";
	  print "</div>";     
	  print "</div>";

  }
      	  print "{$tr}";

?>