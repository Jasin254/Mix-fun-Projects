import pyb
import os

# Configure peripherals
spi_sd = pyb.SPI(2, pyb.SPI.MASTER, baudrate=42000000, polarity=0, phase=0)
spi_codec = pyb.SPI(1, pyb.SPI.MASTER, baudrate=16000000, polarity=0, phase=0)
sd_cs = pyb.Pin('PE3', pyb.Pin.OUT_PP)
codec_cs = pyb.Pin('PD14', pyb.Pin.OUT_PP)
codec_reset = pyb.Pin('PD12', pyb.Pin.OUT_PP)

# Configure audio codec
def codec_init():
    codec_reset.high()
    pyb.delay(5)
    codec_reset.low()
    pyb.delay(5)

    codec_cs.low()
    spi_codec.send(0x02) # write to power control register
    spi_codec.send(0x99) # enable headphone and speaker outputs
    codec_cs.high()

# Read audio data from file and send to audio codec
def play_audio(file):
    dma = pyb.DMA(pyb.DMA.SPI1_TX, 0x4001300C, direction=pyb.DMA_MEM_TO_PERIPH, circular=True, data_size=pyb.DMA_HALF_WORD)
    dma.start()

    while True:
        # Read audio data from file
        buffer = bytearray(4096)
        bytes_read = file.readinto(buffer)

        if bytes_read == 0:
            break

        # Send audio data to audio codec via SPI DMA
        for i in range(0, bytes_read, 2):
            while not dma.transfer_complete():
                pass
            dma.write(buffer[i:i+2])

    dma.stop()

# Mount SD card
sd = pyb.SDCard(spi_sd, sd_cs)
os.mount(sd, '/sd')

# Open audio file and play audio
with open('/sd/audio.wav', 'rb') as f:
    codec_init()
    play_audio(f)

# Unmount SD card
os.umount('/sd')
