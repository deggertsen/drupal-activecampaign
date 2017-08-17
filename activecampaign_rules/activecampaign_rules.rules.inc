<?php

/**
 * @file
 * Contains Rules information for ActiveCampaign.
 */  

/**
 * Implements hook_rules_event_info().
 */
function activecampaign_rules_rules_event_info() {
  $items = array(
    'activecampaign_contact_updated' => array(
      'label' => t('Contact updated'),
      'group' => t('ActiveCampaign'),
    ),
	'activecampaign_contact_add_event' => array(
      'label' => t('After creating a new ActiveCampaign contact'),
      'group' => t('ActiveCampaign'),
      'variables' => array(
        'user' => array('type' => 'user', 'label' => 'Drupal User'),
      ),
    ),
    'activecampaign_contact_sync_event' => array(
      'label' => t('After updating an ActiveCampaign contact'),
      'group' => t('ActiveCampaign'),
      'variables' => array(
        'user' => array('type' => 'user', 'label' => 'Drupal User'),
      ),
    ),
  );
  
  return $items;
}

/**
 * Implements hook_rules_condition_info().
 */
function activecampaign_rules_rules_condition_info() {
  return array(
    'activecampaign_contact_has_tags' => array(
      'label' => t('ActiveCampaign Contact has tag(s)'),
      'parameter' => array(
        'account' => array(
		  'type' => 'user',
		  'label' => t('User'),
		  'description' => t('The drupal user connected to the ActiveCampaign account.'),
		),
        'tags' => array(
          'type' => 'list<integer>',
          'label' => t('Tags'),
          'options list' => 'activecampaign_get_tags_filtered',
        ),
        'operation' => array(
          'type' => 'text',
          'label' => t('Match tags'),
          'options list' => 'activecampaign_rules_condition_operations',
          'restriction' => 'input',
          'optional' => TRUE,
          'default value' => 'AND',
          'description' => t('If matching against all selected tags, the contact must have <em>all</em> the tags selected.'),
        ),
      ),
      'group' => t('ActiveCampaign'),
      'base' => 'rules_condition_activecampaign_contact_has_tag',
    ),
  );
}

/**
 * Options list callback for the operation parameter of condition contact has tag.
 */
function activecampaign_rules_condition_operations() {
  return array(
    'AND' => t('all'),
    'OR' => t('any'),
  );
}

/**
 * Condition to check whether contact has particular tags
 */
function rules_condition_activecampaign_contact_has_tag($account, $tags, $operation = 'AND') {
  if (empty($account->field_activecampaign_id[LANGUAGE_NONE][0]['value'])) {
    return FALSE;
  }
  $contact = activecampaign_contact_load($account->field_activecampaign_id[LANGUAGE_NONE][0]['value']);
  $contacttags = $contact->tags;
  watchdog('activecampaign','The following:'.$contacttagsraw.', '.$contacttags.', '.$tags);

  switch ($operation) {
    case 'OR':
      foreach ($tags as $tag) {
        if (in_array($tag, $contacttags)) {
          return TRUE;
        }
      }
      return FALSE;

    case 'AND':
      foreach ($tags as $tag) {
        if (!in_array($tag, $contacttags)) {
          return FALSE;
        }
      }
      return TRUE;
  }
}

/**
 * Implements hook_rules_action_info().
 */
function activecampaign_rules_rules_action_info() {
  $actions = array();

  $actions['activecampaign_add_contact'] = array(
    'label' => t('Add a Contact by User'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('The Drupal User'),
      ),
    ),
    'group' => t('activecampaign'),
    'callbacks' => array(
      'execute' => 'activecampaign_rules_add_contact',
    ),
  );

  $actions['activecampaign_rules_delete_contact'] = array(
    'label' => t('Delete a Contact'),
    'parameter' => array(
      'email' => array(
        'type' => 'text',
        'label' => t('Email address of a Contact'),
		'description' => t('Email address must be of an existing activecampaign Contact'),
      ),
    ),
    'group' => t('activecampaign'),
    'callbacks' => array(
      'execute' => 'activecampaign_rules_delete_contact',
    ),
  );

  $actions['activecampaign_add_contact_list'] = array(
    'label' => t('Add a Contact to List(s)'),
    'parameter' => array(
      'email' => array(
        'type' => 'text',
        'label' => t('Email address of a Contact'),
		'description' => t('Email address must be of an existing activecampaign Contact'),
      ),
      'activecampaign_list_id' => array(
        'type' => 'list<integer>',
        'label' => t('The ActiveCampaign List(s)'),
        'options list' => 'activecampaign_get_lists_filtered',
      ),
    ),
    'group' => t('activecampaign'),
    'callbacks' => array(
      'execute' => 'activecampaign_rules_add_to_list',
    ),
  );

  $actions['activecampaign_add_contact_tag'] = array(
    'label' => t('Add Tag(s) to a Contact'),
    'parameter' => array(
      'email' => array(
        'type' => 'text',
        'label' => t('Email address of a Contact'),
		'description' => t('Email address must be of an existing activecampaign Contact'),
      ),
      'activecampaign_group_id' => array(
        'type' => 'list<integer>',
        'label' => t('The ActiveCampaign Tag(s)'),
        'options list' => 'activecampaign_get_tags_filtered',
      ),
    ),
    'group' => t('activecampaign'),
    'callbacks' => array(
      'execute' => 'activecampaign_rules_add_to_tag',
    ),
  );
/* TO DO
  $actions['activecampaign_remove_contact_list'] = array(
    'label' => t('Remove a Contact from a List'),
    'parameter' => array(
      'email' => array(
        'type' => 'text',
        'label' => t('Email address of a Contact'),
		'description' => t('Email address must be of an existing activecampaign Contact'),
      ),
      'activecampaign_group_id' => array(
        'type' => 'integer',
        'label' => t('The activecampaign Group'),
        'options list' => 'activecampaign_groups_options',
      ),
    ),
    'group' => t('activecampaign'),
    'callbacks' => array(
      'execute' => 'activecampaign_rules_remove_from_group',
    ),
  ); */

  return $actions;
}

/**
 * Rules action: Add a contact
 */
function activecampaign_rules_add_contact($account) {
  activecampaign_contact_id($account);
}

/**
 * Rules action: Delete a contact
 */
function activecampaign_rules_delete_contact($email) {
  $contact = activecampaign_contact_load_email($email);
  if ($contact) {
    // Delete contact in activecampaign if one exists.
    activecampaign_contact_delete($contact->id);
  }
}

/**
 * Rules action: adds a contact to a list
 */
function activecampaign_rules_add_to_list($email, $lists) {
  $contact['email'] = $email;
  foreach ($lists as $listid => $list) {
    $contact['p['.$listid.']'] = 'p['.$listid.']';
  }
  activecampaign_contact_sync($contact);
}

/**
 * Rules action: adds tag(s) to a contact
 */
function activecampaign_rules_add_to_tag($email, $tags) {
  $contact['email'] = $email;
  $commaList = implode(',', $tags);
  $contact['tags'] = $commaList;
  activecampaign_contact_sync($contact);
}

/**
 * Rules action: remove a contact from a list
 *
function activecampaign_rules_remove_from_list($account, $group_id) {
  activecampaign_user_op('remove', 'group', activecampaign_contact_id($account), $group_id);
}
*/

