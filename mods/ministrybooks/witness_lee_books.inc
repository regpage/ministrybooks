<?php
//#############################################################################
//##################  Модуль сортировки книг по алфавиту  #####################
//#############################################################################
//###############       Страницы, заголовок  ##################################

$query = "SELECT Left(title, 1) AS subgect FROM {$gl_db_prefix}parts_items GROUP BY Left(title, 1)";
    
    $result = db_select($query);

$cntt = count($result);
print "<ul class='breadcrumbs'>
      <li><a href='index.cfm'>Главная</a></li>
      <li class='current'><a href='#'>Книги Уитнесса Ли</a></li>
    </ul><h2>Книги Уитнесса Ли</h2>"; 

print "<dl class='sub-nav'>
      <dt></dt>
      <dd class='active'><a href='?mod=witness_lee_books&alph=all'>Все</a></dd>
      <dd><a href='/?mod=life_study'>Жизнеизучение Библии</a></dd>
      <dd><a href='/?mod=conclnt'>Заключительные сообщения по Новому Завету</a></dd>
      <dd><a href='?mod=high_peak_books'>Вершина божественного откровения</a></dd>
    </dl>"; 
print "<ul class='button-group'>";
 for($i = 0; $i < $cntt; $i++)
{
$alfavit = $result[$i]['subgect'];
//echo '<p>'.$result[$i]['subgect'].'</p>';

print "<a  class='small button radius scroll' style='margin:0px 2px 4px 0px;' href='?mod=witness_lee_books&alph={$alfavit}'>{$alfavit}</a>";      

}
print "<br><a class='small button radius scroll' style='margin:0px 0px 0px 0px;' href='?mod=witness_lee_books&alph=all'>ВСЕ ПУБЛИКАЦИИ</a></ul><hr>";
?>
<?php

$alph = $_GET['alph'];

$alphabet = array (1 => "А",2 => "Б",3 => "В",4 => "Г",5 => "Д",6 => "Е",7 => 'Ж',8 => "З",9 => "И",10 => "К",11 => "Л",12 => "М",13 => "Н",14 => "О",15 => "П",16 => "Р",17 => "С",18 => "Т",19 => "У",20 => "Ф",21 => "Х",22 => "Ц",23 => "Ч",24 => "Ш",25 => "Щ",26 => "Э",27 => "Ю",28 => "Я");

	if(!empty($alph)){$type = $alph;}else{$alph = 'all';}

foreach($alphabet as $key => $type)
{
	if($type == $alph)break; 
}
/*
print "<div style='text-align: left; padding: 0px 0px 0px 0px;'>";
if($alph <> 'all'){ print "<img src='images/letters/{$key}.gif' width='42' height='42' alt='{$type}' />";}
print "</div>"; 
*/
print "<ol>";
 
if($alph == all){ 

    $query = "SELECT *
               FROM {$gl_db_prefix}parts_items 
               WHERE id_author = '2' ORDER BY title ASC, pos";
    $results = db_select($query);

}
else
{
    
    $query = "SELECT *
               FROM {$gl_db_prefix}parts_items
               WHERE title like '{$type}%' AND id_author = '2' ORDER BY title ASC, pos";
    $results = db_select($query);
}
  
  if(is_array($results))
    {
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
        print "<li><a href='?mb={$id_item}'>{$title}</a></li> "; 
        
      }	           
}
 	print "</ol>"; 
print "<div style='padding:20px 0px 10px 0px;'></div>";


	print "<dl class='sub-nav'>
      <dt></dt>
      <dd class='active'><a href='?mod=witness_lee_books&alph=all'>Все</a></dd>
      <dd><a href='/?mod=life_study'>Жизнеизучение Библии</a></dd>
      <dd><a href='/?mod=conclnt'>Заключительные сообщения по Новому Завету</a></dd>
      <dd><a href='?mod=high_peak_books'>Вершина божественного откровения</a></dd></dl>"; 

       print "<div id='to-top' style='text-align: right; padding:0px 0px 10px 0px;'><div class='to-top'><a href='#top' class='scroll'>В начало</a></div></div>";
/* 

$query = "SELECT Left(title, 1) AS subgect FROM {$gl_db_prefix}parts_items GROUP BY Left(title, 1)";
    
    $result = db_select($query);

$cntt = count($result);
 for($i = 0; $i < $cntt; $i++)
{

echo '<p>'.$result[$i]['subgect'].'</p>';
}
*/
?>

