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

#define SRV_ADDR "192.168.1.100"
//#define SRV_ADDR "192.168.4.1"
#define SRV_PORT "9977"

//		CH_PD: Port and Pin
#define ESP8266_CH_PD_PORT GPIO_PORT_P1
#define ESP8266_CH_PD_PIN  GPIO_PIN6

//		Reset: Port and Pin
#define ESP8266_RESET_PORT GPIO_PORT_P6
#define ESP8266_RESET_PIN  GPIO_PIN6

#define MAX_IN_BUF_SZ 64U
#define MAX_OUT_BUF_SZ 64U
#define MAX_AUX_BUF_SZ 32U

//#define MEASUREMENTS_DELAY_S 60U
#define MAX_RETRY_CNT 100U

char in_buf[MAX_IN_BUF_SZ];
char out_buf[MAX_OUT_BUF_SZ];
char aux_buf[MAX_AUX_BUF_SZ];

//   CH_PD Pin Funcitons
void init_CH_PD_PIN(void);
void set_CH_PD_LOW(void);
void set_CH_PD_HIGH(void);

//   RESET Pin Functions
void init_RESET_PIN(void);
void set_RESET_HIGH(void);
void set_RESET_LOW(void);

//   Admin Functions
void ESP8266_setup();
void esp8266reboot();
void esp8266shutdown();
void esp8266poweron();

//   Functions

void ESP8266_setup()
{
	// Init A1
    UART_TERMINAL_init();

    // Init A0
    UART_init(115200);

	//pinMode (ESP8266_CH_PD_PIN, OUTPUT);
	init_CH_PD_PIN();
	init_RESET_PIN();

    esp8266reboot();

}

//char my_network_cmd[] = "AT+CWJAP= TP-LINK_7E50DA, 98195916";
void esp8266reboot()
{
	__bis_SR_register(GIE);
	esp8266shutdown();
	esp8266poweron();

}


void esp8266shutdown()
{
	set_CH_PD_LOW();
	set_RESET_LOW();
	time_delay(1);
}

void esp8266poweron()
{
	set_CH_PD_HIGH();
	set_RESET_HIGH();
	time_delay(30);

}

void esp8266waitrx (const char * cmd)
{
	unsigned retry_cnt = 0;
	uint8_t dAvaliable = UART_DATA_AVALIABLE();

	delay(350);

	while((dAvaliable == 0))
	{
		++retry_cnt;
		delay(500);

	    if (retry_cnt > MAX_RETRY_CNT) {
//	      failure (); // Failed to read from ESP8266

	      }

	    dAvaliable = UART_DATA_AVALIABLE();

  }
}

void esp8266rx (const char * cmd)
{
	// Make note of the UART_array size.
	unsigned bytes_available = UART_DATA_AVALIABLE();

	// Copy info in buffer over to in_buf array.
	copy_UART_buffer(in_buf);

//	UART_TERMINAL_Print_String_NL(in_buf);


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
//	  UART_TERMINAL_Print_String_NL("Device Returned the Value ERROR");
    failure (); // ESP8266 returned error
  }
}

void esp8266cmd (const char * cmd)
{
//	UART_TERMINAL_Print_String_NL(cmd);

	__bis_SR_register(GIE);
	reset_UART_buffer_index();
	Print_String_NL(cmd);
//	reset_UART_buffer_index();

//	Serial.println (cmd);
//	Serial.flush ();
	esp8266waitrx(cmd);
	esp8266rx(cmd);

	delay(50);
}

void esp8266send(const char * packet)
{
  unsigned l = strlen (packet) + 2U;
  sprintf (out_buf, "AT+CIPSEND=%d", l);

  esp8266cmd (out_buf);
  esp8266cmd (packet);
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
	GPIO_setOutputLowOnPin(ESP8266_RESET_PORT, ESP8266_RESET_PIN);
}

void set_RESET_HIGH(void)
{
	GPIO_setOutputHighOnPin(ESP8266_RESET_PORT, ESP8266_RESET_PIN);
}

void init_RESET_PIN(void)
{
	set_RESET_LOW();
	GPIO_setAsOutputPin(ESP8266_RESET_PORT, ESP8266_RESET_PIN);
	return;
}
void init_CH_PD_PIN(void)
{
	set_CH_PD_LOW();
	GPIO_setAsOutputPin(ESP8266_CH_PD_PORT, ESP8266_CH_PD_PIN);

	return;
}


void failure()
{
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

void example(void)
{
	reset_UART_buffer_index();
//	time_delay(11);
	reset_UART_buffer_index();

	esp8266cmd("AT");
	time_delay(2);
//	esp8266cmd("AT+RST");
//	time_delay(20);
//	esp8266cmd("AT+GMR"); // Request Firmware Version Type
//	esp8266cmd("AT+CWJAP="",""");


	// Use this
//	esp8266cmd("AT+CWJAP?");
//	time_delay(20);

	// Check to see which Networks are in your area
//	esp8266cmd("AT+CWLAP");
//	time_delay(20);

	// Join My network
	esp8266cmd("AT+CWJAP=\"TP-LINK_7E50DA\",\"98195916\"");
	time_delay(25);

//	esp8266cmd("AT+CIFSR"); // Find the IP address of the module.
//	time_delay(2);

	esp8266cmd("AT+CIPMUX=1");
	time_delay(20);

	esp8266cmd("AT+CIPSTART=\"TCP\",\"www.google.com\",80");
	time_delay(20);

	esp8266cmd("AT+CIPSEND=18");
	time_delay(25);

	esp8266cmd("GET / HTTP/1.0\r\n");

//	esp8266cmd("AT+CIPMODE=0");
//	esp8266cmd("AT+CIPMUX=0");
//	esp8266cmd("AT+CIPSTART=\"TCP\",\"192.168.1.100\",\"9977\"");

//	esp8266cmd("AT+CIPSTART=0,\"TCP\",\"192.168.3.116\",8080");//0,\"TCP\",\"8.8.8.8\",80");
	time_delay(20);

	//	esp8266cmd("AT+RST");




	while(1)
	{
		time_delay(40);

	}
}


#endif /* DRIVERLIB_MSP430_LIB_TARGETS_ESP8266_H_ */
