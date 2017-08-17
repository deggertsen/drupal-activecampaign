<?php

/**
 * @file
 * Contains ActiveCampaign Configuration Form
 */

function activecampaign_configuration_form($form, &$form_state) {
  $form['activecampaign_api_url'] = array(
    '#type' => 'textfield',
    '#title' => 'API URL',
    '#default_value' => variable_get('activecampaign_api_url', ''),
    '#required' => TRUE,
    '#description' => t('Your ActiveCampaign account API URL. https://ACCOUNT.api-us1.com'),
	'#attributes' => array('placeholder' => t('Enter ActiveCampaign API url')),
  );
  $form['activecampaign_api_key'] = array(
    '#type' => 'textfield',
    '#title' => 'API Key',
    '#default_value' => variable_get('activecampaign_api_key', ''),
    '#required' => TRUE,
    '#description' => t('Your ActiveCampaign account API Key.'),
	'#attributes' => array('placeholder' => t('Enter ActiveCampaign API key')),
  );

  // Button to test the above credentials.
  $form['ac_newsletter_api_test_connection'] = array(
    '#type' => 'button',
    '#value' => t('Test Connection'),
    '#executes_submit_callback' => TRUE,
    '#submit' => array('activecampaign_api_test_connection_submit'),
  );

  return system_settings_form($form);
}

/**
 * Form test submission handler for activecampaign_configuration_form().
 */
function activecampaign_api_test_connection_submit($form, &$form_state) {
  variable_set('activecampaign_api_url', trim($form_state['values']['activecampaign_api_url']));
  variable_set('activecampaign_api_key', trim($form_state['values']['activecampaign_api_key']));
  // Test the credentials.
  if (activecampaign_test_api_credentials()) {
    drupal_set_message(t('Successfully connected'));
  }
  else {
    drupal_set_message(t('Access denied: Invalid credentials (URL and/or API key).'), 'error');
  }
}
