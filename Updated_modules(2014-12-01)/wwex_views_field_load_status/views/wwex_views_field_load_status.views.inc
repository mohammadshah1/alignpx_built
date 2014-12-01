<?php

/**
* @file
*  function wwex_views_field_load_status_views_data() INC file for wwex_views_field_load_status_views module.
*/

/**
 * Implementation of hook_views_data().
 */
function wwex_views_field_load_status_views_data() {
  $data['wwex_views_field_load_status']['table']['group'] = t('Global');
  $data['wwex_views_field_load_status']['table']['join'] = array(
    '#global' => array(),
  );

  $data['wwex_views_field_load_status']['load_status'] = array(
    'title' => t('Load Status Combine'),
    'help' => t('Combine load status fields.'),
    'filter' => array(
      'handler' => 'wwex_views_field_load_status_handler_filter',
    ),
  );
  
  return $data;
}
