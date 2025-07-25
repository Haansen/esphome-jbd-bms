#pragma once

#include "esphome/core/component.h"
#include "esphome/components/ble_client/ble_client.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/select/select.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"

#ifdef USE_ESP32

#include <esp_gattc_api.h>

namespace esphome {
namespace jbd_bms_ble {

namespace espbt = esphome::esp32_ble_tracker;

class JbdBmsBle : public esphome::ble_client::BLEClientNode, public PollingComponent {
 public:
  void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                           esp_ble_gattc_cb_param_t *param) override;
  void dump_config() override;
  void update() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_balancing_binary_sensor(binary_sensor::BinarySensor *balancing_binary_sensor) {
    balancing_binary_sensor_ = balancing_binary_sensor;
  }
  void set_charging_binary_sensor(binary_sensor::BinarySensor *charging_binary_sensor) {
    charging_binary_sensor_ = charging_binary_sensor;
  }
  void set_discharging_binary_sensor(binary_sensor::BinarySensor *discharging_binary_sensor) {
    discharging_binary_sensor_ = discharging_binary_sensor;
  }
  void set_online_status_binary_sensor(binary_sensor::BinarySensor *online_status_binary_sensor) {
    online_status_binary_sensor_ = online_status_binary_sensor;
  }

  void set_read_eeprom_register_select(select::Select *read_eeprom_register_select) {
    read_eeprom_register_select_ = read_eeprom_register_select;
  }

  void set_state_of_charge_sensor(sensor::Sensor *state_of_charge_sensor) {
    state_of_charge_sensor_ = state_of_charge_sensor;
  }
  void set_total_voltage_sensor(sensor::Sensor *total_voltage_sensor) { total_voltage_sensor_ = total_voltage_sensor; }
  void set_current_sensor(sensor::Sensor *current_sensor) { current_sensor_ = current_sensor; }
  void set_power_sensor(sensor::Sensor *power_sensor) { power_sensor_ = power_sensor; }
  void set_charging_power_sensor(sensor::Sensor *charging_power_sensor) {
    charging_power_sensor_ = charging_power_sensor;
  }
  void set_discharging_power_sensor(sensor::Sensor *discharging_power_sensor) {
    discharging_power_sensor_ = discharging_power_sensor;
  }
  void set_nominal_capacity_sensor(sensor::Sensor *nominal_capacity_sensor) {
    nominal_capacity_sensor_ = nominal_capacity_sensor;
  }
  void set_charging_cycles_sensor(sensor::Sensor *charging_cycles_sensor) {
    charging_cycles_sensor_ = charging_cycles_sensor;
  }
  void set_capacity_remaining_sensor(sensor::Sensor *capacity_remaining_sensor) {
    capacity_remaining_sensor_ = capacity_remaining_sensor;
  }
  void set_min_cell_voltage_sensor(sensor::Sensor *min_cell_voltage_sensor) {
    min_cell_voltage_sensor_ = min_cell_voltage_sensor;
  }
  void set_max_cell_voltage_sensor(sensor::Sensor *max_cell_voltage_sensor) {
    max_cell_voltage_sensor_ = max_cell_voltage_sensor;
  }
  void set_min_voltage_cell_sensor(sensor::Sensor *min_voltage_cell_sensor) {
    min_voltage_cell_sensor_ = min_voltage_cell_sensor;
  }
  void set_max_voltage_cell_sensor(sensor::Sensor *max_voltage_cell_sensor) {
    max_voltage_cell_sensor_ = max_voltage_cell_sensor;
  }
  void set_delta_cell_voltage_sensor(sensor::Sensor *delta_cell_voltage_sensor) {
    delta_cell_voltage_sensor_ = delta_cell_voltage_sensor;
  }
  void set_average_cell_voltage_sensor(sensor::Sensor *average_cell_voltage_sensor) {
    average_cell_voltage_sensor_ = average_cell_voltage_sensor;
  }
  void set_operation_status_bitmask_sensor(sensor::Sensor *operation_status_bitmask_sensor) {
    operation_status_bitmask_sensor_ = operation_status_bitmask_sensor;
  }
  void set_errors_bitmask_sensor(sensor::Sensor *errors_bitmask_sensor) {
    errors_bitmask_sensor_ = errors_bitmask_sensor;
  }
  void set_balancer_status_bitmask_sensor(sensor::Sensor *balancer_status_bitmask_sensor) {
    balancer_status_bitmask_sensor_ = balancer_status_bitmask_sensor;
  }
  void set_battery_strings_sensor(sensor::Sensor *battery_strings_sensor) {
    battery_strings_sensor_ = battery_strings_sensor;
  }
  void set_temperature_sensors_sensor(sensor::Sensor *temperature_sensors_sensor) {
    temperature_sensors_sensor_ = temperature_sensors_sensor;
  }
  void set_software_version_sensor(sensor::Sensor *software_version_sensor) {
    software_version_sensor_ = software_version_sensor;
  }
  void set_short_circuit_error_count_sensor(sensor::Sensor *short_circuit_error_count_sensor) {
    short_circuit_error_count_sensor_ = short_circuit_error_count_sensor;
  }
  void set_charge_overcurrent_error_count_sensor(sensor::Sensor *charge_overcurrent_error_count_sensor) {
    charge_overcurrent_error_count_sensor_ = charge_overcurrent_error_count_sensor;
  }
  void set_discharge_overcurrent_error_count_sensor(sensor::Sensor *discharge_overcurrent_error_count_sensor) {
    discharge_overcurrent_error_count_sensor_ = discharge_overcurrent_error_count_sensor;
  }
  void set_cell_overvoltage_error_count_sensor(sensor::Sensor *cell_overvoltage_error_count_sensor) {
    cell_overvoltage_error_count_sensor_ = cell_overvoltage_error_count_sensor;
  }
  void set_cell_undervoltage_error_count_sensor(sensor::Sensor *cell_undervoltage_error_count_sensor) {
    cell_undervoltage_error_count_sensor_ = cell_undervoltage_error_count_sensor;
  }
  void set_charge_overtemperature_error_count_sensor(sensor::Sensor *charge_overtemperature_error_count_sensor) {
    charge_overtemperature_error_count_sensor_ = charge_overtemperature_error_count_sensor;
  }
  void set_charge_undertemperature_error_count_sensor(sensor::Sensor *charge_undertemperature_error_count_sensor) {
    charge_undertemperature_error_count_sensor_ = charge_undertemperature_error_count_sensor;
  }
  void set_discharge_overtemperature_error_count_sensor(sensor::Sensor *discharge_overtemperature_error_count_sensor) {
    discharge_overtemperature_error_count_sensor_ = discharge_overtemperature_error_count_sensor;
  }
  void set_discharge_undertemperature_error_count_sensor(
      sensor::Sensor *discharge_undertemperature_error_count_sensor) {
    discharge_undertemperature_error_count_sensor_ = discharge_undertemperature_error_count_sensor;
  }
  void set_battery_overvoltage_error_count_sensor(sensor::Sensor *battery_overvoltage_error_count_sensor) {
    battery_overvoltage_error_count_sensor_ = battery_overvoltage_error_count_sensor;
  }
  void set_battery_undervoltage_error_count_sensor(sensor::Sensor *battery_undervoltage_error_count_sensor) {
    battery_undervoltage_error_count_sensor_ = battery_undervoltage_error_count_sensor;
  }
  void set_cell_voltage_sensor(uint8_t cell, sensor::Sensor *cell_voltage_sensor) {
    this->cells_[cell].cell_voltage_sensor_ = cell_voltage_sensor;
  }
  void set_temperature_sensor(uint8_t temperature, sensor::Sensor *temperature_sensor) {
    this->temperatures_[temperature].temperature_sensor_ = temperature_sensor;
  }

