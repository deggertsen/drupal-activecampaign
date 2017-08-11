<?php

/**
 * @file
 * Contains ActiveCampaign Configuration Form
 */

function activecampaign_configuration_form($form, &$form_state) {
  $form['activecampaign_api_url'] = [
    '#type' => 'textfield',
    '#title' => 'API URL',
    '#default_value' => variable_get('activecampaign_api_url', ''),
    '#required' => TRUE,
    '#description' => t('Your ActiveCampaign account API URL. https://ACCOUNT.api-us1.com'),
  ];
  $form['activecampaign_api_key'] = [
    '#type' => 'textfield',
    '#title' => 'API Key',
    '#default_value' => variable_get('activecampaign_api_key', ''),
    '#required' => TRUE,
    '#description' => t('Your ActiveCampaign account API Key.'),
  ];

  return system_settings_form($form);
}