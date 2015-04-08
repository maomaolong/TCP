#ifndef COMMON_H
#define COMMON_H

static void endianConvert32(unsigned int *data)
{
	*data = ((*data & 0xff000000) >> 24)
		| ((*data & 0x00ff0000) >> 8)
		| ((*data & 0x0000ff00) << 8)
		| ((*data & 0x000000ff) << 24);
}

#endif