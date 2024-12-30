import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
    DEVICE_CLASS_SWITCH,
)

from .. import CONF_TAS5805M_ID, Tas5805mComponent, tas5805m_ns

DEPENDENCIES = ["tas5805m"]

Tas5805mSwitch = tas5805m_ns.class_("Tas5805mSwitch", switch.Switch)

CONFIG_SCHEMA = switch.switch_schema(
    Tas5805mSwitch,
    device_class=DEVICE_CLASS_SWITCH,
).extend(
    cv.Schema(
        {
           cv.GenerateID(CONF_TAS5805M_ID): cv.use_id(Tas5805mComponent),
        }
    )
)

async def to_code(config):
    await cg.get_variable(config[CONF_TAS5805M_ID])
    s = await switch.new_switch(config)
    await cg.register_parented(s, config[CONF_TAS5805M_ID])
