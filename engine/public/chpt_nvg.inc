<?php
/*
* Блок с информацие о печатном издании с картинкой и ссылкой на сайт магазина
*/
 if(!empty($gl_page))

  {
     $query = "SELECT *
                FROM {$gl_db_prefix}parts_items               
	  WHERE id_item = {$gl_page}";
     
      $results = @db_select($query);

      $title = stripslashes($results[0]['title']);
      $id_author = stripslashes($results[0]['id_author']);        
      $pg_isbn = $results[0]['isbn'];
      $bookstorelink = $results[0]['bookstorelink'];
      $img_book_store = $results[0]['img_book_store'];
      $img_book_store_split;
      if ($img_book_store[4] != 's' && $img_book_store[4] == ':'){
        $img_book_store_split = explode('://', $img_book_store);
        $img_book_store = $img_book_store_split[0] . 's://' . $img_book_store_split[1];
      }
      if(isset($bookstorelink) && !empty($img_book_store)){ $book_store_link = "<strong>Печатное издание: </strong><a href=" . $bookstorelink . "> купить в магазине </a>";
			}  else $book_store_link = "";
      if(isset($img_book_store) && !empty($img_book_store)){ $img_book = "<div class='bookstore'>
            <a href=" . $bookstorelink . "><img src=" . $img_book_store . " alt='' class='coverimgl' width='196' height='164'></a></div>";
			}  else $img_book = "";
       $query = "SELECT author
                FROM {$gl_db_prefix}parts_author
                WHERE id_author = {$id_author}";
                $author = @db_select_one($query);       
  }
echo "<div class='row'>
         <div class='large-12 columns' id='chapter-menu'>";
echo "<ul class='breadcrumbs'>      
          <li><a href='index.cfm'>Главная</a></li>
          <li class='current'><a href='index.cfm'>{$title}</a></li>      
    </ul>
  <div class='section-container accordion' data-section='accordion' data-options='one_up: false;'>
      <section>
        <h5 class='title' data-section-title=''><a href='index.cfm'><span>&nbsp;ИНФОРМАЦИЯ ПО КНИГЕ</span></a></h5>
        <div class='content' data-section-content=''>{$img_book}          
          <h3>{$title}<span>{$author}</span></h3>
          <p><strong>ISBN:</strong> {$pg_isbn}<br>
          {$book_store_link}         
        </p>
        </div>
      </section>
  </div> 
       </div>
           </div>";

?>