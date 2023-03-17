import machine
import sdcard
import os
import dht

# Initialize the SD Card
sd = sdcard.SDCard(machine.SPI(1), machine.Pin('X5'))
os.mount(sd, '/sd')

# Create a file to store the data
filename = '/sd/data.txt'
with open(filename, 'w') as f:
    f.write('Temperature (C),Humidity (%)\n')

# Initialize the DHT sensor
dht_pin = machine.Pin('X4', machine.Pin.OUT, machine.Pin.PULL_UP)
dht_sensor = dht.DHT11(dht_pin)

while True:
    # Read temperature and humidity data from the sensor
    dht_sensor.measure()
    temperature = dht_sensor.temperature()
    humidity = dht_sensor.humidity()

    # Write the data to the file on the SD Card
    with open(filename, 'a') as f:
        f.write('{},{}\n'.format(temperature, humidity))

    # Wait for some time before reading the sensor again
    machine.delay(1000)
