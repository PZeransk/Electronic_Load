#include "MCP4921.h"

uint16_t prepareData(DAC_DATA *data_struct){
    uint16_t temp = data_struct->setup_data + data_struct->v_out_val;
    return temp;
}
/*
void sendData(SPIClass *spi, uint16_t data){
  spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW); //pull SS slow to prep other end for transfer
  spi->transfer16(data);
  digitalWrite(VSPI_SS, HIGH); //pull ss high to signify end of data transfer
  spi->endTransaction();
}*/