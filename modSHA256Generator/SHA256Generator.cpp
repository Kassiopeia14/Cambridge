#include "SHA256Generator.h"

SHA256Generator::SHA256Generator()
{
	ctx.datalen = 0;
	ctx.bitlen[0] = 0;
	ctx.bitlen[1] = 0;
	ctx.state[0] = 0x6a09e667;
	ctx.state[1] = 0xbb67ae85;
	ctx.state[2] = 0x3c6ef372;
	ctx.state[3] = 0xa54ff53a;
	ctx.state[4] = 0x510e527f;
	ctx.state[5] = 0x9b05688c;
	ctx.state[6] = 0x1f83d9ab;
	ctx.state[7] = 0x5be0cd19;
}

SHA256Generator::~SHA256Generator()
{
}

std::string SHA256Generator::generate(const char* data)
{
	int strLen = strlen(data);
	unsigned char hash[32];

	SHA256Update((unsigned char*)data, strLen);
	SHA256Final(hash);

	std::stringstream ss;

	for (int i = 0; i < 32; i++) {
		ss << std::hex << (uint16_t)hash[i];
	}

	return ss.str();
}

void SHA256Generator::SHA256Transform(uchar data[])
{
	uint a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	for (; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	a = ctx.state[0];
	b = ctx.state[1];
	c = ctx.state[2];
	d = ctx.state[3];
	e = ctx.state[4];
	f = ctx.state[5];
	g = ctx.state[6];
	h = ctx.state[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
		t2 = EP0(a) + MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	ctx.state[0] += a;
	ctx.state[1] += b;
	ctx.state[2] += c;
	ctx.state[3] += d;
	ctx.state[4] += e;
	ctx.state[5] += f;
	ctx.state[6] += g;
	ctx.state[7] += h;

}

void SHA256Generator::SHA256Update(uchar data[], uint len)
{
	for (uint i = 0; i < len; ++i) {
		ctx.data[ctx.datalen] = data[i];
		ctx.datalen++;
		if (ctx.datalen == 64) {
			SHA256Transform(ctx.data);
			DBL_INT_ADD(ctx.bitlen[0], ctx.bitlen[1], 512);
			ctx.datalen = 0;
		}
	}
}

void SHA256Generator::SHA256Final(uchar hash[])
{
	uint i = ctx.datalen;

	if (ctx.datalen < 56) {
		ctx.data[i++] = 0x80;

		while (i < 56)
			ctx.data[i++] = 0x00;
	}
	else {
		ctx.data[i++] = 0x80;

		while (i < 64)
			ctx.data[i++] = 0x00;

		SHA256Transform(ctx.data);
		memset(ctx.data, 0, 56);
	}

	DBL_INT_ADD(ctx.bitlen[0], ctx.bitlen[1], ctx.datalen * 8);
	ctx.data[63] = ctx.bitlen[0];
	ctx.data[62] = ctx.bitlen[0] >> 8;
	ctx.data[61] = ctx.bitlen[0] >> 16;
	ctx.data[60] = ctx.bitlen[0] >> 24;
	ctx.data[59] = ctx.bitlen[1];
	ctx.data[58] = ctx.bitlen[1] >> 8;
	ctx.data[57] = ctx.bitlen[1] >> 16;
	ctx.data[56] = ctx.bitlen[1] >> 24;
	SHA256Transform(ctx.data);

	for (i = 0; i < 4; ++i) {
		hash[i] = (ctx.state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (ctx.state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (ctx.state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx.state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx.state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx.state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx.state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx.state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}