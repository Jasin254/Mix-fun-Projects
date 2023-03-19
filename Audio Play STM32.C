#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "ff.h"
#include "waveplayer.h"

/* Define SPI and GPIO pins for SD card */
#define SD_SPI                      SPI1
#define SD_SPI_CLK                  RCC_APB2Periph_SPI1
#define SD_SPI_SCK_PIN              GPIO_Pin_5
#define SD_SPI_SCK_GPIO_PORT        GPIOA
#define SD_SPI_SCK_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define SD_SPI_MISO_PIN             GPIO_Pin_6
#define SD_SPI_MISO_GPIO_PORT       GPIOA
#define SD_SPI_MISO_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define SD_SPI_MOSI_PIN             GPIO_Pin_7
#define SD_SPI_MOSI_GPIO_PORT       GPIOA
#define SD_SPI_MOSI_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define SD_CS_PIN                   GPIO_Pin_3
#define SD_CS_GPIO_PORT             GPIOB
#define SD_CS_GPIO_CLK              RCC_AHB1Periph_GPIOB

/* Define SPI and GPIO pins for audio codec */
#define CODEC_SPI                   SPI2
#define CODEC_SPI_CLK               RCC_APB1Periph_SPI2
#define CODEC_SPI_SCK_PIN           GPIO_Pin_13
#define CODEC_SPI_SCK_GPIO_PORT     GPIOB
#define CODEC_SPI_SCK_GPIO_CLK      RCC_AHB1Periph_GPIOB
#define CODEC_SPI_MISO_PIN          GPIO_Pin_14
#define CODEC_SPI_MISO_GPIO_PORT    GPIOB
#define CODEC_SPI_MISO_GPIO_CLK     RCC_AHB1Periph_GPIOB
#define CODEC_SPI_MOSI_PIN          GPIO_Pin_15
#define CODEC_SPI_MOSI_GPIO_PORT    GPIOB
#define CODEC_SPI_MOSI_GPIO_CLK     RCC_AHB1Periph_GPIOB
#define CODEC_CS_PIN                GPIO_Pin_12
#define CODEC_CS_GPIO_PORT          GPIOB
#define CODEC_CS_GPIO_CLK           RCC_AHB1Periph_GPIOB
#define CODEC_RESET_PIN             GPIO_Pin_2
#define CODEC_RESET_GPIO_PORT       GPIOE
#define CODEC_RESET_GPIO_CLK        RCC_AHB1Periph_GPIOE

/* Define audio file name */
#define AUDIO_FILE_NAME             "audio.wav"

/* Private variables */
FATFS fs;
FIL file;
WAVE_FormatTypeDef wave_format;
uint8_t wave_data[1024];

/* Private functions */
void GPIO_Configuration(void);
void SPI_Configuration(void);
void Codec_Configuration(void);
void Play_Audio(void);

