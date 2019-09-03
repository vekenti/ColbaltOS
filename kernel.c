#include <stddef.h>
#include <stdint.h>

enum colors {
	BLACK = 0x0,
	BLUE = 0x1,
	GREEN = 0x2,
	CYAN = 0x3,
	RED = 0x4,
	MAGENTA = 0x5,
	BROWN = 0x6,
	LIGHT_GRAY = 0x7,
	DARK_GRAY = 0x8,
	LIGHT_BLUE = 0x9,
	LIGHT_GREEN = 0xA,
	LIGHT_CYAN = 0xB,
	LIGHT_RED = 0xC,
	LIGHT_MAGENTA = 0xD,
	YELLOW = 0xE,
	WHITE = 0xF
};

// Beginning of framebuffer.
volatile uint16_t* s_buffer = (uint16_t*)0xB8000;
// 80x25 Resolution
const int S_WIDTH = 80;
const int S_HEIGHT = 25;
// Set cursor to (0, 0) and color to 0x0F
unsigned int s_pos = 0;
int s_col = 0x0F;

void s_init()
{
	for(s_pos = 0; s_pos < S_WIDTH * S_HEIGHT; s_pos++)
	{
		s_buffer[s_pos] = 0;
	}

	s_pos = 0;
}

void s_scroll()
{
	int prev_pos = s_pos;
	for(s_pos = 0; s_pos < S_WIDTH * S_HEIGHT; s_pos++)
	{
		s_buffer[s_pos - (S_WIDTH)] = s_buffer[s_pos];

	}

	s_pos = prev_pos;
}

void s_print(const char *text, const char color)
{
	for(; *text != 0; text++)
	{
		switch(*text)
		{
			case '\n':
				if( (s_pos) > S_WIDTH*S_HEIGHT)
				{
					s_scroll();
					s_pos -= ( (S_WIDTH) + (s_pos % S_WIDTH) );
				}
				else
				{
					s_pos += ( (S_WIDTH) - (s_pos % S_WIDTH) );
				}
				break;
			default:
				s_buffer[s_pos++] = (color << 8) | *text;
		}
	}
}

void kernel_main()
{
	s_init();
	s_print("COLBALT KERNEL\nV.1\n", s_col);
	//s_print("\ntest\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28", s_col);
}
