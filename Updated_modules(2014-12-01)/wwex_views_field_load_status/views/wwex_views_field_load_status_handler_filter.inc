<?php

/**
 * @file
 * Filter classes.
 *
 * These classes are always used together, so we keep them in the same file.
 */

/**
 * Generic views handler filter to add code to manipulate the query object.
 */
class wwex_views_field_load_status_handler_filter extends views_handler_filter {
  // Don't display empty space where the operator would be.
  var $no_operator = TRUE;
  var $no_single = TRUE;
  
  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    return $output;
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['load_status_terms'] = array('default' => array());

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  
  $options = array();
    $load_status_terms = taxonomy_get_tree(2);
  $internal_load_status_terms = taxonomy_get_tree(7);
  if ( !empty($load_status_terms) ) {
    foreach ( $load_status_terms as $load_status_term ) {
      $term_id = $load_status_term->tid;
      $term_name = $load_status_term->name;
      $options[$term_id] = "Load Status: " . $term_name;
    }
  }
  if ( !empty($internal_load_status_terms) ) {
    foreach ( $internal_load_status_terms as $internal_load_status_term ) {
      $term_id = $internal_load_status_term->tid;
      $term_name = $internal_load_status_term->name;
      $options[$term_id] = "Internal Load Status: " . $term_name;
    }
  }
  
    $form['load_status_terms'] = array(
      '#type' => 'checkboxes',
      '#options' => $options,
      '#title' => t('Select Terms'),
      '#description' => t('Choose terms which you want to add in filter.'),
      '#default_value' => $this->options['load_status_terms'],
    );

  }
  
 /**
   * Add this filter to the query.
   *
   * Due to the nature of fapi, the value and the operator have an unintended
   * level of indirection. You will find them in $this->operator
   * and $this->value respectively.
   */
  function query() {
  if ($this->options['exposed']) {
      $input = $this->view->get_exposed_input();
      $identifier = $this->options['expose']['identifier'];
      if (isset($input[$identifier])) {
        $terms = $input[$identifier];
  
    $load_status_vid = 2;
    $internal_load_status_vid = 7;
    
    $load_statuses = array();
    foreach ($terms as $term_tid) {
      if ( $term_tid ) {
        $load_term = taxonomy_term_load($term_tid);
        $load_statuses[$load_term->vid][] = $load_term->tid;
      }
    }
  
    if ( !empty($load_statuses) ) {
      // check only load status
      if ( isset($load_statuses[$load_status_vid]) ) {
    
        $table = $this->ensure_my_table();
        $join = new views_join();
        $join->construct('field_data_field_load_status', 'node', 'nid', 'entity_id');
        $this->query->ensure_table('field_data_field_load_status', 'node', $join);
  
        if (!isset($load_statuses[$internal_load_status_vid])) {
          $this->query->add_where($this->options['group'], "field_data_field_load_status.field_load_status_tid", $load_statuses[$load_status_vid], "IN");
        }
      }
  
      // check only internal load status
      if ( isset($load_statuses[$internal_load_status_vid]) ) {
  
        $table = $this->ensure_my_table();
        $join = new views_join();
        $join->construct('node', 'field_data_field_internal_load_status', 'entity_id', 'nid');
        $this->query->ensure_table('field_data_field_internal_load_status', 'node', $join);
  
        if ( !isset($load_statuses[$load_status_vid]) ) {
          $this->query->add_where($this->options['group'], "field_data_field_internal_load_status.field_internal_load_status_tid", $load_statuses[$internal_load_status_vid], "IN");
        }
  
      }
  
      // check load status and internal load status (OR Condition)
      if ( isset($load_statuses[$load_status_vid]) && isset($load_statuses[$internal_load_status_vid]) ) {
        $or_conditions = db_or()
          ->condition('field_data_field_load_status.field_load_status_tid', $load_statuses[$load_status_vid], 'IN')
          ->condition('field_data_field_internal_load_status.field_internal_load_status_tid', $load_statuses[$internal_load_status_vid], 'IN');
        $this->query->add_where($this->options['group'], $or_conditions);
      }
    }
      }
  }
  }
  
  function pre_query() {
  }
  
  /**
   * Provide a simple textfield for equality
   */
 function value_form(&$form, &$form_state) {
    
    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];
    }
    
  foreach ($this->options['load_status_terms'] as $term_tid) {
    if ( $term_tid ) {
      $load_term = taxonomy_term_load($term_tid);
      $options[$term_tid] = $load_term->name;
      }
    }
  global $user;
   if (in_array('super user', $user->roles)) {
   
$delivered = array(23);
}else{
$delivered = NULL;
}
  $form['value'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Value'),
      '#size' => 30,
      '#options' => $options,
	  '#default_value' => $delivered,

    );
    $form['expose_submitted'] = array(
      '#type' => 'hidden',
	  '#value' => 1
    );
    if (!empty($form_state['exposed']) && !isset($form_state['input']['expose_submitted'])) {
      $form_state['input'][$identifier] = $delivered;
    }

    if (!isset($form['value'])) {
      // Ensure there is something in the 'value'.
      $form['value'] = array(
        '#type' => 'value',
        '#value' => NULL
      );
    }
  }
}
