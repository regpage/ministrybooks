<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� �����
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������� ������ $id_tpl �� �������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $id_tpl = intval($_GET['id_tpl']);
  $state    = intval($_GET['state']);

  //�������� ��������� �������
  $query = "SELECT pos, maintpl, file
              FROM {$gl_db_prefix}sitetpl
             WHERE id_tpl  = {$id_tpl}";
  $results = db_select($query);
  $pos = $results[0]['pos'];
  $file = $results[0]['file'];
  $maintpl = $results[0]['maintpl'];


  //��������� � ���, ��� ������ ������� �������� ������
  if($maintpl == 'yes')
    { print "<h1>{$l_tpl[28]}</h1><br><br><p>{$l_tpl[29]}<br><a href='?adm=tpl_list'>{$l_adm_gen[10]}</a></p>"; return; }
  unset($results);

  //////////////////////////////////////////////////////////////////////////////
  //���������� ���� ������������� ��������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($state))
  {
    print "<h1>{$l_tpl[30]}</h1><br><br><br><br><br><div align='center'><br><br><a href='?adm=tpl_del&id_tpl={$id_tpl}&state=1'>{$l_adm_gen[5]}</a> <a href='?adm=tpl_list'>{$l_adm_gen[6]}</a></div>";
  }

  //////////////////////////////////////////////////////////////////////////////
  //�������� �������
  //////////////////////////////////////////////////////////////////////////////

  if($state == 1)
  {
    $query = "DELETE FROM {$gl_db_prefix}sitetpl
               WHERE id_tpl = {$id_tpl}";
    db_delete($query);

    $path = "{$gl_path_to_templates}site/{$file}.inc";
    if(file_exists($path) && !is_dir($path))
      unlink($path);

    //��������� ������� ��������� ���������
    $query = "UPDATE {$gl_db_prefix}sitetpl
                 SET pos = pos - 1
               WHERE pos > {$pos}";
    db_update($query);

    //��������� � ������ ��������
    echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=?adm=tpl_list'></HEAD></HTML>";
    exit;
  }



?>