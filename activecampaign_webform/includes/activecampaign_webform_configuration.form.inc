<?php

/**
 * @file
 * Contains configuration form for ActiveCampaign Webform.
 */

function activecampaign_webform_configuration_form($form, &$form_state, $node) {
  $settings = activecampaign_webform_get_settings($node->nid);

  $form['#node'] = $node;

  $form['#submit'] = array('activecampaign_webform_configuration_form_submit');

  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );

  $form['activecampaign'] = array(
    '#type' => 'fieldset',
    '#title' => t('ActiveCampaign integration settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Submit to ActiveCampaign
  $form['activecampaign']['submission'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send form submissions to ActiveCampaign'),
    '#description' => t('Checking this box will integrate this form with ActiveCampaign using the settings below.'),
  );
  if (isset($settings->submission)) {
    $form['activecampaign']['submission']['#default_value'] = $settings->submission;
  }

  // Tags for contacts
  $tag_options = activecampaign_webform_get_tag_options();
  $form['activecampaign']['tags'] = array(
    '#type' => 'select',
    '#title' => t('Tags to add to contact'),
    '#options' => $tag_options,
    '#multiple' => TRUE,
    '#size' => min(12, count($tag_options)),
  );
  if (isset($settings->tags)) {
    $form['activecampaign']['tags']['#default_value'] = $settings->tags;
  }

  // Lists to add contact to.
  $list_options = activecampaign_webform_get_list_options();

  $form['activecampaign']['lists'] = array(
    '#type' => 'select',
    '#title' => t('Lists to add contact to'),
    '#options' => $list_options,
    '#multiple' => TRUE,
    '#size' => min(12, count($list_options)),
  );
  if (isset($settings->lists)) {
    $form['activecampaign']['lists']['#default_value'] = $settings->lists;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#weight' => 10,
  );

  return $form;
}

function activecampaign_webform_configuration_form_submit($form, &$form_state) {
  activecampaign_webform_save_settings($form_state['values']);
}

function activecampaign_webform_get_list_options() {
  $lists = activecampaign_get_lists();
  $options = [];
  foreach ($lists as $list) {
    $options[$list->id] = $list->name;
  }

  return $options;
}

function activecampaign_webform_get_tag_options() {
  $tags= activecampaign_get_tags();
  $options = [];
  foreach ($tags as $tag) {
    $options[$tag->id] = $tag->name;
  }

  return $options;
}