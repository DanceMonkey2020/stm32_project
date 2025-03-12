#ifndef IAP_H
#define IAP_H

#include <stdint.h>

const uint8_t* deserializationHex(const uint8_t* array, int32_t arrayLen, int32_t* dataType, uint16_t* dataAddr, int32_t* dataLen);
void IapJumpApp(uint32_t addr);
void IapJumpBoot();

#endif
