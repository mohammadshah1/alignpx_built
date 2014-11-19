<?php

/**
* @file
* Function wwex_customer_list_views_default_views() for wwex_customer_list module.
*/

/**
 * implements hook_views_default_views()
 * @return array
 */
function wwex_customer_list_views_default_views() {
  $views = array();
  $files = file_scan_directory(drupal_get_path('module', 'wwex_customer_list') . '/views', '/.view/');
  foreach ($files as $filepath => $file) {
    require($filepath);
    if (isset($view)) {
      $views[$view->name] = $view;
    }
  }

  return $views;
}

