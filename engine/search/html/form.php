<?php
   /*  + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
    +                     Форма поиска по книгам                     +
    +----------------------------------------------------------------*/

   echo '<div class="row">
            <div class="small-4 small-centered columns">';
   echo "<div id='resultalert' style='color:red; width:380px; text-align: center;margin-bottom:10px;'></div>";
   echo "</div>
            </div>";
  $form_line_tpl = file_get_contents("{$gl_path_to_templates}forms/line1.htm");
  $form_lineobl_tpl = str_replace("{caption}:", "<span class='Mustred'>{caption}:</span>", $form_line_tpl);
  if(!empty($errors))
  print form_print_errors($errors);
  print form_begin('edit_form', '', 'POST', 'multipart');
  print work_template($form_lineobl_tpl, array("{caption}" => $l_search[2],
        "{field}" => form_create_input("template", $css = 'SiteFInputM', $size ='')));
  print work_template($form_lineobl_tpl, array("{caption}" => "Включая все формы",
        "{field}" => form_create_radio("stype", "", "F")));
  print work_template($form_lineobl_tpl, array("{caption}" => "Точное совпадение",
        "{field}" => form_create_radio("stype", "yes", "S")));
  print work_template($form_lineobl_tpl, array("{caption}" => $l_search[3],
        "{field}" => form_create_select('logic', $logic_opt, $css = 'SiteFInputM')));
  print work_template($form_lineobl_tpl, array("{caption}" => "Категория поиска",
        "{field}" => form_create_select('search_by', $id_search_by, $css = 'SiteFInputM')));
  print work_template( $form_line_tpl, array("{caption}:" => "&nbsp;",
        "{field}" => form_create_submit('search', $value='Найти', $css = 'button small radius expand')));
//  print form_create_hidden('blague', session_id());
//  print form_create_hidden('old_pos', $old_pos);
  print form_create_hidden('id_tpl', $id_tpl);
  print form_end();
//  print '<p>Область поиска <strong><a href="#" data-reveal-id="myModalScope">Что это?</a></strong><br>';
  if(isset($_SESSION['template'])){ print '<a class="button radius" href="/?mod=search_on_site&srcStr='. $templateid .'">Очистить поиск</a></p>'; }