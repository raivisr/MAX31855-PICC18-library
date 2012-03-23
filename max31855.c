#include <stdint.h>
#include "max31855.h"

void setupMAX31855(unsigned char (*SPIgetc)(void))
{
    GetSPIc = SPIgetc;
    MAX31855_CS_TRIS = 0;
    MAX31855_CS_LAT = 1;
}

int16_t readFirst16bits(void)
{
    int16_t ret = 0;
    MAX31855_CS_LAT = 0;
    for (int8_t i = 1; i >= 0; i--)
    {
        unsigned char tmp = GetSPIc();
        ret |= (tmp << (i*8));
    }
    MAX31855_CS_LAT = 1;
    return ret;
}

int16_t readSecond32bits(void)
{
    int16_t ret = 0;
    MAX31855_CS_LAT = 0;
    for (int8_t i = 3; i >= 0; i--)
    {
        unsigned char tmp = GetSPIc();
        if (i <= 1)
            ret |= (tmp << (i*8));
    }
    MAX31855_CS_LAT = 1;
    return ret;
}

float readCelsius(void)
{
    int16_t v = readFirst16bits();
    if (v & 0x1)
        return 9999.0;
    if (v & 0x8000)
        return (((~v) & 0xfffc) + 0x4) / -32.0;
    else
        return (v & 0xfffc) / 32.0;
}

float readCJCelsius(void)
{
    int16_t v = readSecond32bits();
    if (v & 0x8000)
        return (((~v) & 0xfff0) + 0x10) / -512.0;
    else
        return (v & 0xfff0) / 512.0;
}

char readStatus(void)
{
    int16_t v = readSecond32bits();
    return v & 0x7;
}