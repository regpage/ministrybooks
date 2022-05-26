<?php

  //////////////////////////////////////////////////////////////////////////////
  // Модуль удаляет соответствие $id_item
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  // Инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

  $state    = intval($_GET['state']);
  $id_item  = intval($_GET['id_item']);

  //выборка данных соответствия
  $query = "SELECT pos
            FROM {$gl_db_prefix}url_and_sitetpl";
	 $results = db_select($query);
	 $pos = $results[0]['pos'];


  //////////////////////////////////////////////////////////////////////////////
	 // вывод диалогового окна подтверждения удаления
	 //////////////////////////////////////////////////////////////////////////////

	 if(empty($state))
	 {
	   print "<h1>{$l_url_and_sitetpl[16]}</h1><br /><br /><br /><br /><br /><div align='center'><br /><br /><a href='index.cfm?mod=url_and_sitetpl_del&amp;state=1&amp;id_item={$id_item}'>{$l_gen[20]}</a> <a href='index.cfm?mod=url_and_sitetpl_list'>{$l_gen[21]}</a></div>";

	 }


  //////////////////////////////////////////////////////////////////////////////
  //удаление соответствия
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    $query = "DELETE FROM {$gl_db_prefix}url_and_sitetpl
                 WHERE id_item = {$id_item}";
    db_delete($query);

    //калибруем позицию остальных элементов
    $query = "UPDATE {$gl_db_prefix}url_and_sitetpl
                 SET pos = pos - 1
                WHERE pos > {$pos}";
    db_update($query);

    //переход в список соответствий
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=url_and_sitetpl_list'></HEAD></HTML>";
    exit;
  }



?>