<?php

  //////////////////////////////////////////////////////////////////////////////
  // Подключает модуль в зависимости от нажатой кнопки: удалить/переместить
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['delete_all']))
    $gl_ed_opt = 'blocks_del_all';
  if(!empty($_POST['move_all']))
    $gl_ed_opt = 'blocks_move_all';



?>