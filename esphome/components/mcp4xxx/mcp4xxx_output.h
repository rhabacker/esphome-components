#pragma once

#include "arduino-mcp4xxx/mcp4xxx.h"

#include "esphome/core/component.h"
#include "esphome/core/entity_base.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace mcp4xxx {

enum MCP4XXXChannelIdx { MCP4XXX_CHANNEL_A = 0, MCP4XXX_CHANNEL_B = 1 };

class MCP4XXXChannel;

/// MCP4XXX float output component.
class MCP4XXXComponent : public Component, icecave::arduino::MCP4XXX
 {
 public:
  MCP4XXXComponent(bool store_in_eeprom, float resistor)
      : icecave::arduino::MCP4XXX::MCP4XXX(SS, icecave::arduino::MCP4XXX::pot_0, icecave::arduino::MCP4XXX::res_8bit, icecave::arduino::MCP4XXX::potentiometer)
      , store_in_eeprom_(store_in_eeprom)
      , resistor_(resistor) {}
  void set_resistor(int resistor) { resistor_ = resistor; }
  int get_resistor() { return resistor_; }

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  void loop() override;

 protected:
  friend MCP4XXXChannel;
  void set_channel_value_(MCP4XXXChannelIdx channel, uint16_t value);

 private:
  bool store_in_eeprom_ = false;
  bool update_ = false;
  float resistor_{10000.0};
};

class MCP4XXXChannel : public output::FloatOutput {
 public:
  MCP4XXXChannel(MCP4XXXComponent *parent, MCP4XXXChannelIdx channel)
      : parent_(parent), channel_(channel)
  {
  }

 protected:
  void write_state(float state) override;
  uint32_t hash_base(); //override;

  MCP4XXXComponent *parent_;
  MCP4XXXChannelIdx channel_;
};

}  // namespace mcp4xxx
}  // namespace esphome
