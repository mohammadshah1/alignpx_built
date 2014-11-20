<?php
// sales rep query for customer rate
function _cd_query_nc_results( $date_range, $w_number = 0 ){
 $place_holders = array(':date_from' => $date_range[0], ':date_to' => $date_range[1], ':w_number' => $w_number);

 $query = "SELECT UNIX_TIMESTAMP(field_data_field_ship_date.field_ship_date_value) AS node_created, COUNT(DISTINCT(node.nid)) AS nid 
 FROM 
 {node} node
 LEFT JOIN {users} users_node ON node.uid = users_node.uid
 LEFT JOIN {field_data_field_w_number} field_data_field_w_number ON node.nid = field_data_field_w_number.entity_id AND (field_data_field_w_number.entity_type = 'node' AND field_data_field_w_number.deleted = '0')
 LEFT JOIN {field_data_field_ship_date} field_data_field_ship_date ON node.nid = field_data_field_ship_date.entity_id AND (field_data_field_ship_date.entity_type = 'node' AND field_data_field_ship_date.deleted = '0')
 WHERE (node.status = '1') AND (node.type IN  ('shipment')) AND (UNIX_TIMESTAMP(field_data_field_ship_date.field_ship_date_value) BETWEEN :date_from AND :date_to) AND (field_data_field_w_number.field_w_number_value = :w_number)
 GROUP BY node_created, node.nid";
 $results = db_query($query, $place_holders);
 return $results;
}

// create charts series
// format data for charts
function _cd_nc_format_results( $results ){
	
	$filtered_rows = wwex_report_charts_filter_weeks( $results );
	
	$formated_results = wwex_report_charts_get_all_weeks();
	if(!empty($filtered_rows)){
		foreach($filtered_rows as $week_number => $week_data){
			foreach($week_data as $row){
				//__pre($row);
				$formated_results[$week_number]['shipments'] += $row->nid;
			}
			$formated_results[$week_number]['shipments_avg'] = _cd_nc_average($formated_results[$week_number]['shipments'], $formated_results[$week_number]['week_dates']['end']);

		
		}		
	}
	
	$chart_serires = array();
	if(!empty($formated_results)){
		foreach($formated_results as $result_row){
			$chart_serires['shipments'][] = isset($result_row['shipments']) ? $result_row['shipments'] : 0;
			$chart_serires['shipments_avg'][] = isset($result_row['shipments_avg']) ? $result_row['shipments_avg'] : 0;
			$chart_serires['chart_dates'][] = isset($result_row['week_dates']['end']) ? date('m/d', strtotime($result_row['week_dates']['end'])) : 0;
		}		
	}
	
	return $chart_serires;	
}

// get field rate 6 weeks average
function _cd_nc_average($field_value, $date_max){
	$average_value = 0;
	if( $field_value ){
		$_date_min = strtotime('-3 weeks', strtotime($date_max));
		$_date_max = strtotime($date_max);
		
		$w_number = wwex_access_clean_input( arg(1) );
		$results = _cd_query_nc_results(array($_date_min, $_date_max), $w_number);
		
		$total = 0;
		if( !empty($results)){
			foreach( $results as $row ){
				$total += $row->nid;
			}
			$average_value = $total > 0 ? round( ($total / 6), 2, PHP_ROUND_HALF_ODD)  : 0;	
		}
	}
	return $average_value;
}

// sales rep chart data
function _cd_nc_chart(){
	$date_min = strtotime( wwex_report_charts_start_date() );
	$date_max = time();
	$w_number = wwex_access_clean_input( arg(1) );
	$results = _cd_query_nc_results(array($date_min, $date_max), $w_number);
	
	$formated_results = _cd_nc_format_results( $results );
	return $formated_results;
}



