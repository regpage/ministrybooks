<?php
//////////////////////////////////////////////////////
// МОДУЛЬ ФОРМИРОВАНИЯ СИСТЕМЫ НАВИГАЦИИ ПО ГЛАВАМ ///
//////////////////////////////////////////////////////

print "<table border='0' cellpadding='0' cellspacing='0' width='665'><tbody><tr><td><h1>{$ed_h1_prefix}</h1></td></tr></tbody></table>";

if(isset($_POST['s'])) {
    if(isset($_POST['Arr'])) {

    //ссылка на страницу

         $ed_page_preview_href = "?mb={$ed_pg}";
         $query = "SELECT content FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks WHERE id_pg = {$ed_pg} ORDER BY pos LIMIT 0, 1";
         $content = stripslashes(db_select_one($query));
         $content = explode("[NEWPAGE]", $content);
         $pages_cnt = count($content);

         $start_table_contents = $_POST['s_table_contents'];

         $String = implode(", ", $_POST['Arr']);   //номера страниц по главам
         $navig_tpl = file_get_contents("{$gl_path_to_engine_root}mods/spaw2full/navigchupter.inc");
         $navig_tpl = str_replace("{ed_page_preview_href}", $ed_page_preview_href, $navig_tpl);
         $navig_tpl = str_replace("{Arr}", $String, $navig_tpl);
	       $navig_tpl = str_replace("{pages_cnt}", $pages_cnt, $navig_tpl);

         save_in_file("{$ed_path_to_file}ch_{$ed_pg}.inc", $navig_tpl, 'w');

         print "<div class='message'>$l_gen[32] $String $start_table_contents</div>";

       } else {
        print "<div class='message'>$l_gen[31]</div>";
       }
       header("refresh: 1; url=?adm=parts_items_pages_chapter&ed_opt=blocks_list_chupters&pg={$id_item}");
    }

//Выводим контент постранично

    $query = "SELECT content FROM {$gl_db_prefix}{$ed_tbl_pref}_blocks WHERE id_pg = {$ed_pg} ORDER BY pos LIMIT 0, 1";
    $content = stripslashes(db_select_one($query));
    $content = explode("[NEWPAGE]", $content);
    $pages_cnt = count($content);

    if($pages_cnt <=1) {
        print "<div class='message'>$l_gen[33]</div>";
    } else {
        $path = "{$ed_path_to_file}ch_{$ed_pg}.inc";

//    Если файл с системой навигации существует извлекаем массив данных
        if(file_exists($path)) {

//   Данные из файла помещаем в массив
            $List=file($path);

//   Определям номер строки в

            foreach ($List as $line_num => $line) {
                  if (substr_count($line, "ch")>0) break;
                  $str_line = $line_num +1;
            }
          }

      $great_labels = array_keys($List, "ch");
      $Arrh = $List[$str_line];

        eval ($Arrh);
        print $List[$str_line-1];
//   Начало формы с checkboxами

      print "<form action ='' method=post>";
      print "<table class='SiteTbl' border='0' cellpadding='0' cellspacing='0' width='650'><tbody><tr><td class='SiteTblTH' align='center'>$l_gen[30]</td>
   <td class='SiteTblTH' align='center'>
   <input   type='checkbox' name='sel_all' onClick='var o=this.form.elements; for(var i=0;i<o.length;i++)if(o[i].type==\"checkbox\")o[i].checked=this.checked'></td></tr>";

    for($i = 0; $i < $pages_cnt; $i++) {

        $part= $i + 1;

   	    $content[$i] =  getPrewText($content[$i]);

        print "<tr><td class='SiteTblLeft' width='700'>";
   		  print "<h2>$l_gen[34] $part </h2><div class='info'>$content[$i]...</div>";
   		  print "</td><td class='SiteTblCenter'>";

//Выбор нужной страницы с главой
         if(in_array($part, $ch)) {
           $checked = 'checked';
         } else {
            $checked = '';
         }
            print "<input type='checkbox' name=Arr[] value=$part $checked>";
            print "</td></tr>";
    }
  //кнопки
  print "<tr><td></td><td><input type='submit' name='s' value=$l_gen[17] class='button'></form></td></tr>";
  print "</tbody></table>";

}

