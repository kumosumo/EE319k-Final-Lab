//
// Created by jspspike on 4/24/18.
//

#include "Display.h"
#include "../tm4c123gh6pm.h"
#include "ST7735.h"
//#include "LCD.s"

int px=-1;
int py=-1;
int psize=-1;

int marSize[5] = {16,14,12,10,8};

const unsigned short clear[5][256] = {
		{//16x16
		0x1337, 0x1337, 0x1337, 0x1337, 0x1337, 0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337, 0x1337, 0x1337, 0x1337, 0x1337, 0x1337,
		0x1337, 0x1337, 0x1337, 0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337, 0x1337, 0x1337, 0x1337,
		0x1337, 0x1337, 0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337, 0x1337, 0x1337,
		0x1337, 0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337, 0x1337,
		0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337,
		0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337,
		0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337, 0x1337,
		0x1337, 0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337, 0x1337,
		0x1337, 0x1337, 0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337, 0x1337, 0x1337,
		0x1337, 0x1337, 0x1337, 0x1337, 0x1337, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1337, 0x1337, 0x1337, 0x1337, 0x1337,			
		},
		
		{//14x14
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		}, 
		
		{//12x12
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		},
		
		{//10x10
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 
		},
		
		{//8x8
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		}
};
const unsigned short marble[5][256] = {
		
		{//16x16
		0x1337, 0x1337, 0x1337, 0x1337, 0x1337, 0x1337, 0xF79E, 0xD6BA, 0xD69A, 0xEF5D, 0x1337, 0x1337, 0x1337, 0x1337, 0x1337, 0x1337,
		0x1337, 0x1337, 0x1337, 0x1337, 0xD677, 0x4A07, 0x1860, 0x1860, 0x08A0, 0x1942, 0x52C9, 0xB5D6, 0x1337, 0x1337, 0x1337, 0x1337,
		0x1337, 0x1337, 0x1337, 0x9C4C, 0x4140, 0x2040, 0x0000, 0x0040, 0x0920, 0x19C0, 0x21E0, 0x42A5, 0x8CD0, 0x1337, 0x1337, 0x1337,
		0x1337, 0x1337, 0xC54C, 0x61E0, 0x30C0, 0x0000, 0x00C0, 0x2220, 0x4A40, 0x61A0, 0x71A0, 0x81C0, 0x4183, 0x738D, 0x1337, 0x1337,
		0x1337, 0xC639, 0x8B20, 0x7A80, 0x1860, 0x00E0, 0x32A0, 0x49A0, 0x79A0, 0x71A0, 0x9260, 0x9260, 0x8200, 0x3984, 0x840F, 0x1337,
		0x1337, 0x5AA8, 0x82C0, 0x7AA0, 0x0060, 0x32A1, 0x31C0, 0x0000, 0x1880, 0x71E0, 0xAAE0, 0xA2A0, 0x9260, 0x6980, 0x3186, 0xFFDF,
		0x1337, 0x28E0, 0x9B60, 0x3980, 0x2223, 0x4322, 0x30E0, 0x1040, 0x0820, 0x0000, 0x0860, 0x5180, 0x9280, 0xA2A0, 0x3901, 0xCE59,
		0xDEFC, 0x5960, 0x9B60, 0x2980, 0x4346, 0x4B63, 0x4940, 0x3100, 0x28E0, 0x28E0, 0x20E0, 0x0040, 0x0040, 0x3120, 0x48E0, 0xBDF7,
		0xCEBB, 0x69C0, 0xA360, 0x3A01, 0x53E8, 0x5C25, 0x51A0, 0x4160, 0x3120, 0x4180, 0x8A80, 0xAB00, 0x7A40, 0x2920, 0x1120, 0xD739,
		0xE77E, 0x69E0, 0xC3C0, 0x6280, 0x542A, 0x64A9, 0x6322, 0x4980, 0x41A0, 0x3980, 0x51E0, 0x92C0, 0xAB00, 0xB2E0, 0x52A1, 0xE7BC,
		0x1337, 0x7241, 0xC3A0, 0xB360, 0x4B46, 0x756D, 0x7529, 0x6281, 0x51E0, 0x4A00, 0x5260, 0x72C0, 0xA300, 0xAAE0, 0x82A0, 0xF7DF,
		0x1337, 0xACF0, 0xBB80, 0xCC00, 0x7A80, 0x5B67, 0x63C6, 0x62C0, 0x5A20, 0x49E0, 0x5280, 0x62E0, 0x7AC0, 0x9A80, 0x9BA9, 0x1337,
		0x1337, 0x1337, 0x8AA0, 0xC3C0, 0xD420, 0x4980, 0x3100, 0x41A0, 0x5A20, 0x5A60, 0x4A40, 0x5B00, 0x5AC0, 0x7220, 0x1337, 0x1337,
		0x1337, 0x1337, 0xEF7E, 0x92C0, 0xBB60, 0x9B20, 0x2100, 0x4221, 0x8CEB, 0x5AE2, 0x52A0, 0x52C0, 0x4A80, 0xCE79, 0x1337, 0x1337,
		0x1337, 0x1337, 0x1337, 0xF7DF, 0x9BA8, 0x8AC0, 0x6B63, 0x7CEB, 0x8DCE, 0x5B64, 0x2180, 0x5346, 0xE75C, 0x1337, 0x1337, 0x1337,
		0x1337, 0x1337, 0x1337, 0x1337, 0x1337, 0xE75E, 0xBDF5, 0xA5D2, 0xAE54, 0xC6D7, 0xEFBD, 0x1337, 0x1337, 0x1337, 0x1337, 0x1337,
		},
		
		{//14x14
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xEF5D, 0xCE38, 0xCE38, 0xE71C, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		0xFFFF, 0xE6FA, 0x5A45, 0x1000, 0x0800, 0x0040, 0x1101, 0x52E9, 0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE13, 0x4140,
		0x2060, 0x0000, 0x00C0, 0x1A00, 0x3A00, 0x41A0, 0x4A44, 0xA594, 0xFFFF, 0xFFFF, 0xFFFF, 0xDEFB, 0x9320, 0x5160, 0x0000, 0x1160,
		0x4280, 0x71C0, 0x6960, 0x9240, 0x81E0, 0x3964, 0xAD34, 0xFFFF, 0xFFFF, 0x62A7, 0x9320, 0x3920, 0x0940, 0x3AA0, 0x1020, 0x5140,
		0x9A80, 0xAAC0, 0x9A80, 0x79C0, 0x2945, 0xFFFF, 0xEF9E, 0x3900, 0x9B80, 0x00C0, 0x32E3, 0x39A0, 0x0800, 0x0000, 0x0020, 0x4960,
		0x8A60, 0xA2A0, 0x4100, 0xC618, 0xC659, 0x61C0, 0x8B00, 0x19E2, 0x4BA5, 0x49A0, 0x3100, 0x28C0, 0x20C0, 0x0880, 0x0020, 0x2100,
		0x5920, 0xA555, 0xB5D8, 0x9260, 0x8AE0, 0x32C5, 0x5C47, 0x5A60, 0x4160, 0x3120, 0x49A0, 0xA2E0, 0x9AC0, 0x51C0, 0x08C0, 0xC6D7,
		0xD6FC, 0x8A40, 0xBBA0, 0x4AE4, 0x64EB, 0x6426, 0x5180, 0x41A0, 0x4180, 0x6220, 0xA300, 0xB300, 0x7240, 0xDF9C, 0xFFFF, 0x8280,
		0xCBC0, 0x8AE0, 0x648B, 0x7DCD, 0x6322, 0x51E0, 0x5220, 0x5AC0, 0x7AC0, 0xAB00, 0x8A20, 0xF7DF, 0xFFFF, 0xB552, 0xBB60, 0xD420,
		0x51C0, 0x41E1, 0x5A00, 0x5A00, 0x4A00, 0x5280, 0x6300, 0x7A40, 0xAC2C, 0xFFFF, 0xFFFF, 0xFFFF, 0x9BA7, 0xBB40, 0xBB80, 0x2900,
		0x3140, 0x73C6, 0x5AC1, 0x5AC0, 0x52C0, 0x6AE4, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xAC6D, 0x92A0, 0x62A0, 0x7469, 0x95CE,
		0x3A20, 0x2160, 0x740A, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xEF9F, 0xBDD4, 0xA5B2, 0xAE54, 0xC6D6, 0xF7DD,
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
		},
		
		{//12x12
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE71B, 0xBDB6, 0xBDB6, 0xDEDB, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF79D, 0x6AC5,
		0x0800, 0x0000, 0x0020, 0x0940, 0x534A, 0xE75D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDE, 0x7260, 0x2060, 0x0000, 0x11A0, 0x4240, 0x59A0,
		0x69C0, 0x4A05, 0xDEDB, 0xFFFF, 0xFFFF, 0x7B67, 0x8AC0, 0x0020, 0x2220, 0x3980, 0x79A0, 0x9220, 0xA280, 0x79E0, 0x3165, 0xFFFF,
		0xE73D, 0x4980, 0x6A60, 0x0981, 0x4280, 0x0800, 0x0000, 0x4140, 0x8A60, 0xAAA0, 0x4920, 0xBDF7, 0xAD76, 0x8260, 0x49E0, 0x3B45,
		0x5240, 0x30E0, 0x20A0, 0x1880, 0x0040, 0x10C0, 0x6180, 0x9492, 0x9D14, 0xB320, 0x4A40, 0x5429, 0x5B22, 0x4160, 0x3120, 0x59E0,
		0xAB00, 0x8260, 0x18C0, 0xB655, 0xC67A, 0xAAE0, 0x9B20, 0x544A, 0x6D2A, 0x5A00, 0x49A0, 0x41C0, 0x7AA0, 0xB320, 0x9A40, 0xCF19,
		0xFFFF, 0x92C0, 0xD400, 0x6281, 0x6CAA, 0x6B22, 0x5200, 0x5240, 0x5AC0, 0x8AE0, 0x8A20, 0xF7DF, 0xFFFF, 0xCE17, 0xB300, 0xC3C0,
		0x3100, 0x3120, 0x62A1, 0x5260, 0x5B00, 0x5240, 0xBD32, 0xFFFF, 0xFFFF, 0xFFFF, 0xC5B4, 0xA2C0, 0x6A60, 0x5B46, 0x8D6D, 0x3180,
		0x29C0, 0xA531, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7DF, 0xBDB3, 0x9D91, 0xA653, 0xBE75, 0xF7DE, 0xFFFF, 0xFFFF, 0xFFFF,
		},
		
		
		{//10x10
		0xFFFF, 0xFFFF, 0xFFFF, 0xDEDB, 0xA4D2, 0x9CF3, 0xD6BA, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x7B47, 0x0800, 0x0000, 0x00E0,
		0x1960, 0x6BAB, 0xFFFF, 0xFFFF, 0xFFFF, 0xA468, 0x4120, 0x0040, 0x3260, 0x71E0, 0x89E0, 0x79A0, 0x4A69, 0xFFFF, 0xDEDC, 0x6A20,
		0x2920, 0x32A1, 0x0820, 0x28A0, 0x8A60, 0xAAC0, 0x5920, 0xB5B7, 0x9CB3, 0x92E0, 0x19E2, 0x4B02, 0x30C0, 0x1880, 0x0840, 0x0880,
		0x5980, 0x8C0F, 0x9CB1, 0xAB20, 0x3AE6, 0x6426, 0x4940, 0x3140, 0x7A40, 0xA2E0, 0x4140, 0x95B2, 0xC638, 0xC340, 0x7302, 0x6DAE,
		0x6343, 0x49C0, 0x4A40, 0x92E0, 0xAA80, 0xC656, 0xFFFF, 0x9B20, 0xCBC0, 0x4A02, 0x5200, 0x5200, 0x5260, 0x62E0, 0x8220, 0xFFFF,
		0xFFFF, 0xEF7E, 0xAB00, 0x8260, 0x39E2, 0x7C68, 0x39C0, 0x3A60, 0xDEFB, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC5B2, 0x9D70, 0xA653,
		0xADB3, 0xFFFF, 0xFFFF, 0xFFFF,
		},
		
		{//8x8
		0xFFFF, 0xFFFF, 0xDEDA, 0x83CF, 0x7C0F, 0xD6BA, 0xFFFF, 0xFFFF, 0xFFFF, 0xB50E, 0x0800, 0x0040, 0x2980, 0x4160, 0x8C70, 0xFFFF,
		0xD6DB, 0x7A60, 0x00E0, 0x2980, 0x6960, 0xB2C0, 0x6140, 0xB5D7, 0x9C6F, 0x5A00, 0x3B23, 0x30A0, 0x0840, 0x1080, 0x5140, 0x838C,
		0xAC8D, 0x7A80, 0x548A, 0x51E0, 0x3940, 0x92A0, 0x7A00, 0x84EE, 0xCE57, 0xC340, 0x5BC7, 0x6BC5, 0x49C0, 0x5AA0, 0x9A80, 0xCDF4,
		0xFFFF, 0xB3E5, 0x9AA0, 0x28E0, 0x6302, 0x4240, 0x6B03, 0xFFFF, 0xFFFF, 0xFFFF, 0xCDD3, 0x952E, 0x9DD1, 0x9D52, 0xFFFF, 0xFFFF,
		}
};

