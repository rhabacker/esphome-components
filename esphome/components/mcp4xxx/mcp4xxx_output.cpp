#include "mcp4xxx_output.h"

#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp4xxx {

static const char *const TAG = "MCP4XXX";

void MCP4XXXComponent::setup() {
    delay(10);
    dump_config();
}

void MCP4XXXComponent::dump_config() {
    ESP_LOGCONFIG(TAG, "config:");
    ESP_LOGI(TAG, "  Maximum value: %d", max_value());
}

void MCP4XXXComponent::loop() {
}

void MCP4XXXComponent::set_channel_value_(MCP4XXXChannelIdx channel, uint16_t value)
{
    ESP_LOGI(TAG, "Writing value %3d to poti %d", value, 0);
    set(value);
}

// 0..1 []
void MCP4XXXChannel::write_state(float state) {
    ESP_LOGI(TAG, "write_state called with %f", state);
    int max_value = parent_->max_value();
    const float digital_value = state * max_value;
    const float duty_rounded = roundf(digital_value);
    auto duty = static_cast<int16_t>(duty_rounded);
    if (duty > max_value) {
        ESP_LOGI(TAG, "overflow detected: value '%d' ", duty);
        duty = max_value;
    }
    double failure = fabs(duty - digital_value) / digital_value;
    if (failure != 0.0)
        ESP_LOGI(TAG, "difference: %.4f %", failure * 100);

    parent_->set_channel_value_(channel_, duty);
}

uint32_t MCP4XXXChannel::hash_base() { return 2455723295UL; }

}  // namespace mcp4xxx
}  // namespace esphome
