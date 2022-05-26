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

$id_author_prec=1;
}

if(!empty($id_author_prec)){

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

if($id_author_prec==1){
print "<div class='large-12 columns'>
    <ul class='breadcrumbs'>
      <li><a href='index.cfm'>Главная</a></li>
      <li class='current'><a href=''>Книги Вочмана Ни</a></li>
    </ul>
    <h2>Книги Вочмана Ни</h2>";
print "<p><span class='gold'></span></p>";
//print "<div style='text-align:right'><a name='top'><img height='40px' src='images/watchman-nee_title.gif' alt='Watchman Nee'/></a></div>";
//print "<img align='left' vspace='10' hspace='10' border='1' alt='Вочман Ни' src='/content/76/wnee.jpg' />";
}

if($id_author_prec==2)
{
//print "<div style='text-align:right'><a name='top'><img height='35px' src='images/books_by_witness-lee.gif' alt='Books by Witness Lee'/></a></div>";
}
$query = "SELECT author
                FROM {$gl_db_prefix}parts_author
                WHERE id_author = {$id_author_prec}";
      $author = db_select_one($query);
  {
    
    //выводим страницы подкатегории
    $query = "SELECT *
               FROM {$gl_db_prefix}parts_items
               WHERE id_author = {$id_author_prec}
               ORDER BY title";
    $results = db_select($query);
    if(is_array($results))
    {
//print "<div style='text-align: left;'><img src='images/list_of_book.gif' alt='Books By Author' height='40'></div>";    
 
//print "<div class='mainpage '>";  
print "<ol class='bullet'>";       
      $cnt = count($results);
      for($i = 0; $i < $cnt; $i++)
      {
        $id_item  = $results[$i]['id_item'];
        $id_parts  = $results[$i]['id_part'];
        $type     = $results[$i]['i_type'];
        $pos      = $results[$i]['pos'];
        $title    = stripslashes($results[$i]['title']);
        $id_author    = stripslashes($results[$i]['id_author']);        
        $mod_name = $results[$i]['mod_name'];
        $params   = $results[$i]['params'];
        $params   = unserialize(stripslashes($params));
 
$query = "SELECT author
                FROM {$gl_db_prefix}parts_author
                WHERE id_author = {$id_author}";
      $author = db_select_one($query);
        
       //print "<tr>";
          
         
          //заголовок
          print "<li><a class='contentpagetitle' href='?mb={$id_item}'>{$title}</a></li>"; 
          //print "<td class='SiteTblLeft'>{$author}</td>";          
        //print "</tr>";
      }
print "</ol></div>"; 
      //print "</table>";
  
    }
  }
}
   
?>

