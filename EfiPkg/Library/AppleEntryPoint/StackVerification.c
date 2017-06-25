/** @file
  Copyright (c) 2017, Apple Inc.  All rights reserved.<BR>

  This program and the accompanying materials have not been licensed.
  Neither is its usage, its redistribution, in source or binary form,
  licensed, nor implicitely or explicitely permitted, except when
  required by applicable law.

  Unless required by applicable law or agreed to in writing, software
  distributed is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
  OR CONDITIONS OF ANY KIND, either express or implied.
**/

#include <AppleMacEfi.h>

// gStackVerificationValue
GLOBAL_REMOVE_IF_UNREFERENCED
UINT64 gStackVerificationValue = 0xAFAFAFAFAFAFAFAF;

// AppleInitializeStackVerification
VOID
AppleInitializeStackVerification (
  VOID
  )
{
  return;
}
