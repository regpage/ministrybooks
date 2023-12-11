<?php
  
  $id_author = intval($_GET['id_author']);
  if(empty($id_author))
  $id_author = intval($_POST['id_author']);


  $id_part_prec = intval($_GET['id_part_prec']);
  if(empty($id_part_prec))
    $id_part_prec = intval($_POST['id_part_prec']);

  $p_save = intval($_GET['p_save']);
  if(empty($p_save))
  $p_save = intval($_POST['p_save']);

  //////////////////////////////////////////////////////////////////////////////
  //     
  //////////////////////////////////////////////////////////////////////////////

 if(!empty($p_save))
{
        print "<div class='message'>$l_parts[89]</div>";

}
  if(empty($_POST))
  {
     $query = "SELECT *
                FROM {$gl_db_prefix}parts_author
               WHERE id_author = {$id_author}";
     $results = db_select($query);    
    if(is_array($results))
    {
       
       $author = stripslashes($results[0]['author']);
       $id_author = $results[0]['id_author'];
       $about_author = stripslashes($results[0]['about_author']);
       $pos = $results[0]['pos'];
       $old_pos = $pos;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // Обработчик формы  
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['save']))
  {
    //,   
    $author = correct_input($_POST['author']);
    $id_author   = intval($_POST['id_author']);
    $about_author = correct_input($_POST['about_author']);
    $pos   = intval($_POST['pos']);
    $old_pos   = intval($_POST['old_pos']);
   if($pos < 1)
      $errors[] = $l_parts[61];

    // 
    if(empty($errors))
    {
      if($old_pos > $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}parts_author
	                        SET pos = pos + 1
	                      WHERE pos >= {$pos}
                         AND pos < {$old_pos}
                         AND id_author = {$id_author}";
      }
      if($old_pos < $pos)
      {
      	 $query_pos = "UPDATE {$gl_db_prefix}parts_author
	                        SET pos = pos - 1
	                      WHERE pos > {$old_pos}
                         AND pos <= {$pos}
                         AND id_author = {$id_author}";
      }
      if(!empty($query_pos))
      {
        db_update($query_pos);
      }
    }
    //  
    if(empty($errors))
    {
        //  
      $query = "UPDATE {$gl_db_prefix}parts_author
                   SET author = '{$author}',
                       pos   = '{$pos}',
                       about_author = '{$about_author}'
                WHERE id_author = {$id_author}";
      db_update($query);
$p_save = 1;
      //    .
      //echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=author_list&id_part_prec={$id_part_prec}'></HEAD></HTML>";
      echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=author_edit&id_part_prec={$id_part_prec}&id_author={$id_author}&p_save={$p_save}'></HEAD></HTML>";
      return;
    }
  }

  print "<h1>{$l_parts[32]}</h1>";

  // 
  include("{$gl_path_to_engine}parts/_author_edit.inc");

  // 
  print "<p><a class='Mustgreen' href='?adm=author_list&id_part_prec={$id_part_prec}'>{$l_parts[36]}</a></p>";

?>