/* ***************************************************************************************************** */
/*
* Chart Name: Spend By Week for ADVANCED DIGITAL BROADCAST
* Chart Function: _cd_customer_rate_chart()
*/
function _cd_query_customer_rate_results( $date_range, $w_number = 0 ){
	$place_holders = array(':date_from' => $date_range[0], ':date_to' => $date_range[1], ':w_number' => $w_number);
	
	$query = "SELECT UNIX_TIMESTAMP(field_data_field_ship_date.field_ship_date_value) AS node_created, field_data_field_customer_rate.field_customer_rate_value AS customer_rate
	FROM 
	{node} node
	LEFT JOIN {field_data_field_customer_rate} field_data_field_customer_rate ON node.nid = field_data_field_customer_rate.entity_id AND (field_data_field_customer_rate.entity_type = 'node' AND field_data_field_customer_rate.deleted = '0')
    LEFT JOIN {field_data_field_w_number} field_data_field_w_number ON node.nid = field_data_field_w_number.entity_id AND (field_data_field_w_number.entity_type = 'node' AND field_data_field_w_number.deleted = '0')
 	LEFT JOIN {field_data_field_ship_date} field_data_field_ship_date ON node.nid = field_data_field_ship_date.entity_id AND (field_data_field_ship_date.entity_type = 'node' AND field_data_field_ship_date.deleted = '0')
	WHERE (node.status = '1') AND (node.type IN  ('shipment')) AND (UNIX_TIMESTAMP(field_data_field_ship_date.field_ship_date_value) BETWEEN :date_from AND :date_to) AND (field_data_field_w_number.field_w_number_value = :w_number)";
	
	$results = db_query($query, $place_holders);
	return $results;
}

// format data for charts
function _cd_customer_rate_format_results( $results ){
	
	$filtered_rows = wwex_report_charts_filter_weeks( $results );
	
	$formated_results = wwex_report_charts_get_all_weeks();
	if(!empty($filtered_rows)){
		foreach($filtered_rows as $week_number => $week_data){
			foreach($week_data as $row){
				//__pre($row);
				$formated_results[$week_number]['customer_rate'] += $row->customer_rate;
			}
			$formated_results[$week_number]['customer_rate_average'] = _cd_customer_rate_average($formated_results[$week_number]['customer_rate'], $formated_results[$week_number]['week_dates']['end']);

		
		}		
	}
	
	$chart_serires = array();
	if(!empty($formated_results)){
		foreach($formated_results as $result_row){
			$chart_serires['customer_rate'][] = isset($result_row['customer_rate']) ? $result_row['customer_rate'] : 0;
			$chart_serires['customer_rate_average'][] = isset($result_row['customer_rate_average']) ? $result_row['customer_rate_average'] : 0;
			$chart_serires['chart_dates'][] = isset($result_row['week_dates']['end']) ? date('m/d', strtotime($result_row['week_dates']['end'])) : 0;
		}		
	}
	
	return $chart_serires;	
}

// get field rate 6 weeks average
function _cd_customer_rate_average($field_value, $date_max){
	$average_value = 0;
	if( $field_value ){
		$_date_min = strtotime('-3 weeks', strtotime($date_max));
		$_date_max = strtotime($date_max);
		
		$w_number = wwex_access_clean_input( arg(1) );
		$results = _cd_query_customer_rate_results(array($_date_min, $_date_max), $w_number);
		
		$total = 0;
		if( !empty($results)){
			foreach( $results as $row ){
				$total += $row->customer_rate;
			}
			$average_value = $total > 0 ? round( ($total / 6), 2, PHP_ROUND_HALF_ODD)  : 0;	
		}
	}
	return $average_value;
}

// customer detail chart data
function _cd_customer_rate_chart(){
	$date_min = strtotime( wwex_report_charts_start_date() );
	$date_max = time();
	
	$w_number = wwex_access_clean_input( arg(1) );
	$results = _cd_query_customer_rate_results(array($date_min, $date_max), $w_number);
	
	$formated_results = _cd_customer_rate_format_results( $results );
	return $formated_results;
}





/* ****************************************************************************** */

