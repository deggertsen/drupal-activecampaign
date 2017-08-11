<?php

/**
 * @file
 * Contains ActiveCampaign Field Configuration form.
 */

function activecampaign_fields_form($form, &$form_state) {
  // Default fields.
  $form['activecampaign_email'] = [
    '#type' => 'select',
    '#title' => t('Email'),
    '#options' => activecampaign_fields_options(),
    '#default_value' => 'mail',
  ];
  $form['activecampaign_first_name'] = [
    '#type' => 'select',
    '#title' => t('First Name'),
    '#options' => activecampaign_fields_options(),
  ];
  $form['activecampaign_last_name'] = [
    '#type' => 'select',
    '#title' => t('Last Name'),
    '#options' => activecampaign_fields_options(),
  ];

  return $form;
}

function activecampaign_fields_options() {
  $options = [
    'activecampaign_not_used' => t('[NOT USED]'),
	'name' => t('Username'),
    'mail' => t('Email'),
    'uid' => t('User ID'),
    'created' => t('Created'),
    'access' => t('Last Access'),
    'status' => t('Status'),
   ];
  $fields = field_info_instances('user', 'user');

  foreach ($fields as $field) {
    $option = array($field['field_name'] => $field['label']);
    $options = array_merge($options, $option);
  }

  return $options;
}