#include "gba.h"
#include "entities.h"
#include "images/player.h"
#include "stdio.h"


struct State {
  struct crate crate[9];
  struct player player;
} cs, ps;

int boxCounter = 0;

void initializeEntities(void) {
  int xcount = 10;
  int ycount = 10;
  for (int i = 0; i < 9; i++) {
    cs.crate[i].l = 7;
    cs.crate[i].x = xcount;
    cs.crate[i].y = ycount;
    cs.crate[i].collected = 0; //0 is false 1 is true 2 is already collected
    drawRectDMA(cs.crate[i].y, cs.crate[i].x, cs.crate[i].l, cs.crate[i].l, RED);
    xcount = xcount + 100;
    if (xcount > WIDTH - cs.crate[i].l - 10) {
      xcount = 10;
      ycount = ycount + 50;
    }
  }
  cs.player.x = 40;
  cs.player.y = 40;
  cs.player.dx = 0;
  cs.player.dy = 0;
}

void updateEntities(unsigned int previousButtons, unsigned int currentButtons) {
  ps = cs;
  if(KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {
    cs.player.dx = 1;
  }
  if(KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {
    cs.player.dx = -1;
  }
  if(KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
    cs.player.dy = -1;
  }
  if(KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
    cs.player.dy = 1;
  }
  if (cs.player.x + cs.player.dx < 0) {
    cs.player.dx = 0;
  }
  if (cs.player.x + cs.player.dx > WIDTH - PLAYER_WIDTH) {
    cs.player.dx = 0;
  }
  if (cs.player.y + cs.player.dy < 0) {
    cs.player.dy = 0;
  }
  if (cs.player.y + cs.player.dy > HEIGHT - PLAYER_HEIGHT) {
    cs.player.dy = 0;
  }
  cs.player.y += cs.player.dy;
  cs.player.x += cs.player.dx;

  //Check Intersect
  for (int i = 0; i < 9; i++) {
    if (cs.player.x < cs.crate[i].x + cs.crate[i].l &&
      cs.player.x + PLAYER_WIDTH > cs.crate[i].x &&
      cs.player.y < cs.crate[i].y + cs.crate[i].l &&
      cs.player.y + PLAYER_HEIGHT > cs.crate[i].y) {
      cs.crate[i].collected++;
    }
  }

  waitForVBlank();
  for (int i = 0; i < 9; i++) {
    if (cs.crate[i].collected == 1) {
      drawRectDMA(cs.crate[i].y, cs.crate[i].x, cs.crate[i].l, cs.crate[i].l, YELLOW);
      cs.crate[i].collected++;
      boxCounter++;
    }
  }
  drawRectDMA(ps.player.y, ps.player.x, PLAYER_WIDTH, PLAYER_HEIGHT, YELLOW);
  drawImageDMA(cs.player.y,cs.player.x,PLAYER_WIDTH,PLAYER_HEIGHT, playerImage);
  char buffer[55];
  drawString(20,20,buffer, YELLOW);
  sprintf(buffer, "BOXES COLLECTED: %d", boxCounter);
  drawString(20,20,buffer, BLACK);
}

void resetEntities(void) {

}
