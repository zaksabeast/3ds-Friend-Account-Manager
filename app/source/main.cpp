#include "./acta.h"
#include "./frda.h"
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handleFinish()                                   \
  needsReboot = true;                                    \
  if (R_SUCCEEDED(rc)) {                                 \
    printf("Success!\n");                                \
    printf("Changes will take affect after a reboot\n"); \
    printf("Press \"Start\" to reboot\n\n");             \
  }

#define handleResult(action, name)           \
  rc = action;                               \
  if (R_FAILED(rc)) {                        \
    printf("%s error: %08lx\n\n", name, rc); \
  }

/**
 * Switches the friends and act accounts.
 *
 * This will also create the act account if it's missing, just to be safe.
 * This will fail if the friend account hasn't been created yet.
 */
Result switchAccounts(u32 friend_account_id) {
  Result rc = 0;

  handleResult(FRDA_SetLocalAccountId(friend_account_id), "Switch account");

  u32 act_account_index = 0;
  handleResult(ACTA_GetAccountIndexOfFriendAccountId(&act_account_index, friend_account_id), "Get persistent id for creation");

  if (act_account_index == 0) {
    handleResult(ACTA_CreateLocalAccount(), "Create act account");
    handleResult(ACTA_GetAccountIndexOfFriendAccountId(&act_account_index, friend_account_id),
                 "Get persistent id after creation");
  }

  handleResult(ACTA_SetDefaultAccount(act_account_index), "Set default account");

  return rc;
}

Result createAccount(NascEnvironment nascEnvironment) {
  Result rc = 0;

  // (Re)Create the friend account
  handleResult(FRDA_CreateLocalAccount(2, nascEnvironment, 0, 1), "Create account");
  // Switch to the friend/act accounts
  handleResult(switchAccounts(2), "Switch account");
  // Reset the act account
  handleResult(ACTA_ResetAccount(2, true), "Reset account");

  return rc;
}

int main(int argc, char *argv[]) {
  nsInit();
  frdAInit();
  actAInit();
  gfxInitDefault();
  consoleInit(GFX_TOP, NULL);

  // This version or higher is required creating/swaping friend accounts
  FRDA_SetClientSdkVersion(0x70000c8);

  bool needsReboot = false;

  printf("3ds account manager\n\n");
  printf("Press \"Start\" to quit or reboot\n");
  printf("Press \"A\" to create a new PROD account 2\n");
  printf("Press \"B\" to create a new TEST account 2\n");
  printf("Press \"X\" to use account 1\n");
  printf("Press \"Y\" to use account 2\n");
  printf("Press \"Select\" to reset act account 2\n");
  printf("Press \"Up\" to view act account info\n\n");

  // Main loop
  while (aptMainLoop()) {
    gspWaitForVBlank();
    gfxSwapBuffers();
    hidScanInput();

    u32 kDown = hidKeysDown();
    if (kDown & KEY_START) {
      if (needsReboot) {
        NS_RebootSystem();
      } else {
        break;  // break in order to return to hbmenu
      }
    }

    Result rc = 0;

    if (kDown & KEY_A) {
      printf("Creating and using PROD account Id 2...\n");
      handleResult(createAccount(NASC_ENV_Prod), "Create account");
      handleFinish();
    }

    if (kDown & KEY_B) {
      printf("Creating and using TEST account Id 2...\n");
      handleResult(createAccount(NASC_ENV_Test), "Create account");
      handleFinish();
    }

    if (kDown & KEY_X) {
      printf("Using friends/act accounts 1...\n");
      handleResult(switchAccounts(1), "Switch account");
      handleFinish();
    }

    if (kDown & KEY_Y) {
      printf("Using friends/act accounts 2...\n");
      handleResult(switchAccounts(2), "Switch account");
      handleFinish();
    }

    if (kDown & KEY_SELECT) {
      printf("Resetting act account 2...\n");
      handleResult(ACTA_ResetAccount(2, true), "Reset account");
      handleFinish();
    }

    if (kDown & KEY_UP) {
      u32 current_persistent_id = 0;
      handleResult(ACTA_GetPersistentId(&current_persistent_id, ACT_CURRENT_ACCOUNT), "Current persistent id");
      printf("Current persistent id: %lx\n", current_persistent_id);

      u32 act_account_count = 0;
      handleResult(ACTA_GetAccountCount(&act_account_count), "Get account count");
      printf("Total act account count: %lx\n", act_account_count);

      for (u32 i = 0; i < act_account_count; i++) {
        u32 account_index = i + 1;
        u32 friend_account_id = 0;
        u32 persistent_id = 0;
        handleResult(ACTA_GetFriendLocalAccountId(&friend_account_id, account_index), "Get local account id");
        handleResult(ACTA_GetPersistentId(&persistent_id, account_index), "Get persistent id");
        printf("Account %lx:\n", account_index);
        printf("- friend_account_id: %lx\n", friend_account_id);
        printf("- persistent_id: %lx\n\n", persistent_id);
      }
    }
  }

  gfxExit();
  actAExit();
  frdAExit();
  nsExit();
  return 0;
}
