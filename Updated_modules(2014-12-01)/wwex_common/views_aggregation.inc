<?php
/*
 * Implementation of hook_views_aggregation_functions_info()
 */
function wwex_common_views_aggregation_functions_info() {
  $functions = array(
    'wwex_common_comma_separated' => array(
      'group' => NULL,
      'column' => t('Comma Separated'),
    ),
    'wwex_common_comma_separated_link' => array(
      'group' => NULL,
      'column' => t('Comma Separated Link'),
    ),
  );
  return $functions;
}

/*
 *  wwex_common_comma_separated()
 */
function wwex_common_comma_separated($groups, $field_handler) {
  $separator_group = ',';
  $separator_column = ',';
  $values = array('column' => array());
  foreach ($groups as $group => $rows) {
    $cell_values = array();
    foreach ($rows as $num => $row) {
      $cell = trim(views_aggregator_get_cell($field_handler, $num, TRUE));
      if (!empty($cell)) {
        if (!in_array($cell, $cell_values)) {
          $cell_values[] = $cell;
        }
        if (!in_array($cell, $values['column'])) {
          $values['column'][] = $cell;
        }
      }
    }
    if (count($cell_values) > 1) {
      // After grouping the fields in the group no longer belong to one
      // entity. Cannot easily support hyper-linking, so switch it off.
      unset($field_handler->options['link_to_node']);
      @sort($cell_values, SORT_NATURAL | SORT_FLAG_CASE);
    }
    $values[$group] = implode($separator_group, $cell_values);
  }
  @sort($values['column'], SORT_NATURAL | SORT_FLAG_CASE);
	// empty totals column
  $values['column'] = array();
  //$values['column'] = implode($separator_column, $values['column']);
  return $values;
}

/*
 *  wwex_common_comma_separated_link()
 */
function wwex_common_comma_separated_link($groups, $field_handler, $separator_group_option, $link) {
  $separator_group = !empty($separator_group_option) ? $separator_group_option : ',';
  $separator_column = ',';
  $values = array('column' => array());
	
	$count_total = 0;
  foreach ($groups as $group => $rows) {
		$cell_values = array();
    foreach ($rows as $num => $row) {
      $cell = trim(views_aggregator_get_cell($field_handler, $num, TRUE));
      if (!empty($cell)) {
				$fetched_values = wwex_common_fetch_array_recursive($cell, $separator_group);
				foreach($fetched_values as $new_value){
					if (!in_array($new_value, $cell_values)) {
          	$cell_values[] = $new_value;
					}
				}
      }
    }
		$col_values = implode($separator_group, $cell_values);
    $values[$group] = l(count($cell_values), $link . '/' . $col_values);
		$count_total += count($cell_values);
  }
	$values['column'] = $count_total;
  return $values;
}

/*
 *  wwex_common_fetch_array_recursive()
 */
function wwex_common_fetch_array_recursive($cell, $separator_group){
	if(!empty($cell)){
		$new_array = explode($separator_group, $cell);
		return $new_array;
	}
}
