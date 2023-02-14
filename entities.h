#ifndef ENTITIES_H
#define ENTITIES_H

#include "gba.h"
#include "stdio.h"

struct crate {
  int x;
  int y;
  int l; //its a square so this is one length side
  int collected;
};

struct player {
  int x;
  int y;
  int dx;
  int dy;
};

void initializeEntities(void);
void updateEntities(unsigned int previousButtons, unsigned int currentButtons);
void resetEntities(void);

#endif