  void set_charging_switch(switch_::Switch *charging_switch) { charging_switch_ = charging_switch; }
  void set_discharging_switch(switch_::Switch *discharging_switch) { discharging_switch_ = discharging_switch; }
  void set_balancer_switch(switch_::Switch *balancer_switch) { balancer_switch_ = balancer_switch; }

  void set_operation_status_text_sensor(text_sensor::TextSensor *operation_status_text_sensor) {
    operation_status_text_sensor_ = operation_status_text_sensor;
  }
  void set_errors_text_sensor(text_sensor::TextSensor *errors_text_sensor) { errors_text_sensor_ = errors_text_sensor; }
  void set_device_model_text_sensor(text_sensor::TextSensor *device_model_text_sensor) {
    device_model_text_sensor_ = device_model_text_sensor;
  }
  void set_password(const std::string &password) {
    password_ = password;
    enable_authentication_ = !password.empty();
  }
  void set_authentication_timeout(uint32_t timeout_ms) { auth_timeout_ms_ = timeout_ms; }

  bool send_command(uint8_t action, uint8_t function);
  bool write_register(uint8_t address, uint16_t value);
  bool change_mosfet_status(uint8_t address, uint8_t bitmask, bool state);
  void on_jbd_bms_data(const uint8_t &function, const std::vector<uint8_t> &data);
  void assemble(const uint8_t *data, uint16_t length);

 protected:
  binary_sensor::BinarySensor *balancing_binary_sensor_;
  binary_sensor::BinarySensor *charging_binary_sensor_;
  binary_sensor::BinarySensor *discharging_binary_sensor_;
  binary_sensor::BinarySensor *online_status_binary_sensor_;

  select::Select *read_eeprom_register_select_;

