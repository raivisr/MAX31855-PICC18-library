#include <htc.h>

#ifndef _MAX31855_H_
#define _MAX31855_H_

#define MAX31855_CS_LAT LATCbits.LATC2
#define MAX31855_CS_TRIS TRISCbits.TRISC2

#define SCV_FAULT 4
#define SCG_FAULT 2
#define OC_FAULT 1

void setupMAX31855(unsigned char (*SPIgetc)(void));
float readCelsius(void);
float readCJCelsius(void);
char readStatus(void);

static unsigned char (*GetSPIc)(void);

#endif