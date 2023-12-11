<?php
// CLASS START
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
      $innerHTML .= $child->ownerDocument->saveXML($child);
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
// CLASS STOP
?>
