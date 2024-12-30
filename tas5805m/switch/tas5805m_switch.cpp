#include "tas5805m_switch.h"

namespace esphome {
namespace tas5805m {

void Tas5805mSwitch::write_state(bool state) {
  this->publish_state(state);
  this->parent_->set_tas5805m_state(state);
}

}  // namespace tas5805m
}  // namespace esphome
