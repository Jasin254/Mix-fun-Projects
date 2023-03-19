#![no_main]
#![no_std]

use panic_halt as _;

use cortex_m_rt::entry;
use stm32f4xx_hal::{
    dma::Dma,
    gpio::{self, Output, PushPull},
    pac,
    prelude::*,
    spi::Spi,
    sdio::{self, Sdio},
};

use core::fmt::Write;

// Configure peripherals
#[entry]
fn main() -> ! {
    if let (Some(dp), Some(cp)) = (pac::Peripherals::take(), cortex_m::peripheral::take()) {
        let rcc = dp.RCC.constrain();
        let gpioa = dp.GPIOA.split();
        let gpiob = dp.GPIOB.split();
        let gpiod = dp.GPIOD.split();
        let gpioe = dp.GPIOE.split();

        // Configure SPI for SD card
        let sd_cs = gpioe.pe3.into_push_pull_output().set_speed(gpio::Speed::High);
        let sd_spi = Spi::new(
            dp.SPI2,
            (
                gpio::AlternateFunction::AF5,
                gpioa.pa3.into_alternate_af5(),
                gpioa.pa4.into_alternate_af5(),
                sd_cs,
            ),
            sdio::MODE,
            42_000_000.hz(),
            rcc.apb1,
        );

        let sdio = Sdio::new(sd_spi);

        // Configure SD card
        let mut sd = sdio::Sd::new(sdio, sd_cs);
        sd.init().unwrap();

        // Configure SPI for audio codec
        let codec_cs = gpiod.pd14.into_push_pull_output().set_speed(gpio::Speed::High);
        let codec_reset = gpiod.pd12.into_push_pull_output().set_speed(gpio::Speed::High);
        let codec_spi = Spi::new(
            dp.SPI1,
            (
                gpio::AlternateFunction::AF5,
                gpiob.pb3.into_alternate_af5(),
                gpiob.pb5.into_alternate_af5(),
                codec_cs,
            ),
            sdio::MODE,
            16_000_000.hz(),
            rcc.apb2,
        );

        // Configure audio codec
        let mut codec = AudioCodec::new(codec_spi, codec_cs, codec_reset);
        codec.init().unwrap();

        // Open audio file and play audio
        if let Ok(file) = sd.open("/audio.wav") {
            codec.play_audio(&file);
        }
    }

    loop {}
}

struct AudioCodec<SPI, CS, RESET>
where
    SPI: embedded_hal::blocking::spi::Transfer<u8> + embedded_hal::blocking::spi::Write<u8>,
    CS: Output<PushPull>,
    RESET: Output<PushPull>,
{
    spi: SPI,
    cs: CS,
    reset: RESET,
}

impl<SPI, CS, RESET> AudioCodec<SPI, CS, RESET>
where
    SPI: embedded_hal::blocking::spi::Transfer<u8> + embedded_hal::blocking::spi::Write<u8>,
    CS: Output<PushPull>,
    RESET: Output<PushPull>,
{
    pub fn new(spi: SPI, cs: CS, reset: RESET) -> Self {
        Self { spi, cs, reset }
    }

    pub fn init(&mut self) -> Result<(), ()> {
        self.reset.set_low().unwrap();
        cortex
    cortex_m::asm::delay(1_000_000);
    self.reset.set_high().unwrap();
    cortex_m::asm::delay(1_000_000);

    // Initialize audio codec registers
    self.cs.set_low().unwrap();
    self.spi.write(&[0x20, 0x77]).unwrap(); // power control
    self.spi.write(&[0x21, 0x01]).unwrap(); // left headphone volume
    self.spi.write(&[0x22, 0x01]).unwrap(); // right headphone volume
    self.spi.write(&[0x24, 0x01]).unwrap(); // digital audio interface
    self.spi.write(&[0x25, 0x00]).unwrap(); // sampling rate control
    self.spi.write(&[0x26, 0x00]).unwrap(); // digital audio interface
    self.spi.write(&[0x27, 0x00]).unwrap(); // digital audio interface
    self.spi.write(&[0x30, 0x03]).unwrap(); // clock control
    self.spi.write(&[0x32, 0x00]).unwrap(); // codec input select
    self.spi.write(&[0x33, 0x30]).unwrap(); // jack detect control
    self.cs.set_high().unwrap();

    Ok(())
}

pub fn play_audio(&mut self, file: &sdio::File) {
    let mut dma = Dma::new(self.spi);

    // Configure DMA stream
    let stream = dma.streams.5;
    let channel = stm32f4xx_hal::dma::dma1::C6;
    let priority = stm32f4xx_hal::dma::Priority::High;
    let mut transfer = stm32f4xx_hal::dma::Transfer::init(
        stream,
        channel,
        priority,
        None,
        None,
        stm32f4xx_hal::dma::Direction::FromMemory,
        self.spi,
    );
    transfer.enable_double_buffer();
    transfer.set_peripheral_size(stm32f4xx_hal::dma::DataSize::Byte);
    transfer.set_memory_size(stm32f4xx_hal::dma::DataSize::Byte);
    transfer.set_peripheral_increment(stm32f4xx_hal::dma::Increment::None);
    transfer.set_memory_increment(stm32f4xx_hal::dma::Increment::Byte);
    transfer.set_transfer_complete_interrupt(true);
    transfer.set_transfer_error_interrupt(true);

    // Read and send audio data to codec via DMA
    let mut buffer1 = [0u8; 1024];
    let mut buffer2 = [0u8; 1024];
    let mut current_buffer = &mut buffer1[..];
    loop {
        let read_bytes = file.read(current_buffer).unwrap_or(0);
        if read_bytes == 0 {
            break;
        }
        transfer.start(read_bytes as u16, current_buffer.as_ptr() as u32);
        while !transfer.get_transfer_complete_flag() {}
        current_buffer = if current_buffer.as_ptr() == buffer1.as_ptr() {
            &mut buffer2[..read_bytes]
        } else {
            &mut buffer1[..read_bytes]
        };
    }
}
}
