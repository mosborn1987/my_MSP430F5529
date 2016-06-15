/*
 * ESP8266.h
 *
 *  Created on: Jun 10, 2016
 *      Author: Mario Osborn
 */

#ifndef DRIVERLIB_MSP430_LIB_TARGETS_ESP8266_H_
#define DRIVERLIB_MSP430_LIB_TARGETS_ESP8266_H_

//#include <USCI_B0_SPI.h>
#include <UART_A0.h>
#include <UART_TERMINAL_A1.h>
#include <gpio.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
//#include <ISR_UART.h>


//#include "tones.h"

//#include <DHT22_430.h>

#define SRV_ADDR "192.168.1.100"
#define SRV_PORT "9977"

//#define DHT_PIN P2_1
#define ESP8266_CH_PD_PORT GPIO_PORT_P1
#define ESP8266_CH_PD_PIN  GPIO_PIN6
#define ESP8266_RESET_PORT GPIO_PORT_P6
#define ESP8266_RESET_PIN  GPIO_PIN6

//#define BUZZER_PIN P1_4
//#define RED_LED P1_0

#define MAX_IN_BUF_SZ 64U
#define MAX_OUT_BUF_SZ 64U
#define MAX_AUX_BUF_SZ 32U

#define MEASUREMENTS_DELAY_S 60U
//#define ALARM_DELAY_MS 1000U
#define MAX_RETRY_CNT 100U

char in_buf[MAX_IN_BUF_SZ];
char out_buf[MAX_OUT_BUF_SZ];
char aux_buf[MAX_AUX_BUF_SZ];

//DHT22 dht (DHT_PIN);
void delay(uint8_t delay_cycles);
void delay(uint8_t delay_cycles)
{
	while(delay_cycles>0)
	{
		_delay_cycles(1);
		delay_cycles--;
	}
}

void set_CH_PD_LOW(void)
{
	GPIO_setOutputLowOnPin(ESP8266_CH_PD_PORT, ESP8266_CH_PD_PIN);
}
void set_CH_PD_HIGH(void)
{
	GPIO_setOutputHighOnPin(ESP8266_CH_PD_PORT, ESP8266_CH_PD_PIN);
}

void set_RESET_LOW(void)
{
	GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN6);
}

void set_RESET_HIGH(void)
{
	GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);
}

void init_CH_PD_PIN(void);
void init_CH_PD_PIN(void)
{
	set_CH_PD_LOW();
	GPIO_setAsOutputPin(ESP8266_CH_PD_PORT, ESP8266_CH_PD_PIN);
//	set_CH_PD_HIGH();
//	GPIO_setAsOutputPin(ESP8266_RESET_PORT, ESP8266_RESET_PIN);
//	GPIO_setOutputLowOnPin(ESP8266_RESET_PORT, ESP8266_RESET_PIN);

	return;
}

void ESP8266_setup()
{
	// buzzer not needed.
//	pinMode (BUZZER_PIN, OUTPUT);


    // Init A1
    UART_TERMINAL_init();

    // Init A0
    UART_init();
//    print_UART_buffer();

	//pinMode (ESP8266_CH_PD_PIN, OUTPUT);
	init_CH_PD_PIN();


//	Serial.begin (115200);

//	dht.begin ();

    esp8266reboot();

}

//void loop()
//{
//  esp8266rx (NULL);
//
////  boolean flag = dht.get ();
////  int h = dht.humidityX10 ();
////  int t = dht.temperatureX10 ();
//
//  if (!flag) {
//    failure (); // failed to read from DHT sensor
//  }
//  else {
////    sprintf (aux_buf, "[H:%d.%d,T:%d.%d]", h / 10, h % 10, t / 10, t % 10);
//    esp8266send (aux_buf);
//  }
//
//  goLowPower ();
//}

//void goLowPower ()
//{
//  sprintf (aux_buf, "AT+GSLP=", MEASUREMENTS_DELAY_S * 1000 - 250);
//  esp8266cmd (aux_buf);
//  sleepSeconds (MEASUREMENTS_DELAY_S);
//}

void sTone (unsigned note, unsigned len)
{
	UART_TERMINAL_Print_String_NL("Tone was Played:");
//	unsigned duration = 1000U / len;
//
//	tone (BUZZER_PIN, note, duration);
//	delay (duration * 1.3);
//	noTone (BUZZER_PIN);
}


