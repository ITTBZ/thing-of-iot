#include "MbedJSONValue.h"
#include "OLEDDisplay.h"
#include "http_parser.h"
#include "http_request.h"
#include "mbed.h"
#include <cstdio>
#if MBED_CONF_IOTKIT_HTS221_SENSOR == true
#include "HTS221Sensor.h"
#endif
#if MBED_CONF_IOTKIT_BMP180_SENSOR == true
#include "BMP180Wrapper.h"
#endif
#include "OLEDDisplay.h"

#include <MQTTClientMbedOs.h>
#include <MQTTNetwork.h>
#include <MQTTClient.h>
#include <MQTTmbed.h> // Countdown

// UI
OLEDDisplay oled(MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL);
static DevI2C devI2c(MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL);
#if MBED_CONF_IOTKIT_HTS221_SENSOR == true
static HTS221Sensor hum_temp(&devI2c);
#endif
#if MBED_CONF_IOTKIT_BMP180_SENSOR == true
static BMP180Wrapper hum_temp(&devI2c);
#endif

DigitalOut myled(MBED_CONF_IOTKIT_LED1);


void publish( MQTTNetwork &mqttNetwork, MQTT::Client<MQTTNetwork, Countdown> &client, char* topic, char payload[100]) {
    MQTT::Message message;    
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*) payload;
    message.payloadlen = strlen(payload)+1;
    client.publish( topic, message);  
}

int main() {
  char weather_csv[100];
  float temperature, humidity;

  printf("\tWeather Station\n");
  myled = 1;

  /* Init all sensors with default params */
  hum_temp.init(NULL);
  hum_temp.enable();

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
  myled = 0;
  
  MQTTNetwork mqttNetwork( network );
  MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);
  
  printf("Connecting to %s:%d\r\n", MBED_CONF_APP_GATEWAY_HOST, MBED_CONF_APP_GATEWAY_PORT);
  int rc = mqttNetwork.connect(MBED_CONF_APP_GATEWAY_HOST, MBED_CONF_APP_GATEWAY_PORT);
  if (rc != 0)
    printf("rc from TCP connect is %d\r\n", rc);

  MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
  data.MQTTVersion = 3;
  data.clientID.cstring = (char*) network->get_mac_address();
  if ((rc = client.connect(data)) != 0)
    printf("rc from MQTT connect is %d\r\n", rc);    
  
  while (true) {
    hum_temp.get_temperature(&temperature);
    hum_temp.get_humidity(&humidity);

    oled.clear();
    oled.printf("Temperature: %.1f%c C\nHumidity: %.1f", temperature, (char)247, humidity);

    sprintf(weather_csv, "%f,%f", temperature, humidity);
    publish(mqttNetwork, client, "weather", weather_csv);

    thread_sleep_for(3000);
  }
}