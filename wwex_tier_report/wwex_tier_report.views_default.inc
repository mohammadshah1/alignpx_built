<?php

/**
* @file
* This is wwex_tier_report_views_default_views() for wwex_tier_report module.
*/

/**
* Implements hook_views_default_views().
**/
function wwex_tier_report_views_default_views() {
  
  $files = file_scan_directory(drupal_get_path('module', 'wwex_tier_report') . '/views', '/.view/');
  $views = array();

  foreach ($files as $filepath => $file) {
    require $filepath;
    if (isset($view)) {
      $views[$view->name] = $view;
    }
  }

  return $views;
}

