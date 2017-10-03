<?php

/**
 * @file
 * Admin page callbacks for the smooth_scroll module.
 */

/**
 * Menu callback - Configure scroll speed.
 */
function smooth_scroll_admin() {
  $form = array();

  $form['smooth_scroll_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Scroll speed'),
    '#default_value' => config_get('smooth_scroll.settings', 'smooth_scroll_speed'),
    '#description' => t('Scroll animation speed.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for smooth_scroll admin form.
 */
function smooth_scroll_admin_submit($form, &$form_state) {
  config_set('smooth_scroll.settings', 'smooth_scroll_speed', (int) $form_state['values']['smooth_scroll_speed']);
  backdrop_set_message(t('The configuration options have been saved.'));
}
