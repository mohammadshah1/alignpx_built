<?php

/**
* @file
* function wwex_sales_rep_report_views_default_views() use in wwex_sale_rep_report module.
**/

/**
* Implements hook_views_default_views().
**/
function wwex_sales_rep_report_views_default_views() {
  $files = file_scan_directory(drupal_get_path('module', 'wwex_sales_rep_report') . '/views', '/.view/');  
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

