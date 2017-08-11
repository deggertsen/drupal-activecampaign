<?php

/**
 * @file
 * Contains ActiveCampaign User Profile page.
 */

function activecampaign_profile_view($uid) {
  $user = user_load($uid);
  $mail = $user->mail;
  $client = activecampaign_get_client();
  $response = $client->api('contact/list?filters[email]=' . $mail . '&sort=id&sort_direction=ASC&page=1');

  // Contact found, so we display their ActiveCampaign profile.
  if ($response->result_code === 1) {
    foreach ($response as $key => $contact) {
      if (is_int($key) || $key == 0) {
        $activecampaign_link = variable_get('activecampaign_api_url') . '/app/contacts/' . $contact->id;
        $activecampaign_fields = $contact->fields;
        $activecampaign_lists = $contact->lists;
        $activecampaign_tags = $contact->tags;
        $activecampaign_actions = $contact->actions;
        $activecampaign_history = $contact->campaign_history;

        // Link to ActiveCampaign Contact
        $build['activecampaign_link'] = [
          '#type' => 'link',
          '#title' => 'View Contact in ActiveCampaign',
          '#href' => $activecampaign_link,
        ];

        foreach ($activecampaign_lists as $list) {
          $lists[] = $list->listname;
        }

        $build['activecampaign_lists'] = [
          '#theme' => 'item_list',
          '#title' => t('Lists'),
          '#items' => $lists,
        ];

        $build['activecampaign_tags'] = [
          '#theme' => 'item_list',
          '#title' => t('Tags'),
          '#items' => $activecampaign_tags,
        ];

        foreach ($activecampaign_actions as $action) {
          $actions_rows[] = [
            0 => $action->tstamp,
            1 => $action->type,
            2 => $action->text,
          ];
        }

        $build['activecampaign_actions'] = [
          '#theme' => 'table',
          '#prefix' => '<h3>' . t('Recent Actions') . '</h3>',
          '#header' => [t('Date'), t('Type'), t('Action')],
          '#rows' => $actions_rows,
        ];

        return $build;
      }
    }
  }
}