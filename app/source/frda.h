#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <3ds/types.h>

typedef enum {
  NASC_ENV_Prod = 0,
  NASC_ENV_Dev = 1,
  NASC_ENV_Test = 2,
} NascEnvironment;

Result frdAInit();
void frdAExit();
Handle *frdAGetSessionHandle();
Result FRDA_CreateLocalAccount(u8 localAccountId, NascEnvironment nascEnvironment, u8 serverTypeField1, u8 serverTypeField2);
Result FRDA_SetLocalAccountId(u8 localAccountId);

#ifdef __cplusplus
}
#endif