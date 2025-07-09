#ifndef __RELAY_H
#define __RELAY_H

#include "sys.h"

#define BIGLED_ON  PBout(10)=0;PBout(11)=0
#define BIGLED_OFF PBout(10)=1;PBout(11)=1
#define REDLED_ON  PBout(13)=0
#define REDLED_OFF PBout(13)=1

void Relay_Init(void);

#endif

