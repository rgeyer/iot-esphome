#include <esphome.h>

class CyberPowerUps : public PollingComponent, public UARTDevice
{
public:
  CyberPowerUps(UARTComponent *parent) : UARTDevice(parent) {}

  Sensor *inputVolts = new Sensor();
  Sensor *outputVolts = new Sensor();
  Sensor *loadPercent = new Sensor();
  Sensor *temperature = new Sensor();
  Sensor *batteryPercent = new Sensor();
  Sensor *inputFreqHz = new Sensor();
  Sensor *outputFreqHz = new Sensor();
  Sensor *runtimeMinutes = new Sensor();
  Sensor *loadHundredWatts = new Sensor();
  // BinarySensor *upsStatus = new BinarySensor();
  // BinarySensor *lineStatus = new BinarySensor();
  // BinarySensor *batteryLow = new BinarySensor();
  // BinarySensor *upsTesting = new BinarySensor();
  // BinarySensor *upsRunning = new BinarySensor();

  void setup() override
  {
    this->set_update_interval(3000);
  }

  void loop() override
  {
  }

  void writeSensor(Sensor *s, char *val, int len)
  {
    if (s != nullptr && len)
    {
      val[len] = '\0'; // Terminate the val
      s->publish_state((float)atof(val));
    }
  }

  void update() override
  {
    write_array(new byte[2]{0x44, 0x0D}, 2); // D\r

    const int max_value_length = 16;
    static char buffer[max_value_length];
    int pos = 0;
    Sensor *currentSensor = nullptr;

    while (available())
    {
      char rchar = read();
      switch (rchar)
      {
      case 'I':
        writeSensor(currentSensor, buffer, pos);
        currentSensor = this->inputVolts;
        pos = 0;
        break;
      case 'O':
        writeSensor(currentSensor, buffer, pos);
        currentSensor = this->outputVolts;
        pos = 0;
        break;
      case 'L':
        writeSensor(currentSensor, buffer, pos);
        currentSensor = this->loadPercent;
        pos = 0;
        break;
      case 'B':
        writeSensor(currentSensor, buffer, pos);
        currentSensor = this->batteryPercent;
        pos = 0;
        break;
      case 'T':
        writeSensor(currentSensor, buffer, pos);
        currentSensor = this->temperature;
        pos = 0;
        break;
      case 'F':
        writeSensor(currentSensor, buffer, pos);
        currentSensor = this->outputFreqHz;
        pos = 0;
        break;
      case 'H':
        writeSensor(currentSensor, buffer, pos);
        currentSensor = this->inputFreqHz;
        pos = 0;
        break;
      case 'R':
        writeSensor(currentSensor, buffer, pos);
        currentSensor = this->runtimeMinutes;
        pos = 0;
        break;
      case 'Q':
        writeSensor(currentSensor, buffer, pos);
        currentSensor = this->loadHundredWatts;
        pos = 0;
        break;
      case '#':
        pos = 0;
        break;
      case 'S':
        writeSensor(currentSensor, buffer, pos);
        pos = 0;
        break;
      case '\r':
        pos = 0;
        break;
      default:
        buffer[pos++] = rchar;
        if (pos == max_value_length - 1)
        {
          ESP_LOGD("cyberpower_ups", "Buffer overflow");
          pos = 0;
        }
      }
    }
  }
};