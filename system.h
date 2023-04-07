/*
	brief: system files
	author: Luca Agostini
	date: 10/4/2019
*/

//WIFI data
const char* ssid = "";
const char* password = ";

/********************************************
  //ROM MAP
  typedef union{
  uint8_t mem_byte_access[1024];
  char * mem_string_access;
  } _ROM_access;

  #define ROM (( _ROM_access *)0x40000000)
  #define ROM_index ROM[0]
*********************************************/

//Defines aplicacion
#define RESET_PIN 2//D4
#define OFF 0
#define ON 1
#define PASS_LENGTH_MAX 10
#define EEPROM_INDEX_PASSWORD 0
#define HARD_RESET_PIN 0//D3