void SEND_FAILED_MESSAGE ()
{
	UART_TERMINAL_Print_String_NL("THE PROCESSS FAILED:");
	print_UART_buffer();
}

void esp8266shutdown ()
{
	set_CH_PD_LOW();
	set_RESET_HIGH();
//	GPIO_setOutputLowOnPin(ESP8266_CH_PD_PORT, ESP8266_CH_PD_PIN);
//	digitalWrite (ESP8266_CH_PD_PIN, LOW);
	time_delay(1);
}

void esp8266poweron ()
{
	set_CH_PD_HIGH();
//	set_RESET_LOW();
//	GPIO_setOutputHighOnPin(ESP8266_CH_PD_PORT, ESP8266_CH_PD_PIN);
//	digitalWrite (ESP8266_CH_PD_PIN, HIGH);
//	delay(1000);
	time_delay(5);

//	while (Serial.available () > 0) {
//		Serial.read ();
//  }

}

void esp8266reboot ()
{
	__bis_SR_register(GIE);

//	while(1)
	{
		esp8266shutdown();
		esp8266poweron();

//		UART_TERMINAL_Print_String_NL("New Line");
	}



	reset_UART_buffer_index();

	esp8266cmd("AT");
	esp8266cmd("AT+CIPMODE=0");
	esp8266cmd("AT+CIPMUX=0");
	esp8266cmd("AT+CIPSTART=\"TCP\",\"" SRV_ADDR "\"," SRV_PORT);
}

void esp8266waitrx (const char * cmd)
{
	unsigned retry_cnt = 0;
	uint8_t dAvaliable = UART_DATA_AVALIABLE();

	delay(250);

	while((dAvaliable == 0))
	{
		++retry_cnt;
		delay(500);

	    if (retry_cnt > MAX_RETRY_CNT) {
	      failure (); // Failed to read from ESP8266

	      }

	    dAvaliable = UART_DATA_AVALIABLE();

//  while (!Serial.available ()) {
//    ++retry_cnt;
//    delay (100);
//
//    if (retry_cnt > MAX_RETRY_CNT) {
//      failure (); // Failed to read from ESP8266
//    }
  }
}

void esp8266rx (const char * cmd)
{
	// Make note of the UART_array size.
	unsigned bytes_available = UART_DATA_AVALIABLE();

	// Copy info in buffer over to in_buf array.
	copy_UART_buffer(in_buf);

	UART_TERMINAL_Print_String_NL(in_buf);


//  unsigned offset = 0;
//
//  while ((bytes_available = Serial.available ())) {
//    offset += Serial.readBytes (in_buf + offset, bytes_available);
//  }

//  if (offset == 0) {
//    return;
//  }

  in_buf[bytes_available+1] = '\0';

  if (strstr (in_buf, "ERROR") != NULL) {
    failure (); // ESP8266 returned error
  }
}

void esp8266cmd (const char * cmd)
{
//	UART_TERMINAL_Print_String_NL(cmd);

	__bis_SR_register(GIE);
	Print_String_NL(cmd);


//	Serial.println (cmd);
//	Serial.flush ();
	esp8266waitrx(cmd);
	esp8266rx(cmd);
}

void esp8266send (const char * packet)
{
  unsigned l = strlen (packet) + 2U;
  sprintf (out_buf, "AT+CIPSEND=%d", l);

  esp8266cmd (out_buf);
  esp8266cmd (packet);
}

void failure ()
{
	SEND_FAILED_MESSAGE();
	time_delay(10);
//  pinMode (RED_LED, OUTPUT);
//
//  unsigned cnt = 0;
//  unsigned tone_interval = 1U;
//
//  while (true) {
//    digitalWrite (RED_LED, (cnt % 2) ? HIGH : LOW);
//    sleep (ALARM_DELAY_MS);
//
//    if ((cnt % tone_interval) == 0) {
//      SEND_FAILED_MESSAGE ();
//      tone_interval *= 10U;
//    }
//
//    ++cnt;
//  }
}


#endif /* DRIVERLIB_MSP430_LIB_TARGETS_ESP8266_H_ */
