#define INIT_COMMS 		0x55  // 0101 0101
#define MASTER_ID  		0x65  // 0110 0101
#define PERIPH1_ID 		0xA5  // 1010 0101

void clearSerialBuffer()
{
	while (Serial.available() > 0) Serial.read();
}

void decodeSerialLine()
{

}

// Byte 1 = 01010101
// Byte 2 = 01010101
// Byte 3 = Peripheral ID
// Byte 4 = Command
