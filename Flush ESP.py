import subprocess

# Set the path to the esptool.py utility
esptool_path = "/path/to/esptool.py"

# Set the serial port of the ESP32 board
serial_port = "/dev/ttyUSB0"

# Set the path to the binary file that you want to flash
binary_file_path = "/path/to/binary/file.bin"

# Flash the binary file to the ESP32 board
subprocess.run([esptool_path, "--chip", "esp32", "--port", serial_port, "--baud", "115200", "write_flash", "-z", "--flash_mode", "dio", "--flash_freq", "80m", "--flash_size", "detect", "0x1000", binary_file_path])
