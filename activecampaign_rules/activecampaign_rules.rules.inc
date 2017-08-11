<?php

/**
 * @file
 * Contains Rules information for ActiveCampaign.
 */

/**
 * Implements hook_rules_action_info().
 */
function activecampaign_rules_rules_action_info() {
  return [
    'activecampaign_add_contact' => [
      'label' => t('Add contact'),
      'group' => t('ActiveCampaign'),
    ],
    'activecampaign_remove_contact' => [
      'label' => t('Remove contact'),
      'group' => t('ActiveCampaign'),
    ],
    'activecampaign_add_contact_to_list' => [
      'label' => t('Add contact to list'),
      'group' => t('ActiveCampaign'),
    ],
    'activecampaign_remove_contact_from_list' => [
      'label' => t('Remove contact from list'),
      'group' => t('ActiveCampaign'),
    ],
    'activecampaign_update_contact_fields' => [
      'label' => t('Update contact fields'),
      'group' => t('ActiveCampaign'),
    ],
    'activecampaign_add_tag_to_contact' => [
      'label' => t('Add tag to contact'),
      'group' => t('ActiveCampaign'),
    ],
    'activecampaign_remove_tag_from_contact' => [
      'label' => t('Remove tag from contact'),
      'group' => t('ActiveCampaign'),
    ],
  ];
}

/**
 * Implements hook_rules_condition_info().
 */
function activecampaign_rules_rules_condition_info() {
  return [
    'activecampaign_contact_has_tag' => [
      'label' => t('Contact has tag'),
      'group' => t('ActiveCampaign'),
    ],
  ];
}

/**
 * Implements hook_rules_event_info().
 */
function activecampaign_rules_rules_event_info() {
  return [
    'activecampaign_contact_updated' => [
      'label' => t('Contact updated'),
      'group' => t('ActiveCampaign'),
    ],
  ];
}