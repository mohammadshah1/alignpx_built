<?php
/**
* @file
* function wwex_revenue_report_views_default_views() use in wwex_revenue_report module.
**/

/*** Implements hook_views_default_views().
**/
function wwex_revenue_report_views_default_views() {
  $files = file_scan_directory(drupal_get_path('module', 'wwex_revenue_report') . '/views', '/.view/');
  
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
