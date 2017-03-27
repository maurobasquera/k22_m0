/*
 * modbusMaster.h
 *
 *  Created on: 20/03/2017
 *      Author: mauro
 */

#ifndef SOURCES_MODBUSMASTER_H_
#define SOURCES_MODBUSMASTER_H_

#define READ_HOLDING_REGISTERS 3
#define	PRESET_MULTIPLE_REGISTERS 16

typedef struct
{
  // specific packet info
  unsigned char id;
  unsigned char function;
  unsigned int address;
  unsigned int no_of_registers;
//  unsigned int *register_array;
  unsigned char buffer;

  // modbus information counters
  unsigned int requests;
  unsigned int successful_requests;
  unsigned long total_errors;
  unsigned int retries;
  unsigned int timeout;
  unsigned int incorrect_id_returned;
  unsigned int incorrect_function_returned;
  unsigned int incorrect_bytes_returned;
  unsigned int checksum_failed;
  unsigned int buffer_errors;

  // modbus specific exception counters
  unsigned int illegal_function;
  unsigned int illegal_data_address;
  unsigned int illegal_data_value;
  unsigned char misc_exceptions;

  // connection status of packet
  unsigned char connection;

}Packet;

int regs_rw;
static Packet pack = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// function definitions
//unsigned int modbus_update(Packet *pack);
void modbus_configure();


#endif /* SOURCES_MODBUSMASTER_H_ */
