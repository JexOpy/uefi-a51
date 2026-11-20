#include <Library/MemoryMapLib.h>

//
// Memory map for Samsung Galaxy A51 (SM-A515F, Exynos 9611 / S5E9611).
// Verified against physical SM-A515F (bootloader A515FXXU8HWI1) /proc/iomem and /sys/firmware/fdt:
//   - Low DRAM: 0x80000000..0xBAB00000, 0xC0000000..0xE0000000, 0xE1900000..0x100000000
//   - TZ Holes: 0xBAB00000..0xC0000000 (85 MiB), 0xE0000000..0xE1900000 (25 MiB)
//   - S-Boot initrd load region (0x89000000, 72 MiB) reserved so DXE never overwrites UniXNU payload.
//   - Display Reserved 20 MiB at 0xCA000000 (verified s3cfb.bootloaderfb=0xca000000, 1080x2400x32bpp).
//   - Clean 655 MiB Conv RAM at 0x91C00000..0xBAB00000 for DarwinBoot / XNU owned window.
//

STATIC
EFI_MEMORY_REGION_DESCRIPTOR
gMemoryDescriptor[] = {
  // Name, Address, Length, HobOption, ResourceType, ResourceAttribute, MemoryType, ArmAttribute

  // DDR Bank 0a: 0x80000000 .. 0xBAB00000 (939 MiB)
  {"SEC Debug",          0x80000000, 0x00001000, AddMem, SYS_MEM, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED},
  {"Kaslr",              0x80001000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0x80002000, 0x06FFE000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"EL2 Code",           0x87000000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, BsCode, WRITE_BACK},
  {"RAM Partition",      0x87200000, 0x01E00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"Payload RAM disk",   0x89000000, 0x04800000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0x8D800000, 0x03A00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"SEC Debug Logs",     0x91200000, 0x00A00000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0x91C00000, 0x28F00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},

  // Memory Hole: 0xBAB00000 -> 0xC0000000 (0x05500000, 85 MiB) [TZ Secure DRAM]

  // DDR Bank 0b: 0xC0000000 .. 0xE0000000 (512 MiB)
  {"SEC Log",            0xC0000000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"DXE Heap",           0xC0080000, 0x03C00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"RAM Partition",      0xC3C80000, 0x05380000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"UEFI FD",            0xC9000000, 0x00300000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
  {"UEFI Stack",         0xC9300000, 0x00040000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
  {"RAM Partition",      0xC9340000, 0x00CC0000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"Display Reserved",   0xCA000000, 0x01400000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_THROUGH},
  {"RAM Partition",      0xCB400000, 0x10500000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"Camera Contig",      0xDB900000, 0x00700000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0xDC000000, 0x04000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},

  // Memory Hole: 0xE0000000 -> 0xE1900000 (0x01900000, 25 MiB) [Secure PGTBL]

  // DDR Bank 0c: 0xE1900000 .. 0x100000000 (487 MiB)
  {"Secure Camera",      0xE1900000, 0x02000000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0xE3900000, 0x05B00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"ABOX RMEM",          0xE9400000, 0x02800000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0xEBC00000, 0x01400000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"Modem and CP Log",   0xED000000, 0x0A800000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0xF7800000, 0x01800000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"ESS Debug",          0xF9000000, 0x01000000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0xFA000000, 0x01000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"GNSS IF",            0xFB000000, 0x00800000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0xFB800000, 0x01800000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
  {"CHUB RMEM",          0xFD000000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
  {"RAM Partition",      0xFD080000, 0x02F80000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},

  // Non-Secure iRAM Regions
  {"DDR Info",           0x02038000, 0x00030000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},

  // Register Regions (Exynos 9610 / 9611)
  {"Chip Info",          0x10000000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Pinctrl SHUB",       0x11080000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Pinctrl ALIVE",      0x11850000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"PMU",                0x11860000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Speedy",             0x11A10000, 0x00002000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Pinctrl CMGP",       0x11C20000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Clock Controller",   0x12100000, 0x00008000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Gic Distributor",    0x12301000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Gic CPU Interface",  0x12302000, 0x00006000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"USB DWC3",           0x13200000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"CMU FSYS",           0x13400000, 0x00002000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Sysreg FSYS",        0x13410000, 0x00002000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Pinctrl FSYS",       0x13490000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"UFS UNIPRO",         0x13510000, 0x00008000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"UFS HCI",            0x13520000, 0x00005000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"UFS PHY",            0x13530000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"UART0",              0x13820000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"HSI2C4 Touch",       0x13870000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Pinctrl TOP",        0x139B0000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Decon",              0x148B0000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
  {"Pinctrl DISPAUD",    0x14A60000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}
};

VOID
GetMemoryMap (
  OUT EFI_MEMORY_REGION_DESCRIPTOR **MemoryDescriptor,
  OUT UINT8                         *MemoryDescriptorCount)
{
  *MemoryDescriptor      = gMemoryDescriptor;
  *MemoryDescriptorCount = ARRAY_SIZE (gMemoryDescriptor);
}
