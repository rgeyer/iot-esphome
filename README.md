I'm slowly migrating off of tasmota to esphome for several devices I use in my smarthome.

These are relevant configuration files for that goodness.

# TopGreener TGWF115PQM
These are little smart plugs with power monitoring capabilities. I've got a bunch of them.

The `devices/tgplug` directory contains a config file for each of them, which imports a lot of common libs from `lib/tgplug`.

The `devices/tgplug/ota.yaml` is intended as an initial firmware with a device name of `tgplugota` which I can then tail the logs of for calibration, before uploading the calibrated firmware.