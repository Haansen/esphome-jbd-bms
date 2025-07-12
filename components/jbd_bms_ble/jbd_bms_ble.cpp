#include "jbd_bms_ble.h"
#include "esphome/core/log.h"

namespace esphome {
namespace jbd_bms_ble {

static const char *const TAG = "jbd_bms_ble";

void JbdBmsBle::dump_config() {
  ESP_LOGCONFIG(TAG, "JBD BMS BLE:");
  LOG_SENSOR("  ", "Total Voltage", this->total_voltage_sensor_);
  LOG_SENSOR("  ", "Current", this->current_sensor_);
  LOG_SENSOR("  ", "Remaining Capacity", this->capacity_remaining_sensor_);
  LOG_SENSOR("  ", "State of Charge", this->state_of_charge_sensor_);
  LOG_SENSOR("  ", "Power", this->power_sensor_);
  LOG_SENSOR("  ", "Temperature 1", this->temperature_sensor_1_);
  LOG_SENSOR("  ", "Battery Cycle Capacity", this->battery_cycle_capacity_sensor_);
  LOG_SENSOR("  ", "Charging Power", this->charging_power_sensor_);
  LOG_SENSOR("  ", "Discharging Power", this->discharging_power_sensor_);
}

void JbdBmsBle::handle_notify_data(std::vector<uint8_t> &data) {
  if (data.size() < 10) return;

  std::map<uint8_t, float> values;

  for (size_t i = 0; i + 2 < data.size(); i++) {
    uint8_t key = data[i];
    uint16_t raw = (data[i + 1] << 8) | data[i + 2];

    switch (key) {
      case 0xC0:  // Voltage
        values[key] = raw / 100.0f;
        if (this->total_voltage_sensor_ != nullptr)
          this->total_voltage_sensor_->publish_state(values[key]);
        break;
      case 0xC1:  // Current
        values[key] = raw / 100.0f;
        if (this->current_sensor_ != nullptr)
          this->current_sensor_->publish_state(values[key]);
        break;
      case 0xD0:  // SoC
        values[key] = raw / 1.0f;
        if (this->state_of_charge_sensor_ != nullptr)
          this->state_of_charge_sensor_->publish_state(values[key]);
        break;
      case 0xD2:  // Remaining Ah
        values[key] = raw / 1000.0f;
        if (this->capacity_remaining_sensor_ != nullptr)
          this->capacity_remaining_sensor_->publish_state(values[key]);
        break;
      case 0xD8:  // Power
        values[key] = raw / 100.0f;
        if (this->power_sensor_ != nullptr)
          this->power_sensor_->publish_state(values[key]);
        break;
      case 0xD9:  // Temp
        values[key] = raw - 100.0f;
        if (this->temperature_sensor_1_ != nullptr)
          this->temperature_sensor_1_->publish_state(values[key]);
        break;
      case 0xD5:  // Accumulated Ah (battery cycle capacity)
        values[key] = raw / 1000.0f;
        if (this->battery_cycle_capacity_sensor_ != nullptr)
          this->battery_cycle_capacity_sensor_->publish_state(values[key]);
        break;
      case 0xD4:  // Charge today
        values[key] = raw / 100000.0f;
        if (this->charging_power_sensor_ != nullptr)
          this->charging_power_sensor_->publish_state(values[key]);
        break;
      case 0xD3:  // Discharge today
        values[key] = raw / 100000.0f;
        if (this->discharging_power_sensor_ != nullptr)
          this->discharging_power_sensor_->publish_state(values[key]);
        break;
      default:
        break;
    }
  }
}

}  // namespace jbd_bms_ble
}  // namespace esphome
