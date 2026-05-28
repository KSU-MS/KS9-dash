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

      bool apps_fault, bse_fault, ss_fault;
      decode_can_0x0c3_VCU_ACCEL_IMPLAUSIBLE(&kms_can, (uint8_t *)&apps_fault);
      decode_can_0x0c3_VCU_BRAKE_IMPLAUSIBLE(&kms_can, (uint8_t *)&bse_fault);
      decode_can_0x0c3_VCU_ACCEL_BRAKE_IMPLAUSIBLE(&kms_can,
                                                   (uint8_t *)&ss_fault);

      if (apps_fault)
        lv_label_set_text_fmt(joe_dash.Screenshot_fault, "SS");
      else
        lv_label_set_text_fmt(joe_dash.Screenshot_fault, "");

      if (bse_fault)
        lv_label_set_text_fmt(joe_dash.BSE_fault, "BSE");
      else
        lv_label_set_text_fmt(joe_dash.BSE_fault, "");

      if (ss_fault)
        lv_label_set_text_fmt(joe_dash.APPS_fault, "APPS");
      else
        lv_label_set_text_fmt(joe_dash.APPS_fault, "");

      uint8_t max_torque;
      decode_can_0x0c3_VCU_MAX_TORQUE(&kms_can, &max_torque);

      lv_label_set_text_fmt(joe_dash.Torque_limit_nm, "%iNm", max_torque);

      uint8_t vcu_state;
      decode_can_0x0c3_VCU_STATEMACHINE_STATE(&kms_can, &vcu_state);

      switch (vcu_state) {
      case 0:
        lv_label_set_text(joe_dash.VCU_state, "STARTUP");
        break;
      case 1:
        lv_label_set_text(joe_dash.VCU_state, "TS DISABLED");
        break;
      case 2:
        lv_label_set_text(joe_dash.VCU_state, "TS ENERGIZED");
        break;
      case 3:
        lv_label_set_text(joe_dash.VCU_state, "TS ENABLED");
        break;
      case 4:
        lv_label_set_text(joe_dash.VCU_state, "READY TO RIP");
        break;
      case 5:
        lv_label_set_text(joe_dash.VCU_state, "LAUNCH WAIT");
        break;
      case 6:
        lv_label_set_text(joe_dash.VCU_state, "LAUNCH");
        break;
      default:
        lv_label_set_text(joe_dash.VCU_state, "UNKNOWN");
        break;
      }
      break;

    case CAN_ID_M167_VOLTAGE_INFO:
      unpack_message(&kms_can, CAN_ID_M167_VOLTAGE_INFO, msg_in.buf.val,
                     msg_in.length, 0);
      double ts_voltage_double;

      decode_can_0x0a7_INV_DC_Bus_Voltage(&kms_can, &ts_voltage_double);

      lv_label_set_text_fmt(joe_dash.TS_voltage, "%iv", (int)ts_voltage_double);
      break;

    case CAN_ID_M160_TEMPERATURE_SET_1:
      unpack_message(&kms_can, CAN_ID_M160_TEMPERATURE_SET_1, msg_in.buf.val,
                     msg_in.length, 0);

      uint8_t module_a, module_b, module_c;

      decode_can_0x0a0_INV_Module_A_Temp(&kms_can, (double *)&module_a);
      decode_can_0x0a0_INV_Module_B_Temp(&kms_can, (double *)&module_b);
      decode_can_0x0a0_INV_Module_C_Temp(&kms_can, (double *)&module_c);

      lv_label_set_text_fmt(joe_dash.Inverter_temps_c, "%i/%i/%i", module_a,
                            module_b, module_c);
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
