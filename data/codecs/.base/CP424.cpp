/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace codecs {


static const unicode \
TABLE_CP424[] = \
{
  0x00, 0x00000000,
  0x01, 0x00000001,
  0x02, 0x00000002,
  0x03, 0x00000003,
  0x04, 0x0000009C,
  0x05, 0x00000009,
  0x06, 0x00000086,
  0x07, 0x0000007F,
  0x08, 0x00000097,
  0x09, 0x0000008D,
  0x0A, 0x0000008E,
  0x0B, 0x0000000B,
  0x0C, 0x0000000C,
  0x0D, 0x0000000D,
  0x0E, 0x0000000E,
  0x0F, 0x0000000F,
  0x10, 0x00000010,
  0x11, 0x00000011,
  0x12, 0x00000012,
  0x13, 0x00000013,
  0x14, 0x0000009D,
  0x15, 0x00000085,
  0x16, 0x00000008,
  0x17, 0x00000087,
  0x18, 0x00000018,
  0x19, 0x00000019,
  0x1A, 0x00000092,
  0x1B, 0x0000008F,
  0x1C, 0x0000001C,
  0x1D, 0x0000001D,
  0x1E, 0x0000001E,
  0x1F, 0x0000001F,
  0x20, 0x00000080,
  0x21, 0x00000081,
  0x22, 0x00000082,
  0x23, 0x00000083,
  0x24, 0x00000084,
  0x25, 0x0000000A,
  0x26, 0x00000017,
  0x27, 0x0000001B,
  0x28, 0x00000088,
  0x29, 0x00000089,
  0x2A, 0x0000008A,
  0x2B, 0x0000008B,
  0x2C, 0x0000008C,
  0x2D, 0x00000005,
  0x2E, 0x00000006,
  0x2F, 0x00000007,
  0x30, 0x00000090,
  0x31, 0x00000091,
  0x32, 0x00000016,
  0x33, 0x00000093,
  0x34, 0x00000094,
  0x35, 0x00000095,
  0x36, 0x00000096,
  0x37, 0x00000004,
  0x38, 0x00000098,
  0x39, 0x00000099,
  0x3A, 0x0000009A,
  0x3B, 0x0000009B,
  0x3C, 0x00000014,
  0x3D, 0x00000015,
  0x3E, 0x0000009E,
  0x3F, 0x0000001A,
  0x40, 0x00000020,
  0x41, 0x000005D0,
  0x42, 0x000005D1,
  0x43, 0x000005D2,
  0x44, 0x000005D3,
  0x45, 0x000005D4,
  0x46, 0x000005D5,
  0x47, 0x000005D6,
  0x48, 0x000005D7,
  0x49, 0x000005D8,
  0x4A, 0x000000A2,
  0x4B, 0x0000002E,
  0x4C, 0x0000003C,
  0x4D, 0x00000028,
  0x4E, 0x0000002B,
  0x4F, 0x0000007C,
  0x50, 0x00000026,
  0x51, 0x000005D9,
  0x52, 0x000005DA,
  0x53, 0x000005DB,
  0x54, 0x000005DC,
  0x55, 0x000005DD,
  0x56, 0x000005DE,
  0x57, 0x000005DF,
  0x58, 0x000005E0,
  0x59, 0x000005E1,
  0x5A, 0x00000021,
  0x5B, 0x00000024,
  0x5C, 0x0000002A,
  0x5D, 0x00000029,
  0x5E, 0x0000003B,
  0x5F, 0x000000AC,
  0x60, 0x0000002D,
  0x61, 0x0000002F,
  0x62, 0x000005E2,
  0x63, 0x000005E3,
  0x64, 0x000005E4,
  0x65, 0x000005E5,
  0x66, 0x000005E6,
  0x67, 0x000005E7,
  0x68, 0x000005E8,
  0x69, 0x000005E9,
  0x6A, 0x000000A6,
  0x6B, 0x0000002C,
  0x6C, 0x00000025,
  0x6D, 0x0000005F,
  0x6E, 0x0000003E,
  0x6F, 0x0000003F,
  0x71, 0x000005EA,
  0x74, 0x000000A0,
  0x78, 0x00002017,
  0x79, 0x00000060,
  0x7A, 0x0000003A,
  0x7B, 0x00000023,
  0x7C, 0x00000040,
  0x7D, 0x00000027,
  0x7E, 0x0000003D,
  0x7F, 0x00000022,
  0x81, 0x00000061,
  0x82, 0x00000062,
  0x83, 0x00000063,
  0x84, 0x00000064,
  0x85, 0x00000065,
  0x86, 0x00000066,
  0x87, 0x00000067,
  0x88, 0x00000068,
  0x89, 0x00000069,
  0x8A, 0x000000AB,
  0x8B, 0x000000BB,
  0x8F, 0x000000B1,
  0x90, 0x000000B0,
  0x91, 0x0000006A,
  0x92, 0x0000006B,
  0x93, 0x0000006C,
  0x94, 0x0000006D,
  0x95, 0x0000006E,
  0x96, 0x0000006F,
  0x97, 0x00000070,
  0x98, 0x00000071,
  0x99, 0x00000072,
  0x9D, 0x000000B8,
  0x9F, 0x000000A4,
  0xA0, 0x000000B5,
  0xA1, 0x0000007E,
  0xA2, 0x00000073,
  0xA3, 0x00000074,
  0xA4, 0x00000075,
  0xA5, 0x00000076,
  0xA6, 0x00000077,
  0xA7, 0x00000078,
  0xA8, 0x00000079,
  0xA9, 0x0000007A,
  0xAF, 0x000000AE,
  0xB0, 0x0000005E,
  0xB1, 0x000000A3,
  0xB2, 0x000000A5,
  0xB3, 0x000000B7,
  0xB4, 0x000000A9,
  0xB5, 0x000000A7,
  0xB6, 0x000000B6,
  0xB7, 0x000000BC,
  0xB8, 0x000000BD,
  0xB9, 0x000000BE,
  0xBA, 0x0000005B,
  0xBB, 0x0000005D,
  0xBC, 0x000000AF,
  0xBD, 0x000000A8,
  0xBE, 0x000000B4,
  0xBF, 0x000000D7,
  0xC0, 0x0000007B,
  0xC1, 0x00000041,
  0xC2, 0x00000042,
  0xC3, 0x00000043,
  0xC4, 0x00000044,
  0xC5, 0x00000045,
  0xC6, 0x00000046,
  0xC7, 0x00000047,
  0xC8, 0x00000048,
  0xC9, 0x00000049,
  0xCA, 0x000000AD,
  0xD0, 0x0000007D,
  0xD1, 0x0000004A,
  0xD2, 0x0000004B,
  0xD3, 0x0000004C,
  0xD4, 0x0000004D,
  0xD5, 0x0000004E,
  0xD6, 0x0000004F,
  0xD7, 0x00000050,
  0xD8, 0x00000051,
  0xD9, 0x00000052,
  0xDA, 0x000000B9,
  0xE0, 0x0000005C,
  0xE1, 0x000000F7,
  0xE2, 0x00000053,
  0xE3, 0x00000054,
  0xE4, 0x00000055,
  0xE5, 0x00000056,
  0xE6, 0x00000057,
  0xE7, 0x00000058,
  0xE8, 0x00000059,
  0xE9, 0x0000005A,
  0xEA, 0x000000B2,
  0xF0, 0x00000030,
  0xF1, 0x00000031,
  0xF2, 0x00000032,
  0xF3, 0x00000033,
  0xF4, 0x00000034,
  0xF5, 0x00000035,
  0xF6, 0x00000036,
  0xF7, 0x00000037,
  0xF8, 0x00000038,
  0xF9, 0x00000039,
  0xFA, 0x000000B3,
  0xFF, 0x0000009F,
  0x110000, 0x110000
}; // CP424


} // namespace codecs
} // namespace quirinus