void Display::initDisplay(){
	Output_Init();
}


void Display::drawMaze(const uint8_t maze[40][32]){		
		for(int i =0; i< 40;i++){
			for(int j =0; j< 32;j++){
				if(maze[i][j]==2){
					ST7735_FillRect((j*4), (i*4), 4, 4 ,ST7735_Color565(0,255,0));
				}
				if(maze[i][j]==3){
				ST7735_FillRect((j*4), (i*4), 4, 4 ,ST7735_Color565(255,0,0));
				}
				if(maze[i][j]==0){
					ST7735_FillRect((j*4), (i*4), 4, 4 ,ST7735_Color565(255,222,173));
				}
			}
		}
}

void Display::displayBlack() {
	ST7735_FillScreen(0x0000);
}

void Display::displayWhite() {
	ST7735_FillScreen(0xFFFF);
}

void Display::displayBlue() {
	ST7735_FillScreen(ST7735_Color565(102,204,255));
}

void Display::titleScreen(char* title1 = "Marble", char* title2 = "Maze", char* title3 = "Josh and Kumo"){
	ST7735_DrawString(4, 4, title1, 0xFFFF);
	ST7735_DrawString(8, 6, title2, 0xFFFF);
	ST7735_DrawString(4, 12, title3, 0xFFFF);
	
}

void Display::setMarble(uint8_t x, uint8_t y, uint8_t size){
	ST7735_DrawBitmap(x,y, marble[size], marSize[size], marSize[size]);
}

void Display::clearMarble(uint8_t x, uint8_t y, uint8_t size){
	if(px!=-1&&py!=-1&&psize!=-1){
		ST7735_DrawBitmap(px,py, clear[psize], marSize[psize], marSize[psize]);
	}
	px=x, py=y; psize=size;
}
void Display::drawMarble(uint8_t x, uint8_t y, uint8_t size){
	int val = 8-size;
	clearMarble((x-val),(y+val),size);
	setMarble((x-val),(y+val),size);	
}



