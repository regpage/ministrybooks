<?php

  //////////////////////////////////////////////////////////////////////////////
  // Выводит список полей формы $id_form
  //////////////////////////////////////////////////////////////////////////////

  //инициалзиация переменных
  $id_form = intval($_GET['id_form']);
  $page    = intval($_GET['page']);
  if(empty($page)) $page = 1;

  //выбираем название текущей формы
  $query = "SELECT title FROM {$gl_db_prefix}forms WHERE id_form = {$id_form}";
  $f_title = stripslashes(db_select_one($query));

  //заголовок
  print "<h1>Formularium :: {$l_forms[41]} :: {$f_title}</h1>";


  //////////////////////////////////////////////////////////////////////////////
  //Форма выбора типа добавляемого поля
  //Форма выбора страницы
  //////////////////////////////////////////////////////////////////////////////

  print "<form name='sel_form' action='index.cfm?mod=forms_fields_add&id_form={$id_form}' method='post'>";
    print "<table style='padding-left:10px' cellspacing='0' cellpadding='0' border='0'>";
      print "<tr>";
        //Добавить поле
        print "<td class='Text'>{$l_forms[42]}:&nbsp;&nbsp;</td>";
        print "<td>";
          print "<select name='type' class='SiteFInputS'>";
            print "<option value='text'>{$l_forms[43]}</option>";
            print "<option value='textarea'>{$l_forms[44]}</option>";
            print "<option value='checkbox'>{$l_forms[45]}</option>";
            print "<option value='radio'>{$l_forms[46]}</option>";
            print "<option value='select'>{$l_forms[47]}</option>";
            print "<option value='groupe_title'>{$l_forms[48]}</option>";
          print "</select>";
        print "</td>";
        print "<td>&nbsp;<input class='SiteFButton' type='submit' name='add_field' value='{$l_forms[49]}'></td>";
      print "</tr>";
      print "<tr>";
        //Перейти на страницу
        print "<td class='Text'>{$l_forms[50]}:&nbsp;&nbsp;</td>";
        print "<td>";
          print "<select name='sel_page' class='SiteFInputS' onChange=\"location.href='index.cfm?mod=forms_fields_list&id_form={$id_form}&page=' + document.sel_form.sel_page.value\">";
            $pages = array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
            $cnt = count($pages);
            for($i = 0; $i < $cnt; $i++)
            {
              print "<option value='{$pages[$i]}'";
              if($page == $pages[$i])
                print " selected";
              print ">{$pages[$i]}</option>";
            }
          print "</select>";
        print "</td>";
        print "<td>&nbsp;</td>";
      print "</tr>";
    print "</table>";
    print "<input type='hidden' name='id_form' value='{$id_form}'>";
    print "<input type='hidden' name='page'    value='{$page}'>";
  print "</form>";

  //выбираем поля текущей страницы
  $query = "SELECT *
              FROM {$gl_db_prefix}forms_fields
             WHERE id_form = {$id_form}
               AND page    = {$page}
             ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      //print "<td class='SiteTblTH' width='20'>id</td>";
      print "<td class='SiteTblTH' width='20'>pos</td>";
      print "<td class='SiteTblTH'>{$l_forms[51]}</td>";
      print "<td class='SiteTblTH'>{$l_forms[52]}</td>";
      print "<td class='SiteTblTH'>{$l_forms[53]}</td>";
      print "<td class='SiteTblTH' width='180'>{$l_forms[54]}</td>";
    print "</tr>";
    $cnt = count($results);
    for($i = 0; $i < $cnt; $i++)
    {
      $id_field     = $results[$i]['id_field'];
      $pos         = $results[$i]['pos'];
      $caption       = stripslashes($results[$i]['caption']);
      $oblig       = $results[$i]['oblig'];
      $type      = $results[$i]['type'];

      print "<tr>";
          //print "<td class='SiteTblLeft'>{$id_cat}</td>";
          //позиция
          print "<td class='SiteTblLeft'>{$pos}</td>";
          //название поля
          print "<td class='SiteTblLeft'>{$caption}</td>";
          //тип поля
          print "<td class='SiteTblLeft'>{$type}</td>";
          //обязательное / необязательное
          print "<td class='SiteTblLeft'>{$oblig}</td>";
          print "<td class='SiteTblLeft'>";
            //параметры поля
            print "<a href='index.cfm?mod=forms_fields_edit&id_form={$id_form}&page={$page}&id_field={$id_field}'>{$l_forms[55]}</a><br>";
            //удалить поле
            print "<a href='index.cfm?mod=forms_fields_del&id_form={$id_form}&page={$page}&id_field={$id_field}'>{$l_forms[56]}</a><br>";
          print "</td>";
        print "</tr>";
    }
    print "</table>";
  } else print "<p>{$l_forms[57]}</p>";

  //ссылка назад
  print "<br><p><a class='Mustgreen' href='index.cfm?mod=forms_list'>{$l_forms[58]}</a></p>";



?>