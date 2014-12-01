<?php

/**
* @file
* function wwex_market_performance_report_views_default_views() use in wwex_market_performance_report module.
**/

/**
* Implements hook_views_default_views().
**/
function wwex_market_performance_report_views_default_views() {
  $files = file_scan_directory(drupal_get_path('module', 'market_performance_report') . '/views', '/.view/');  
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

