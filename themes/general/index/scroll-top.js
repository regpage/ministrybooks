$(document).ready(function(){
			$('a.scroll').click(function(){
				var el = $(this).attr('href');
				var elWrapped = $(el);
				scrollToDiv(elWrapped,40);
				return false;
			});
			function scrollToDiv(element,navheight){
				var offset = element.offset();
				var offsetTop = offset.top;
				var totalScroll = offsetTop-navheight;
				$('body,html').animate({
						scrollTop: totalScroll
				}, 500);
			}
		});