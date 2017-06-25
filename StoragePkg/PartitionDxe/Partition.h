/*++

Copyright (c) 2004 - 2007, Intel Corporation       
Portions Copyright (c) 2005 - 2017, Apple Inc.
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  Partition.h
  
Abstract:

  Partition driver that produces logical BlockIo devices from a physical 
  BlockIo device. The logical BlockIo devices are based on the format
  of the raw block devices media. Currently "El Torito CD-ROM", Legacy 
  MBR, and GPT partition schemes are supported.

Revision History

--*/

#ifndef _PARTITION_H_
#define _PARTITION_H_

#include <AppleMacEfi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

//
// Driver Consumed Protocol Prototypes
//
#include <Protocol/DevicePath.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DiskIo.h>

//
// Driver Consumed Guids
//
#include <Guid/Gpt.h>

//
// Driver Produced Protocol Prototypes
//
#include <Protocol/DriverBinding.h>
#include <Protocol/ComponentName.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/ApplePartitionInfo.h>

//
// Partition private data
//
#define PARTITION_PRIVATE_DATA_SIGNATURE  SIGNATURE_32 ('P', 'a', 'r', 't')
typedef struct {
  UINT64                        Signature;

  EFI_HANDLE                    Handle;
  EFI_DEVICE_PATH_PROTOCOL      *DevicePath;
  EFI_BLOCK_IO_PROTOCOL         BlockIo;
  EFI_BLOCK_IO_MEDIA            Media;

  EFI_DISK_IO_PROTOCOL          *DiskIo;
  EFI_BLOCK_IO_PROTOCOL         *ParentBlockIo;
  UINT64                        Start;
  UINT64                        End;
  UINT32                        BlockSize;

  EFI_GUID                      *EspGuid;

  APPLE_PARTITION_INFO_PROTOCOL PartitionInfo;
} PARTITION_PRIVATE_DATA;

#define PARTITION_DEVICE_FROM_BLOCK_IO_THIS(a)  CR (a, PARTITION_PRIVATE_DATA, BlockIo, PARTITION_PRIVATE_DATA_SIGNATURE)

//
// Global Variables
//
extern EFI_DRIVER_BINDING_PROTOCOL  gPartitionDriverBinding;
extern EFI_COMPONENT_NAME_PROTOCOL  gPartitionComponentName;

//
// Extract INT32 from char array
//
#define UNPACK_INT32(a) (INT32)( (((UINT8 *) a)[0] <<  0) |    \
                                 (((UINT8 *) a)[1] <<  8) |    \
                                 (((UINT8 *) a)[2] << 16) |    \
                                 (((UINT8 *) a)[3] << 24) )

//
// Extract UINT32 from char array
//
#define UNPACK_UINT32(a) (UINT32)( (((UINT8 *) a)[0] <<  0) |    \
                                   (((UINT8 *) a)[1] <<  8) |    \
                                   (((UINT8 *) a)[2] << 16) |    \
                                   (((UINT8 *) a)[3] << 24) )

EFI_STATUS
PartitionInstallChildHandle (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     ParentHandle,
  IN  EFI_DISK_IO_PROTOCOL           *ParentDiskIo,
  IN  EFI_BLOCK_IO_PROTOCOL          *ParentBlockIo,
  IN  EFI_DEVICE_PATH_PROTOCOL       *ParentDevicePath,
  IN  EFI_DEVICE_PATH_PROTOCOL       *DevicePathNode,
  IN  EFI_LBA                        Start,
  IN  EFI_LBA                        End,
  IN  UINT32                         BlockSize,
  IN  BOOLEAN                        InstallEspGuid,
  IN  APPLE_PARTITION_INFO_PROTOCOL  *PartitionInfo
  )
;

BOOLEAN
PartitionInstallGptChildHandles (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   Handle,
  IN  EFI_DISK_IO_PROTOCOL         *DiskIo,
  IN  EFI_BLOCK_IO_PROTOCOL        *BlockIo,
  IN  EFI_DEVICE_PATH_PROTOCOL     *DevicePath
  )
;

BOOLEAN
PartitionInstallAppleChildHandles (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   Handle,
  IN  EFI_DISK_IO_PROTOCOL         *DiskIo,
  IN  EFI_BLOCK_IO_PROTOCOL        *BlockIo,
  IN  EFI_DEVICE_PATH_PROTOCOL     *DevicePath
  )
;

BOOLEAN
PartitionInstallElToritoChildHandles (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   Handle,
  IN  EFI_DISK_IO_PROTOCOL         *DiskIo,
  IN  EFI_BLOCK_IO_PROTOCOL        *BlockIo,
  IN  EFI_DEVICE_PATH_PROTOCOL     *DevicePath
  )
;

BOOLEAN
PartitionInstallMbrChildHandles (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   Handle,
  IN  EFI_DISK_IO_PROTOCOL         *DiskIo,
  IN  EFI_BLOCK_IO_PROTOCOL        *BlockIo,
  IN  EFI_DEVICE_PATH_PROTOCOL     *DevicePath
  )
;

typedef 
BOOLEAN
(*PARTITION_DETECT_ROUTINE) (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   Handle,
  IN  EFI_DISK_IO_PROTOCOL         *DiskIo,
  IN  EFI_BLOCK_IO_PROTOCOL        *BlockIo,
  IN  EFI_DEVICE_PATH_PROTOCOL     *DevicePath
  );

#endif
