/*
 * modbusMaster.c
 *
 *  Created on: 20/03/2017
 *      Author: mauro
 */
#include "ASerialLdd1.h"
#include "sleepModbus.h"
#include "indicationModbus.h"
#include "BitIoLdd1.h"
#include "enableModbus.h"
#include "BitIoLdd2.h"
#include "timeout.h"
#include "modbusSerial.h"
#include "delay.h"
#include "modbusMaster.h"
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "red.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "MCUC1.h"
#include "green.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "blue.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "delay.h"
//#include "adc.h"
#include "main_header.h"
#include "math.h"

// modbus specific exceptions
#define ILLEGAL_FUNCTION 1
#define ILLEGAL_DATA_ADDRESS 2
#define ILLEGAL_DATA_VALUE 3

unsigned char transmission_Flag;
unsigned char messageOkFlag, messageErrFlag;
unsigned char lixoOverflow;

#define BUFFER_SIZE 128

unsigned int timeout = 1000; // timeout em ms
unsigned int polling = 200; // polling em ms
unsigned int error_max = 5; // numero maximo de erros
unsigned int baud = 9600; // baudrate

unsigned char frame[BUFFER_SIZE]; // frame utilizado para enviar
unsigned char frame_receive[BUFFER_SIZE]; // frame utilizado para receber
unsigned int T1_5; // timeout entre chars em us
unsigned int T3_5; // delay em us para iniciar e terminar transmissao

unsigned int total_no_of_packets;
unsigned int poll_flag;
unsigned int timeout_flag = 0;
unsigned int timeout_total = 0;
unsigned int error_total = 0;

int flag_poll;

static Packet packet; // estrutura utilizada para envio e armazenamento de informacoes

void verifyData();
void getData();
unsigned int calculateCRC(unsigned char bufferSize);
unsigned int calculateCRC_received(unsigned char bufferSize);
void sendPacket(unsigned char bufferSize);
void transmitData(unsigned char ID, unsigned char FC, unsigned int AD, unsigned int REG_NUM);
void modbus_update();
void modbus_master(unsigned char ID, unsigned char FC, unsigned int AD, unsigned int REG_NUM);
void poll(unsigned int poll_time);
void modbus_configure();

void modbus_master(unsigned char ID, unsigned char FC, unsigned int AD, unsigned int REG_NUM){

	if (flag_poll == 1){
	modbus_update();
	transmitData(ID,FC,AD,REG_NUM);
	getData();
	verifyData();
	}
}

void modbus_configure(){

	enableModbus_PutVal(FALSE);

	//configuracoes iniciais

	if (baud > 19200)
	{
		T1_5 = 750;
		T3_5 = 1750;
	}
	else
	{
		T1_5 = 15000000/baud; // 1T * 1.5 = T1.5
		T3_5 = 35000000/baud; // 1T * 3.5 = T3.5
	}

	// inicializa variaveis
  transmission_Flag = 1;
  messageOkFlag = 0;
  messageErrFlag = 0;
  modbusSerial_ClearTxBuf();
  modbusSerial_ClearRxBuf();
}

void modbus_update(){

    if (messageOkFlag) // se a mensagem esta correta apos ser verificada na funcao verifyData()
    {
    messageOkFlag = 0; // zera a flag para o proximo frame a ser analisado
    pack.successful_requests++; // ++ numero de transacoes ok
    transmission_Flag = 1; // habilita transmissao
    }

    if (messageErrFlag) // se a mensagem recebida nao esta correta
    {
    error_total++; // ++ numero total de erros
    messageErrFlag = 0; // zera a flag para o proximo frame ser analisado
    }

    if (error_total > error_max){ //se estourou o numero total de erros permitidos
    	transmission_Flag = 0;  // desabilita transmissao
    	red_On();
    }

	if (transmission_Flag) // atualiza numero total de erros
	{
		pack.total_errors = pack.timeout + pack.incorrect_id_returned + pack.incorrect_function_returned + pack.incorrect_bytes_returned +
							pack.checksum_failed + pack.buffer_errors + pack.illegal_function + pack.illegal_data_address +	 pack.illegal_data_value;
	}
}

