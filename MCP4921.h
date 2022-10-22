#pragma once
#include <SPI.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <cstdint>

#define VSPI_MISO 26
#define VSPI_MOSI 27
#define VSPI_SCLK 14
#define VSPI_SS   12

#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
#define VSPI FSPI
#endif

static const int spiClk = 1000000; // 1 MHz

struct DAC_DATA
{
    uint16_t setup_data;
    uint16_t v_out_val;
}DAC_DATA;

enum setup{
    //All data will be send with 1x gain
    MCP4921_WRITE_BUFFERED   = 0x7;
    MCP4921_WRITE_UNBUFFERED = 0x3;
    MCP4921_STOP             = 0x2;
}

uint16_t prepareData(DAC_DATA *data_struct);

void sendData(SPIClass *spi, uint16_t data){
  spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW); //pull SS slow to prep other end for transfer
  spi->transfer16(data);
  digitalWrite(VSPI_SS, HIGH); //pull ss high to signify end of data transfer
  spi->endTransaction();
}


