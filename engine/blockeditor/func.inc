<?php
  //////////////////////////////////////////////////////////////////////////////
  // Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Фукнции Antf Blockeditor
  //////////////////////////////////////////////////////////////////////////////

  //преобразует блоки страницы id_pg в html код,
  //возвращает html-код
  //$ed_tbl_pref - префикс mysql-таблицы с блоками
  function ed_process_data($ed_tbl_pref, $id_pg)
  {
    global $ed_path_to_img, $ed_path_to_file, $ed_path_to_img_for_url, $nl2br, $gl_db_prefix, $l_gen;

    //текущий номер страницы
    $pg_num = 1;

    //шапка страницы
    $page = "<?php\r\n";
    $page .= "  \$pg_part = intval(\$_GET['pg_part']);\r\n";
    $page .= "  if(empty(\$pg_part)) \$pg_part = 1 ;\r\n\r\n";
    $page .= "  if(\$pg_part == {$pg_num})\r\n";
    $page .= "  {\r\n";
    $page .= "?>\r\n";
    $pg_num++;

    //выбор блоков страницы id_pg
    $query = "SELECT *
                FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks
               WHERE id_pg = {$id_pg}
               ORDER BY pos";
    $results = db_select($query);
    if(is_array($results))
    {
      $cnt_r = count($results);
      for($i = 0; $i < $cnt_r; $i++)
	     {
        $id_block   = $results[$i]['id_block'];
        $type = $results[$i]['type'];
        $gen_type = $results[$i]['gen_type'];
        $text       = stripslashes($results[$i]['content']);
        $params     = $results[$i]['params'];
        $params     = unserialize($params) ;

        if($gen_type == 'newpage')
        {
          $page .= "  <?php }\r\n";
          $page .= "  if(\$pg_part == {$pg_num})\r\n";
          $page .= "  { ?>\r\n";
          $pg_num++;
        }


        if($gen_type == 'text')
        {
          $text = preg_replace("/\[CODEFR=([^\]]+)\]/i", "<?php include(\"codesfragms/$1\"); ?>", $text);
          $text = preg_replace("/\[MENU=([^\]]+)\]/i", "<?php create_menu(\$1); ?>", $text);

        }

	       if($type == 'p_just')
	       {

	         $text = convert_bb_tags($text, 'forum');
          if($nl2br == 'yes')
	           $text = nl2br($text);
	         $text = "<p>{$text}</p>";
	         $page .= $text;

	       }

	       if($type == 'p_just_indent')
	       {
	         $text = convert_bb_tags($text, 'forum');
          if($nl2br == 'yes')
            $text = nl2br($text);
	         $text = "<p class='JustIndent'>{$text}</p>";
	         $page .= $text;
	       }

	       if($type == 'p_left')
	       {
	         $text = convert_bb_tags($text, 'forum');
          if($nl2br == 'yes')
            $text = nl2br($text);
	         $text = "<p class='Left'>{$text}</p>";
	         $page .= $text;
	       }

	       if($type == 'p_right')
	       {
	         $text = convert_bb_tags($text, 'forum');
          if($nl2br == 'yes')
            $text = nl2br($text);
	         $text = "<p class='Right'>{$text}</p>";
	         $page .= $text;
	       }

	       if($type == 'p_center')
	       {
	         $text = convert_bb_tags($text, 'forum');
          if($nl2br == 'yes')
            $text = nl2br($text);
	         $text = "<p class='Center'>{$text}</p>";
	         $page .= $text;
	       }

	       if($type == 'h1')
	       {

	         $text = convert_bb_tags($text, 'forum');
	         //$text = nl2br($text);
	         $text = "<h1>{$text}</h1>";
	         $page .= $text;
	       }

	       if($type == 'h2')
	       {
	         $text = convert_bb_tags($text, 'forum');
	         //$text = nl2br($text);
	         $text = "<h2>{$text}</h2>";
	         $page .= $text;
	       }


	       if($type == 'h3')
	       {
	         $text = convert_bb_tags($text, 'forum');
	         $text = "<h3>{$text}</h3>";
	         $page .= $text;
	       }

	       if($type == 'ul_mark')
	       {
	         $text = convert_bb_tags($text, 'forum');
	         //$text = nl2br($text);
	         $page .= "<ul>";
	         $items = explode("\n", $text);
	         $cnt = count($items);
	         for($b = 0; $b < $cnt; $b++)
	           $page .= "<li>{$items[$b]}</li>";


	         $page .= "</ul>";
	       }

	       if($type == 'ol_numbers')
	       {
	         $text = convert_bb_tags($text, 'forum');
	         //$text = nl2br($text);
	         $page .= "<ol type='1'>";
	         $items = explode("\n", $text);
	         $cnt = count($items);
	          for($b = 0; $b < $cnt; $b++)
	           $page .= "<li>{$items[$b]}</li>";


	         $page .= "</ol>";
	       }

	       if($type == 'ol_letters')
	       {
	         $text = convert_bb_tags($text, 'forum');
	         $page .= "<ol type='a'>";
	         $items = explode("\n", $text);
	         $cnt = count($items);
	          for($b = 0; $b < $cnt; $b++)
	           $page .= "<li>{$items[$b]}</li>";
	         $page .= "</ol>";
	       }

        if($type == 'images')
	       {

	         $in_row = $params['in_row'];

          $query = "SELECT id_img, pos, title, img_min, img_max
             	        FROM {$gl_db_prefix}{$ed_tbl_pref}_images
	                    WHERE id_block = {$id_block}
	                    ORDER BY pos";

          $results_img = db_select($query);
          if(is_array($results_img))
          {

            $cnt_img = count($results_img);
            $page .= "<table class='ImageInBlockTbl' cellspacing='0' cellpadding='0' border='0'><tr>";
            for($b = 0; $b < $cnt_img; $b++)
            {
            	 $title = stripslashes($results_img[$b]['title']);
	             $img_min = stripslashes($results_img[$b]['img_min']);
	             $img_max = stripslashes($results_img[$b]['img_max']);

              if(!empty($img_max))
                $page .= "<td><a target='_blank' href='{$ed_path_to_img_for_url}{$img_max}' target='_blank'><img class='ImageInBlock' src='{$ed_path_to_img_for_url}{$img_min}' border='0' alt='{$title}'></a></td>";
              else
                $page .= "<td><img class='ImageInBlock' src='{$ed_path_to_img_for_url}{$img_min}' border='0' alt='{$title}'></td>";
              if(($b + 1) % $in_row == 0)
                $page .=  "</tr></table><table class='ImageInBlockTbl' cellspacing='0' cellpadding='0' border='0'><tr>";

            }
            $page .= "</tr></table>";
          }
	       }

        if($type == 'images_text_in_bottom')
	       {

	         $in_row = $params['in_row'];

          $query = "SELECT id_img, pos, title, img_min, img_max, text
             	        FROM {$gl_db_prefix}{$ed_tbl_pref}_images
	                    WHERE id_block = {$id_block}
	                    ORDER BY pos";

          $results_img = db_select($query);
          if(is_array($results_img))
          {

            $cnt_img = count($results_img);
            $page .= "<table class='ImageInBlockTbl' cellspacing='0' cellpadding='0' border='0'><tr>";
            for($b = 0; $b < $cnt_img; $b++)
            {
            	 $title = stripslashes($results_img[$b]['title']);
              $text = stripslashes($results_img[$b]['text']);
              $text = convert_bb_tags($text, 'forum');
              $text = nl2br($text);

	             $img_min = stripslashes($results_img[$b]['img_min']);
	             $img_max = stripslashes($results_img[$b]['img_max']);

              if(!empty($img_max))
                $page .= "<td class='ImagesTextSub' valign='bottom'><a target='_blank' href='{$ed_path_to_img_for_url}{$img_max}' target='_blank'><img class='ImageInBlock' src='{$ed_path_to_img_for_url}{$img_min}' border='0' alt='{$title}'></a><span class='Text'>{$text}</span></td>";
              else
                $page .= "<td class='ImagesTextSub' valign='bottom'><img class='ImageInBlock' src='{$ed_path_to_img_for_url}{$img_min}' border='0' alt='{$title}'><span class='Text'>{$text}</span></td>";
              if((($b + 1) % $in_row == 0) && $cnt_img > $in_row)
                $page .=  "</tr></table><table class='ImageInBlockTbl' cellspacing='0' cellpadding='0' border='0'><tr>";

            }
            $page .= "</tr></table>";
          }
	       }

        if($type == 'images_text_in_right')
	       {

	         $in_row = $params['in_row'];

          $query = "SELECT id_img, pos, title, img_min, img_max, text
             	        FROM {$gl_db_prefix}{$ed_tbl_pref}_images
	                    WHERE id_block = {$id_block}
	                    ORDER BY pos";

          $results_img = db_select($query);
          if(is_array($results_img))
          {

            $cnt_img = count($results_img);
            $page .= "<table class='ImageInBlockTbl' cellspacing='0' cellpadding='0' border='0'><tr>";
            for($b = 0; $b < $cnt_img; $b++)
            {
            	 $title = stripslashes($results_img[$b]['title']);
              $text = stripslashes($results_img[$b]['text']);
              $text = convert_bb_tags($text, 'forum');
              $text = nl2br($text);

	             $img_min = stripslashes($results_img[$b]['img_min']);
	             $img_max = stripslashes($results_img[$b]['img_max']);

              if(!empty($img_max))
                $page .= "<td><a target='_blank' href='{$ed_path_to_img_for_url}{$img_max}' target='_blank'><img  class='ImageInBlock' src='{$ed_path_to_img_for_url}{$img_min}' border='0' alt='{$title}'></a></td><td class='Text'>{$text}</td>";
              else
                $page .= "<td><img  class='ImageInBlock' src='{$ed_path_to_img_for_url}{$img_min}' border='0' alt='{$title}'></td><td class='Text'>{$text}</td>";
              if(($b + 1) % $in_row == 0)
                $page .=  "</tr></table><table class='ImageInBlockTbl' cellspacing='0' cellpadding='0' border='0'><tr>";

            }
            $page .= "</tr></table>";
          }
	       }
        if($type == 'table')
	       {

          $text = convert_bb_tags($text, 'forum');
          preg_match("#<table.+?<\/table>#ims", $text, $matches);
          $text = $matches[0];
          $text = str_replace("border=\"1\">", '', $text);
          $text = "<div class='TblDiv'>{$text}</div>";//var_dump($_POST);
	         $page .= $text;
	       }

        if($type == 'file')
	       {
          $f_name = $text;
          $file = $params['file'];
          $path = $ed_path_to_img_for_url.$file;
          $size = @filesize($path);
          $size = round($size / 1024, 2);
          $f_name = preg_replace("/\[size\]/i", "{$size} {$l_gen[27]}", $f_name);
          $page .= "<p><a href='{$path}'>{$f_name}</a></p>";
        }
	     }
    }

    $page .= "<?php  } ?>\r\n";

    //постраничная навигация
    $pages_count = $pg_num - 1;
    if($pages_count > 1)
      $page .= "<?php print create_navigation({$pages_count}, \"?mb={$id_pg}\", \$pg_part, 'pg_part'); ?>\r\n";

    return $page;
  }


?>