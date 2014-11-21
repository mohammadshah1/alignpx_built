<?php

/**
* @file
* function wwex_shipments_detail_report_views_default_views() INC file for wwex_shipment_detail_report module.
*/

/**
* Implements hook_views_default_views().
**/
function wwex_shipments_detail_report_views_default_views() {
	
	$files = file_scan_directory(drupal_get_path('module', 'wwex_shipments_detail_report'). '/views', '/.view/');
	
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

