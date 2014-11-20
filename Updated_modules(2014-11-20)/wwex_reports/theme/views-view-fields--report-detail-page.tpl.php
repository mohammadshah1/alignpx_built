<?php  if(!isset($_GET)){ ?>
<script type="text/javascript">
	jQuery(document).ready(function(){
			jQuery('input[type="checkbox"]').attr('checked','checked');
	});
</script>
<?php } ?>
<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
  // drupal_set_message('<pre>' . print_r(array_keys($fields), TRUE) . '</pre>');
?>
<article class="">
	<fieldset id="node_shipment_full_group_load_info" class="group-load-info field-group-fieldset form-wrapper"> 
		<legend>
			<span class="fieldset-legend">Bol#- Carrier</span>
		</legend>
		<div class="fieldset-wrapper">
			
			<div class="field-label"><?php print $fields['id']->label_html; ?> </div> 
			<div class="field-items">
				<div class="field-item even"><?php print  $fields['id']->content; ?></div>
			</div>

			<div class="field-label"><?php print  $fields['field_shipment_carrier']->label_html; ?></div> 
			<div class="field-items">
				<div class="field-item even"><?php print  $fields['field_shipment_carrier']->content; ?></div>
			</div>
			
			<div class="field-label"><?php print $fields['created']->label_html; ?> </div> 
			<div class="field-items">
				<div class="field-item even"><?php print $fields['created']->content;?></div>
			</div>
			
			<div class="field-label"><?php print $fields['field_ship_date']->label_html; ?> </div> 
			<div class="field-items">
				<div class="field-item even"><?php print $fields['field_ship_date']->content;?> </div>
			</div>
			
			<div class="field-label"><?php print $fields['field_time_marked_delivered']->label_html; ?> </div> 
			<div class="field-items">
				<div class="field-item even"><?php print $fields['field_time_marked_delivered']->content;?></div>
			</div>
			
			<div class="field-label"><?php print $fields['field_delivery_date']->label_html; ?> </div> 
			<div class="field-items">
				<div class="field-item even"><?php print $fields['field_delivery_date']->content; ?></div>
			</div>
			<div class="field-label"><?php print $fields['field_load_status']->label_html; ?> </div> 
			<div class="field-items">
				<div class="field-item even"><?php print $fields['field_load_status']->content; ?></div>
			</div>
		</div>	
	</fieldset>

	<fieldset id="node_shipment_full_group_load_info" class="group-load-info field-group-fieldset form-wrapper"> 
		<legend>
			<span class="fieldset-legend">Shiper Info</span>
		</legend>
		<div class="fieldset-wrapper">
			
			<div class="field-label"><?php print $fields['field_origin_contact_name']->label_html; ?> </div>
			<div class="field-items">
				<div class="field-item even"><?php print  $fields['field_origin_contact_name']->content; ?></div>
			</div>
			
			<div class="field-label"><?php print $fields['field_origin_phone']->label_html; ?> </div>
			<div class="field-items">
				<div class="field-item even"><?php print  $fields['field_origin_phone']->content; ?></div>
			</div>

			<div class="field-label"><?php print  $fields['field_shipment_origin']->label_html; ?></div> 
			<div class="field-label">
				<div class="field-item even"><?php print  $fields['field_shipment_origin']->content; ?></div>
			</div>
			
		</div>		
	</fieldset>

	<fieldset id="node_shipment_full_group_load_info" class="group-load-info field-group-fieldset form-wrapper"> 
		<legend>
			<span class="fieldset-legend">Receiver Info</span>
		</legend>
		
		<div class="fieldset-wrapper">
			
			<div class="field-label"><?php print $fields['field_dest_contact_name']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print $fields['field_dest_contact_name']->content;?></div>
			</div>
			
			<div class="field-label"><?php print $fields['field_dest_phone']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print $fields['field_dest_phone']->content;?></div>
			</div>	
			
			<div class="field-label"><?php print $fields['field_destination']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print $fields['field_destination']->content;?></div>
			</div>
			
		</div> 
	</fieldset>

	<fieldset id="node_shipment_full_group_load_info" class="group-load-info field-group-fieldset form-wrapper">
		<legend>
			<span class="fieldset-legend">Billing Info</span>
		</legend>
		<div class="fieldset-wrapper"> 	
			
			<div class="field-label"><?php print $fields['field_customer_rate']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print '$'.number_format($fields['field_customer_rate']->content,2); ?></div>
			</div>
			
			<div class="field-label"><?php print $fields['field_carrier_rate']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print '$'.number_format($fields['field_carrier_rate']->content,2);?></div>
			</div>
			
			<div class="field-label"><?php print $fields['field_shipment_booking_fee']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print '$'.number_format($fields['field_shipment_booking_fee']->content,2);?></div>
			</div>
			
			<div class="field-label"><?php print $fields['expression']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print '$'.number_format($fields['expression']->content,2);?></div>
			</div>
			
			<div class="field-label"><?php print $fields['expression_1']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print '$'.number_format($fields['expression_1']->content,2);?></div>
			</div>
			
			<div class="field-label"><?php print $fields['expression_2']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print  number_format($fields['expression_2']->content,2).'%';?></div>
			</div>
			 
		</div> 
	 </fieldset>
	 
	 <fieldset id="node_shipment_full_group_load_info" class="group-load-info field-group-fieldset form-wrapper"> 
		<legend>
			<span class="fieldset-legend">xxxx</span>
		</legend>
		
		<div class="fieldset-wrapper">
			
			<div class="field-label"><?php print $fields['field_shipment_franchise']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print $fields['field_shipment_franchise']->content;?></div>
			</div>	
			
			<div class="field-label"><?php print $fields['field_company']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print $fields['field_company']->content;?></div>
			</div>
			<div class="field-label"><?php 
				 print $fields['field_w_number']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print $fields['field_w_number']->content;?></div>
			</div>
			<div class="field-label"><?php print $fields['field_shipment_broker']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print $fields['field_shipment_broker']->content;?></div>
			</div>
		<div class="field-label"><?php print $fields['php']->label_html; ?> </div> 
			<div class="field-label">
				<div class="field-item even"><?php print $fields['php']->content;?></div>
			</div>
				
		</div> 
	</fieldset>
</article> 
<?php// foreach ($fields as $id => $field): ?>
  <?php// if (!empty($field->separator)): ?>
    <?php //print $field->separator; ?>
  <?php //endif; ?>

  <?php //print $field->wrapper_prefix; ?>
    <?php //print $field->label_html; ?>
    <?php  //print $field->content; ?>
	 
  <?php //print $field->wrapper_suffix; ?>
<?php //endforeach; ?>
