<?php
  //////////////////////////////////////////////////////////////////////////////
  // Конструктор меню
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //Модуль удаляет пункт меню
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //инициализация переменных
  //////////////////////////////////////////////////////////////////////////////

	 $id_item = intval($_GET['id_item']);
	 $id_item_prec = intval($_GET['id_item_prec']);
	 $id_menu = intval($_GET['id_menu']);
	 $state    = intval($_GET['state']);

  //выбираем параметры удаляемого пункта
  $query = "SELECT pos
              FROM {$gl_db_prefix}menu_items
             WHERE id_item  = {$id_item}";
  $results = db_select($query);
  $pos = $results[0]['pos'];
  unset($results);


  //////////////////////////////////////////////////////////////////////////////
  //диалоговое окно подтверждения удаления
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_menu[58]}</h1><br><br><br><br><br><div align='center'><br><br><a href='?adm=menu_items_del&id_menu={$id_menu}&id_item_prec={$id_item_prec}&id_item={$id_item}&state=1'>{$l_adm_gen[5]}</a> <a href='?adm=menu_items_list&id_menu={$id_menu}&id_item_prec={$id_item_prec}&id_item={$id_item}'>{$l_adm_gen[6]}</a></div>";
  }


  //////////////////////////////////////////////////////////////////////////////
  //удаление пункта
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    //функция удаляет пункт меню id_item и все его подпункты
    //содержит рекурсию
    function del_menu_item($id_item)
    {
      global $gl_db_prefix;

      $query = "DELETE FROM {$gl_db_prefix}menu_items
                 WHERE id_item = {$id_item}";
      db_delete($query);

      $query = "SELECT id_item
                  FROM {$gl_db_prefix}menu_items WHERE id_item_prec = {$id_item}";
      $results = db_select($query);
      if(is_array($results))
      {
        $cnt = count($results);
        for($i = 0; $i < $cnt; $i++)
        {
          $tmp_id_item = $results[$i]['id_item'];
          del_menu_item($tmp_id_item);
        }
      }
    }

    del_menu_item($id_item);

    //калибруем позицию остальных пунктов меню id_menu
    $query = "UPDATE {$gl_db_prefix}menu_items
                 SET pos = pos - 1
               WHERE pos > {$pos}
                 AND id_item_prec = {$id_item_prec}
                 AND id_menu = {$id_menu}";
    db_update($query);

    //переходим в список пунктов меню id_menu
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=menu_items_list&id_menu={$id_menu}&id_item_prec={$id_item_prec}'></HEAD></HTML>";
    exit;
  }



?>