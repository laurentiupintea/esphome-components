#include "dyson_tp07.h"
#include "esphome/core/log.h"
#include <cstddef>

namespace esphome {
namespace dyson_tp07 {

static const char *TAG = "dyson_tp07.sensor";
static const int max_line_length = 1024;
Dyson_regs_t dyson_reg;

void DysonTP07::setup() { ESP_LOGCONFIG(TAG, "Setting up Dyson TP07..."); }

// Thanks ChatGPT
void DysonTP07::printDysonRegisters(const Dyson_regs_t *dyson_reg) {
  if (dyson_reg == NULL) {
    ESP_LOGV(TAG, "Dyson registers are NULL");
    return;
  }

  ESP_LOGV(TAG, "================ Dyson Registers ================");

  // Flow_reg
  ESP_LOGV(TAG, "Flow_reg: Flow1: %u, Flow2: %u, Flow3: %u, Flow4: %u",
           dyson_reg->Flow_reg.Flow1, dyson_reg->Flow_reg.Flow2,
           dyson_reg->Flow_reg.Flow3, dyson_reg->Flow_reg.Flow4);

  // UpTime_reg
  ESP_LOGV(TAG, "UpTime_reg: %u", dyson_reg->UpTime_reg);

  // reg_2_0_4_0
  ESP_LOGV(TAG,
           "Temp_reg: Temp1: %.2f, Temp2: %.2f, Temp3: %.2f, Humidity: %.2f, "
           "Vent_level: %.2f",
           dyson_reg->Temp_reg.Temp1, dyson_reg->Temp_reg.Temp2,
           dyson_reg->Temp_reg.Temp3, dyson_reg->Temp_reg.Humidity,
           dyson_reg->Temp_reg.Vent_level);

  // reg_2_0_3_0
  ESP_LOGV(
      TAG,
      "reg_2_0_3_0: Reg1: %.2f, Reg2: %.2f, Reg3: %.2f, Reg4: %.2f, Reg5: %.2f",
      dyson_reg->reg_2_0_3_0.Reg1, dyson_reg->reg_2_0_3_0.Reg2,
      dyson_reg->reg_2_0_3_0.Reg3, dyson_reg->reg_2_0_3_0.Reg4,
      dyson_reg->reg_2_0_3_0.Reg5);

  // reg_2_0_2_0
  ESP_LOGV(TAG, "reg_2_0_2_0: Reg1: %u, Reg2: %u, Reg3: %u, Reg4: %u",
           dyson_reg->reg_2_0_2_0.Reg1, dyson_reg->reg_2_0_2_0.Reg2,
           dyson_reg->reg_2_0_2_0.Reg3, dyson_reg->reg_2_0_2_0.Reg4);

  // reg_2_0_5_0
  ESP_LOGV(TAG, "reg_2_0_5_0: Reg1: %u, Reg2: %u, Reg3: %u",
           dyson_reg->reg_2_0_5_0.Reg1, dyson_reg->reg_2_0_5_0.Reg2,
           dyson_reg->reg_2_0_5_0.Reg3);

  // reg_2_0_6_0
  ESP_LOGV(TAG, "reg_2_0_6_0: Reg1: %u, Reg2: %u", dyson_reg->reg_2_0_6_0.Reg1,
           dyson_reg->reg_2_0_6_0.Reg2);

  // reg_2_0_7_0
  ESP_LOGV(TAG, "reg_2_0_7_0:");
  for (int i = 0; i < 13; i++) {
    ESP_LOGV(TAG, "   Reg%d: %.2f", i + 1,
             ((double *)&dyson_reg->reg_2_0_7_0)[i]);
  }

  // reg_2_0_8_0
  ESP_LOGV(TAG, "reg_2_0_8_0:");
  for (int i = 0; i < 12; i++) {
    ESP_LOGV(TAG, "   Reg%d: %u", i + 1,
             ((uint8_t *)&dyson_reg->reg_2_0_8_0)[i]);
  }

  // reg_2_0_9_0
  ESP_LOGV(
      TAG,
      "reg_2_0_9_0: Reg1: %.2f, Reg2: %.2f, Reg3: %.2f, Reg4: %.2f, Reg5: %.2f",
      dyson_reg->reg_2_0_9_0.Reg1, dyson_reg->reg_2_0_9_0.Reg2,
      dyson_reg->reg_2_0_9_0.Reg3, dyson_reg->reg_2_0_9_0.Reg4,
      dyson_reg->reg_2_0_9_0.Reg5);

  // reg_2_0_10_0
  ESP_LOGV(TAG, "reg_2_0_10_0:");
  for (int i = 0; i < 7; i++) {
    ESP_LOGV(TAG, "   Reg%d: %.2f", i + 1,
             ((double *)&dyson_reg->reg_2_0_10_0)[i]);
  }

  // reg_2_0_12_0
  ESP_LOGV(TAG, "reg_2_0_12_0: Reg1: %u, Reg2: %u, Reg3: %u, Reg4: %u",
           dyson_reg->reg_2_0_12_0.Reg1, dyson_reg->reg_2_0_12_0.Reg2,
           dyson_reg->reg_2_0_12_0.Reg3, dyson_reg->reg_2_0_12_0.Reg4);

  // reg_3_0_1_0
  ESP_LOGV(TAG, "reg_3_0_1_0: Reg1: %u, Reg2: %u", dyson_reg->reg_3_0_1_0.Reg1,
           dyson_reg->reg_3_0_1_0.Reg2);

  // reg_3_0_5_0
  ESP_LOGV(TAG, "reg_3_0_5_0:");
  for (int i = 0; i < 4; i++) {
    ESP_LOGV(TAG, "   Reg%d: %.2f", i + 1,
             ((double *)&dyson_reg->reg_3_0_5_0)[i]);
  }

  // reg_3_0_6_0
  ESP_LOGV(TAG, "reg_3_0_6_0:");
  for (int i = 0; i < 5; i++) {
    ESP_LOGV(TAG, "   Reg%d: %.2f", i + 1,
             ((double *)&dyson_reg->reg_3_0_6_0)[i]);
  }

  // reg_3_0_7_0
  ESP_LOGV(TAG, "reg_3_0_7_0:");
  for (int i = 0; i < 5; i++) {
    ESP_LOGV(TAG, "   Reg%d: %.2f", i + 1,
             ((double *)&dyson_reg->reg_3_0_7_0)[i]);
  }

  // reg_3_0_8_0
  ESP_LOGV(TAG, "reg_3_0_8_0:");
  for (int i = 0; i < 4; i++) {
    ESP_LOGV(TAG, "   Reg%d: %.2f", i + 1,
             ((double *)&dyson_reg->reg_3_0_8_0)[i]);
  }

  // reg_3_0_9_0
  ESP_LOGV(TAG, "reg_3_0_9_0:");
  for (int i = 0; i < 6; i++) {
    ESP_LOGV(TAG, "   Reg%d: %.2f", i + 1,
             ((double *)&dyson_reg->reg_3_0_9_0)[i]);
  }

  // reg_3_0_10_0
  ESP_LOGV(TAG, "reg_3_0_10_0:");
  for (int i = 0; i < 5; i++) {
    ESP_LOGV(TAG, "   Reg%d: %.2f", i + 1,
             ((double *)&dyson_reg->reg_3_0_10_0)[i]);
  }

  ESP_LOGV(TAG, "================================================");
}

void DysonTP07::update() {
  ESP_LOGV(TAG, "Dyson TP07 update starting...");
  ESP_LOGD(
      TAG,
      "Temp1=%0.2f, Temp2=%0.2f, Temp3=%0.2f, Humidity=%0.2f, Vent_level=%0.2f",
      dyson_reg.Temp_reg.Temp1, dyson_reg.Temp_reg.Temp2,
      dyson_reg.Temp_reg.Temp3, dyson_reg.Temp_reg.Humidity,
      dyson_reg.Temp_reg.Vent_level);

  this->printDysonRegisters(&dyson_reg);

  if (dyson_reg.Temp_reg.Temp3 == 0) {
    ESP_LOGD(TAG, "Data not ready yet, returning...");
    return;
  }

  if (this->temperature_1_sensor_ != nullptr) {
    this->temperature_1_sensor_->publish_state(dyson_reg.Temp_reg.Temp1);
  }
  if (this->temperature_2_sensor_ != nullptr) {
    this->temperature_2_sensor_->publish_state(dyson_reg.Temp_reg.Temp2);
  }
  if (this->temperature_3_sensor_ != nullptr) {
    this->temperature_3_sensor_->publish_state(dyson_reg.Temp_reg.Temp3);
  }
  if (this->humidity_sensor_ != nullptr) {
    this->humidity_sensor_->publish_state(dyson_reg.Temp_reg.Humidity);
  }
  if (this->flow_1_sensor_ != nullptr) {
    this->flow_1_sensor_->publish_state(dyson_reg.Flow_reg.Flow1);
  }
  if (this->flow_2_sensor_ != nullptr) {
    this->flow_2_sensor_->publish_state(dyson_reg.Flow_reg.Flow2);
  }
  if (this->flow_3_sensor_ != nullptr) {
    this->flow_3_sensor_->publish_state(dyson_reg.Flow_reg.Flow3);
  }
  if (this->flow_4_sensor_ != nullptr) {
    this->flow_4_sensor_->publish_state(dyson_reg.Flow_reg.Flow4);
  }
  if (this->speed_sensor_ != nullptr) {
    this->speed_sensor_->publish_state(dyson_reg.Temp_reg.Vent_level);
  }
  if (this->uptime_sensor_ != nullptr) {
    this->uptime_sensor_->publish_state(dyson_reg.UpTime_reg);
  }
  if (this->pm25_sensor_ != nullptr) {
    this->pm25_sensor_->publish_state(dyson_reg.reg_2_0_7_0.Part_2_5);
  }
  if (this->pm10_sensor_ != nullptr) {
    this->pm10_sensor_->publish_state(dyson_reg.reg_2_0_7_0.Part_10);
  }
  if (this->is_on_sensor_ != nullptr) {
    this->is_on_sensor_->publish_state(dyson_reg.Temp_reg.Vent_level > 0);
  }

  ESP_LOGV(TAG, "Dyson TP07 update complete.");
}

// A method to immediately get the most up-to-date value for the speed instead
// of having to wait for the 60s polling interval
double DysonTP07::get_speed_sensor() {
  auto speed = dyson_reg.Temp_reg.Vent_level;
  if (speed > 0) {
    return speed;
  } else {
    return -1;
  };
};

bool DysonTP07::get_is_on_sensor() { return this->get_speed_sensor() > 0; }


void DysonTP07::loop() {
  // Never block the ESP8266 event loop for too long.
  static constexpr size_t MAX_BYTES_PER_LOOP = 96;
  static constexpr size_t MAX_FRAME_SIZE = 256;

  // Keep incomplete packets between loop() calls.
  static uint8_t buffer[MAX_FRAME_SIZE] = {};
  static size_t buffer_len = 0;

  size_t processed = 0;

  while (processed < MAX_BYTES_PER_LOOP && this->available()) {
    uint8_t data = 0;

    if (!this->read_byte(&data)) {
      break;
    }

    ++processed;

    // Wait for the start delimiter.
    if (buffer_len == 0) {
      if (data == START_BYTE) {
        buffer[buffer_len++] = data;
      }
      continue;
    }

    // Reject oversized packets without writing past the buffer.
    if (buffer_len >= MAX_FRAME_SIZE) {
      buffer_len = 0;

      if (data == START_BYTE) {
        buffer[buffer_len++] = data;
      }
      continue;
    }

    buffer[buffer_len++] = data;

    // Packet is not complete yet.
    if (data != START_BYTE) {
      continue;
    }

    // We have a complete delimited frame.
    if (buffer_len >= 2) {
      uart_packet_t packet = {};
      packet.packet_size = buffer_len;

      memcpy(packet.ptr, buffer, buffer_len);

      uart_packet_t *unstuffed = this->UnstuffPacket(&packet);

      if (unstuffed != nullptr) {
        this->ParseDysonPacket(*unstuffed, dyson_reg);
        free(unstuffed);
      }
    }

    // Start collecting the next packet.
    buffer_len = 0;
  }
}



uart_packet_t *DysonTP07::UnstuffPacket(uart_packet_t *pack) {
  if (pack == nullptr ||
      pack->packet_size < 2 ||
      pack->packet_size > sizeof(pack->ptr)) {
    return nullptr;
  }

  // Verify framing.
  if (pack->ptr[0] != START_BYTE ||
      pack->ptr[pack->packet_size - 1] != START_BYTE) {
    return nullptr;
  }

  uart_packet_t *newPack =
      (uart_packet_t *) calloc(1, sizeof(uart_packet_t));

  if (newPack == nullptr) {
    return nullptr;
  }

  // Remove framing and decode escaped bytes.
  for (size_t i = 1; i + 1 < pack->packet_size; ++i) {
    uint8_t value = pack->ptr[i];

    if (value == STUFF_BYTE_1) {
      // An escape must have another byte before the end delimiter.
      if (i + 2 >= pack->packet_size) {
        free(newPack);
        return nullptr;
      }

      const uint8_t escaped = pack->ptr[++i];

      if (escaped == STUFF_BYTE_2) {
        value = START_BYTE;
      } else if (escaped == STUFF_BYTE_3) {
        value = STUFF_BYTE_1;
      } else {
        free(newPack);
        return nullptr;
      }
    }

    if (newPack->packet_size >= sizeof(newPack->ptr)) {
      free(newPack);
      return nullptr;
    }

    newPack->ptr[newPack->packet_size++] = value;
  }

  newPack->time = pack->time;
  return newPack;
}


uint8_t DysonTP07::ParseDysonPacket(uart_packet_t &pack, Dyson_regs_t &regs) {

  if (pack.packet_size < 18) {
    return 1;
  }

  uint16_t packSize = pack.ptr[0] | (pack.ptr[1] << 8);
  if (packSize != (pack.packet_size - 3)) {
    return 1;
  }

  // TODO: Implement CRC checking logic
  // if (!CRC32_check(packCRC32, &pack.ptr[3], packSize)) return 2;

  uint32_t packCRC32 = (pack.ptr[packSize + 2] << 24) |
                       (pack.ptr[packSize + 1] << 16) |
                       (pack.ptr[packSize] << 8) | (pack.ptr[packSize - 1]);

  if (pack.ptr[9] != 49) {
    return 1;
  }

  uint8_t regpos = 10;
  uint8_t parseRes = 0;
  const uint8_t *data_pos_ptr = &pack.ptr[regpos + 4];

  switch (pack.ptr[regpos]) {
  case 18:
    if (pack.ptr[regpos + 1] == 0 && pack.ptr[regpos + 2] == 1 &&
        pack.ptr[regpos + 3] == 0) {
      parseRes = ParseData(data_pos_ptr, regs.Flow_reg);
    }
    break;

  case 2:
    parseRes = ParseSecondaryRegister(pack.ptr[regpos + 2], data_pos_ptr, regs);
    break;

  case 3:
    parseRes = ParseTertiaryRegister(pack.ptr[regpos + 2], data_pos_ptr, regs);
    break;

  default:
    ESP_LOGVV(TAG, "Unknown first reg: %d", pack.ptr[regpos]);
    break;
  }

  return parseRes;
}

uint8_t DysonTP07::ParseSecondaryRegister(uint8_t reg, const uint8_t *data,
                                          Dyson_regs_t &regs) {
  switch (reg) {
  case 2:
    return ParseData(data, regs.reg_2_0_2_0);
  case 3:
    return ParseData(data, regs.reg_2_0_3_0);
  case 4:
    return ParseData(data, regs.Temp_reg);
  case 5:
    return ParseData(data, regs.reg_2_0_5_0);
  case 6:
    return ParseData(data, regs.reg_2_0_6_0);
  case 7:
    return ParseData(data, regs.reg_2_0_7_0);
  case 8:
    return ParseData(data, regs.reg_2_0_8_0);
  case 9:
    return ParseData(data, regs.reg_2_0_9_0);
  case 10:
    return ParseData(data, regs.reg_2_0_10_0);
  case 11:
    return ParseData(data, regs.UpTime_reg);
  case 12:
    return ParseData(data, regs.reg_2_0_12_0);
  default:
    ESP_LOGW(TAG, "Unknown second reg: %d", reg);
    return 0;
  }
}

uint8_t DysonTP07::ParseTertiaryRegister(uint8_t reg, const uint8_t *data,
                                         Dyson_regs_t &regs) {
  switch (reg) {
  case 1:
    return ParseData(data, regs.reg_3_0_1_0);
  case 5:
    return ParseData(data, regs.reg_3_0_5_0);
  case 6:
    return ParseData(data, regs.reg_3_0_6_0);
  case 7:
    return ParseData(data, regs.reg_3_0_7_0);
  case 8:
    return ParseData(data, regs.reg_3_0_8_0);
  case 9:
    return ParseData(data, regs.reg_3_0_9_0);
  case 10:
    return ParseData(data, regs.reg_3_0_10_0);
  default:
    ESP_LOGW(TAG, "Unknown third reg: %d", reg);
    return 0;
  }
}

template <typename T> uint8_t DysonTP07::ParseData(const uint8_t *ptr, T &reg) {
  uint8_t length = ptr[1];
  switch (ptr[0]) {
  case 98: // uint8_t
    if (length > sizeof(reg))
      return 0;
    memcpy(&reg, ptr + 2, length);
    break;

  case 100: // uint16_t
    if (length * sizeof(uint16_t) > sizeof(reg))
      return 0;
    for (uint8_t i = 0; i < length; ++i) {
      ((uint16_t *)&reg)[i] = ptr[2 + i * 2] | (ptr[3 + i * 2] << 8);
    }
    break;

  case 102: // uint32_t
    if (length * sizeof(uint32_t) > sizeof(reg))
      return 0;
    for (uint8_t i = 0; i < length; ++i) {
      ((uint32_t *)&reg)[i] = ptr[2 + i * 4] | (ptr[3 + i * 4] << 8) |
                              (ptr[4 + i * 4] << 16) | (ptr[5 + i * 4] << 24);
    }
    break;

  case 107: // double
    if (length * sizeof(double) > sizeof(reg))
      return 0;
    for (uint8_t i = 0; i < length; ++i) {
      memcpy(&((double *)&reg)[i], &ptr[2 + i * 8], sizeof(double));
    }
    break;

  default:
    ESP_LOGW(TAG, "ParseData: unknown format");
    return 0;
  }

  return 1;
}

void DysonTP07::dump_config() {
  ESP_LOGCONFIG(TAG, "Dyson TP07 config goes here...");
}

} // namespace dyson_tp07
} // namespace esphome
