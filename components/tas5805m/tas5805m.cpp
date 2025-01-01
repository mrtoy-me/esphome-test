#include "tas5805m.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace tas5805m {

static const char *const TAG = "tas5805m";
static const uint8_t DEVICE_CTRL_2_REGISTER = 0x03; // Device state control register

void Tas5805mComponent::setup() {
  if (this->enable_pin_ != nullptr) {
    // Set enable pin as OUTPUT and disable the enable pin
    this->enable_pin_->setup();
    this->enable_pin_->digital_write(false);
    delay(200);
    this->enable_pin_->digital_write(true);
  }
  
  if (!this->tas5805m_write_byte(DEVICE_CTRL_2_REGISTER, 0x02)) { // device state Hi-Z
    this->error_code_ = WRITE_REGISTER_FAILED;
    this->mark_failed();
    return;
  }
  delay(50);
  if (!this->tas5805m_write_byte(DEVICE_CTRL_2_REGISTER, 0x03)) { // device state PLAY
    this->error_code_ = WRITE_REGISTER_FAILED;
    this->mark_failed();
    return;
  }
}

void Tas5805mComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "TAS5805M:");

  switch (this->error_code_) {
    case WRITE_REGISTER_FAILED:
      ESP_LOGE(TAG, "  Write register failed with error code = %i",this->last_i2c_error_);
      break;
    case NONE:
      ESP_LOGD(TAG, "  Setup successful");
      LOG_I2C_DEVICE(this);
      break;
  }
}
void Tas5805mComponent::set_tas5805m_state(bool enable) {
  uint8_t value = enable ? 0x03 : 0x00; // device state PLAY or Deep Sleep
  this->tas5805m_write_byte(DEVICE_CTRL_2_REGISTER, value);
}

bool Tas5805mComponent::tas5805m_write_byte(uint8_t a_register, uint8_t data) {
    i2c::ErrorCode error_code = this->write_register(a_register, &data, 1, true);
    if (error_code != i2c::ERROR_OK) {
      ESP_LOGE(TAG, "  write register error %i", error_code);
      this->last_i2c_error_ = (uint8_t)error_code;
      return false;
    }
    return true;
}

}  // namespace tas5805m
}  // namespace esphome
