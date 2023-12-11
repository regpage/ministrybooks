<?php
/*


http://www.internet-technologies.ru/articles/article_1126.html
http://www.sql.ru/forum/356124/php-kak-peredavat-massiv-ot-stranicy-k-stranice
http://www.softtime.ru/forum/read.php?id_forum=3&id_theme=28098&page=0
http://htmlweb.ru/php/example/postranichniy_vivod.php
http://www.manhunter.ru/webmaster/478_relevantniy_poisk_po_baze_mysql.html  

*/
function PagePrint($variable) {
global $beginPage, $endPage;//------Объявляем глобальные переменные, отвечающие за ссылку на первую и последнюю страницу
 $href='';//-----Перемменная содержащая в себе постраничный вывод
 $separator=' ';//-----Переменная задающая разделитель между ссылками, по умолчанию пробел
 $style='style="text-decoration:none" style="color:orange" style="font-weight:bold"';//-------Задаёт стиль текущей страницы
 $stylePage='style="text-decoration:none" style="color:blue" style="font-weight:bold"';//------Задаёт стиль ссылки на первую и последнюю страницу
 if(is_array($variable))://------Проверяем тип array
 #Перебираем массив и присваиваем $number - количество записей, $start - точка извлечения, $pageCount - количество записей, $andere - другие свойства ссылки, $class - стиль для ссылок, $showLink - количество ссылок на странице
 list($number, $start, $pageCount, $andere, $class, $showLink)=$variable;
 #Обрабатывам $start
 if(empty($start) && !is_int($start) && !is_numeric($start)) $start=0;
 else $start=$start;
 #Обрабатываем $number
 if(empty($number) && !is_int($number) && !is_numeric($number)) $number=10;
 else $number=$number;

 $page=(($start/10)+1);//-------Рассчитывавем номер страницы
 $count=ceil($pageCount/$number);//------Количество страниц 

 #Вывод сслыки на первую и последнюю страницы
 if($count!==1) :
 $beginPage="<a href="".getenv('PHP_SELF')."?start=0".$andere."" ".$stylePage.">перв</a>";//--------Первая страница
 $endPage="<a href="".getenv('PHP_SELF')."?start=".(($count-1)*10).$andere."" ".$stylePage.">посл</a>";//-----Последняя страница
 else: FALSE;
 endif;

 if($pageCount==10): return False;
 else:
 #Постраничный вывод
 $begin=$page - intval($showLink/2);//------Определяет номер страницы с которой выводить
 for($j=0; $j<=$showLink; $j++):
 $i=$begin+$j;//------Номер страницы
 //#Защищает скрипт если $<0, будет до тех пор увеличивать пока $showPage=1

 if($i<1):
 $showLink++;
 continue;
 endif;
 //#Постраничный вывод
 if($i>$count) break;//-----Защита если количество $i>возможных записей
 if($i==$page) $href=$href." <a ".$style." >".$i."</a>";//------Вывод текущей страницы
 else $href=$href." <a href="".getenv('PHP_SELF')."?start=".(($i - 1)*10).$andere."" ".$class.">".$i."</a> ";//------Вывод следующих страниц
 endfor;
 return $href;
 endif;
 endif;
}
?>