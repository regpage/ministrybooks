<?php
  $query = "SELECT id_page, title  FROM pages_list WHERE page = '{$gl_page}'";
  $results = db_select($query);
  $title     = stripslashes($results[0]['title']);
  $id_page   = stripslashes($results[0]['id_page']);
  print "<h3>{$title}</h3>";
  /*print "<table class='' cellspacing='0' cellpadding='0' border='0' width='688'>";
  print "<tr>";

       $query = "SELECT *
              FROM pages_images
             WHERE id_page = {$id_page}
             ORDER BY pos";
       $results_img = db_select($query);

       $cnt = count($results_img);
       if(is_array($results_img))
       {
         print "<td valign='top'>";
         for($i = 0; $i < $cnt; $i++)
         {
            $img_min = stripslashes($results_img[$i]['img_min']);
            $img_max = stripslashes($results_img[$i]['img_max']);
            $path = "content/pages/{$id_page}/";
            $img = "<img src='{$path}{$img_min}' border='0'>";
            if(!empty($img_max))
              $img = "<a href='{$path}{$img_max}' target='_blank'><img src='{$path}{$img_min}' border='0'></a>";
              print "<br>";
           print $img;
         }
         print "</td>";
       }

    print "<td>";
      if($gl_page != 'main')
      {
      	 $path = "content/pages/{$id_page}/{$id_page}.inc";
	       if(file_exists($path))
	         include($path);
      }
      else
        include("content/main/main.inc");

	     if($gl_group == 'admin')
      {
        print "<p>";
        print "<a href='?mod=pages_images_list&id_page={$id_page}&menu_part={$gl_menu_part}'>изображения</a>&nbsp;&nbsp;";
        print "<a href='?mod=pages_edit&ed_opt=blocks_list&pg={$id_page}'>редактировать</a>";
        print "</p>";
      }
    /*print "</td>";
  print "</tr>";
  print "</table>";*/
?>