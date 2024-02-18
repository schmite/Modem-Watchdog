#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0D, 0x10, 0x16
};

// IP address to compare when DHCP client fails
IPAddress undifined(0, 0, 0, 0);

// Time to waiting device be up and running.
int timeToUnR = 1800;

// Couter to track how many cicles this watchdogdog do since power on
unsigned int count = 0;

int relay = 8;

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH Shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit FeatherWing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit FeatherWing Ethernet

  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Vamos começar...");

  // start the Ethernet connection:
  Ethernet.begin(mac);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }

  // give the Ethernet shield a second to initialize:
  delay(1000);

  Serial.println(Ethernet.linkStatus());

  while (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    delay(500);
  }
}

void loop() {
  Serial.print("Contagem de execução: ");
  Serial.println(count++);
  // start the Ethernet connection:
  Ethernet.begin(mac);

  Serial.println(Ethernet.localIP());

  if( Ethernet.localIP() == undifined) {
    Serial.println("Falha ao obter IP.");
    Serial.println("Vamos rebotar o modem.");
    digitalWrite(relay, LOW);
    delay(10000);
    digitalWrite(relay, HIGH);
    Serial.println("Modem religado.");
    Serial.println("Vamos aguardar o modem inicializar.");
    delay(timeToUnR);
  }

  Serial.println("Vamos aguardar a próxima verificação...");
  delay(5000);
}
