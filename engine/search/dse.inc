<?php 
 $stemmed[0] = $_GET['stemmed'];
 $wrd_cnt = count($stemmed); 
 $colorstyle = array('Yellow', 'powderblue', 'PaleTurquoise', 'Wheat', 'Tomato', 'Gold', 'LightCyan', 'Orchid', 'Goldenrod', 'papayawhip', 'lemonchiffon', 'palevioletred', 'Green');
?>
<style type="text/css">
	.Yellow { background-color: Yellow; }
	.Green { background-color: Green; }
	.PaleTurquoise { background-color: PaleTurquoise; }
	.Wheat { background-color: Wheat; }
	.Tomato { background-color: Tomato; }
	.Gold { background-color: Gold; }
	.LightCyan { background-color: LightCyan; }
	.Orchid { background-color: Orchid; }
	.Goldenrod { background-color: Goldenrod; }
	.papayawhip { background-color: papayawhip; }
	.lemonchiffon { background-color: lemonchiffon; }
	.palevioletred { background-color: palevioletred; }
	.powderblue { background-color: powderblue; }
</style>
<script type="text/javascript">
       var Word = {
	selected: function(word, where, className, del) {
		where = typeof where == 'string' ? document.getElementById(where) : where || console.log('Error');
		if(!where) return;
		where.innerHTML = ' '+where.innerHTML.replace(new RegExp(word, 'g'), '<mark class=' + className + '>' + '' + word + '' + '</mark>');		
	},
	deleted: function() {
		var elems = document.getElementsByClassName('wordSelected');
		for(var i=elems.length-1; i>=0; i--) elems[i].outerHTML = ' '+elems[i].innerHTML+' ';
	},
	focused: function() {
		var elems = document.getElementsByClassName('wordSelected');
		if(!elems[0]) return;
		if(elems[this.focusIndex]) elems[this.focusIndex].classList.remove('wordFocused');
		if(elems[++this.focusIndex]) elems[this.focusIndex].classList.add('wordFocused');
		else {
			this.focusIndex = -1;
			this.focused();
		}
	},
	focusIndex: -1
}
<?  if ($wrd_cnt > 0) {  ?> 
  $(document).ready(function() {
<? for($k = 0; $k < $wrd_cnt; $k++) { ?>
     Word.selected('<?=$stemmed[$k]; ?>', 'ministry-text', '<? echo $colorstyle[$k]; ?>');
<? } ?>
 });
<?  } ?> 
</script>
<? // echo $stemmed[0] . " | " . $wrd_cnt . " | " . $colorstyle[0]; ?>




