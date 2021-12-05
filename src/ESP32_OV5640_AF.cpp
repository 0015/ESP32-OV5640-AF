/*
  ESP32_OV5640_AF.cpp - Library for OV5640 Auto Focus (ESP32 Camera)
  Created by Eric Nam, December 08, 2021.
  Released into the public domain.
*/

#include "ESP32_OV5640_AF.h"

OV5640::OV5640() {
  isOV5640 = false;
}

bool OV5640::start(sensor_t* _sensor) {
  sensor = _sensor;
  uint8_t vid, pid;
  vid = sensor->get_reg(sensor, OV5640_CHIPID_HIGH, 0xff);
  pid = sensor->get_reg(sensor, OV5640_CHIPID_LOW, 0xff);

  isOV5640 = (vid == 0x56) && (pid == 0x40);
  return isOV5640;
}

uint8_t OV5640::focusInit() {
  if (!isOV5640) return -1;

  uint16_t i;
  uint16_t addr = 0x8000;
  uint8_t state = 0x8F;
  uint8_t rc = 0;
  rc = sensor->set_reg(sensor, 0x3000, 0xff, 0x20);  //reset
  if (rc < 0) return -1;

  for (i = 0; i < sizeof(OV5640_AF_Config); i++) {
    rc = sensor->set_reg(sensor, addr, 0xff, OV5640_AF_Config[i]);
    if (rc < 0) return -1;

    addr++;
  }

  sensor->set_reg(sensor, OV5640_CMD_MAIN, 0xff, 0x00);
  sensor->set_reg(sensor, OV5640_CMD_ACK, 0xff, 0x00);
  sensor->set_reg(sensor, OV5640_CMD_PARA0, 0xff, 0x00);
  sensor->set_reg(sensor, OV5640_CMD_PARA1, 0xff, 0x00);
  sensor->set_reg(sensor, OV5640_CMD_PARA2, 0xff, 0x00);
  sensor->set_reg(sensor, OV5640_CMD_PARA3, 0xff, 0x00);
  sensor->set_reg(sensor, OV5640_CMD_PARA4, 0xff, 0x00);
  sensor->set_reg(sensor, OV5640_CMD_FW_STATUS, 0xff, 0x7f);
  sensor->set_reg(sensor, 0x3000, 0xff, 0x00);

  i = 0;
  do {
    state = sensor->get_reg(sensor, 0x3029, 0xff);
    delay(5);
    i++;
    if (i > 1000) return 1;
  } while (state != FW_STATUS_S_IDLE);

  return 0;
}

uint8_t OV5640::autoFocusMode() {
  if (!isOV5640) return -1;

  uint8_t rc = 0;
  uint8_t temp = 0;
  uint16_t retry = 0;
  rc = sensor->set_reg(sensor, OV5640_CMD_MAIN, 0xff, 0x01);
  rc = sensor->set_reg(sensor, OV5640_CMD_MAIN, 0xff, 0x08);
  do {
    temp = sensor->get_reg(sensor, OV5640_CMD_ACK, 0xff);
    retry++;
    if (retry > 1000) return 2;
    delay(5);
  } while (temp != 0x00);
  rc = sensor->set_reg(sensor, OV5640_CMD_ACK, 0xff, 0x01);
  rc = sensor->set_reg(sensor, OV5640_CMD_MAIN, 0xff, AF_CONTINUE_AUTO_FOCUS);
  retry = 0;
  do {
    temp = sensor->get_reg(sensor, OV5640_CMD_ACK, 0xff);
    retry++;
    if (retry > 1000) return 2;
    delay(5);
  } while (temp != 0x00);
  return 0;
}

uint8_t OV5640::getFWStatus() {
  if (!isOV5640) return -1;
  uint8_t rc = sensor->get_reg(sensor, OV5640_CMD_FW_STATUS, 0xff);
  return rc;
}