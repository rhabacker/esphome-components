#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace ntcsim {

class NTCSimulation : public Component, public sensor::Sensor {
 public:
  void set_sensor(Sensor *sensor) { sensor_ = sensor; }
  void set_output(output::FloatOutput *output) { output_ = output; }
  void set_output_resistance(float resistance) { resistance_ = resistance; }
  void set_a(double a) { a_ = a; }
  void set_b(double b) { b_ = b; }
  void set_c(double c) { c_ = c; }
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;

 protected:
  void process_(float value);

  sensor::Sensor *sensor_;
  output::FloatOutput *output_{nullptr};
  double a_;
  double b_;
  double c_;
  float resistance_{1.0f};
};

}  // namespace ntcsim
}  // namespace esphome
