<?php

/**
 * @file
 * Contains ActiveCampaign Field Configuration form.
 */

function activecampaign_fields_form($form, &$form_state) {
  // Default fields.
  $form['activecampaign_default_list'] = array(
    '#type' => 'select',
    '#title' => t('Default ActiveCampaign List'),
    '#options' => activecampaign_list_options(),
    '#default_value' => variable_get('activecampaign_default_list', 'activecampaign_list_not_set'),
    '#description' => t('The default list you would like to add new ActiveCampaign contacts to.'),
  );
  $form['activecampaign_email'] = array(
    '#type' => 'select',
    '#title' => t('Email'),
    '#options' => activecampaign_fields_options(),
    '#default_value' => variable_get('activecampaign_email', 'mail'),
  );
  $form['activecampaign_first_name'] = array(
    '#type' => 'select',
    '#title' => t('First Name'),
    '#options' => activecampaign_fields_options(),
    '#default_value' => variable_get('activecampaign_first_name', ''),
  );
  $form['activecampaign_last_name'] = array(
    '#type' => 'select',
    '#title' => t('Last Name'),
    '#options' => activecampaign_fields_options(),
    '#default_value' => variable_get('activecampaign_last_name', ''),
  );
  $form['activecampaign_phone'] = array(
    '#type' => 'select',
    '#title' => t('Phone'),
    '#options' => activecampaign_fields_options(),
    '#default_value' => variable_get('activecampaign_phone', ''),
  );
  $form['activecampaign_orgname'] = array(
    '#type' => 'select',
    '#title' => t('Organization Name'),
    '#options' => activecampaign_fields_options(),
    '#default_value' => variable_get('activecampaign_orgname', ''),
  );
  $fields = activecampaign_get_fields();
  foreach ($fields as $field) {
    if (is_object($field)) {
      $form['activecampaign_'.$field->id] = array(
        '#type' => 'select',
        '#title' => $field->title,
        '#options' => activecampaign_fields_options(),
        '#default_value' => variable_get('activecampaign_'.$field->id, ''),
      );
    }
  }
  $form['#submit'][] = 'activecampaign_fields_form_submit';

  return system_settings_form($form);
}

/**
 * Form list options for activecampaign_configuration_form().
 */
function activecampaign_list_options() {
  if (activecampaign_test_api_credentials()) {
    $activecampaign_lists = activecampaign_get_lists();
    foreach ($activecampaign_lists as $list) {
      $options[$list->id] = $list->name;
    }
  }
  else {
    $options = array(
      'activecampaign_list_not_set' => t('Please run a successful test on your api credentials first.'),
    );
  }

  return $options;
}

/**
 * Form field options for activecampaign_configuration_form().
 */
function activecampaign_fields_options() {
  $options = array(
    'activecampaign_not_used' => t('NOT USED'),
	'name' => t('Username'),
    'mail' => t('Email'),
    'uid' => t('User ID'),
    'created' => t('Created'),
    'access' => t('Last Access'),
    'status' => t('Status'),
   );
  $fields = field_info_instances('user', 'user');

  foreach ($fields as $field) {
    $option = array($field['field_name'] => $field['label']);
    $options = array_merge($options, $option);
  }

  return $options;
}

/**
 * Form submission handler for activecampaign_fields_form().
 */
function activecampaign_fields_form_submit($form, &$form_state) {
  drupal_set_message(t('The form has been submitted.'));
  variable_set('activecampaign_field_mapping', $form_state['input']);
  print_r($form_state['submitted']);
}
