<?php
/**
 * @file
 * Developer hooks for activecampaign module.
 */

/**
 * Alter Hook to modify the activecampaign contact information
 * before it is sent to ActiveCampaign.  See contact info
 * data format in 'activecampaign_contact' type
 * @see http://www.activecampaign.com/api/overview.php
 *
 * @param array $contact
 *   An array of key value pairs of the activecampaign_contact
 *   data type
 * @param StdClass $account
 *   A Drupal User
 */
function hook_activecampaign_contact_alter(&$contact, $account) {
  if ($account->some_param) {
    $contact['phone'] = my_function_get_user_phone($account);
  }
}
