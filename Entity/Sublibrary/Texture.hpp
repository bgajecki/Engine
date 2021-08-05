#pragma once

#include <cstdio> // File operations
#include <cmath> // abs
#include <algorithm>
#include <cstdint> // Data types
#include <./zlib/zlib.h> // uncompress
#include <./GL/glut.h>

#if defined(__MINGW32__) || defined(__MINGW64__)
#define GL_BGR_EXT 0x80E0
uint64_t _byteswap_ulong(uint64_t bits);
#else
#define _CRT_SECURE_NO_DEPRECATE
#include <intrin.h>
#endif

namespace Engine
{
	typedef GLuint Texture;

	typedef unsigned long DataSize;
	typedef uint32_t DataInformation;
	typedef uint8_t Data;
	typedef int16_t DataOperation; // A special data type for date operations used in PaethPredictor to prevent overflow and underflow
	typedef Data* DataArray;

	Data PaethPredictor(Data a, Data b, Data c);
	Texture loadTexture(const char* filename); // Load texture from PNG file
	Texture loadTextureBMP(const char* filename); // Load texture from BMP file
}