<?php
print "<div class='large-12 columns'>
    <ul class='breadcrumbs'>
      <li><a href='index.cfm'>Главная</a></li>
      <li class='current'><a href=''>Карта сайта</a></li>
    </ul>
    <h2>Карта сайта <a href='https://ministrybooks.ru'>www.ministrybooks.ru</a></h2>";
    //выводим страницы подкатегории
    $query = "SELECT *
               FROM {$gl_db_prefix}parts_items WHERE bookstorelink is NULL OR bookstorelink ='' ORDER BY title";
    $results = db_select($query);
    if(is_array($results))
    {
print "<ul class='regular'>
      <li><a href='index.cfm'>Главная</a></li>
      <li><a href='/?mod=by_alphabet'>Книги А-Я</a>
        <ul>"; 
print "<ol>";       
      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $title    = stripslashes($results[$i]['title']);
        $id_item  = $results[$i]['id_item'];
        //$date  = date('d-m-Y', $results[$i]['date']);
       $date  = date("d-m-Y", strtotime($results[$i]['date']));

     		print "<li><a class='contentpagetitle' href='?mb={$id_item}'>{$title}</a> - {$date}</li>"; 
      }
}
print "</ol></ul>"; 
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
/*
  $query = "SELECT *
            FROM {$gl_db_prefix}parts
                        ORDER BY pos";
  $result = db_select($query);
  if(is_array($result))
 {

print "<ul class='regular'>";
   $cnt = count($result);  
    for($i = 0; $i < $cnt; $i++)
    {
      $title = stripslashes($result[$i]['title']);
      $id_part_t = $result[$i]['id_part'];
      $id_part_prec = $results[$i]['id_part_prec'];

    		print "<li><a href='#'><strong>{$title}</strong></a></li>";
//----------------------------------------------------------------------
//###################  ПРОВЕРЯЕМ НАЛИЧИЕ ПОДКАТЕГОРИЙ В КАТЕГОРИИ  ####################
 		$query_w = "SELECT id_part 
					FROM parts WHERE id_part_prec = {$id_part_t} UNION 
					SELECT t1.id_part FROM parts t1 JOIN parts t2 ON t1.id_part_prec = t2.id_part 
					WHERE t2.id_part_prec = {$id_part_t} LIMIT 0, 30"; 
  				
  $results_w = db_select($query_w);
if(is_array($results_w))
  {
 $cnt_w = count($results_w);
//#####  Если категории есть выводим список категорий и содержащихся в них книг  ####################
  	 if($cnt_w > 0)
   { 
     for($w = 0; $w < $cnt_w; $w++)
           {
    $id_part_w = $results_w[$w]['id_part'];
      $id_part_prec_w = $results_w[$w]['id_part_prec'];
      $query_title = "SELECT title FROM {$gl_db_prefix}parts WHERE id_part = {$id_part_w}";                
      $title_w = db_select_one($query_title);
     $query_z = "SELECT *
                FROM {$gl_db_prefix}parts_items
               	WHERE id_part = {$id_part_w}
               	ORDER BY title ASC";
    $results_z = db_select($query_z);
    if(is_array($results_z))
       {
 //###################    Вывод книг всех подкатегорий  ####################
      $cnt_z = count($results_z);
         	for($j = 0; $j < $cnt_z; $j++)
             	{
              	$id_item_z  = $results_z[$j]['id_item'];
        		$id_parts_z  = $results_z[$j]['id_part'];
        		$title_z    = stripslashes($results_z[$j]['title']);
        		$id_author_z    = stripslashes($results_z[$j]['id_author']);        
				$query_k = "SELECT author
                FROM {$gl_db_prefix}parts_author
                WHERE id_author = {$id_author_z}";
      			$author_k = db_select_one($query_k); 
           		$titles[] = array("title" => $title_z, "page" => $id_item_z,  "author" => $author_k);
          		
           		}
        }
   		 }
    }

      sort($titles);   	 
        print "<div class='content' data-section-content=''><ul class='bullet'>";     
          for($t=0; $t<count($titles); $t++) print "<li><a href='?mb={$titles[$t][page]}'>{$titles[$t][title]}</a></li>";
        print "</ul>";
}
      $query_q = "SELECT *
                	FROM {$gl_db_prefix}parts_items
               		WHERE id_part = {$id_part_t}
               		ORDER BY title ASC";
    $results_q = db_select($query_q);
    if(is_array($results_q))
    	{
    print "<ul>";     
      $cnt_q = count($results_q);
      for($q = 0; $q < $cnt_q; $q++)
         	 {
         		$id_item_q  = $results_q[$q]['id_item'];
        		$id_parts_q  = $results_q[$q]['id_part'];
        		$type_q     = $results_q[$q]['i_type'];
        		$pos_q      = $results_q[$q]['pos'];
        		$title_q    = stripslashes($results_q[$q]['title']);
        		$id_author_q    = stripslashes($results_q[$q]['id_author']);        
        		
        		$mod_name_q = $results_q[$q]['mod_name'];
        		$params_q   = $results_q[$q]['params'];
        		$params_q   = unserialize(stripslashes($params_q)); 
					
		$query_k = "SELECT author FROM parts_author WHERE id_author = {$id_author_q}";                
              $author_k = db_select_one($query_k);
             
          print "<li><a href='?mb={$id_item_q}'>{$title_q}</a></li>"; 


}
      print "</ul>";

}
//----------------------------------------------------------------------

	}
print "</ul>";

}
*/
print "<div class='to-top'><a href='#top' class='scroll'>В начало</a></div></div>"; 
?>

