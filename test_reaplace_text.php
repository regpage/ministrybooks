<?php
	
$path_book = "/home/u385758/recovery.ministrybooks.ru/www/content/397/test_397.inc";

//$path_book = ""{$ed_path_to_file}{$ed_pg}.inc";";

if(file_exists($path_book))

$str = file_get_contents($path_book);

$star = '~ class=\"decimalbd\">\s+(.*?)\s+<\/ol>~s';

if (preg_match($star, $str)) {    
   echo "Вхождение найдено." . $star;}
else {
   echo "Вхождение не найдено то что нужно.";
}

$patern='#<ol\s+(.*?)<\/ol>#is';

preg_match($patern, $str, $arr);

if (preg_match($patern, $str)) {    
	echo "Вхождение найдено.";
    //echo "\n\n | {$arr[0]}\n";
} 
else 
{
   echo "Вхождение не найдено.";
}

session_start(); 
$id_part = $_SESSION['id_part'];
//echo $id_part;
echo $ar[0]["attr"]["start"];

if (isset($id_part)) echo $id_part; else echo "<br><br><br>Cсылка не определена!<br><br><br>";
//echo $str;   // Текст книги
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

//print_r($ar[0]["child"]);
var_dump($ar[0]);

echo "<br><br>";        
	echo $ar[0]["name"] . " ---Значение тега 'ol' или 'ul'";
echo "<br><br>";        
	echo $ar[0]["attr"]["class"] . " ---Значение атибута 'class'";
echo "<br><br>";        
	echo $ar[0]["attr"]["start"] . " ---Значение атибута 'start'"; // Значение атибута 'start'

	session_start(); 
	$id_part=$ar[0]["attr"]["start"]; 
	$_SESSION['id_part'] = $id_part;

echo "<br><br>";
        echo count($ar[0]["child"]) . " --- Количесво элементов в массиве";
echo "<br><br><br>"; 
	echo $ar[0]["child"][0]["text"] . " ----Название сообщений";
echo "<br><br>"; 
	echo $ar[0]["child"][0]["child"][0]["text"] . " ----Название сообщений";

if (isset($ar[0]["attr"]["class"])) {

	 if (isset($ar[0]["attr"]["start"])){ $atr_start = " start =" . $ar[0]["attr"]["start"];} else {$atr_start="";} 

	$url = "?mb=397";
	$ch=array(2, 7, 11, 15, 20, 24, 27, 31, 34, 38, 43, 47, 51, 53, 57, 61, 64, 68, 72);

		$bar = "<ol{$atr_start}>";

	for ($i = 1; $i <= count($ar[0]["child"]); $i++) 
 	 { 
		$j=$i-1;

		$bar = $bar."<li>";   		 	
		$bar = $bar."<a href='http://recovery.ministrybooks.ru/$url&&part=$ch[$j]'>" . $ar[0]["child"][$j]["child"][0]["text"] . "</a>";
		$bar = $bar."</li>";
  
	} 

		$bar = $bar."</ol>";

       echo $bar;

	$str = preg_replace($patern, $bar, $str, 1);

	//file_put_contents($path_book, $str);
}

?>
 
 