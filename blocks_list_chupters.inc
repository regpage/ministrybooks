<?php

/////////////////////////////////////////////////////////////////////
////   МОДУЛЬ ФОРМИРОВАНИЯ СИСТЕМЫ НАВИГАЦИИ ПО ГЛАВАМ      /////////
/////////////////////////////////////////////////////////////////////

//Функция корректно урезает строку в конце слова.

function getPrewText( $text, $maxwords = 20, $maxchar = 300 )
 {
    $sep = ' ';
    $words = split( $sep, $text );
    $char = iconv_strlen($text, 'utf-8');

         if(count($words) > $maxwords)
      {
          $text = join($sep, array_slice($words, 0, $maxwords));
      }
    if ($char > $maxchar)
      {
        $text = iconv_substr( $text, 0, $maxchar, 'utf-8' );
      }
   return $text;
  } 

////////////////////////////////////////////////////////////////////////
  
print "<h1>{$ed_h1_prefix}</h1><br>";

if(isset($_POST['s']))
  {
       if(isset($_POST['Arr']))
       {

//ссылка на страницу 
    
    $ed_page_preview_href = "index.php?mb={$ed_pg}"; 

        $String = implode(",", $_POST['Arr']);
          $navig_tpl = file_get_contents("{$gl_path_to_engine_root}mods/spaw2full/navigchupter.inc");
          $navig_tpl = str_replace("{ed_page_preview_href}", $ed_page_preview_href, $navig_tpl);
          $navig_tpl = str_replace("{Arr}", $String, $navig_tpl);
        
        save_in_file("{$ed_path_to_file}ch_{$ed_pg}.inc", $navig_tpl, 'w');

        print "<div class='message'>$l_gen[32] $String</div>";
       }
     else
       {
        print "<div class='message'>$l_gen[31]</div>";
       }

    }



//Выводим контент постранично
 
    $query = "SELECT content FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks WHERE id_pg = {$ed_pg} ORDER BY pos LIMIT 0, 1";
    $content = stripslashes(db_select_one($query));   
    $content = explode("[NEWPAGE]", $content);
    $pages_cnt = count($content);
             
    if($pages_cnt <=1)
                {
                  print "<div class='message'>$l_gen[33]</div><br/><br/>";
                }
                  else
                {   

  $path = "{$ed_path_to_file}ch_{$ed_pg}.inc";
//    Если файл с системой навигации существует извлекаем массив данных 
             if(file_exists($path))

//   Данные из файла помещаем в массив

               $List=file($path);

//   Определям номер строки в 
            
              foreach ($List as $line_num => $line) {
                      if (substr_count($line, "ch")>0) break;
                           $str_line = $line_num +1;
               } 

        $great_labels = array_keys($List, "ch"); 
        $Arrh = $List[$str_line];

        eval ($Arrh);   

//   Начало формы с checkboxами
  
   print "<form action ='' method=post>";
   print "<table class='SiteTblTH' border='0' cellpadding='0' cellspacing='0' width='650'><tbody><tr><td class='SiteTblTH' align='center'>$l_gen[30]</td>
   <td class='SiteTblTH' align='center'>
   <input   type='checkbox' name='sel_all' onClick='var o=this.form.elements; for(var i=0;i<o.length;i++)if(o[i].type==\"checkbox\")o[i].checked=this.checked'></td></tr>";
 
    for($i = 0; $i < $pages_cnt; $i++)
      {
     
        $part= $i + 1;        
     
   	$content[$i] =  getPrewText($content[$i]);
                
                print "<tr><td class='SiteTblLeft' width='700'>";  
   		print "<h2>$l_gen[34] $part </h2><div class='info'>$content[$i]...</div>";
   		print "</td><td class='SiteTblCenter'>";
       
//Выбор нужной страницы с главой                
         if(in_array($part, $ch))
    { 
      $checked = 'checked';
    } 
     else
    {
               $checked = '';
    }  
                print "<input type='checkbox' name=Arr[] value=$part $checked>";
                print "</td></tr>";    
    }
  //кнопки
  print "<tr><td></td><td><br/><input type='submit' name='s' value=$l_gen[17]></form></td></tr>";
  print "</tbody></table><br/>"; 
}
?>