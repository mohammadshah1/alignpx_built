<?php

/**
 * return date of week with week number
 * @param $week_year
 * @return mixed
 */
function wwex_report_charts_date_of_weeks($week_year) {
  $week_year = explode('-', $week_year);	
  // Adding leading zeros for weeks 1 - 9.
  $date_string = $week_year[0] . 'W' . sprintf('%02d', $week_year[1]);
  $return['start'] = date('Y-m-d', strtotime($date_string));
  $return['end'] = date('Y-m-d', strtotime($date_string . '7'));
  return $return;
}

/**
 * get start date 52 weeks back.
 * @return bool|string
 */
function wwex_report_charts_start_date(){
  return date('Y-m-d', strtotime('-53 monday'));
}

/**
 * get 52 weeks range
 * @param int $weeks_limit
 * @return array
 */
function wwex_report_charts_get_all_weeks($weeks_limit = 53){
	$all_weeks = array();
	for( $i = $weeks_limit; $i>=1; $i--){
		$week_number = date('Y-W', strtotime('-'.$i.' monday'));
		$week_dates = wwex_report_charts_date_of_weeks($week_number);
		$all_weeks[$week_number] = array(
			'week_dates' => $week_dates
		);
	}
	return $all_weeks;
}

/**
 * aggregate nodes with weeks
 * @param $results
 * @return array
 */
function wwex_report_charts_filter_weeks( $results ){
	$filtered_rows = array();
	if(!empty($results)){
		foreach($results as $row){
			$week_number = date("Y-W", $row->node_created);
			$filtered_rows[$week_number][] = $row;
		}		
	}
	return $filtered_rows;	
}
