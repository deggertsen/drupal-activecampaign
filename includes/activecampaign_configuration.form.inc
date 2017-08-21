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

  // ActiveCampaign Tracking Code Settings.
  $form['tracking'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tracking code'),
	'#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Textarea for entering ActiveCampaign tracking code.
  $form['tracking']['activecampaign_tracking_code'] = array(
    '#type' => 'textarea',
    '#title' => 'Tracking Code',
    '#default_value' => variable_get('activecampaign_tracking_code', ''),
    '#required' => FALSE,
    '#description' => t('Your ActiveCampaign tracking code. <strong>Exclude script tags</strong>.'),
    '#attributes' => array('placeholder' => t('Enter ActiveCampaign tracking code.')),
  );

  // Page specific visibility configurations.
  $php_access = user_access('use PHP for tracking visibility');
  $visibility = variable_get('activecampaign_visibility_pages', 0);
  $pages = variable_get('activecampaign_pages', ACTIVECAMPAIGN_PAGES);

  $form['tracking']['page_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  if ($visibility == 2 && !$php_access) {
    $form['tracking']['page_vis_settings'] = array();
    $form['tracking']['page_vis_settings']['activecampaign_visibility_pages'] = array('#type' => 'value', '#value' => 2);
    $form['tracking']['page_vis_settings']['activecampaign_pages'] = array('#type' => 'value', '#value' => $pages);
  }
  else {
    $options = array(
      t('Every page except the listed pages'),
      t('The listed pages only'),
    );
    $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));

    if (module_exists('php') && $php_access) {
      $options[] = t('Pages on which this PHP code returns <code>TRUE</code> (experts only)');
      $title = t('Pages or PHP code');
      $description .= ' ' . t('If the PHP option is chosen, enter PHP code between %php. Note that executing incorrect PHP code can break your Drupal site.', array('%php' => '<?php ?>'));
    }
    else {
      $title = t('Pages');
    }
    $form['tracking']['page_vis_settings']['activecampaign_visibility_pages'] = array(
      '#type' => 'radios',
      '#title' => t('Add tracking to specific pages'),
      '#options' => $options,
      '#default_value' => $visibility,
    );
    $form['tracking']['page_vis_settings']['activecampaign_pages'] = array(
      '#type' => 'textarea',
      '#title' => $title,
      '#title_display' => 'invisible',
      '#default_value' => $pages,
      '#description' => $description,
      '#rows' => 10,
    );
  }

  // Render the role overview.
  $form['tracking']['role_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Roles'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['tracking']['role_vis_settings']['activecampaign_visibility_roles'] = array(
    '#type' => 'radios',
    '#title' => t('Add tracking for specific roles'),
    '#options' => array(
      t('Add to the selected roles only'),
      t('Add to every role except the selected ones'),
    ),
    '#default_value' => variable_get('activecampaign_visibility_roles', 0),
  );

  $role_options = array_map('check_plain', user_roles());
  $form['tracking']['role_vis_settings']['activecampaign_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#default_value' => variable_get('activecampaign_roles', array()),
    '#options' => $role_options,
    '#description' => t('If none of the roles are selected, all users will be tracked. If a user has any of the roles checked, that user will be tracked (or excluded, depending on the setting above).'),
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
