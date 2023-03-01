use std::time::Duration;
use arduino_uno::hal::port::mode::{Output, Input};
use arduino_uno::hal::port::portd::{PD3, PD5};
use arduino_uno::prelude::*;
use arduino_uno::delay_ms;

fn main() {
    let mut motor_1 = arduino_uno::hal::port::portd::PD3.into_output(&mut arduino_uno::hal::port::PORTD);
    let mut motor_2 = arduino_uno::hal::port::portd::PD5.into_output(&mut arduino_uno::hal::port::PORTD);
    
    loop {
        // Forward direction
        motor_1.set_high().unwrap();
        motor_2.set_high().unwrap();
        delay_ms(1000);
        
        // Stop motors
        motor_1.set_low().unwrap();
        motor_2.set_low().unwrap();
        delay_ms(500);
        
        // Reverse direction
        motor_1.set_low().unwrap();
        motor_2.set_high().unwrap();
        delay_ms(1000);
        
        // Stop motors
        motor_1.set_low().unwrap();
        motor_2.set_low().unwrap();
        delay_ms(500);
    }
}
