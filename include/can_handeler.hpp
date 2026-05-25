#pragma once
#include "main.hpp"
#include "parameters.hpp"
#include <can_tools.hpp> // ksu-fw-common
#include <car.h>         // can_lib

can_obj_car_h_t kms_can;

canMan inv_can(TEENSY_CAN2, INVERTER_CAN_BAUD_RATE);

void check_messages() {
  if (inv_can.check_controller_message()) {
    can_message msg_in = inv_can.get_controller_message();

    switch (msg_in.id) {
    case CAN_ID_ACU_SHUTDOWN_STATUS:
      unpack_message(&kms_can, CAN_ID_ACU_SHUTDOWN_STATUS, msg_in.buf.val,
                     msg_in.length, 0);

      decode_can_0x258_acu_bms_relay_state(&kms_can, (uint8_t *)&BMS_state);
      decode_can_0x258_acu_imd_relay_state(&kms_can, (uint8_t *)&IMD_state);
      break;

    case CAN_ID_VCU_STATUS:
      unpack_message(&kms_can, CAN_ID_VCU_STATUS, msg_in.buf.val, msg_in.length,
                     0);

      decode_can_0x0c3_VCU_BSPD_OK_HIGH(&kms_can, (uint8_t *)&BSPD_state);
      break;

    case CAN_ID_M167_VOLTAGE_INFO:
      unpack_message(&kms_can, CAN_ID_M167_VOLTAGE_INFO, msg_in.buf.val,
                     msg_in.length, 0);
      break;
    }
  }
}

void send_firmware_status_message() {
  encode_can_0x0ec_dash_on_time_seconds(&kms_can, millis() / 1000);
  encode_can_0x0ec_dash_fw_version(&kms_can, AUTO_VERSION);
  encode_can_0x0ec_dash_project_is_dirty(&kms_can, FW_PROJECT_IS_DIRTY);
  encode_can_0x0ec_dash_project_on_main(&kms_can, FW_PROJECT_IS_MAIN_OR_MASTER);

  can_message out_msg;
  out_msg.id = CAN_ID_DASH_FIRMWARE_VERSION;
  out_msg.length =
      pack_message(&kms_can, CAN_ID_DASH_FIRMWARE_VERSION, &out_msg.buf.val);

  inv_can.send_controller_message(out_msg);
}

void send_button_status_message(bool button_1, bool button_2, bool button_3,
                                bool button_4, bool button_5, bool button_6) {
  encode_can_0x0eb_dash_button1status(&kms_can, button_1);
  encode_can_0x0eb_dash_button2status(&kms_can, button_2);
  encode_can_0x0eb_dash_button3status(&kms_can, button_3);
  encode_can_0x0eb_dash_button4status(&kms_can, button_4);
  encode_can_0x0eb_dash_button5status(&kms_can, button_5);
  encode_can_0x0eb_dash_button6status(&kms_can, button_6);

  can_message out_msg;
  out_msg.id = CAN_ID_DASH_BUTTONS;
  out_msg.length =
      pack_message(&kms_can, CAN_ID_DASH_BUTTONS, &out_msg.buf.val);

  inv_can.send_controller_message(out_msg);
}
