#include "jbd_bms_ble.h" #include "esphome/core/log.h"

namespace esphome { namespace jbd_bms_ble {

static const char *const TAG = "jbd_bms_ble";

void JbdBmsBle::dump_config() { ESP_LOGCONFIG(TAG, "JBD BMS BLE:"); LOG_SENSOR("  ", "Total Voltage", this->total_voltage_sensor_); LOG_SENSOR("  ", "Current", this->current_sensor_); LOG_SENSOR("  ", "Remaining Capacity", this->capacity_remaining_sensor_); LOG_SENSOR("  ", "State of Charge", this->state_of_charge_sensor_); LOG_SENSOR("  ", "Power", this->power_sensor_); LOG_SENSOR("  ", "Charging Power", this->charging_power_sensor_); LOG_SENSOR("  ", "Discharging Power", this->discharging_power_sensor_); LOG_SENSOR("  ", "Battery Cycle Capacity", this->battery_cycle_capacity_sensor_); LOG_SENSOR("  ", "Temperature 1", this->temperature_sensors_[0]); }

void JbdBmsBle::handle_notify_data(const std::vector<uint8_t> &data) { if (data.size() < 5) return;

for (size_t i = 0; i + 2 < data.size(); i++) { uint8_t key = data[i]; uint16_t raw = (data[i + 1] << 8) | data[i + 2];

switch (key) {
  case 0xC0:  // Voltage
    if (this->total_voltage_sensor_ != nullptr)
      this->total_voltage_sensor_->publish_state(raw / 100.0f);
    break;
  case 0xC1:  // Current
    if (this->current_sensor_ != nullptr)
      this->current_sensor_->publish_state(raw / 100.0f);
    break;
  case 0xD0:  // SoC
    if (this->state_of_charge_sensor_ != nullptr)
      this->state_of_charge_sensor_->publish_state(raw * 1.0f);
    break;
  case 0xD2:  // Remaining Ah
    if (this->capacity_remaining_sensor_ != nullptr)
      this->capacity_remaining_sensor_->publish_state(raw / 1000.0f);
    break;
  case 0xD8:  // Power
    if (this->power_sensor_ != nullptr)
      this->power_sensor_->publish_state(raw / 100.0f);
    break;
  case 0xD9:  // Temp
    if (!this->temperature_sensors_.empty() && this->temperature_sensors_[0] != nullptr)
      this->temperature_sensors_[0]->publish_state(static_cast<float>(raw) - 100.0f);
    break;
  case 0xD5:  // Battery cycle capacity
    if (this->battery_cycle_capacity_sensor_ != nullptr)
      this->battery_cycle_capacity_sensor_->publish_state(raw / 1000.0f);
    break;
  case 0xD4:  // Charge today
    if (this->charging_power_sensor_ != nullptr)
      this->charging_power_sensor_->publish_state(raw / 100000.0f);
    break;
  case 0xD3:  // Discharge today
    if (this->discharging_power_sensor_ != nullptr)
      this->discharging_power_sensor_->publish_state(raw / 100000.0f);
    break;
  default:
    break;
}

} }

}  // namespace jbd_bms_ble }  // namespace esphome

