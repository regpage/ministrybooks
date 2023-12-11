<?php
/*****************************************************************************
#                    Модуль сортировки книг по алфавиту                      #
#                                                                            #
#                           Страницы, заголовок                              #
*****************************************************************************/
$query = "SELECT Left(title, 1) AS subgect FROM {$gl_db_prefix}parts_items GROUP BY Left(title, 1)";
    $result = db_select($query);
    $cntt = count($result);

print "<ul class='breadcrumbs'>
            <li><a href='index.cfm'>Главная</a></li>
            <li class='current'><a href='#'>Книги А-Я</a></li>
    </ul><h2>Книги А-Я</h2>"; 
print "<ul class='button-group'>";
 for($i = 0; $i < $cntt; $i++)
{
$alfavit = $result[$i]['subgect'];
print "<a  class='small button radius scroll' style='margin:0px 2px 4px 0px;' href='?mod=by_alphabet&alph={$alfavit}'>{$alfavit}</a>";      
}
print "<br><a class='small button radius scroll' style='margin:0px 0px 0px 0px;' href='?mod=by_alphabet&&alph=all'>ВСЕ ПУБЛИКАЦИИ</a></ul>";
?>
<?php
$alph = $_GET['alph'];

$alphabet = array (1 => "А",2 => "Б",3 => "В",4 => "Г",5 => "Д",6 => "Е",7 => 'Ж',8 => "З",9 => "И",10 => "К",11 => "Л",12 => "М",13 => "Н",14 => "О",15 => "П",16 => "Р",17 => "С",18 => "Т",19 => "У",20 => "Ф",21 => "Х",22 => "Ц",23 => "Ч",24 => "Ш",25 => "Щ",26 => "Э",27 => "Ю",28 => "Я");

	if(!empty($alph)){$type = $alph;}else{$alph = 'all';}

foreach($alphabet as $key => $type)
{
	if($type == $alph)break; 
}
print "<div style='text-align: left; padding:10px 0px 4px 0px;'>";
if($alph <> 'all'){ print "<img src='images/letters/{$key}.gif' width='42' height='42' alt='{$type}' />";}

print "</div>";
print "<table>
            <thead>
              <tr>
                <th>Название публикации</th>
		  <th style='width: 15%;'>Автор</th>               
              </tr>
            </thead>
            <tbody>"; 
if($alph == all){ 
    $query = "SELECT *
               FROM {$gl_db_prefix}parts_items ORDER BY title ASC";
    $results = db_select($query);
     }
      else
     {
    $query = "SELECT *
               FROM {$gl_db_prefix}parts_items
               WHERE title like '{$type}%' ORDER BY title ASC, pos";
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
        print "<tr>";
        print "<td><a href='?mb={$id_item}'>{$title}</a></td><td>{$author}</td> "; 
        print "</tr>";
      }	           
}
 	print "</tbody></table>"; 
       print "<div class='to-top'><a href='#top' class='scroll'>В начало</a></div>";

?>

