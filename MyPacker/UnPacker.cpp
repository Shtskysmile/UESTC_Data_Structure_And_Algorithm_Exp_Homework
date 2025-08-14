#include "UnPacker.hpp"
using namespace std;

UnPacker::UnPacker(const std::string& filename)
{
    fileStream.open(filename, std::ios::binary);
    if (!fileStream.is_open()) {
        std::cout << "Failed to open Pak file\n";
        exit(1);
    }
    // 读取Huffman Tree信息
    for (int i = 0; i < 255; i++) {
        indexInfos[i].leftChild = binin(9);
        indexInfos[i].rightChild = binin(9);
    }
    // 读取文件数量
    fileCount = binin(32);
}

UnPacker::~UnPacker()
{
    if (fileStream.is_open())
        fileStream.close();
}

ll UnPacker::binin(int len)
{
    // 读取len个bit，返回一个long long
    ll x = 0;
    if (bitCachePosition == 0) {
        bitCache = fileStream.get();
        bitCachePosition = 8;
    }
    for (int i = 1; i <= len; i++) {
        x = (x << 1) + ((bitCache >> 7) & 1);
        bitCachePosition--;
        bitCache <<= 1;
        if (bitCachePosition == 0) {
            bitCache = fileStream.get();
            bitCachePosition = 8;
        }
    }
    return x;
}

void UnPacker::unpack()
{
    for (int Fi = 0; Fi < fileCount; Fi++) {
        // 解压缩第Fi个文件
        // 读取当前文件名称长度和文件名
        int len = binin(8);
        currentFileName.resize(len);
        for (int i = 0; i < len; i++)
            currentFileName[i] = binin(8);

        // 建立新的解压缩文件
        outFileStream.open(currentFileName, std::ios::binary);
        if (outFileStream.is_open()) {
            double pct = 0;
            // 读取总大小
            totalWeight = binin(64);
            std::cout << "Unpacking File " << currentFileName << " (" << Fi + 1 << "/" << fileCount << ")\n";

            // Huffman Tree的树根
            point = 510;
            for (ll p = 0; p < totalWeight; p++) {
                // 计算压缩进度
                if (int(pct * 100) != int(double(p + 1) / double(totalWeight) * 100)) {
                    std::cout << "\r" << int(double(p + 1) / double(totalWeight) * 100) << "%";
                    pct = double(p + 1) / double(totalWeight);
                }

                // Huffman译码
                // point小于256代表读取到了叶子节点
                // point对应了char信息
                while (point >= 256)
                    if (binin(1) == 0)
                        point = indexInfos[point - 256].leftChild;
                    else
                        point = indexInfos[point - 256].rightChild;

                // 写入译码信息
                outFileStream.put(static_cast<unsigned char>(point));
                // point回到树根
                point = 510;
            }
            // 关闭文件，准备解压下一份文件。
            outFileStream.close();
            std::cout << "\rDone!    \n";
        } else {
            std::cout << "Failed to open file : " << currentFileName << "\n";
            exit(1);
        }
    }
}