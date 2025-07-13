//
// Created by oleg on 12.07.2025.
//

#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

struct RawImageData {
    int width;
    int height;
    std::vector<unsigned char> data;
};

inline RawImageData loadGrayscaleBMP(const std::string &filePath) {
    std::ifstream in(filePath, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open BMP file.");

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    in.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    in.read(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.bfType != 0x4D42)
        throw std::runtime_error("Not a BMP file.");
    if (infoHeader.biBitCount != 8)
        throw std::runtime_error("Only 8-bit BMP supported.");
    if (infoHeader.biCompression != 0)
        throw std::runtime_error("Compressed BMP not supported.");

    int width = infoHeader.biWidth;
    int height = std::abs(infoHeader.biHeight);
    bool bottomUp = infoHeader.biHeight > 0;

    in.seekg(fileHeader.bfOffBits, std::ios::beg);

    int rowSize = ((width + 3) / 4) * 4;
    std::vector<unsigned char> data(width * height);

    for (int row = 0; row < height; ++row) {
        int targetRow = bottomUp ? height - 1 - row : row;
        std::vector<uint8_t> rowData(rowSize);
        in.read(reinterpret_cast<char *>(rowData.data()), rowSize);
        std::copy(rowData.begin(), rowData.begin() + width, data.begin() + targetRow * width);
    }

    return RawImageData{width, height, std::move(data)};
}

inline void saveAsGrayscaleBMP(const RawImageData &img, const std::string &filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot open output BMP file.");

    const int rowSize = ((img.width + 3) / 4) * 4;
    const int imageSize = rowSize * img.height;
    const int paletteSize = 256 * 4;
    const int fileSize = 14 + 40 + paletteSize + imageSize;

    out.put('B').put('M');
    uint32_t u32 = fileSize;
    out.write(reinterpret_cast<const char *>(&u32), 4);
    uint16_t u16 = 0;
    out.write(reinterpret_cast<const char *>(&u16), 2);
    out.write(reinterpret_cast<const char *>(&u16), 2);
    u32 = 14 + 40 + paletteSize;
    out.write(reinterpret_cast<const char *>(&u32), 4);

    u32 = 40;
    out.write(reinterpret_cast<const char *>(&u32), 4);
    int32_t i32 = img.width;
    out.write(reinterpret_cast<const char *>(&i32), 4);
    i32 = img.height;
    out.write(reinterpret_cast<const char *>(&i32), 4);
    u16 = 1;
    out.write(reinterpret_cast<const char *>(&u16), 2);
    u16 = 8;
    out.write(reinterpret_cast<const char *>(&u16), 2);
    u32 = 0;
    out.write(reinterpret_cast<const char *>(&u32), 4);
    u32 = imageSize;
    out.write(reinterpret_cast<const char *>(&u32), 4);
    i32 = 2835;
    out.write(reinterpret_cast<const char *>(&i32), 4);
    out.write(reinterpret_cast<const char *>(&i32), 4);
    u32 = 256;
    out.write(reinterpret_cast<const char *>(&u32), 4);
    u32 = 0;
    out.write(reinterpret_cast<const char *>(&u32), 4);

    for (int i = 0; i < 256; ++i) {
        out.put(i).put(i).put(i).put(0);
    }

    int padSize = std::max(0, rowSize - img.width);
    std::vector<uint8_t> padding(padSize, 0x00);
    for (int row = img.height - 1; row >= 0; --row) {
        const unsigned char *rowData = &img.data[row * img.width];
        out.write(reinterpret_cast<const char *>(rowData), img.width);
        out.write(reinterpret_cast<const char *>(padding.data()), padSize);
    }
}

inline bool isLineEmpty(const RawImageData &img, int row) {
    for (int col = 0; col < img.width; ++col)
        if (img.data[row * img.width + col] != 0xFF)
            return false;
    return true;
}

inline std::vector<uint8_t> encodeLine(const std::vector<unsigned char> &line) {
    std::vector<uint8_t> encoded;
    std::vector<bool> bits;

    for (size_t i = 0; i < line.size(); i += 4) {
        std::vector<unsigned char> chunk(4, 0xFF);
        for (size_t j = 0; j < 4 && i + j < line.size(); ++j)
            chunk[j] = line[i + j];

        bool allWhite = std::all_of(chunk.begin(), chunk.end(), [](unsigned char b) { return b == 0xFF; });
        bool allBlack = std::all_of(chunk.begin(), chunk.end(), [](unsigned char b) { return b == 0x00; });

        if (allWhite) {
            bits.push_back(0);
        } else if (allBlack) {
            bits.push_back(1);
            bits.push_back(0);
        } else {
            bits.push_back(1);
            bits.push_back(1);
            for (unsigned char b: chunk)
                for (int j = 7; j >= 0; --j)
                    bits.push_back((b >> j) & 1);
        }
    }

    uint8_t curByte = 0;
    for (size_t i = 0; i < bits.size(); ++i) {
        curByte = (curByte << 1) | bits[i];
        if ((i + 1) % 8 == 0) {
            encoded.push_back(curByte);
            curByte = 0;
        }
    }
    if (bits.size() % 8 != 0) {
        curByte <<= (8 - bits.size() % 8);
        encoded.push_back(curByte);
    }

    return encoded;
}

inline void saveBarch(const RawImageData &img, const std::string &outputPath) {
    std::ofstream out(outputPath, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot open .barch file");

    uint32_t w = img.width, h = img.height;
    out.write(reinterpret_cast<const char *>(&w), 4);
    out.write(reinterpret_cast<const char *>(&h), 4);

    std::vector<bool> lineIndexBits;
    std::vector<std::vector<uint8_t> > encodedLines;

    for (int row = 0; row < img.height; ++row) {
        if (isLineEmpty(img, row)) {
            lineIndexBits.push_back(1);
        } else {
            lineIndexBits.push_back(0);
            std::vector<unsigned char> line(img.data.begin() + row * img.width,
                                            img.data.begin() + (row + 1) * img.width);
            encodedLines.push_back(encodeLine(line));
        }
    }

    uint8_t byte = 0;
    for (size_t i = 0; i < lineIndexBits.size(); ++i) {
        byte = (byte << 1) | lineIndexBits[i];
        if ((i + 1) % 8 == 0) {
            out.put(byte);
            byte = 0;
        }
    }
    if (lineIndexBits.size() % 8 != 0) {
        byte <<= (8 - lineIndexBits.size() % 8);
        out.put(byte);
    }

    size_t encodedIdx = 0;
    for (bool empty: lineIndexBits) {
        if (!empty) {
            const std::vector<uint8_t> &line = encodedLines[encodedIdx++];
            uint32_t lineSize = static_cast<uint32_t>(line.size());
            out.write(reinterpret_cast<const char *>(&lineSize), sizeof(lineSize));
            out.write(reinterpret_cast<const char *>(line.data()), lineSize);
        }
    }
}


inline RawImageData loadBarch(const std::string &inputPath) {
    std::ifstream in(inputPath, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open .barch file");

    uint32_t width, height;
    in.read(reinterpret_cast<char *>(&width), 4);
    in.read(reinterpret_cast<char *>(&height), 4);

    size_t indexBytes = (height + 7) / 8;
    std::vector<bool> lineIsEmpty(height);

    for (size_t i = 0; i < indexBytes; ++i) {
        uint8_t byte = in.get();
        for (int bit = 7; bit >= 0; --bit) {
            int row = i * 8 + (7 - bit);
            if (row < height)
                lineIsEmpty[row] = (byte >> bit) & 1;
        }
    }

    std::vector<unsigned char> decodedData(width * height);
    for (int row = 0; row < static_cast<int>(height); ++row) {
        if (lineIsEmpty[row]) {
            std::fill(decodedData.begin() + row * width, decodedData.begin() + (row + 1) * width, 0xFF);
        } else {
            uint32_t lineSize;
            in.read(reinterpret_cast<char *>(&lineSize), 4);
            std::vector<uint8_t> encoded(lineSize);
            in.read(reinterpret_cast<char *>(encoded.data()), lineSize);

            std::vector<bool> bits;
            for (uint8_t b: encoded) {
                for (int i = 7; i >= 0; --i)
                    bits.push_back((b >> i) & 1);
            }

            size_t pos = 0;
            int count = 0;
            while (count < width && pos < bits.size()) {
                int first = bits[pos++];
                if (first == 0) {
                    for (int i = 0; i < 4 && count < width; ++i)
                        decodedData[row * width + count++] = 0xFF;
                } else {
                    int second = bits[pos++];
                    if (second == 0) {
                        for (int i = 0; i < 4 && count < width; ++i)
                            decodedData[row * width + count++] = 0x00;
                    } else {
                        for (int i = 0; i < 4 && count < width; ++i) {
                            uint8_t byte = 0;
                            for (int j = 0; j < 8; ++j)
                                byte = (byte << 1) | bits[pos++];
                            decodedData[row * width + count++] = byte;
                        }
                    }
                }
            }
        }
    }

    return RawImageData{static_cast<int>(width), static_cast<int>(height), std::move(decodedData)};
}
#endif //COMPRESSOR_H
