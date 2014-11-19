<?php
/**
 * sales rep custom filter handler
 */
class wwex_views_uid_filter_handler_filter_author_select extends views_handler_filter_in_operator {

	/**
	 * Override parent get_value_options() function.
	 *
	 * @return
	 *   Return the stored values in $this->value_options if someone expects it.
	 */
  function get_value_options() {
		$sql_string = "";
		global $user;
		
		if( user_is_logged_in() ) {
			
			if( in_array('super user', $user->roles) ) {
				$sql_string = " ";
			}
			else {
				$user_obj = user_load($user->uid);
				$franchise_nid = $user_obj->field_user_franchise[LANGUAGE_NONE][0]['nid'];
				$user_obj = user_load($user->uid); 
				$user_franchise_nid = $user_obj->field_user_franchise[LANGUAGE_NONE][0]['nid'];
				$sql_string = " AND fr.field_user_franchise_nid = '" .$user_franchise_nid. "'";
			}
		}
	
		$query = "SELECT DISTINCT fr.entity_id, usr.name 
		FROM {field_data_field_user_franchise} fr, {users_roles} ur, {node} n, {users} usr 
		WHERE  (fr.entity_id = ur.uid AND ur.rid != '7') 
		AND fr.entity_id = n.uid AND fr.entity_id = usr.uid AND n.type = 'shipment' " .$sql_string. "";
		
		$res = db_query($query); 

		foreach ( $res as $user_value ) {
			$users[$user_value->entity_id] = $user_value->name;
		}
    // We don't need Guest user here, so remove it.
    unset($users[0]);
		// Sort by username.
    natsort($users);

    $this->value_options = $users;

    return $users;
  }
}