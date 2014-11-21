<?php

/**
* @file
* Function wwex_customer_list_views_default_views() for wwex_customer_list module.
*/

/**
 * Implements hook_views_default_views().
 */
function wwex_customer_list_views_default_views() {
  $files = file_scan_directory(drupal_get_path('module', 'wwex_customer_list') . '/views', '/.view/');
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

