<?php

/**
 * @file
 * Admin page callbacks for the smooth_scrolling module.
 */

/**
 * Form to config scrolling block settings.
 */
function smooth_scrolling_admin() {
  $form = array();

  $form['smooth_scrolling'] = array(
    '#type' => 'textarea',
    '#title' => t('Smooth scrolling settings'),
    '#default_value' => _smooth_scrolling_admin_convert_array_to_text(variable_get('smooth_scrolling', array())),
    '#description' => t('Smooth scrolling configurations, one per line in the formation <code>[Scroll speed]|[extra settings]</code>.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

function smooth_scrolling_admin_validate($form, &$form_state) {
  $array = _smooth_scrolling_admin_convert_text_to_array($form_state['values']['smooth_scrolling']);
  $string = _smooth_scrolling_admin_convert_array_to_text($array);

  // Compare that scrolling block settings string to array conversion is
  // idempotent. New line characters \n and \r get make comparison difficult.
  if (str_replace(array("\n", "\r"), '', $string) != str_replace(array("\n", "\r"), '', $form_state['values']['smooth_scrolling'])) {
    form_set_error('smooth_scrolling', t('Each line must of the format: <code>selector|setting_key=setting_value,setting_key=setting_value,...</code>'));
  }
}

/**
 * Submit handler for smooth_scrolling admin form.
 *
 * Saves smooth_scrolling variable.
 */
function smooth_scrolling_admin_submit($form, &$form_state) {
  variable_set('smooth_scrolling', _smooth_scrolling_admin_convert_text_to_array($form_state['values']['smooth_scrolling']));
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Converts a string representation of scrolling block settings to an array.
 *
 * @param $smooth_scrolling
 *   A string representation of scrolling block settings.
 *
 * @return
 *   An array representation of scrolling block settings.
 */
function _smooth_scrolling_admin_convert_text_to_array($smooth_scrolling) {
  $smooth_scrolling = preg_split("/(\r\n|\n)/", $smooth_scrolling, NULL, PREG_SPLIT_NO_EMPTY);
  $output = array();

  foreach ($smooth_scrolling as $smooth_scrolling) {
    $settings = explode('|', $smooth_scrolling);
    $output[$settings[0]] = array();
    if (isset($settings[1])) {
      preg_match_all("/([^=|,]*)=([^=|,]*),?/", $settings[1], $matches, PREG_SET_ORDER);
      foreach ($matches as $match) {
        $output[$settings[0]][$match[1]] = $match[2];
      }
    }
  }
  return $output;
}

/**
 * Converts an array representation of scrolling block settings to a string.
 *
 * @param $smooth_scrolling
 *   An array representation of scrolling block settings.
 *
 * @return
 *   A string representation of scrolling block settings.
 */
function _smooth_scrolling_admin_convert_array_to_text($smooth_scrolling) {
  $output = array();
  foreach ($smooth_scrolling as $selector => $settings) {
    $output_line = $selector;
    if (count($settings)) {
      $settings_line = array();
      foreach ($settings as $key => $value) {
        $settings_line[] = $key . '=' . $value;
      }
      $output_line .= '|' . implode(',', $settings_line);
    }
    $output[] = $output_line;
  }
  return implode("\n", $output);
}
