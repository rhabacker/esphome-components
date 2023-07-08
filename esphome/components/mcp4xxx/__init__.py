import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@rhabacker"]
MULTI_CONF = True
CONF_STORE_IN_EEPROM = "store_in_eeprom"
CONF_RESISTOR = "resistor"

mcp4xxx_ns = cg.esphome_ns.namespace("mcp4xxx")
MCP4XXXComponent = mcp4xxx_ns.class_("MCP4XXXComponent", cg.Component)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(MCP4XXXComponent),
            # only some chips
            cv.Optional(CONF_STORE_IN_EEPROM, default=False): cv.boolean,
            cv.Required(CONF_RESISTOR): cv.resistance,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_STORE_IN_EEPROM], config[CONF_RESISTOR])
    await cg.register_component(var, config)
    cg.add(var.set_resistor(config[CONF_RESISTOR]))