void sendPacket(unsigned char bufferSize) // envia dados e entra
{
	if(transmission_Flag){

    modbusSerial_ClearTxBuf();
	enableModbus_PutVal(TRUE);
	unsigned char i = 0;

	for (i = 0; i < bufferSize; i++) modbusSerial_SendChar(frame[i]);

	sleepModbus_Waitus(T3_5);

	enableModbus_PutVal(FALSE);
	timeout_Reset();
	}
}

void transmitData(unsigned char ID, unsigned char FC, unsigned int AD, unsigned int REG_NUM)
{

	pack.id = ID;
	pack.function = FC;
	pack.address = AD;
	pack.no_of_registers = REG_NUM;

	extern unsigned int regs_send[];

	frame[0] = pack.id;
	frame[1] = pack.function;
	frame[2] = pack.address >> 8; // separa em dois bytes
	frame[3] = pack.address & 0xFF; //
	frame[4] = pack.no_of_registers >> 8; //
	frame[5] = pack.no_of_registers & 0xFF; //

  unsigned int crc16;

  // construct the frame according to the modbus function
  if (frame[1] == PRESET_MULTIPLE_REGISTERS)
  {
    unsigned char no_of_bytes = pack.no_of_registers * 2;
    unsigned char frameSize = 9 + no_of_bytes; // first 7 bytes of the array + 2 bytes CRC+ noOfBytes
    frame[6] = no_of_bytes; // number of bytes
    unsigned char index = 7; // user data starts at index 7
    unsigned int temp;
	unsigned char no_of_registers = pack.no_of_registers;

    for (unsigned char i = 0; i < no_of_registers; i++)
    {
      temp = regs_send[i]; // pega os dados do registrador utilizado para armazenar os valores a ser enviados
      frame[index] = temp >> 8;
      index++;
      frame[index] = temp & 0xFF;
      index++;
    }
    crc16 = calculateCRC(frameSize - 2);
    frame[frameSize - 2] = crc16 >> 8; // split crc into 2 bytes
    frame[frameSize - 1] = crc16 & 0xFF;
    sendPacket(frameSize);
  }
	else // READ_HOLDING_REGISTERS is assumed
	{
	crc16 = calculateCRC(6); // the first 6 bytes of the frame is used in the CRC calculation
    frame[6] = crc16 >> 8; // crc Lo
    frame[7] = crc16 & 0xFF; // crc Hi
    sendPacket(8); // a request with function 3, 4 & 6 is always 8 bytes in size
	}

  if (pack.id == 0) // check broadcast id
  {
			messageOkFlag = 1; // nao tem verificação de mensagem
  }

}

unsigned int calculateCRC(unsigned char bufferSize)
{
  unsigned int temp, temp2, flag;
  temp = 0xFFFF;
  for (unsigned char i = 0; i < bufferSize; i++)
  {
    temp = temp ^ frame[i];
    for (unsigned char j = 1; j <= 8; j++)
    {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag)
        temp ^= 0xA001;
    }
  }
  // Reverse byte order.
  temp2 = temp >> 8;

  temp = (temp << 8) | temp2;
  temp &= 0xFFFF;
  return temp; // the returned value is already stopped - crcLo byte is first & crcHi byte is last
}

unsigned int calculateCRC_received(unsigned char bufferSize)
{
  unsigned int temp, temp2, flag;
  temp = 0xFFFF;
  for (unsigned char i = 0; i < bufferSize; i++)
  {
    temp = temp ^ frame_receive[i];
    for (unsigned char j = 1; j <= 8; j++)
    {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag)
        temp ^= 0xA001;
    }
  }
  // Reverse byte order.
  temp2 = temp >> 8;

  temp = (temp << 8) | temp2;
  temp &= 0xFFFF;
  return temp; // the returned value is already stopped - crcLo byte is first & crcHi byte is last
}

