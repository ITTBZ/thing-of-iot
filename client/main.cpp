#include "MbedJSONValue.h"
#include "OLEDDisplay.h"
#include "http_request.h"
#include "mbed.h"
#if MBED_CONF_IOTKIT_HTS221_SENSOR == true
#include "HTS221Sensor.h"
#endif
#if MBED_CONF_IOTKIT_BMP180_SENSOR == true
#include "BMP180Wrapper.h"
#endif
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled(MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL);
static DevI2C devI2c(MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL);
#if MBED_CONF_IOTKIT_HTS221_SENSOR == true
static HTS221Sensor hum_temp(&devI2c);
#endif
#if MBED_CONF_IOTKIT_BMP180_SENSOR == true
static BMP180Wrapper hum_temp(&devI2c);
#endif

const char host[] = "http://weatherapp.just2flex.com/weather";
char request_body[1024];

DigitalOut myled(MBED_CONF_IOTKIT_LED1);

int main() {
  uint8_t id;
  float temperature, humidity;

  printf("\tWeather Station\n");

  /* Init all sensors with default params */
  hum_temp.init(NULL);
  hum_temp.enable();

  hum_temp.read_id(&id);
  //printf("HTS221  humidity & temperature    = 0x%X\r\n", id);

  // Connect to the network with the default networking interface
  // if you use WiFi: see mbed_app.json for the credentials
  WiFiInterface *network = WiFiInterface::get_default_instance();
  if (!network) {
    printf("ERROR: No WiFiInterface found.\n");
    return -1;
  }

  printf("\nAttempting to connect to '%s'...\n", MBED_CONF_APP_WIFI_SSID);
  int network_state = 1;
  while(network_state != 0) {
    network_state = network->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    thread_sleep_for(1000);
  }

  SocketAddress socket_address;
  network->get_ip_address(&socket_address);
  printf("Connected to network!\n├ MAC: %s\n└ IP: %s\n", network->get_mac_address(), socket_address.get_ip_address());

  while (1) {
    myled = 1;
    hum_temp.get_temperature(&temperature);
    hum_temp.get_humidity(&humidity);

    oled.clear();
    oled.cursor(1, 0);
    oled.printf("Temperature: %.1f%c C\nHumidity: %.1f", temperature, (char)247, humidity);

    sprintf(request_body, "{\"temperature\": %f, \"humidity\": %f}", temperature, humidity);

    HttpRequest *weather_update_request = new HttpRequest(network, HTTP_POST, host);
    weather_update_request->set_header("content-type", "application/json");
    weather_update_request->send(request_body, strlen(request_body));
    delete weather_update_request;

    myled = 0;
    thread_sleep_for(30000);
  }
}