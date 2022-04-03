# Reflection (LB2)
As of now, the project was really fun to work with. We both had no experience with C++ before. During the first part of the project we connected the IoT-Kit and learned how to write our own code on it. We learned how to collect sensor data and send it to another service via the HTTP protocol from the mbed board. When we were trying to find out how to enable SSL, going through the `http_request.h` code, we realized that it only supports non-SSL requests. The `https_request.h` file caught our attention really fast. We recognized that we have to utilze another Class which requires another parameter, a String containing the trusted root certificate authoritie.

**Without SSL/TLS**:
```cpp
HttpRequest *request = new HttpRequest(network, HTTP_POST, MBED_CONF_APP_SPRING_API_URL);
// ...
delete request;
```

**With SSL/TLS**:  
*To extract the root CA for a domain open up Firefox, visit the https website, click on the padlock next to the url, click "Connection secure" > "More information" > "Security" > View certificate. The certificate on the very right side is the root certificate. Scroll down to the "Miscellaneous" and download the "PEM (cert)" file.*
```cpp
const char SSL_CA_PEM[] = "-----BEGIN CERTIFICATE-----\n" // The whole certificate

HttpsRequest *request = new HttpsRequest(network, SSL_CA_PEM, HTTP_POST, MBED_CONF_APP_SPRING_API_URL);
// ...
delete request;
```

When enabling HTTPS for our Java spring application, we have chosen between 2 options. Option 1 was using Let's encrypt to request a trusted certificate or create a self-signed certificate. Option 2 was to use Cloudflare which generates a certificate for us. We chose the second option because it can be done really easy. Usually Cloudflare gives you a origin certificate which should be installed on the origin server/application to create an encrypted connection from your application to Cloudflare. We skipped this part so we don't have to handle SSL in our Java spring application or use Nginx/Apache2 as a proxy. This makes things a bit less secure since the connection to Cloudflare is not encrypted but it's enough for our case.

For the deployment we were first thinking about deploying the spring application to our server as a jar file but we quickly realized that it would make sense to make it easily scalable for the second part of the project (LB3). So we decided to use Docker which would allow us to scale it with Kubernetes and Traefik load balancing if convenient in LB3, when using MQTT.

Editing config files within the codebase to configure things is not the most convenient way, especially when using docker. We may improve the mariadb configuration in LB3 by accepting environment variables from docker in our spring application. This will allow us to deploy the docker container without the additional step of editing the config files before building the image.

# Important acquisitions
* Setting up Mbed (board and studio)
* Programming with C++
* Temperature sensor and it's associated I²C bus.
* Communicating via the HTTP protocol between board and our spring application
* Enabling SSL
* Deploying with Docker

# Knowledgebase

## IoT-Kit B-L475VG-IOT01A 
The B-L475VG-IOT01A Discovery kit for IoT node allows users to develop applications with direct connection to cloud servers. The Discovery kit enables a wide diversity of applications by exploiting low-power communication, multiway sensing and ARM Cortex -M4 core-based STM32L4 Series features. 

The development platform includes a lot of features like: 128KB SRAM, 1MB Flash, GPIO (82) with external interrupt capability, 80 MHz max CPU frequency, bus systems like I2C, SPI, UART, etc. and much more.

It is programmed in C++. Other programming languages like Java 8 ME are also supported.

## I²C
I²C, Inter-Integrated Circuit, is a serial data bus developed by Philips Semiconductors (today NXP Semiconductors).The bus was introduced by Philips in 1982 for device internal communication between ICs in e.g. CD players and TV sets.

## Temperature sensor
The TMP75 is a temperature sensor which is addressed via I²C bus. The TMP75 is mounted on the SMD shield. The temperature is returned as a 12-bit number with a resolution of 0.0625, see data sheet. Implementation by means of TMP175 library.