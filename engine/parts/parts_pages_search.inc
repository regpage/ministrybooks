<?php
  //////////////////////////////////////////////////////////////////////////////
  // ������� ���������� ��������� � ����������
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  //������ ������������ ����� �������� �� id/���������
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  //�������������� $_POST ����������
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    $template = correct_input($_POST['template']);
    $srch_field = correct_input($_POST['srch_field']);
  }

  //////////////////////////////////////////////////////////////////////////////
  // ����� ������
  //////////////////////////////////////////////////////////////////////////////

  print "<h1>{$l_parts[46]}</h1>";
  print "<form action='' method='post'>";
    print "<table style='margin-left:10px' class='' cellspacing='0' cellpadding='0' border='0'>";
      print "<tr>";
                                //����� �������� ��
        print "<td class='Text'>{$l_parts[47]}&nbsp;&nbsp;</td>";
        print "<td>";
          //���� ������ �������� ������
          print "<select name='srch_field'>";
            print "<option value='id_item'";
            if($srch_field == 'id_item')
               print "selected";
            print ">id</option>";
            print "<option value='title'";
            if($srch_field == 'title')
               print "selected";
            print ">{$l_parts[49]}</option>";
          print "</select>";
        print "</td>";
        //���� �����
        print "<td class=''>&nbsp;<input style='width:300px' type='text' class='SiteFInputM' name='template' value=\"{$template}\"></td>";
        //������
        print "<td class=''>&nbsp;<input type='submit' class='button' name='search' value=\"{$l_parts[48]}\"></td>";
      print "</tr>";
    print "</table>";
  print "</form>";


  //////////////////////////////////////////////////////////////////////////////
  // ���������� �����
  //////////////////////////////////////////////////////////////////////////////

  if(!empty($_POST))
  {
    //������� ntub
    $template = strip_tags($template);

    //������������ ����� ������� � ��������� ������ ��� ������ �� ��������� ��������
    if($srch_field == 'title')
    {
      //������� ������������ �������
    	 $tpl = preg_replace("/[^\w\x7F-\xFF\s]/", " ", $template);

	     //�������� ������������ ����������� �� ����������� mysql
	     $tpl = str_replace('?', '_', $tpl);
	     $tpl = str_replace('*', '%', $tpl);

	     //��������� �������� �����
	     //$tpl = trim(preg_replace("/\s(\S{1,2})\s/", " ", ereg_replace(" +", "  "," $tpl ")));
       $tpl = trim(preg_replace("/\s(\S{1,2})\s/", " ", mb_ereg_replace(" +", "  "," $tpl ")));
	     //������� ������ �������
	     
       //$tpl = ereg_replace(" +", " ", $tpl);
       $tpl = mb_ereg_replace(" +", " ", $tpl);

      //����� �������, ���������� ������� ������
      if(!empty($tpl))
      {
        $words = explode(" ", $tpl);
	       $wrd_cnt = count($words);

        $query_part .= " (";
    	   for($i = 0; $i < $wrd_cnt; $i++)
	       {
	         if($i != 0)
	           $query_part .= ' AND ';
	         $query_part .= " {$srch_field}  LIKE '%{$words[$i]}%'";
	       }
	       $query_part .= " )";
      }
    }
    //������������ ����� ������� � ��������� ������ ��� ������ �� id
    else
    {
      $tpl = intval($template);
      $query_part = " id_item = {$tpl}";
    }

    //���� ���� ����� �� ������
    if(empty($tpl))
    {
      print $l_parts[50];
      return;
    }

    //���-�� �����������
    $printed = 0;

    //������ �� ������� ������� �� �������� ������ � ������� ������
    $query = "SELECT *
	             FROM {$gl_db_prefix}parts_items
	             WHERE ";
    $query .= $query_part;
    //print $query;
	   $results = db_select($query);

    //������� �����������
	   print "<h2>{$l_parts[51]}</h2>";
	     if(is_array($results))
	     {
	       $cnt = count($results);

	       print "<p>";
	       //���������� ��������� ��-���
	       print "{$l_parts[52]} {$cnt}";

	       print "</p><br />";
        print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
      	   print "<tr>";
	           print "<td class='SiteTblTH' width='20'>{$l_parts[16]}</td>";
	           //print "<td class='SiteTblTH'>���</td>";
	           print "<td class='SiteTblTH'>{$l_parts[17]}</td>";
	           print "<td class='SiteTblTH' width='200'>{$l_parts[18]}</td>";
	         print "</tr>";
	         $cnt = count($results);
	         for($i = 0; $i < $cnt; $i++)
	         {
	           $id_item  = $results[$i]['id_item'];
	           $id_part_prec  = $results[$i]['id_part'];
            $id_part = $id_part_prec;
	           $type     = $results[$i]['i_type'];
	           $pos      = $results[$i]['pos'];
	           $title    = stripslashes($results[$i]['title']);
	           $mod_name = $results[$i]['mod_name'];
	           $params   = $results[$i]['params'];
	           $params   = unserialize(stripslashes($params));
	           print "<tr>";
	             print "<td class='SiteTblLeft'>{$pos}</td>";
	             //print "<td class='SiteTblLeft'>{$type}</td>";
	             print "<td class='SiteTblLeft'>{$title}</td>";
	             print "<td class='SiteTblLeft'>";
	               //�����
	               print "<a href='?adm=parts_items_pages_text&ed_opt=blocks_list&pg={$id_item}&id_part={$id_part_prec}&id_item={$id_item}'>{$l_parts[19]}</a><br>";
                //���������
	               print "<a href='?adm=parts_items_pages_edit&id_part_prec={$id_part_prec}&id_item={$id_item}'>{$l_parts[20]}</a><br>";
	               //url-�����
	               if($type == 'page')
	                 print "<a href='?adm=parts_items_pages_url&id_part_prec={$id_part_prec}&id_item={$id_item}'>{$l_parts[21]}</a><br>";
	               //���������
	               print "<a href='?adm=parts_items_pages_move&id_part_prec={$id_part_prec}&id_item={$id_item}&id_part={$id_part}'>{$l_parts[22]}</a><br>";
	               //�������
	               print "<a href='?adm=parts_items_pages_del&id_part_prec={$id_part_prec}&id_item={$id_item}'>{$l_parts[23]}</a><br>";
	             print "</td>";
	           print "</tr>";
	         }
	         print "</table>";
	     }  else print "<p>{$l_parts[53]}</p>";

   }

?>