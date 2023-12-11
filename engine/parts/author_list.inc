<?php
$id_part_prec = intval($_GET['id_part_prec']);

  //заголовок
  if(empty($id_part_prec))
  {
    print "<h1>{$l_parts[81]}</h1>";
  }
  else
  {
    $query = "SELECT title
                FROM {$gl_db_prefix}parts
               WHERE id_part = {$id_part_prec}";
    $title = stripslashes(db_select_one($query));

    print "<h1>{$l_parts[81]}</h1>";
  }

  //навигация в виде хлебной крошки
  if(!empty($id_part_prec))
  {
    $tmp_id_part_prec = $id_part_prec;

    while($tmp_id_part_prec != 0)
    {
      $query = "SELECT title, id_part, id_part_prec
                FROM {$gl_db_prefix}parts
                WHERE id_part = {$tmp_id_part_prec}";
      $results = db_select($query);
      if(!empty($results))
      {
        $tmp_title = stripslashes($results[0]['title']);
        $tmp_id_part = $results[0]['id_part'];
        $tmp_id_part_prec = $results[0]['id_part_prec'];

        if($tmp_id_part != $id_part_prec)
        {
          $navig = "<a class='Mustdarkred' href='?adm=parts_list&id_part_prec={$tmp_id_part}'>{$tmp_title}</a> / ".$navig;
        }
      }
    }
    
    //$navig = $navig."<a class='Mustdarkred' href='?adm=parts_list&id_part_prec={$tmp_id_part}'>$title</a> / ".{$l_parts[81]};
    
    $navig = "<a class='Mustdarkred' href='?adm=parts_list'>{$l_parts[24]}</a> / ".$navig;
    $navig = $navig."<a class='Mustdarkred' href='?adm=parts_list&id_part_prec={$tmp_id_part}'>$title</a> / "."{$l_parts[81]}"; 
     //$navig = $navig."$title ";
   
        
    if(!empty($navig))
    {
      $navig = "<p>{$navig}</p>";
    }

  }

  if(!empty($id_part_prec))
    print $navig;

  print "<br />";
  print "<p><a class='Mustred' href='?adm=author_add&id_part_prec={$id_part_prec}'>{$l_parts[83]}</a></p><br>";
    //шапка таблицы
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0' >";
    print "<tr>";
      print "<td class='SiteTblTH' width='20'>{$l_parts[6]}</td>";
        print "<td class='SiteTblTH'>{$l_parts[7]}</td>";
        print "<td class='SiteTblTH' width='200'>{$l_parts[8]}</td>";
    print "</tr>";

$query = "SELECT author,id_author,pos
                FROM {$gl_db_prefix}parts_author";
$results = db_select($query);
    
$cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
        $id_author  = $results[$i]['id_author'];
        $author  = $results[$i]['author']; 
        $pos  = $results[$i]['pos']; 
      print "<tr>";
        //позиция
        print "<td class='SiteTblLeft' width='40'>{$pos}</td>";
        //название раздела
        print "<td class='SiteTblLeft' width='300'>{$author}</td>";
        //опции
        print "<td class='SiteTblLeft' width='130'>";
          
          //редактировать
          print "<a href='?adm=author_edit&id_part_prec={$id_part_prec}&id_author={$id_author}'>{$l_parts[82]}</a><br>";
          //удалить
          print "<a href='?adm=author_del&id_part_prec={$id_part_prec}&id_author={$id_author}'>{$l_parts[13]}</a><br>";

        print "</td>";
      print "</tr>";
    }
    print "</table>";
  print "<br /><br /><br />"; 
    print "<a class='Mustgreen' href='?adm=parts_list&id_part_prec={$tmp_id_part}'>{$l_parts[64]}</a>";
  print "<br /><br /><br />";
?>