//---------скрипт добавления гиперссылок к оглавлению -----------------------------
/* */

if(isset($_POST['s']))
  {
$path_book = "{$ed_path_to_file}{$ed_pg}.inc";

 if(file_exists($path_book))

    $str = file_get_contents($path_book);

    $star = '~ class=\"decimalbd\">\s+(.*?)\s+<\/ol>~s';
      if (preg_match($star, $str)) {
         //echo $str;
         //$patern='#<ol class="decimalbd">(.*?)</ol>#is';
       $patern='#<ol\s+(.*?)<\/ol>#is';

       preg_match($patern, $str, $arr);

class myXML{
    function __construct($text_xml){
        $this->dom=new DOMDocument();
        $this->dom->loadXml($text_xml);
        $this->index=0;
        $this->method=array();
    }
    private function get_inner_html($node){
        $innerHTML= '';
        $children = $node->childNodes;
        foreach ($children as $child) {
            $innerHTML .= $child->ownerDocument->saveXML( $child );
        }
        return $innerHTML;
    }
    public function toArray(&$ar,$dom="",$cas=0){
        if($dom==""){$dom=$this->dom;}
        foreach($dom->childNodes as $child){
            if($child->nodeName!="#text"){
                $attr_ar=array();
                if($child->hasAttributes()){
                    $attributes=$child->attributes;
                    if(!is_null($attributes)){
                        foreach ($attributes as $index=>$attr){
                            $attr_ar[$attr->name]=$attr->value;
                        }
                    }
                }
                if($attr_ar["method"]=="ajax"){
                    $this->method[]=$this->index;
                }
                $ok=array("name"=>$child->nodeName,"index"=>$this->index++);
                if($cas>=0 && $child->nodeName!="xml"){
                    $ok["text"]=$this->get_inner_html($child);
                }
                if(sizeof($attr_ar)!=0){$ok["attr"]=$attr_ar;}
                $inner_=array();
                $this->toArray($inner_,$child,$cas+1);
                if(sizeof($inner_)!=0){$ok["child"]=$inner_;}
                $ar[]=$ok;
            }
        }
    }
}

	$strHTMLcod = $arr[0];
	$xml=new myXML($strHTMLcod);
	$ar=array();
	$xml->toArray($ar);

     if (isset($ar[0]["attr"]["class"])) {
	 if (isset($ar[0]["attr"]["start"])){ $atr_start = " start =" . $ar[0]["attr"]["start"]; $table_start = $ar[0]["attr"]["start"];} else {$atr_start=""; $table_start = 0;}

       $start_table_contents = $table_start;

	$url = $ed_page_preview_href;
		$bar = "<ol{$atr_start}>";
	for ($i = 1; $i <= count($ar[0]["child"]); $i++)
 	 {
		$j=$i-1;

		$bar = $bar."<li>";
		$bar = $bar."<a href='/$url&part=$ch[$j]'>" . $ar[0]["child"][$j]["child"][0]["text"] . "</a>";
		$bar = $bar."</li>";

	}

		$bar = $bar."</ol>";

        if (isset($bar)){ $table_content = $bar;} else {$table_content = "";}

	$str = preg_replace($patern, $bar, $str, 1);

	file_put_contents($path_book, $str);

        $navig_tpl = str_replace("{start_table_contents}", $start_table_contents, $navig_tpl);
        $navig_tpl = str_replace("{table_content}", $table_content, $navig_tpl);

        save_in_file("{$ed_path_to_file}ch_{$ed_pg}.inc", $navig_tpl, 'w');


}
	}

        $start_table_contents = ""; $table_content = "";
        $navig_tpl = str_replace("{start_table_contents}", $start_table_contents, $navig_tpl);
        $navig_tpl = str_replace("{table_content}", $table_content, $navig_tpl);

        save_in_file("{$ed_path_to_file}ch_{$ed_pg}.inc", $navig_tpl, 'w');

}

//header("refresh: 2; url=?adm=parts_items_pages_chapter&ed_opt=blocks_list_chupters&pg={$id_item}");


//--------------------------------------------------------------------------


?>