  sensor::Sensor *state_of_charge_sensor_;
  sensor::Sensor *total_voltage_sensor_;
  sensor::Sensor *current_sensor_;
  sensor::Sensor *power_sensor_;
  sensor::Sensor *charging_power_sensor_;
  sensor::Sensor *discharging_power_sensor_;
  sensor::Sensor *nominal_capacity_sensor_;
  sensor::Sensor *charging_cycles_sensor_;
  sensor::Sensor *capacity_remaining_sensor_;
  sensor::Sensor *min_cell_voltage_sensor_;
  sensor::Sensor *max_cell_voltage_sensor_;
  sensor::Sensor *min_voltage_cell_sensor_;
  sensor::Sensor *max_voltage_cell_sensor_;
  sensor::Sensor *delta_cell_voltage_sensor_;
  sensor::Sensor *average_cell_voltage_sensor_;
  sensor::Sensor *operation_status_bitmask_sensor_;
  sensor::Sensor *errors_bitmask_sensor_;
  sensor::Sensor *balancer_status_bitmask_sensor_;
  sensor::Sensor *battery_strings_sensor_;
  sensor::Sensor *temperature_sensors_sensor_;
  sensor::Sensor *software_version_sensor_;
  sensor::Sensor *short_circuit_error_count_sensor_;
  sensor::Sensor *charge_overcurrent_error_count_sensor_;
  sensor::Sensor *discharge_overcurrent_error_count_sensor_;
  sensor::Sensor *cell_overvoltage_error_count_sensor_;
  sensor::Sensor *cell_undervoltage_error_count_sensor_;
  sensor::Sensor *charge_overtemperature_error_count_sensor_;
  sensor::Sensor *charge_undertemperature_error_count_sensor_;
  sensor::Sensor *discharge_overtemperature_error_count_sensor_;
  sensor::Sensor *discharge_undertemperature_error_count_sensor_;
  sensor::Sensor *battery_overvoltage_error_count_sensor_;
  sensor::Sensor *battery_undervoltage_error_count_sensor_;

  switch_::Switch *charging_switch_;
  switch_::Switch *discharging_switch_;
  switch_::Switch *balancer_switch_;

  text_sensor::TextSensor *operation_status_text_sensor_;
  text_sensor::TextSensor *errors_text_sensor_;
  text_sensor::TextSensor *device_model_text_sensor_;

  struct Cell {
    sensor::Sensor *cell_voltage_sensor_{nullptr};
  } cells_[32];

  struct Temperature {
    sensor::Sensor *temperature_sensor_{nullptr};
  } temperatures_[6];

  // @TODO:
  //
  // Cycle life
  // Production date
  // Balance status bitmask (32 Bits)
  // Protection status bitmask (16 Bits)
  // Version

  std::vector<uint8_t> frame_buffer_;
  std::string device_model_{""};
  uint16_t char_notify_handle_;
  uint16_t char_command_handle_;
  uint8_t no_response_count_{0};
  uint8_t mosfet_status_{255};

  void on_cell_info_data_(const std::vector<uint8_t> &data);
  void on_error_counts_data_(const std::vector<uint8_t> &data);
  void on_hardware_info_data_(const std::vector<uint8_t> &data);
  void on_hardware_version_data_(const std::vector<uint8_t> &data);
  void publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_state_(switch_::Switch *obj, const bool &state);
  void publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state);
  void publish_device_unavailable_();
  void reset_online_status_tracker_();
  void track_online_status_();
  std::string error_bits_to_string_(uint16_t bitmask);

  uint16_t chksum_(const uint8_t data[], const uint16_t len) {
    uint16_t checksum = 0x00;
    for (uint16_t i = 0; i < len; i++) {
      checksum = checksum - data[i];
    }
    return checksum;
  }

  uint8_t auth_chksum_(const uint8_t *data, uint16_t length) {
    uint8_t checksum = 0;
    for (uint16_t i = 0; i < length; i++) {
      checksum += data[i];
    }
    return checksum;
  }

  enum class AuthState {
    NOT_AUTHENTICATED,
    SENDING_APP_KEY,
    REQUESTING_RANDOM,
    SENDING_PASSWORD,
    REQUESTING_ROOT_RANDOM,
    SENDING_ROOT_PASSWORD,
    AUTHENTICATED
  };

  bool enable_authentication_{false};
  AuthState authentication_state_{AuthState::NOT_AUTHENTICATED};
  uint8_t random_byte_;
  std::string password_{""};
  uint32_t auth_timeout_start_{0};
  uint32_t auth_timeout_ms_{10000};

  void start_authentication_();
  void send_app_key_();
  void request_random_byte_();
  void send_user_password_();
  void send_root_password_();
  void send_auth_frame_(uint8_t *frame, size_t length);
  void handle_auth_response_(uint8_t command, const uint8_t *data, uint8_t data_len);
  void check_auth_timeout_();
};

}  // namespace jbd_bms_ble
}  // namespace esphome

#endif
