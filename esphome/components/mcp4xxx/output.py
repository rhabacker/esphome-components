import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_CHANNEL, CONF_ID, CONF_GAIN
from . import MCP4XXXComponent, mcp4xxx_ns

DEPENDENCIES = ["mcp4xxx"]

MCP4XXXChannel = mcp4xxx_ns.class_("MCP4XXXChannel", output.FloatOutput)
CONF_MCP4XXX_ID = "mcp4xxx_id"

MCP4XXXChannelIdx = mcp4xxx_ns.enum("MCP4XXXChannelIdx")
CHANNEL_OPTIONS = {
    "A": MCP4XXXChannelIdx.MCP4XXX_CHANNEL_A,
    "B": MCP4XXXChannelIdx.MCP4XXX_CHANNEL_B
}

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(MCP4XXXChannel),
        cv.GenerateID(CONF_MCP4XXX_ID): cv.use_id(MCP4XXXComponent),
        cv.Required(CONF_CHANNEL): cv.enum(CHANNEL_OPTIONS, upper=True)
    }
)

async def to_code(config):
    paren = await cg.get_variable(config[CONF_MCP4XXX_ID])
    var = cg.new_Pvariable(
        config[CONF_ID],
        paren,
        config[CONF_CHANNEL],
    )
    await output.register_output(var, config)
