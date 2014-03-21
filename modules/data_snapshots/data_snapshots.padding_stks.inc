<?php

function _data_snapshots_pad_snapshots($dsmn, $ptks, &$stks) {
  $PAD_VALUE = NULL;
  $frequency = _data_snapshots_get_data_source_frequency($dsmn);
  $callback = '_data_snapshots_pad_' . $frequency;
  $callback($ptks, $stks, $PAD_VALUE);
}

function _data_snapshots_pad_Custom($ptks, &$stks, $PAD_VALUE) {
  
}

function _data_snapshots_pad_Monthly($ptks, &$stks, $PAD_VALUE) {
  $MONTH_LENGTH = 12;
  $EXPECTED_MONTH_VALUES = array('01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12');

  for ($i = 0; $i < count($ptks); $i++) {
    if (count($stks[$ptks[$i]]) == $MONTH_LENGTH) {
      continue;
    }

    // pad the front
    $front_value = $stks[$ptks[$i]][0];
    if ($front_value != $EXPECTED_MONTH_VALUES[0]) {
      $front_value_index = 0;
      for ($j = 1; $j < count($EXPECTED_MONTH_VALUES); $j++) {
        if ($EXPECTED_MONTH_VALUES[$j] == $front_value) {
          $front_value_index = $j;
          break;
        }
      }

      for ($j = 0; $j < $front_value_index; $j++) {
        array_unshift($stks[$ptks[$i]], $PAD_VALUE);
      }
    }

    if (count($stks[$ptks[$i]]) == $MONTH_LENGTH) {
      continue;
    }

    //pad the back
    while (count($stks[$ptks[$i]]) != $MONTH_LENGTH) {
      array_push($stks[$ptks[$i]], $PAD_VALUE);
    }
  }
}

function _data_snapshots_pad_Weekly($ptks, &$stks, $PAD_VALUE) {}

function _data_snapshots_pad_Annual($ptks, &$stks, $PAD_VALUE) {
  // nothing needs to happen here. There will never be stks.
  // This functions just created to avoid the need for additional logic
}