/*
* Chart Name: Margin $ By Week for ADVANCED DIGITAL BROADCAST chart
* Chart Function: _cd_margin_chart()
*/
function _cd_query_margin_results( $date_range, $w_number = 0 ){
	$place_holders = array(':date_from' => $date_range[0], ':date_to' => $date_range[1], ':w_number' => $w_number);
	
	$query = "SELECT UNIX_TIMESTAMP(field_data_field_ship_date.field_ship_date_value) AS node_created, ((field_data_field_customer_rate.field_customer_rate_value) - (field_data_field_carrier_rate.field_carrier_rate_value + field_data_field_shipment_booking_fee.field_shipment_booking_fee_value)) AS margin
	FROM
	{node} node
	LEFT JOIN {field_data_field_customer_rate} field_data_field_customer_rate ON node.nid = field_data_field_customer_rate.entity_id AND (field_data_field_customer_rate.entity_type = 'node' AND field_data_field_customer_rate.deleted = '0')
	LEFT JOIN {field_data_field_carrier_rate} field_data_field_carrier_rate ON node.nid = field_data_field_carrier_rate.entity_id AND (field_data_field_carrier_rate.entity_type = 'node' AND field_data_field_carrier_rate.deleted = '0')
	LEFT JOIN {field_data_field_shipment_booking_fee} field_data_field_shipment_booking_fee ON node.nid = field_data_field_shipment_booking_fee.entity_id AND (field_data_field_shipment_booking_fee.entity_type = 'node' AND field_data_field_shipment_booking_fee.deleted = '0')
	LEFT JOIN {field_data_field_w_number} field_data_field_w_number ON node.nid = field_data_field_w_number.entity_id AND (field_data_field_w_number.entity_type = 'node' AND field_data_field_w_number.deleted = '0')
 	LEFT JOIN {field_data_field_ship_date} field_data_field_ship_date ON node.nid = field_data_field_ship_date.entity_id AND (field_data_field_ship_date.entity_type = 'node' AND field_data_field_ship_date.deleted = '0')
	WHERE (node.status = '1') AND (node.type IN  ('shipment')) AND (UNIX_TIMESTAMP(field_data_field_ship_date.field_ship_date_value) BETWEEN :date_from AND :date_to) AND (field_data_field_w_number.field_w_number_value = :w_number)";
	$results = db_query($query, $place_holders);
	return $results;
}

// formate shipments data
function _cd_margin_format_results( $results ){
	
	$filtered_rows = wwex_report_charts_filter_weeks( $results );
	
	$formated_results = wwex_report_charts_get_all_weeks();
	if(!empty($filtered_rows)){
		foreach($filtered_rows as $week_number => $week_data){
			foreach($week_data as $row){
				//__pre($row);
				$formated_results[$week_number]['margin'] += $row->margin;
			}
			$formated_results[$week_number]['margin_average'] = _cd_margin_average($formated_results[$week_number]['margin'], $formated_results[$week_number]['week_dates']['end']);

		
		}		
	}
	
	$chart_serires = array();
	if(!empty($formated_results)){
		foreach($formated_results as $result_row){
			$chart_serires['margin'][] = isset($result_row['margin']) ? $result_row['margin'] : 0;
			$chart_serires['margin_average'][] = isset($result_row['margin_average']) ? $result_row['margin_average'] : 0;
			$chart_serires['chart_dates'][] = isset($result_row['week_dates']['end']) ? date('m/d', strtotime($result_row['week_dates']['end'])) : 0;
		}		
	}
	
	return $chart_serires;	
}

// get field rate 6 weeks average
function _cd_margin_average($field_value, $date_max){
	$average_value = 0;
	if( $field_value ){
		$_date_min = strtotime('-3 weeks', strtotime($date_max));
		$_date_max = strtotime($date_max);
		
		$w_number = wwex_access_clean_input( arg(1) );
		$results = _cd_query_margin_results(array($_date_min, $_date_max), $w_number);
		
		$total = 0;
		if( !empty($results)){
			foreach( $results as $row ){
				$total += $row->margin;
			}
			$average_value = $total > 0 ? round( ($total / 6), 2, PHP_ROUND_HALF_ODD)  : 0;	
		}
	}
	return $average_value;
}

// sales rep chart data
function _cd_margin_chart(){
	$date_min = strtotime( wwex_report_charts_start_date() );
	$date_max = time();
	
	$w_number = wwex_access_clean_input( arg(1) );
	$results = _cd_query_margin_results(array($date_min, $date_max), $w_number);
	
	$formated_results = _cd_margin_format_results( $results );
	return $formated_results;
}

