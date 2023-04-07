#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "htmlPages.h"
#include "system.h"

static uint8_t FL_reset = 0;
String currentUser;

ESP8266WebServer server(80);

uint8_t EEPROM_save(String data, uint32_t index = 0)
{
  uint16_t dataLength = data.length();
  Serial.print("EEPROM_DATA: ");
  Serial.print(data);
  Serial.print('\n');
  Serial.print("EEPROM_DATA LENGTH: ");
  Serial.print(dataLength);
  Serial.print('\n');
  EEPROM.write(index, dataLength);
  index ++;

  for (int i = index; i < dataLength + index; i++ )
  {
    EEPROM.write(i, data[i - 1]);
  }

  return EEPROM.commit();
}


void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(ssid, password);
  delay(1000);
  server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI
  server.on("/login", HTTP_POST, handleLogin);
  server.on("/reset", HTTP_POST, handleReset);
  server.on("/passwordChange", HTTP_POST, handlePasswordChange);
  server.on("/backToMain", HTTP_POST, generateMainPage);
  server.on("/changePasswordAccept", HTTP_POST, handlePasswordValidate);
  server.begin();
  delay(2000);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(HARD_RESET_PIN, INPUT);
  delay(100);
  digitalWrite(RESET_PIN, LOW);

  Serial.print("Utilizar el siguiente IP: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  Serial.print(getPassword());
}

void loop() {

  server.handleClient();   // Listen for HTTP requests from clients
  task_handler();
  checkForHardReset();
}

void task_handler()
{
  const uint32_t resetTimeout = 5000; //ms
  static long resetCurrTime = 0;

  if (FL_reset == ON)
  {
    resetCurrTime = millis();
    digitalWrite(RESET_PIN, HIGH);
    FL_reset = OFF;
  }

  if ((resetCurrTime > 0) && (millis() >= resetCurrTime + resetTimeout))
  {
    digitalWrite(RESET_PIN, LOW);
    resetCurrTime = 0;
  }

}


void handleLogin()
{
  String currentPassword = getPassword();
  // If a POST request is made to URI /login
  if ( ! server.hasArg("username") || ! server.hasArg("password") || server.arg("username") == NULL || server.arg("password") == NULL)
  { // If the POST request doesn't have username and password data
    server.send(400, "text/plain", "400: Invalid Request");         // The request is invalid, so send HTTP status 400
    return;
  }
  if (server.arg("username") == "Admin" && server.arg("password") == currentPassword)
  { // If both the username and the password are correct
    currentUser = server.arg("username");
    generateMainPage();
  }
  else
  { // Username and password don't match
    server.send(401, "text/plain", "401: Unauthorized");
  }
}

void generateMainPage()
{
  server.send(200, "text/html", (String)MAIN_page + "<p>&nbsp;Usuario: " + currentUser + "</p>");
}

void handleRoot()
{
  // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", ROOT_page);
}

void handleReset()
{
  FL_reset = ON;

  server.send(200, "text/html", (String)MAIN_page + "<p>&nbsp;Usuario: " + currentUser + "</p>");
}

void handlePasswordChange()
{
  server.send(200, "text/html", PASSWORDCH_page);
}

void handlePasswordValidate()
{
  String currentPassword = getPassword();

  if ( !server.hasArg("passwordOld") || !server.hasArg("passwordNew1") || !server.hasArg("passwordNew2")
       || server.arg("passwordOld") == NULL || server.arg("passwordNew1")  == NULL || server.arg("passwordNew2") == NULL)
  {
    server.send(400, "text/plain", "Se deben llenar todos los campos.");         // The request is invalid, so send HTTP status 400
    return;
  }
  if ( server.arg("passwordNew1").length() > PASS_LENGTH_MAX )
  {
    server.send(400, "text/plain", "La password supera la long. maxima.");
  }
  else
  {
    if ( server.arg("passwordOld") == currentPassword && (server.arg("passwordNew1") == server.arg("passwordNew2")))
    {      
      EEPROM_save(String(server.arg("passwordNew1")),EEPROM_INDEX_PASSWORD);
      generateMainPage();
    }
    else
    {
      server.send(400, "text/plain", "Datos invalidos.");
    }
  }
}

String getPassword()
{
  String buff;
  uint32_t passLength =  EEPROM.read(EEPROM_INDEX_PASSWORD);

  if (passLength > PASS_LENGTH_MAX)
  {
    Serial.print("Error de lectura de ROM\n");
    return "#ERROR";
  }

  for (int i = EEPROM_INDEX_PASSWORD; i < passLength + EEPROM_INDEX_PASSWORD; i++)
  {
    buff += (char)EEPROM.read(i + 1);
  }

  return buff;
}


void checkForHardReset()
{
  static int counter = 0;
  
  if ( digitalRead(HARD_RESET_PIN) == 0 && millis() % 10000 == 0)
  {
    counter ++;
    
    if(counter > 15)
    {
      EEPROM_save("admin123", EEPROM_INDEX_PASSWORD);
      Serial.print("Contraseña reseteada\n");
      counter = 0;  
    }
  }
  else
  {
    counter = 0;
  }
}
