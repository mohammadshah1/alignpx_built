<?php
// charts filters
function _sr_query_where( $date_range ){
	$where = "WHERE (( (node.status = '1') AND (node.type IN  ('shipment')) AND (node.created BETWEEN ".$date_range[0]." AND ".$date_range[1].") AND (field_data_field_internal_load_status.field_internal_load_status_tid IN  ('22', '23')) ))";
	
	$sale_rep = (isset($_GET['sales_rep']) && $_GET['sales_rep']!='') ? "AND (node.uid = '".$_GET['sales_rep']."' )" : "";
	$where .= $sale_rep;
	
	return $where;
}

/*
* Chart Name: Sales rep customer rate chart
* Chart Function: _sr_customer_rate_chart()
*/
function _sr_query_customer_rate_results( $date_range ){
	$query = "SELECT node.created AS node_created, field_data_field_customer_rate.field_customer_rate_value AS customer_rate 
	FROM 
	node node
	INNER JOIN field_data_field_internal_load_status field_data_field_internal_load_status ON node.nid = field_data_field_internal_load_status.entity_id AND (field_data_field_internal_load_status.entity_type = 'node' AND field_data_field_internal_load_status.deleted = '0')
	LEFT JOIN field_data_field_customer_rate field_data_field_customer_rate ON node.nid = field_data_field_customer_rate.entity_id AND (field_data_field_customer_rate.entity_type = 'node' AND field_data_field_customer_rate.deleted = '0')
"._sr_query_where( $date_range )."";
	$results = db_query($query);
	return $results;
}

