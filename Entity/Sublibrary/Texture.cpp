#include "Texture.hpp"

#if defined(__MINGW32__) || defined(__MINGW64__)
uint64_t _byteswap_ulong(uint64_t bits)
{
	uint64_t r = (bits & 0xffu) << 24;
	r |= (bits << 8) & 0xff0000u;
	r |= ((bits >> 8) & 0xff00u);
	r |= ((bits >> 24) & 0xffu);

	return r;
}
#endif

namespace Engine
{
	Data PaethPredictor(Data a, Data b, Data c)
	{
		DataOperation p, pa, pb, pc, _a, _b, _c;
		_a = static_cast<DataOperation>(a);
		_b = static_cast<DataOperation>(b);
		_c = static_cast<DataOperation>(c);
		p = _a + _b - _c;
		pa = abs(p - _a);
		pb = abs(p - _b);
		pc = abs(p - _c);
		if (pa <= pb && pa <= pc)
			return a;
		else if (pb <= pc)
			return b;
		else
			return c;
	}
	
	Texture loadTexture(const char* filename)
	{
		DataInformation width,
			height,
			bpp;
		Data bitDeep,
			colorType;
		DataSize fSize,
			iDataPos,
			iDataSize,
			uncompressedDataSize,
			imageSize;
		DataArray fileData,
			compressedData,
			uncompressedData,
			*imageData,
			reverseImageData;

		FILE* file = fopen(filename, "rb"); // Read file binary
		if (file == NULL) return false;

		fseek(file, 0, SEEK_END); // Move the pointer to the end
		fSize = ftell(file); // Get the file size from the pointer
		rewind(file); // Set the pointer to the beginning

		fileData = new Data[fSize]; // Create array with file size
		fread(fileData, 1, fSize, file); // Read all file
		fclose(file);
		// Finish working with the file

		if (fileData[0] != 0x89 || fileData[1] != 'P' || fileData[2] != 'N' || fileData[3] != 'G')
			return false;

		// Read values from file
		width = static_cast<DataInformation>(_byteswap_ulong(*(DataInformation*) & (fileData[0x10]))); // Conversion from litle endian to big endian
		height = static_cast<DataInformation>(_byteswap_ulong(*(DataInformation*) & (fileData[0x14])));
		bitDeep = fileData[0x18];
		colorType = fileData[0x19];
		for (iDataPos = 0; iDataPos < fSize; ++iDataPos)
			if (fileData[iDataPos] == 'I' && fileData[iDataPos + 1] == 'D' && fileData[iDataPos + 2] == 'A' && fileData[iDataPos + 3] == 'T')
				break;
		iDataSize = static_cast<DataSize>(_byteswap_ulong(*(DataInformation*) & (fileData[iDataPos - 4])));

		switch (colorType)
		{
		case 0: // Grey scale
			if (bitDeep == 16)
				bpp = 2;
			else
				bpp = 1;
			break;
		case 2: // RGB
			bpp = 3 * (bitDeep / 8);
			break;
		case 3: // Palette index and PLTE
			bpp = 2; // I'm not sure about it
			break;
		case 4: // Grey scale and alpha channel
			bpp = 2 * (bitDeep / 8);
			break;
		case 6: // RGBA
			bpp = 4 * (bitDeep / 8);
			break;
		}

		imageSize = width * height * bpp; // width * heights * bytes on pixel
		compressedData = new Data[iDataSize];
		for (DataSize i = 0; i < iDataSize; ++i)
			compressedData[i] = fileData[i + iDataPos + 4]; // Read compressed data
		delete[] fileData; // Delete array with file data

		uncompressedDataSize = imageSize + height; // Picture size(bytes) + filter code
		uncompressedData = new unsigned char[uncompressedDataSize];
		int nResult = uncompress(uncompressedData, &uncompressedDataSize, compressedData, iDataSize); // Uncompress data

		delete[] compressedData; //  Delete array with compressed data
		imageData = new Data*[height];
		for (DataSize i = 0; i < height; ++i)
			imageData[i] = new Data[width * bpp];

		if (nResult == Z_OK)
		{
			
			for (DataSize i = 0, k = 0; i < uncompressedDataSize; i += width * bpp + 1, ++k) // Read filter digit
			{
				switch (uncompressedData[i]) // Data filter
				{
				case 0: // None
					for (DataSize j = i, d = 0; j < i + width * bpp; ++j, ++d)
						imageData[k][d] = uncompressedData[j + 1];
					break;
				case 1: // Left - getting the value of a given channel earlier and summing it up
					for (DataSize j = i, d = 0; j < i + bpp; ++j, ++d)
						imageData[k][d] = uncompressedData[j + 1];
					for (DataSize j = i + bpp, d = bpp; j < i + width * bpp; ++j, ++d)
						imageData[k][d] = uncompressedData[j + 1] + imageData[k][d -bpp];
					break;
				case 2: // Up - getting the value ​​from the top row and summing it up
					if(k == 0)
						for (DataSize j = i, d = 0; j < i + width * bpp; ++j, ++d)
							imageData[k][d] = uncompressedData[j + 1];
					else
						for (DataSize j = i, d = 0; j < i + width * bpp; ++j, ++d)
							imageData[k][d] = uncompressedData[j + 1] + imageData[k - 1][d];
					break;
				case 3: // Average - average between Up and Down methods rounded down
					for (DataSize j = i, d = 0; j < i + bpp; ++j, ++d)
						imageData[k][d] = uncompressedData[j + 1];
					if (k == 0)
						for (DataSize j = i + bpp, d = bpp; j < i + width * bpp; ++j, ++d)
							imageData[k][d] = uncompressedData[j + 1] + ((imageData[k][d - bpp]) / 2);
					else
						for (DataSize j = i + bpp, d = bpp; j < i + width * bpp; ++j, ++d)
							imageData[k][d] = uncompressedData[j + 1] + ((imageData[k][d - bpp] + imageData[k - 1][d]) / 2);
					break;

				case 4: // Paeth - looking for the best method (a - left, b - up, c - left up)
					for (DataSize j = i, d = 0; j < i + bpp; ++j, ++d)
						imageData[k][d] = uncompressedData[j + 1];
					if (k == 0)
						for (DataSize j = i + bpp, d = bpp; j < i + width * bpp; ++j, ++d)
							imageData[k][d] = uncompressedData[j + 1] + PaethPredictor(imageData[k][d - bpp], 0, 0);
					else
						for (DataSize j = i + bpp, d = bpp; j < i + width * bpp; ++j, ++d)
							imageData[k][d] = uncompressedData[j + 1] + PaethPredictor(imageData[k][d - bpp], imageData[k - 1][d], imageData[k - 1][d - bpp]);

					break;

				}
				// One-dimensional array
				/*
				for (unsigned long i = 0, k = 0; i < uncompressedDataSize; i += width * bpp + 1, ++k) // Wczytuje numer filtru danych
				{
					switch (uncompressedData[i]) // Filtr danych
					{
					case 0:
						for (unsigned long j = i; j < i + width * bpp; ++j)
							imageData[j - k] = uncompressedData[j + 1];
						break;
					case 1:
						for (unsigned long j = i; j < i + bpp; ++j)
							imageData[j - k] = imageData[j + 1];
						for (unsigned long j = i + bpp; j < i + width * bpp; ++j)
							imageData[j - k] = uncompressedData[j + 1] + imageData[j - k - bpp];
						break;
					case 2:
						for (unsigned long j = i; j < i + width * bpp; ++j)
							imageData[j - k] = uncompressedData[j + 1] + imageData[j - k - width * bpp];

						break;
					case 3:
						for (unsigned long j = i; j < i + bpp; ++j)
							imageData[j - k] = uncompressedData[j + 1];
						for (unsigned long j = i + bpp; j < i + width * bpp; ++j)
							imageData[j - k] = uncompressedData[j + 1] + ((imageData[j - k - bpp] + imageData[j - k - width * bpp]) / 2);
						break;

					case 4:
						for (unsigned long j = i; j < i + bpp; ++j)
							imageData[j - k] = uncompressedData[j + 1];
						for (unsigned long j = i + bpp; j < i + width * bpp; ++j)
							imageData[j - k] = uncompressedData[j + 1] + PaethPredictor(imageData[j - k - bpp], imageData[j - k - width * bpp], imageData[j - k - width * bpp - bpp]);
						break;

					}
					*/
			}
			delete[] uncompressedData; // Delete uncompressed data before filtering

			// Change data to texture
			// I assume color type 6 (RGBA) and bit depth 8, which is one byte per channel
			reverseImageData = new Data[imageSize];
			for (DataSize i = height, k = 0; (long)i - 1 >= 0; --i)
				for (DataSize j = 0; j < width * bpp; ++j, ++k)
					reverseImageData[k] = imageData[i - 1][j];

			for (DataSize i = 0; i < height; ++i)
				delete[] imageData[i];
			delete[] imageData;


			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, reverseImageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			delete[] reverseImageData;
			return texture;

		}
		delete[] uncompressedData;
		return false;
	}

	Texture loadTextureBMP(const char* filename)
	{
		Data header[54];
		DataInformation dataPos,
			width,
			height,
			imageSize;

		DataArray data;

		FILE* file = fopen(filename, "rb");

		if (file == NULL) 
			return false;

		if (fread(header, 1, 54, file) != 54)
			return false;

		if (header[0] != 'B' || header[1] != 'M')
			return false;

		dataPos = *(DataInformation*) & (header[0x0A]);
		imageSize = *(DataInformation*) & (header[0x22]);
		width = *(DataInformation*) & (header[0x12]);
		height = *(DataInformation*) & (header[0x16]);

		if (imageSize == 0)    imageSize = width * height * 3;
		if (dataPos == 0)      dataPos = 54;

		data = new Data[imageSize];

		fread(data, 1, imageSize, file);

		fclose(file);

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		delete[] data;
		return texture;
	}
}