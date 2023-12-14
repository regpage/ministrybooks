<?php

 /* Основные узлы системы 
 *  Copyright (C) 2017 
 *  Version:      1.5 
 *  LastModified: March 20, 2017 
 *  загрузка нужной навигации по главам в область 
 *  в зависимости от значения переменной $gl_page
 */
  if(!empty($gl_page))
      {
        //загружаем панель навигации по главам
 $ch_path = "{$gl_path_to_root}content/{$gl_page}/ch_{$gl_page}.inc";
    if(file_exists($ch_path))include($ch_path); 
         $path = "{$gl_path_to_root}content/{$gl_page}/ch_{$gl_page}.inc";
           if(file_exists($path) && $_GET['part']<= $pages_count)
                  include($path); 
           else
              {
                 echo "<div class='row collapse' id='ministry'>";                                                      
                   //include("{$gl_path_to_engine}errors/errors.inc");      
                  //return;
	         echo "";                   
               }
         /* $path_content = "{$gl_path_to_root}content/{$gl_page}/{$gl_page}.inc?value=' . $pages_cnt";            
                     if(file_exists($path_content))     
                  $navig_tpl = file_get_contents("{$gl_path_to_root}content/{$gl_page}/{$gl_page}.inc");  */   
       }
  if (count($ch)>0 && $_GET['part']<= $pages_count) 
      { 
	   $var_name="part";
	   $count=0;
	     $j = 1;
           for($i=0; $i<count($ch); $i++)
              {
	         $part = $i + 1;
	         $text_r = "<a {$l_menu[7]} href='{$url}&{$var_name}={$ch[$i]}'>$part</a>&nbsp;|&nbsp; "; 
	         $text = "{$text}{$text_r}";
	         $len = strlen($text);
	         $count++;
               }   
            echo "<div class='row collapse' id='ministry'>
                         <div class='small-12 large-6 columns' id='chapter-menu'>
                                   <div class='row collapse'>";
                  echo "<form method=post class='no-custom'>
                  <div class='small-10 columns'>
	                <select name='book_chapter' id='chapter'>"; // Список начало
		  echo "<option value='1' selected='' >Глава</option>";
		  echo "<option value='1'>Содержание</option>";
 			$select=""; 
                    if ($start_table_cnt>1) $start_table_cnt = ($start_table_cnt-1);
	                $j = 0 + $start_table_cnt;
	                   foreach($ch as $k =>$v) {
 		                $j = $j + 1;
 	                             $select .= "<option value='$v'>$j\n";
		                 }
	                         echo $select."</select></div><div class='small-2 columns'><input type=submit name='doSend' value='перейти' class='tiny button radius'></div>";
                                 echo "";
                   echo "</form></div>"; // Список конец 
                   echo "</div>";
                            if(@$_POST['doSend']) {
	                              $chapter = $ch[$_POST['book_chapter']];
 	                              $link = $url.'&'.$var_name.'='.htmlspecialchars($_POST['book_chapter']);     	
	                         echo '<script type="text/javascript">';
	                         echo 'window.location.href="'.$link.'";';
                                 echo '</script>'; }

	           if(isset($_GET['part'])){ $pages = htmlspecialchars($_GET['part']);} else {$pages = 1;}
	                     $count=0;
                           for($i=0; $i<count($ch); $i++){
 	                      $part = $i + $start_table_cnt; 	
                                   if($part < (1 + $start_table_cnt)) {$chpt="Содержание";} else {$chpt =$part; $chapter="Глава: ";} 
		                   if($_GET['part'] < $ch[$i]) break; else {$chpt = ($part+1);}
	 		                        $count++;   }

 echo "<div class='small-12 large-6 columns'><div class='book-pos'><span style='white-space: nowrap;'>" .$chapter. "<span class='secondary radius label'>" .$chpt. "</span> стр. <span class='secondary radius label'>" .$pages. "</span></span></div></div><div class='clear'></div>";

echo '<div class="row tools"><div class="small-4 columns">
            	 <div class="font-resizer" style="margin-left:15px;"><div class="font-sizer-buttons"><a href="#" id="plustext" class="button radius" title="Увеличить размер шрифта"><span>A</span><i class="fa fa-plus" aria-hidden="true"></i></a><a href="#" id="minustext" class="button radius" title="Уменьшить размер шрифта"><span>A</span><i class="fa fa-minus"></i></a></div>
<br>
<a href="#" id="resetfontsize">  </a>
                 <p style="font-size:9px; color:#000; font-family: arial, helvetica, verdana;">Размер шрифта</p></div>
            </div>';
                             $navig = navigation_books($pages_count, $url, $pages);	
	echo "<div class='section-nav'  style='margin-right:15px;'>$navig</div>"; 

       } else { echo "<div class='row collapse' id='ministry'>
                         <div class='large-6 columns' id='chapter-menu'>
                                   <div class='row collapse'>";
echo "Такой страницы нет в данной книге  » "; echo "<a href='/?mb={$gl_page}'> Вернуться в книгу</a>";

	         echo "</div></div></div>"; 
 }
 //session_start();
 $stemmed = unserialize($_SESSION['words_sessia']);
 $wrd_cnt = count($stemmed); 
if ($wrd_cnt > 1) { echo '<div class="small-9 columns"><p style="margin: 5px 0px 0px 20px; float: left;"><a href="/?mod=search_tips"> « результаты поиска </a></p></div>';}
?>
</div>
<hr style="margin-top:5px;">
