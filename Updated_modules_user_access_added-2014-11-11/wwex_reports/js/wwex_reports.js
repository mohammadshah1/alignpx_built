
jQuery(document).ready(function(){
 
		jQuery('input[type="checkbox"]').attr('checked','checked');
		
		jQuery("select option").each(function(){
			 
				jQuery(this).attr("selected","selected");
			});
});