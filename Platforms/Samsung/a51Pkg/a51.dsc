##
#  Copyright (c) 2011 - 2022, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2020, Intel Corporation. All rights reserved.
#  Copyright (c) 2018, Bingxing Wang. All rights reserved.
#  Copyright (c) Microsoft Corporation.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
##

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = a51
  PLATFORM_GUID                  = 8F4A2D19-515F-4A51-9611-7E2C1B4D8A51
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/a51Pkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = RELEASE|DEBUG
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = a51Pkg/a51.fdf
  USE_CUSTOM_DISPLAY_DRIVER      = 0
  UNIXNU_PAYLOAD                 = 0

!include S5E9610Pkg/S5E9610Pkg.dsc.inc

[PcdsFixedAtBuild]
  #
  # DDR Memory
  #
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000

  #
  # UEFI Stack (placed immediately after 3 MiB FD at 0xC9000000)
  #
  gArmPlatformTokenSpaceGuid.PcdCPUCoresStackBase|0xC9300000
  gArmPlatformTokenSpaceGuid.PcdCPUCorePrimaryStackSize|0x40000

  #
  # SMBIOS (Samsung Galaxy A51 SM-A515F / Exynos 9611)
  #
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemManufacturer|"Samsung"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Galaxy A51"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"SM-A515F"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Galaxy_A51_a51"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosBoardModel|"Galaxy A51 (SM-A515F)"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosProcessorModel|"Exynos (TM) 9611 @ 2.31 GHz"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosProcessorPartNumber|"S5E9611"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosMaxCpuFreq|2310

  #
  # Simple Frame Buffer (1080x2400 Super AMOLED, 32 bpp)
  #
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferWidth|1080
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferHeight|2400
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferColorDepth|32

[LibraryClasses]
  #
  # Memory Libraries
  #
  MemoryMapLib|a51Pkg/Library/MemoryMapLib/MemoryMapLib.inf

  #
  # Input Libraries
  #
  KeypadDeviceLib|a51Pkg/Library/KeypadDeviceLib/KeypadDeviceLib.inf

!if $(UNIXNU_PAYLOAD) == 1
  #
  # UniXNU Libraries (supplied by assembled UniXNU build tree)
  #
  UniXNULib|UniXNUPkg/Library/UniXNULib/UniXNULib.inf
!endif

[Components]
  #
  # Input
  #
  SiliciumPkg/Drivers/KeypadDxe/KeypadDxe.inf
  SiliciumPkg/Drivers/KeypadDeviceDxe/KeypadDeviceDxe.inf

!if $(UNIXNU_PAYLOAD) == 1
  #
  # UniXNU Boot Manager, Payload RAM Disk, and DarwinBoot XNU Loader
  #
  UniXNUPkg/Application/UniXNU/UniXNU.inf
  UniXNUPkg/Driver/UniXNUDxe/UniXNUDxe.inf
  UniXNUPkg/Driver/UniXNURamDiskDxe/UniXNURamDiskDxe.inf
  DarwinBootPkg/Driver/DarwinBoot.inf
!endif
