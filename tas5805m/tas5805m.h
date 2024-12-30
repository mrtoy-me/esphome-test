#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace tas5805m {

class Tas5805mComponent : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_enable_pin(GPIOPin *enable) { this->enable_pin_ = enable; }
  void set_tas5805m_state(bool enable);

 protected:
   bool tas5805m_write_byte(uint8_t a_register, uint8_t data);

   enum ErrorCode {
     NONE = 0,
     WRITE_REGISTER_FAILED,
   } error_code_{NONE};

   GPIOPin *enable_pin_{nullptr};
};

}  // namespace tas5805m
}  // namespace esphome
