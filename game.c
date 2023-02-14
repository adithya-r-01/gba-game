#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "entities.h"
#include "images/startscreen.h"
#include "images/winscreen.h"


extern int boxCounter;

/* TODO: */
// Add any additional states you need for your app.
typedef enum {
  START,
  PLAY,
  WIN,
} GBAState;

int main(void) {
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial game state
  GBAState state = START;

  int justMoved = 1;

  while (1) {
    currentButtons = BUTTONS;  // Load the current state of the buttons

    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    switch (state) {
      case START:
        if (justMoved == 1) {
          waitForVBlank();
          drawFullScreenImageDMA(startscreen);
          waitForVBlank();
          drawString(80,70,"Press A to Begin", RED);
          justMoved--;
        }
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          justMoved++;
          state = PLAY;
        }
        break;

      case PLAY:
        if (justMoved == 1) {
          waitForVBlank();
          fillScreenDMA(YELLOW);
          waitForVBlank();
          initializeEntities();
          justMoved--;
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          justMoved++;
          resetEntities();
          state = START;
        }
        updateEntities(previousButtons, currentButtons);
        if (boxCounter == 9) {
          justMoved++;
          state = WIN;
        }
        break;

    case WIN:
      if (justMoved == 1) {
        waitForVBlank();
        drawFullScreenImageDMA(winscreen);
        justMoved--;
      }
      if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
        justMoved++;
        resetEntities();
        state = START;
      }
      break;
    }
    previousButtons = currentButtons;  // Store the current state of the buttons
  }

  return 0;
}
