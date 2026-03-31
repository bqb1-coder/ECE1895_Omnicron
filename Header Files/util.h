#define UART_INIT_COMMS 		0x55  // 0101 0101
#define UART_MASTER_ID  		0x65  // 0110 0101
#define UART_PERIPH1_ID 		0xA5  // 1010 0101

void clearSerialBuffer()
{
	while (Serial.available() > 0) Serial.read();
}

// Byte 1 = 01010101
// Byte 2 = 01010101
// Byte 3 = Peripheral ID
// Byte 4 = Command


void writeRegisterTo(uint8_t reg, uint8_t val, int slave_address)
{
  Wire.beginTransmission(slave_address);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

uint8_t readRegisterFrom(uint8_t reg, int slave_address)
{
  Wire.beginTransmission(slave_address);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(slave_address, 1);
  return Wire.read();
}
