<?php
	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+         Выпадющий список: | Логига поиска: И, ИЛИ              +
	+ --------------------------------------------------------------*/

    $logic_opt .= "<option value='AND' ";
  if($logic == 'AND')
    $logic_opt .= " selected" ;
    $logic_opt .= ">{$l_search[9]}</option>";
    $logic_opt .= "<option value='OR' ";
  if($logic == 'OR')
    $logic_opt .= " selected";
    $logic_opt .= ">{$l_search[10]}</option";

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+             Выпадющий список: | Все публикации                 +
	+ --------------------------------------------------------------*/

    $id_search_by .= "<option value='All'";
  if($search_by == 'Все публикации')
    $id_search_by .= " selected" ;
    $id_search_by .= ">Все публикации</option>";


	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+             Выпадющий список: | Список по автору               +
	+ --------------------------------------------------------------*/


    $id_search_by .= "<optgroup label='По автору:'><option value='WL'";
  if($search_by == 'Уитнесс Ли')
    $id_search_by .= " selected" ;
    $id_search_by .= ">Уитнесс Ли</option>";

    $id_search_by .= "<option value='WN'";
  if($search_by == 'Вочман Ни')
    $id_search_by .= " selected" ;
    $id_search_by .= ">Вочман Ни</option></optgroup>";

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+             Выпадющий список: | Список категорий               +
	+ --------------------------------------------------------------*/

  $query_CAT = "SELECT *
             FROM {$gl_db_prefix}parts
             ORDER BY title ASC";
  $results_CAT = db_select($query_CAT);

  if(is_array($results_CAT))
    {
      $cnt_CAT = count($results_CAT);

      $id_search_by .= "<optgroup label='По категории:'>";

      for($i = 0; $i < $cnt_CAT; $i++)
         {
            $id_part = $results_CAT[$i]['id_part'];
            $title_ct = stripslashes($results_CAT[$i]['title']);

            $query_z = "SELECT *
                FROM {$gl_db_prefix}parts_items
               	WHERE id_part = {$id_part}
               	ORDER BY title ASC";
              $results_z = db_select($query_z);
              $cnt_z = count($results_z);
              if($cnt_z > 0) { $title_CAT = $results_CAT[$i]['title'];
               $id_search_by .= "<option value={$id_part}";
                  if($search_by == $title_CAT)
                       $id_search_by .= " selected" ;
                       $id_search_by .= ">" . $title_ct . " (" . $cnt_z . ") " . "</option>";
         }}
                       $id_search_by .= "></optgroup>";
     }

	/* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
	+             Выпадющий список: | Список все книги               +
	+ --------------------------------------------------------------*/

   $query_all_books = "SELECT *
             FROM {$gl_db_prefix}parts_items
             ORDER BY title ASC, pos";
   $results_all_books = db_select($query_all_books);

   if(is_array($results_all_books))

    {
      $cnt_all_books = count($results_all_books);

      $id_search_by .= "<optgroup label='По книге:'>";

      for($q = 0; $q < $cnt_all_books; $q++)
          {
              $title_all_books = $results_all_books[$q]['title'];
              $id_item_all_books  = $results_all_books[$q]['id_item'];
              $id_item_all_books  = "G" . $id_item_all_books ;

              $id_search_by .= "<option value={$id_item_all_books}";
              if($search_by == $title_all_books)
              $id_search_by .= " selected" ;
              $id_search_by .= ">" . $title_all_books . "</option>";
           }
              $id_search_by .= "></optgroup>";
     }