int main(void)
{
  /* Initialize GPIO and SPI */
  GPIO_Configuration();
  SPI_Configuration();

  /* Initialize audio codec */
  Codec_Configuration();

  /* Mount file system */
  if (f_mount(&fs, "", 0) != FR_OK)
  {
    /* Error occurred while mounting file system */
    while (1);
  }

  /* Open audio file */
  if (f_open(&file, AUDIO_FILE_NAME, FA_READ) != FR_OK)
  {
    /* Error occurred while opening audio file */
    while (1);
  }

  /* Read wave format */
  if (Read_WaveFormat(&file, &wave_format) != 0)
  {
    /* Error occurred while reading wave format */
    while (1
}

/* Play audio */
Play_Audio();

/* Close audio file */
f_close(&file);

/* Unmount file system */
f_mount(NULL, "", 0);

while (1);
}

void GPIO_Configuration(void)
{
GPIO_InitTypeDef GPIO_InitStructure;

/* Enable GPIO clocks */
RCC_AHB1PeriphClockCmd(SD_CS_GPIO_CLK | CODEC_CS_GPIO_CLK | CODEC_RESET_GPIO_CLK, ENABLE);

/* Configure SD card CS pin */
GPIO_InitStructure.GPIO_Pin = SD_CS_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(SD_CS_GPIO_PORT, &GPIO_InitStructure);

/* Configure audio codec CS pin */
GPIO_InitStructure.GPIO_Pin = CODEC_CS_PIN;
GPIO_Init(CODEC_CS_GPIO_PORT, &GPIO_InitStructure);

/* Configure audio codec RESET pin */
GPIO_InitStructure.GPIO_Pin = CODEC_RESET_PIN;
GPIO_Init(CODEC_RESET_GPIO_PORT, &GPIO_InitStructure);
}

void SPI_Configuration(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef SPI_InitStructure;

/* Enable SPI clocks */
RCC_APB2PeriphClockCmd(SD_SPI_CLK, ENABLE);
RCC_APB1PeriphClockCmd(CODEC_SPI_CLK, ENABLE);

/* Configure SPI pins for SD card */
GPIO_InitStructure.GPIO_Pin = SD_SPI_SCK_PIN | SD_SPI_MISO_PIN | SD_SPI_MOSI_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(SD_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

GPIO_PinAFConfig(SD_SPI_SCK_GPIO_PORT, GPIO_PinSource5, GPIO_AF_SPI1);
GPIO_PinAFConfig(SD_SPI_MISO_GPIO_PORT, GPIO_PinSource6, GPIO_AF_SPI1);
GPIO_PinAFConfig(SD_SPI_MOSI_GPIO_PORT, GPIO_PinSource7, GPIO_AF_SPI1);

/* Configure SPI pins for audio codec */
GPIO_InitStructure.GPIO_Pin = CODEC_SPI_SCK_PIN | CODEC_SPI_MISO_PIN | CODEC_SPI_MOSI_PIN;
GPIO_Init(CODEC_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

GPIO_PinAFConfig(CODEC_SPI_SCK_GPIO_PORT, GPIO_PinSource13, GPIO_AF_SPI2);
GPIO_PinAFConfig(CODEC_SPI_MISO_GPIO_PORT, GPIO_PinSource14, GPIO_AF_SPI2);
GPIO_PinAFConfig(CODEC_SPI_MOSI_GPIO_PORT, GPIO_PinSource15, GPIO_AF_SPI2);

/* Configure SPI for SD card */
SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
SPI_Init(SD_SPI, &SPI_InitStructure);

/* Configure SPI for audio codec */
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
SPI_Init(CODEC_SPI

, &SPI_InitStructure);

/* Enable SPIs */
SPI_Cmd(SD_SPI, ENABLE);
SPI_Cmd(CODEC_SPI, ENABLE);
}

void Codec_Configuration(void)
{
/* Reset audio codec */
CODEC_RESET_GPIO_PORT->BSRRH = CODEC_RESET_PIN;
Delay(5);
CODEC_RESET_GPIO_PORT->BSRRL = CODEC_RESET_PIN;
Delay(5);

/* Configure audio codec */
CS43L22_Init();

/* Set volume */
CS43L22_SetVolume(70);

/* Configure audio interface */
CODEC_IO_Write(CODEC_I2C_ADDRESS, 0x04, 0x03);
}

void SD_Configuration(void)
{
/* Configure SD card */
if (SD_Init() != SD_OK) {
Error_Handler();
}

/* Mount file system */
if (f_mount(&fs, "", 0) != FR_OK) {
Error_Handler();
}
}

void Error_Handler(void)
{
while (1);
}

void Delay(__IO uint32_t nCount)
{
while(nCount--) {
}
}

void Play_Audio(void)
{
uint8_t buffer[4096];
UINT bytes_read;
int i;

/* Configure DMA for SPI */
SPI_I2S_DMACmd(CODEC_SPI, SPI_I2S_DMAReq_Tx, ENABLE);

/* Loop and play audio /
while (1) {
/ Read data from audio file */
if (f_read(&file, buffer, sizeof(buffer), &bytes_read) != FR_OK) {
Error_Handler();
}

scss
Copy code
/* Check if end of file has been reached */
if (bytes_read == 0) {
  break;
}

/* Write data to audio codec */
for (i = 0; i < bytes_read; i += 2) {
  while (!SPI_I2S_GetFlagStatus(CODEC_SPI, SPI_I2S_FLAG_TXE));
  SPI_I2S_SendData(CODEC_SPI, ((uint16_t)buffer[i + 1] << 8) | buffer[i]);
}
}

/* Stop DMA */
SPI_I2S_DMACmd(CODEC_SPI, SPI_I2S_DMAReq_Tx, DISABLE);
}
           
int main(void)
{
/* System initialization */
SystemInit();

/* Configure peripherals */
RCC_Configuration();
GPIO_Configuration();
NVIC_Configuration();
SPI_Configuration();
Codec_Configuration();
SD_Configuration();

/* Open audio file */
if (f_open(&file, "audio.wav", FA_READ) != FR_OK) {
Error_Handler();
}

/* Play audio */
Play_Audio();

/* Close audio file */
f_close(&file);

/* Infinite loop */
while (1);
}
