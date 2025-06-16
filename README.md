I'm slowly migrating off of tasmota to esphome for several devices I use in my smarthome.

These are relevant configuration files for that goodness.

# Devices

## TopGreener TGWF115PQM
These are little smart plugs with power monitoring capabilities. I've got a bunch of them.

The `devices/tgplug` directory contains a config file for each of them, which imports a lot of common libs from `lib/tgplug`.

The `devices/tgplug/ota.yaml` is intended as an initial firmware with a device name of `tgplugota` which I can then tail the logs of for calibration, before uploading the calibrated firmware.

## Cyberpower UPS Monitoring


# Usage/dev/notes

Using USB devices from windows WSL2 for initial flashing. Info [here](https://devblogs.microsoft.com/commandline/connecting-usb-devices-to-wsl/)

Couldn't figure out how to communicate for the longest time, but finally got it working with the raw platform io project foind in `./devices/cyberpower-mon/piotest`. The trick, as it turns out, is that my UPS' TTL *is* indeed inverted, contrary to what is shared [here](https://www.jmayes.com/cyberpower-backup-serial-protocol-and-interface/).

Also, my UPS seems to emit a different set of details when checking with "D/r", namely..

`#I113O113L26B94T46F60.0H60.0R24Q1.8S�����W�`

## Useful commands

Compiling using a docker container
`docker run --rm -i -v "${PWD}":/config ghcr.io/esphome/esphome compile devices/path/to/config.yaml`

Flashing using a docker container
`docker run --rm -i -v "${PWD}":/config ghcr.io/esphome/esphome upload --device <ip or serial port etc> devices/path/to/config.yaml`