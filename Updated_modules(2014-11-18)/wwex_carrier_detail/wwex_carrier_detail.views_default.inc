<?php

/**
* @file
* function wwex_carrier_detail_views_default_views() INC file for wwex_carrier_detail module.
*/

/**
* Implements hook_views_default_views().
**/
function wwex_carrier_detail_views_default_views() {
	
	$files = file_scan_directory(drupal_get_path('module', 'wwex_carrier_detail'). '/views', '/.view/');
	
	foreach ($files as $filepath => $file) {
		require $filepath;
		if (isset($view)) {
			$views[$view->name] = $view;
		}
	}
	
	if ($views) {
		return $views;
	}
}

