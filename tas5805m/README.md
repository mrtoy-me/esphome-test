
## Usage: "tas5805m" component
Copy files in "tas5805m" directory into a "tas5805m" subdirectory under a "components" directory<BR>
under the "esphome" addon directory (of your homeassistant install)<BR>
For example:
```
esphome
├── components
   ├── tas5805m
```
The following yaml can then be used to access the component:
```
external_components:
  - source: components
```
Alternatively

## Example YAML
## Note that esp32 board, !secrets , psram configuration (if required)
## and most importantly GPIO pins will need to be configured according to your hardware
```
esphome:
  name: louder-esp32
  friendly_name: louder-esp32
  on_boot:
  ## use priority 250 so gpio and i2c dac is setup before volume is set
    priority: 250
    then:
    ## Set a volume limit just to be safe...
    - media_player.volume_set:
        id: louderesp32
        volume: 10%

esp32:
  board: esp32dev
  framework:
    type: arduino

# Enable logging
logger:

# Enable Home Assistant API
api:
  encryption:
    key: !secret esphome_api_key

ota:
  - platform: esphome
    password: !secret esphome_ota_password

wifi:
  ssid: !secret esphome_wifi_ssid
  password: !secret esphome_wifi_password

  ap:
    ssid: "Fallback Hotspot"
    password: !secret esphome_ap_password

captive_portal:

external_components:
   - source: components
     components: [ tas5805m ]

i2c:
  sda: GPIO21
  scl: GPIO27
  scan: True

tas5805m:
  id: my_dac
  enable_pin: GPIO33

switch:
  - platform: tas5805m
    tas5805m_id: my_dac
    id: dac_pwer

i2s_audio:
  i2s_lrclk_pin: GPIO25
  i2s_bclk_pin: GPIO26

media_player:
  - platform: i2s_audio
    name: louder_mediaplayer
    id: louderesp32
    dac_type: external
    i2s_dout_pin: GPIO22
    mode: stereo
```