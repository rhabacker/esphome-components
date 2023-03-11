#include "ntc.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ntc {

static const char *const TAG = "ntc";

void NTC::setup() {
  this->sensor_->add_on_state_callback([this](float value) { this->process_(value); });
  if (this->sensor_->has_state())
    this->process_(this->sensor_->state);
}
void NTC::dump_config() { LOG_SENSOR("", "NTC Sensor", this) }
float NTC::get_setup_priority() const { return setup_priority::DATA; }
void NTC::process_(float value) {
  if (std::isnan(value)) {
    this->publish_state(NAN);
    return;
  }
  if (reversed_) {
    double T = value + 273.15;
    double y = (a_ - 1 / (T)) / (2 * c_);
    double x = sqrt(pow(b_ / (3 * c_), 3) + y * y);
    auto resistance = exp(pow(x - y, 1 / 3.0) - pow(x + y, 1 / 3.0));
    ESP_LOGD(TAG, "'%s' - Resistance: %.1f Ohm", this->name_.c_str(), resistance);
    this->publish_state(resistance);
  } else {
    double lr = log(double(value));
    double v = this->a_ + this->b_ * lr + this->c_ * lr * lr * lr;
    auto temp = float(1.0 / v - 273.15);
    ESP_LOGD(TAG, "'%s' - Temperature: %.1f°C", this->name_.c_str(), temp);
    this->publish_state(temp);
  }
}

}  // namespace ntc
}  // namespace esphome
