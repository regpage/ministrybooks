<?php

/////////////////////////////////////////////////////////////////////
////   МОДУЛЬ ФОРМИРОВАНИЯ СИСТЕМЫ НАВИГАЦИИ ПО ГЛАВАМ (автоматически по классу msg )   /////////
/////////////////////////////////////////////////////////////////////

  
print "<table border='0' cellpadding='0' cellspacing='0' width='650'><tbody><tr><td><h1>{$ed_h1_prefix}</h1><br></td></tr></tbody></table>";

//****   Фрагмент кода выполняется после нажатия кнопки  ***************************

//******************************************************************************************
$ed_back = "<a class='' href='?adm=parts_items_pages_text&ed_opt=blocks_list&pg={$ed_pg}&id_part={$id_part}&id_item={$ed_pg}'>{$l_parts[64]} &laquo;{$ed_h1_prefix}&raquo;</a>";

// извлекаем контент постранично для поиска msg
 
    $query = "SELECT content FROM pages_blocks WHERE id_pg = {$ed_pg} ORDER BY pos LIMIT 0, 1";
    $content = stripslashes(db_select_one($query));   
    $content = explode("[NEWPAGE]", $content);
    $pages_cnt = count($content);
             
if($pages_cnt <=1)
{
print "<div class='message'>$l_gen[33]</div><br/><br/>";   // Выводим сообщение, если текст не разбит на страницы                         
}
else
{   

    for($i = 0; $i < $pages_cnt; $i++)
      {     
       $part= $i + 1;     
   	$content[$i] =  getPrewText($content[$i]);   
	$substr_count = substr_count($content[$i],'msg');   // Поиск подстрки msg в тексте страницы 
  	if($substr_count > 0) 
	    {
	      $Arr[] = $part;            // Если в тексте есть искомая подстрока то помещаем значение страницы $part в массив 
   	    }  
       }
          
          $String = implode(", ", $Arr);   //номера страниц по главам
          $navig_tpl = file_get_contents("{$gl_path_to_engine_root}mods/spaw2full/navigchupter.inc");
          $navig_tpl = str_replace("{ed_page_preview_href}", $ed_page_preview_href, $navig_tpl);
          $navig_tpl = str_replace("{Arr}", $String, $navig_tpl);
	 // $navig_tpl = str_replace("{pages_cnt}", $pages_cnt, $navig_tpl);
        
          save_in_file("{$ed_path_to_file}ch_{$ed_pg}.inc", $navig_tpl, 'w');

	print "<div class='message'>$l_gen[32] $String</div>";
  	print "<p>{$ed_back}</p>";

}

//---------скрипт добавления гиперссылок к оглавлению -----------------------------
/*


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

 */


?>