// format data for charts
function _sr_customer_rate_format_results( $results ){
	
	$filtered_rows = wwex_report_charts_filter_weeks( $results );
	
	$formated_results = wwex_report_charts_get_all_weeks();
	if(!empty($filtered_rows)){
		foreach($filtered_rows as $week_number => $week_data){
			foreach($week_data as $row){
				//__pre($row);
				$formated_results[$week_number]['customer_rate'] += $row->customer_rate;
			}
			$formated_results[$week_number]['customer_rate_average'] = _sr_customer_rate_average($formated_results[$week_number]['customer_rate'], $formated_results[$week_number]['week_dates']['end']);

		
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
function _sr_customer_rate_average($field_value, $date_max){
	$average_value = 0;
	if( $field_value ){
		$_date_min = strtotime('-5 weeks', strtotime($date_max));
		$_date_max = strtotime($date_max);
		
		$results = _sr_query_customer_rate_results(array($_date_min, $_date_max));
		
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

// sales rep chart data
function _sr_customer_rate_chart(){
	$date_min = strtotime( wwex_report_charts_start_date() );
	$date_max = time();
	
	$results = _sr_query_customer_rate_results(array($date_min, $date_max));
	
	$formated_results = _sr_customer_rate_format_results( $results );
	return $formated_results;
}

/*
* Chart Name: Sales rep customers chart
* Chart Function: _sr_customer_rate_chart()
*/
function _sr_query_customer_results( $date_range ){
	$query = "SELECT node.created AS node_created, COUNT(DISTINCT(field_data_field_w_number.field_w_number_value)) AS w_number 
	FROM 
	node node
	INNER JOIN field_data_field_internal_load_status field_data_field_internal_load_status ON node.nid = field_data_field_internal_load_status.entity_id AND (field_data_field_internal_load_status.entity_type = 'node' AND field_data_field_internal_load_status.deleted = '0')
	LEFT JOIN field_data_field_w_number field_data_field_w_number ON node.nid = field_data_field_w_number.entity_id AND (field_data_field_w_number.entity_type = 'node' AND field_data_field_w_number.deleted = '0')
"._sr_query_where( $date_range )."
	GROUP BY field_data_field_w_number.field_w_number_value, node.created
  ";
	$results = db_query($query);
	return $results;
}

// formate customers data
function _sr_customer_format_results( $results ){
	
	$filtered_rows = wwex_report_charts_filter_weeks( $results );
	
	$formated_results = wwex_report_charts_get_all_weeks();
	if(!empty($filtered_rows)){
		foreach($filtered_rows as $week_number => $week_data){
			foreach($week_data as $row){
				//__pre($row);
				$formated_results[$week_number]['customer'] += $row->w_number;
			}
			$formated_results[$week_number]['customer_average'] = _sr_customer_average($formated_results[$week_number]['customer'], $formated_results[$week_number]['week_dates']['end']);

		
		}		
	}
	
	$chart_serires = array();
	if(!empty($formated_results)){
		foreach($formated_results as $result_row){
			$chart_serires['customer'][] = isset($result_row['customer']) ? $result_row['customer'] : 0;
			$chart_serires['customer_average'][] = isset($result_row['customer_average']) ? $result_row['customer_average'] : 0;
			$chart_serires['chart_dates'][] = isset($result_row['week_dates']['end']) ? date('m/d', strtotime($result_row['week_dates']['end'])) : 0;
		}		
	}
	
	return $chart_serires;	
}

// get field rate 6 weeks average
function _sr_customer_average($field_value, $date_max){
	$average_value = 0;
	if( $field_value ){
		$_date_min = strtotime('-5 weeks', strtotime($date_max));
		$_date_max = strtotime($date_max);
		
		$results = _sr_query_customer_results(array($_date_min, $_date_max));
		
		$total = 0;
		if( !empty($results)){
			foreach( $results as $row ){
				$total += $row->w_number;
			}
			$average_value = $total > 0 ? round( ($total / 6), 2, PHP_ROUND_HALF_ODD)  : 0;	
		}
	}
	return $average_value;
}

// sales rep chart data
function _sr_customers_chart(){
	$date_min = strtotime( wwex_report_charts_start_date() );
	$date_max = time();
	
	$results = _sr_query_customer_results(array($date_min, $date_max));
	
	$formated_results = _sr_customer_format_results( $results );
	return $formated_results;
}

/*
* Chart Name: Sales rep shipments chart
* Chart Function: _sr_customers_chart()
*/
function _sr_query_shipments_results( $date_range ){
	$query = "SELECT node.created AS node_created, COUNT(DISTINCT(node.nid)) AS node_nid 
	FROM 
	node node
	INNER JOIN field_data_field_internal_load_status field_data_field_internal_load_status ON node.nid = field_data_field_internal_load_status.entity_id AND (field_data_field_internal_load_status.entity_type = 'node' AND field_data_field_internal_load_status.deleted = '0')
"._sr_query_where( $date_range )."
	GROUP BY node.nid, node.created
	";
	$results = db_query($query);
	return $results;
}

// formate shipments data
function _sr_shipments_format_results( $results ){
	
	$filtered_rows = wwex_report_charts_filter_weeks( $results );
	
	$formated_results = wwex_report_charts_get_all_weeks();
	if(!empty($filtered_rows)){
		foreach($filtered_rows as $week_number => $week_data){
			foreach($week_data as $row){
				//__pre($row);
				$formated_results[$week_number]['shipments'] += $row->node_nid;
			}
			$formated_results[$week_number]['shipments_average'] = _sr_shipments_average($formated_results[$week_number]['shipments'], $formated_results[$week_number]['week_dates']['end']);

		
		}		
	}
	
	$chart_serires = array();
	if(!empty($formated_results)){
		foreach($formated_results as $result_row){
			$chart_serires['shipments'][] = isset($result_row['shipments']) ? $result_row['shipments'] : 0;
			$chart_serires['shipments_average'][] = isset($result_row['shipments_average']) ? $result_row['shipments_average'] : 0;
			$chart_serires['chart_dates'][] = isset($result_row['week_dates']['end']) ? date('m/d', strtotime($result_row['week_dates']['end'])) : 0;
		}		
	}
	
	return $chart_serires;	
}

// get field rate 6 weeks average
function _sr_shipments_average($field_value, $date_max){
	$average_value = 0;
	if( $field_value ){
		$_date_min = strtotime('-5 weeks', strtotime($date_max));
		$_date_max = strtotime($date_max);
		
		$results = _sr_query_shipments_results(array($_date_min, $_date_max));
		
		$total = 0;
		if( !empty($results)){
			foreach( $results as $row ){
				$total += $row->node_nid;
			}
			$average_value = $total > 0 ? round( ($total / 6), 2, PHP_ROUND_HALF_ODD)  : 0;	
		}
	}
	return $average_value;
}

// sales rep chart data
function _sr_shipments_chart(){
	$date_min = strtotime( wwex_report_charts_start_date() );
	$date_max = time();
	
	$results = _sr_query_shipments_results(array($date_min, $date_max));
	
	$formated_results = _sr_shipments_format_results( $results );
	return $formated_results;
}


/*
* Chart Name: Sales rep margin chart
* Chart Function: _sr_customers_chart()
*/
function _sr_query_margin_results( $date_range ){
	$query = "SELECT node.created AS node_created, ((field_data_field_customer_rate.field_customer_rate_value) - (field_data_field_carrier_rate.field_carrier_rate_value + field_data_field_shipment_booking_fee.field_shipment_booking_fee_value)) AS margin
FROM
node
INNER JOIN field_data_field_internal_load_status ON node.nid = field_data_field_internal_load_status.entity_id AND (field_data_field_internal_load_status.entity_type = 'node' AND field_data_field_internal_load_status.deleted = '0')
LEFT JOIN field_data_field_customer_rate ON node.nid = field_data_field_customer_rate.entity_id AND (field_data_field_customer_rate.entity_type = 'node' AND field_data_field_customer_rate.deleted = '0')
LEFT JOIN field_data_field_carrier_rate ON node.nid = field_data_field_carrier_rate.entity_id AND (field_data_field_carrier_rate.entity_type = 'node' AND field_data_field_carrier_rate.deleted = '0')
LEFT JOIN field_data_field_shipment_booking_fee ON node.nid = field_data_field_shipment_booking_fee.entity_id AND (field_data_field_shipment_booking_fee.entity_type = 'node' AND field_data_field_shipment_booking_fee.deleted = '0')
"._sr_query_where( $date_range )."";
	$results = db_query($query);
	return $results;
}

// formate shipments data
function _sr_margin_format_results( $results ){
	
	$filtered_rows = wwex_report_charts_filter_weeks( $results );
	
	$formated_results = wwex_report_charts_get_all_weeks();
	if(!empty($filtered_rows)){
		foreach($filtered_rows as $week_number => $week_data){
			foreach($week_data as $row){
				//__pre($row);
				$formated_results[$week_number]['margin'] += $row->margin;
			}
			$formated_results[$week_number]['margin_average'] = _sr_margin_average($formated_results[$week_number]['margin'], $formated_results[$week_number]['week_dates']['end']);

		
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
function _sr_margin_average($field_value, $date_max){
	$average_value = 0;
	if( $field_value ){
		$_date_min = strtotime('-5 weeks', strtotime($date_max));
		$_date_max = strtotime($date_max);
		
		$results = _sr_query_margin_results(array($_date_min, $_date_max));
		
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
function _sr_margin_chart(){
	$date_min = strtotime( wwex_report_charts_start_date() );
	$date_max = time();
	
	$results = _sr_query_margin_results(array($date_min, $date_max));
	
	$formated_results = _sr_margin_format_results( $results );
	return $formated_results;
}

