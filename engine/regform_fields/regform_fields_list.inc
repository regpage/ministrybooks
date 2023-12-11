<?php
  //////////////////////////////////////////////////////////////////////////////
  // Выводит список полей формы регистрации
  //////////////////////////////////////////////////////////////////////////////


  //заголовок
  print "<h1>{$l_regform_fields[1]}</h1>";


  //////////////////////////////////////////////////////////////////////////////
  //Форма выбора типа добавляемого поля
  //Форма выбора страницы
  //////////////////////////////////////////////////////////////////////////////

  print "<form name='sel_form' action='?adm=regform_fields_add' method='post'>";
    print "<table style='padding-left:10px' cellspacing='0' cellpadding='0' border='0'>";
      print "<tr>";
        //Добавить поле
        print "<td class='Text'>{$l_regform_fields[53]}:&nbsp;&nbsp;</td>";
        print "<td>";
          print "<select name='type' class='SiteFInputS'>";
            print "<option value='text'>{$l_regform_fields[2]}</option>";
            print "<option value='textarea'>{$l_regform_fields[3]}</option>";
            print "<option value='checkbox'>{$l_regform_fields[4]}</option>";
            print "<option value='radio'>{$l_regform_fields[5]}</option>";
            print "<option value='select'>{$l_regform_fields[6]}</option>";
            //print "<option value='groupe_title'>{$l_regform_fields[7]}</option>";
          print "</select>";
        print "</td>";
        print "<td>&nbsp;<input class='SiteFButton' type='submit' name='add_field' value='{$l_regform_fields[8]}'></td>";
      print "</tr>";
    print "</table>";
  print "</form>";

  //выбираем поля текущей страницы
  $query = "SELECT *
              FROM {$gl_db_prefix}regform_fields
             ORDER BY pos";
  $results = db_select($query);
  if(is_array($results))
  {
    print "<table class='SiteTbl' width='650' cellspacing='0' cellpadding='0' border='0'>";
    print "<tr>";
      //print "<td class='SiteTblTH' width='20'>id</td>";
      print "<td class='SiteTblTH' width='20'>pos</td>";
      print "<td class='SiteTblTH'>{$l_regform_fields[45]}</td>";
      print "<td class='SiteTblTH'>{$l_regform_fields[46]}</td>";
      print "<td class='SiteTblTH'>{$l_regform_fields[47]}</td>";
      print "<td class='SiteTblTH' width='180'>{$l_regform_fields[48]}</td>";
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
            print "<a href='?adm=regform_fields_edit&id_field={$id_field}'>{$l_regform_fields[49]}</a><br>";
            //удалить поле
            print "<a href='?adm=regform_fields_del&id_field={$id_field}'>{$l_regform_fields[50]}</a><br>";
          print "</td>";
        print "</tr>";
    }
    print "</table>";
  } else print "<p>{$l_regform_fields[51]}</p>";




?>