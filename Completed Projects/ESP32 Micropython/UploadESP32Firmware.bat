esptool --chip esp32 -p COM11 erase_flash
esptool --chip esp32 -p COM11 write_flash -z 0x1000 Z:/ESP32_FIRMWARE.bin