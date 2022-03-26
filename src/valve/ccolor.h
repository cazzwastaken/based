#pragma once

struct Color_t
{
	unsigned char r, g, b, a;

	Color_t() = default;

	Color_t(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 255) : r(_r), g(_g), b(_b), a(_a) { }

	struct palletes_t
	{
		static auto red(unsigned char alpha = 255) { return Color_t(255, 0, 0, alpha); }
		static auto green(unsigned char alpha = 255) { return Color_t(0, 255, 0, alpha); }
		static auto blue(unsigned char alpha = 255) { return Color_t(0, 0, 255, alpha); }
		static auto black(unsigned char alpha = 255) { return Color_t(0, 0, 0, alpha); }
		static auto white(unsigned char alpha = 255) { return Color_t(255, 255, 255, alpha); }
	};
};
