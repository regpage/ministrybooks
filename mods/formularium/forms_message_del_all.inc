<?php
  //////////////////////////////////////////////////////////////////////////////
  //������� ��������� ��������� ����� $id_form
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //������������� ����������
  //////////////////////////////////////////////////////////////////////////////

  $state    = intval($_GET['state']);
  if(empty($state))
    $state    = intval($_POST['state']);

  $part     = intval($_GET['part']);
  if(empty($part))
    $part     = intval($_POST['part']);

  $id_form     = intval($_GET['id_form']);
  if(empty($id_form))
    $id_form     = intval($_POST['id_form']);

  $to_del = $_POST['items'];


  //////////////////////////////////////////////////////////////////////////////
  //���������� ����, ������������ ��������
  //////////////////////////////////////////////////////////////////////////////

  if(empty($_POST['del_all']))
  {
    if(is_array($to_del))
    {
      //������
      print "<h1>{$l_forms[90]}</h1>";
	     print "<form name='del_form' action='' method='post'>";
	     print "<br><br><br><br><br>";
      //������
      print "<div align='center'><input type='submit' name='del_all' value='{$l_gen[20]}'>&nbsp;<input type='button' name='back' value='{$l_gen[21]}' onClick=\"location.href='index.cfm?mod=forms_message_list&id_form={$id_form}&part={$part}'\"></div>";
      //������� ����
      foreach($to_del as $id_mess => $value)
      {
        print "<input type='hidden' name='items[$id_mess]' value='$value'>";

      }
      print "</p>";
      print "<input type='hidden' name='mod' value='forms_message_del_all'>";
      print "<input type='hidden' name='id_form' value='{$id_form}'>";
      print "<input type='hidden' name='part' value='{$part}'>";
      print "</form>";
    }
    //��������� �� ������, ���� �� ������ �� ���� �������
    else
    {
      print "<h1>{$l_forms[91]}</h1>";
      print "<p>{$l_forms[92]}<br><a href='index.cfm?mod=forms_message_list&id_form={$id_form}&part={$part}&id_form={$id_form}'>{$l_forms[93]}</a></p>";
      return;
    }
  }


  //////////////////////////////////////////////////////////////////////////////
  //�������� ���������
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST['del_all']))
  {
    foreach($to_del as $id_mess => $value)
    {
      //������� ������� �� ���� ������
	     $query = "DELETE FROM {$gl_db_prefix}forms_messages
	                WHERE id_mess = {$id_mess}";
	     db_delete($query);
    }

    //��������� � ������ ��������� ������� �����
	   echo "<HTML><HEAD><META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.cfm?mod=forms_message_list&id_form={$id_form}&part={$part}'></HEAD></HTML>";
	   exit;
  }




?>