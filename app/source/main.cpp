#include "./frda.h"
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handleResult(action)                          \
  Result rc = action;                                 \
  if (R_FAILED(rc)) {                                 \
    printf("Error: %08lx\n\n", rc);                   \
  } else {                                            \
    hasTakenAction = true;                            \
    printf("Success!  Will reboot on \"Start\"\n\n"); \
  }

int main(int argc, char *argv[]) {
  nsInit();
  frdAInit();
  gfxInitDefault();
  consoleInit(GFX_TOP, NULL);

  // This version or higher is required creating/swaping local accounts
  FRDA_SetClientSdkVersion(0x70000c8);

  bool hasTakenAction = false;

  printf("Friend account manager\n");
  printf("Press \"Start\" to quit or reboot\n");
  printf("Press \"A\" to create a new PROD account 2\n");
  printf("Press \"B\" to create a new TEST account 2\n");
  printf("Press \"X\" to use account 1\n");
  printf("Press \"Y\" to use account 2\n\n");

  // Main loop
  while (aptMainLoop()) {
    gspWaitForVBlank();
    gfxSwapBuffers();
    hidScanInput();

    // Your code goes here
    u32 kDown = hidKeysDown();
    if (kDown & KEY_START) {
      if (hasTakenAction) {
        NS_RebootSystem();
      } else {
        break;  // break in order to return to hbmenu
      }
    }

    if (kDown & KEY_A) {
      printf("Creating PROD account Id 2...\n");
      handleResult(FRDA_CreateLocalAccount(2, NASC_ENV_Prod, 0, 1));
    }

    if (kDown & KEY_B) {
      printf("Creating TEST account Id 2...\n");
      handleResult(FRDA_CreateLocalAccount(2, NASC_ENV_Test, 0, 1));
    }

    if (kDown & KEY_X) {
      printf("Using account Id 1...\n");
      handleResult(FRDA_SetLocalAccountId(1));
    }

    if (kDown & KEY_Y) {
      printf("Using account Id 2...\n");
      handleResult(FRDA_SetLocalAccountId(2));
    }
  }

  gfxExit();
  frdAExit();
  nsExit();
  return 0;
}