void getData(){

	unsigned char buffer = 0;
	unsigned char overflow = 0;
	unsigned int timeout_count = 0;
	unsigned int exit_receive_loop = 0;

	pack.buffer = buffer;

	if(pack.id!=0){

	transmission_Flag = 0;
	indicationModbus_PutVal(TRUE);

	if(!exit_receive_loop){

	if (modbusSerial_GetCharsInRxBuf()){

		while (modbusSerial_GetCharsInRxBuf()){

			if (overflow) modbusSerial_RecvChar(&lixoOverflow);
			else{
				if (buffer == BUFFER_SIZE) {overflow = 1;}
				modbusSerial_RecvChar(&frame_receive[buffer]);
				buffer++;
			    pack.buffer = buffer;
			    }
					sleepModbus_Waitus(T1_5); // inter character time out
				}
						 if ((buffer > 0 && buffer < 5) || overflow)
							  {
								buffer = 0;
								pack.buffer_errors++;
								messageErrFlag = 1; // set an error
							  }

								modbusSerial_ClearRxBuf();
								exit_receive_loop = 1;
								timeout_flag = 0;
								transmission_Flag = 1;
	 	}
	timeout_GetTimeMS(&timeout_count);

	if (timeout_count>timeout){
								timeout_flag = 1;
								messageErrFlag = 1;
								pack.timeout++;
								exit_receive_loop = 1;
								transmission_Flag = 1;
	                          }
	    }
	}
}

void verifyData(){

	if (pack.id!=0){ // se nao tiver sido broadcast

	extern unsigned int regs_receive[];

	    if (pack.buffer > 0) // if there's something in the buffer continue
	    {
	      if (frame_receive[0] == pack.id) // check id returned
	      {
			// to indicate an exception response a slave will 'OR'
	        // the requested function with 0x80
					if ((frame_receive[1] & 0x80) == 0x80) // extract 0x80
					{
						// the third byte in the exception response packet is the actual exception
						switch (frame_receive[2])
						{
							case ILLEGAL_FUNCTION: pack.illegal_function++; break;
							case ILLEGAL_DATA_ADDRESS: pack.illegal_data_address++; break;
							case ILLEGAL_DATA_VALUE: pack.illegal_data_value++; break;
							default: pack.misc_exceptions++;
						}
						messageErrFlag = 1; // set an error
					}
					else // the response is valid
					{
						if (frame_receive[1] == pack.function) // check function number returned
						{
							// receive the frame according to the modbus function
							if (pack.function == PRESET_MULTIPLE_REGISTERS)
								{
								  unsigned int recieved_address = ((frame_receive[2] << 8) | frame_receive[3]);
								  unsigned int recieved_registers = ((frame_receive[4] << 8) | frame_receive[5]);
								  unsigned int recieved_crc = ((frame_receive[6] << 8) | frame_receive[7]); // combine the crc Low & High bytes
								  unsigned int calculated_crc = calculateCRC(6); // only the first 6 bytes are used for crc calculation

								  // check the whole packet
								  if (recieved_address == pack.address &&
								      recieved_registers == pack.no_of_registers &&
								      recieved_crc == calculated_crc)
								      messageOkFlag = 1; // message successful
								  else
								  {
								    pack.checksum_failed++;
								    messageErrFlag = 1;
								  }
								}

							else {
								  unsigned char no_of_registers = pack.no_of_registers;
								  unsigned char no_of_bytes = no_of_registers * 2;
								  if (frame_receive[2] == no_of_bytes) // check number of bytes returned
								  {
								    // combine the crc Low & High bytes
								    unsigned int recieved_crc = ((frame_receive[pack.buffer - 2] << 8) | frame_receive[pack.buffer - 1]);
								    unsigned int calculated_crc = calculateCRC_received(pack.buffer - 2);

								    if (calculated_crc == recieved_crc) // verify checksum
								    {
								      unsigned char index = 3;
											for (unsigned char i = 0; i < no_of_registers; i++)
								      {
								        // start at the 4th element in the recieveFrame and combine the Lo byte
												regs_receive[i] = (frame_receive[index] << 8) | frame_receive[index + 1];
								        index += 2;
								      }
								      messageOkFlag = 1; // message successful
								    }
								    else // checksum failed
								    {
								      pack.checksum_failed++;
								      messageErrFlag = 1; // set an error
								    }
								  }
								  else // incorrect number of bytes returned
								  {
								    pack.incorrect_bytes_returned++;
								    messageErrFlag = 1; // set an error
								  }
								}
						}
						else // incorrect function number returned
						{
							pack.incorrect_function_returned++;
							messageErrFlag = 1; // set an error
						}
					} // check exception response
				}
				else // incorrect id returned
				{
					pack.incorrect_id_returned++;
					messageErrFlag = 1; // set an error
				}
			} // check buffer
	}
} // check message booleans
