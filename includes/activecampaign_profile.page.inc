<?php

/**
 * @file
 * Contains ActiveCampaign User Profile page.
 */

function activecampaign_profile_view_form($form, &$form_state, $uid) {
  if (!activecampaign_check_settings()) {
    return FALSE;
  }

  $form = array(
    '#prefix' => '<div id="activecampaign-user-widget">',
    '#suffix' => '</div>',
  );
  $account = user_load($uid);
  $activecampaign_id = activecampaign_contact_id($account, FALSE);

  if (!$activecampaign_id) {
    $ac_contact = activecampaign_contact_load_email($account->mail);
    if (!$ac_contact->success) {
      $form['quick_add'] = array(
        '#type' => 'fieldset',
        '#title' => 'Add User to ActiveCampaign',
      );
      $form['quick_add']['add'] = array(
        '#type' => 'submit',
        '#value' => 'Add to ActiveCampaign',
        '#submit' => array('activecampaign_user_form_submit'),
        '#name' => 'add_user',
        '#ajax' => array(
          'wrapper' => 'activecampaign-user-widget',
          'callback' => 'activecampaign_user_form_js',
        ),
      );
    }
    else {
      user_save($account, array($account->field_activecampaign_id[LANGUAGE_NONE][0]['value'] = $ac_contact->id));
      $form_state['rebuild'] = TRUE;
	  return header("Refresh:0");
    }
  }
  else {
    $contact = activecampaign_contact_load($activecampaign_id);
	$available_lists = activecampaign_get_lists();
    $activecampaign_account = activecampaign_account_load();
    $activecampaign_link = 'https://' . $activecampaign_account->account . '/app/contacts/' . $activecampaign_id;
    $activecampaign_fields = $contact->fields;
    $activecampaign_lists = $contact->lists;
    $activecampaign_tags = $contact->tags;
    $activecampaign_actions = $contact->actions;
    $activecampaign_history = $contact->campaign_history;

    $form['quick_add'] = array(
      '#type' => 'fieldset',
      '#title' => 'Contact from ActiveCampaign',
    );
    $form['quick_add']['user_id'] = array(
      '#markup' => t('User is ActiveCampaign Contact# !contact_num', array('!contact_num' => $activecampaign_id)),
      '#prefix' => '<div>',
      '#suffix' => '</div>',
    );

    $form['quick_add']['user_link'] = array(
      '#markup' => l(
        t('View User in ActiveCampaign'), $activecampaign_link, array(
        'query' => array('view' => 'edit', 'ID' => $activecampaign_id),
        'attributes' => array('target' => '_blank'),
        )
      ),
      '#prefix' => '<div>',
      '#suffix' => '</div>',
    );

    if ($activecampaign_lists) {
      foreach ($activecampaign_lists as $list) {
        $lists[] = array(
          0 => $list->listname,
          1 => $list->sdate,
        );
      }
      $form['activecampaign_lists'] = array(
        '#type' => 'fieldset',
        '#title' => 'Current ActiveCampaign Lists',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $form['activecampaign_lists']['group_table'] = array(
        '#theme' => 'table',
        '#header' => array(t('List'), t('Date Added')),
        '#rows' => $lists,
      );
    }

    if ($activecampaign_tags) {
      $form['activecampaign_tags'] = array(
        '#type' => 'fieldset',
        '#title' => 'ActiveCampaign Tags',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $form['activecampaign_tags']['tags_list'] = array(
        '#theme' => 'item_list',
        '#items' => $activecampaign_tags,
      );
    }

    if ($activecampaign_actions) {
      foreach ($activecampaign_actions as $action) {
        $actions_rows[] = array(
          0 => $action->tstamp,
          1 => $action->type,
          2 => $action->text,
        );
      }

      $form['activecampaign_actions'] = array(
        '#theme' => 'table',
        '#prefix' => '<h3>' . t('Recent Actions') . '</h3>',
        '#header' => [t('Date'), t('Type'), t('Action')],
        '#rows' => $actions_rows,
      );
    }
  }

  $form_state['user'] = $account;

  return $form;

}

/**
 * User Form JS
 */
function activecampaign_user_form_js($form, $form_state) {
  return $form;
}

/**
 * User Form Submit Handler
 */
function activecampaign_user_form_submit($form, &$form_state) {
  $action = $form_state['triggering_element']['#name'];
  if ($action === 'add_user') {
    $activecampaign_id = activecampaign_user_to_contact($form_state['user']);
  }
  else {
    $activecampaign_id = activecampaign_contact_id($form_state['user']);
  }
  $form_state['rebuild'] = TRUE;
}
