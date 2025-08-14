#include "Packer.hpp"
using namespace std;

void Packer::heapifyUp(const int& st)
{
    int i = st, j = i / 2;
    minHeap[0] = minHeap[i];
    while (j > 0) {
        if (minHeap[0].weight >= minHeap[j].weight)
            break;
        minHeap[i] = minHeap[j];
        i = j;
        j = i / 2;
    }
    minHeap[i] = minHeap[0];
}

void Packer::heapifyDown(const int& st)
{
    int i = st, j = i * 2;
    minHeap[0] = minHeap[i];
    while (j <= heapTop) {
        if (j < heapTop && minHeap[j].weight > minHeap[j + 1].weight)
            j++;
        if (minHeap[0].weight <= minHeap[j].weight)
            break;
        minHeap[i] = minHeap[j];
        i = j;
        j = i * 2;
    }
    minHeap[i] = minHeap[0];
}

void Packer::insertIntoHeap(const PointInfo& a)
{
    heapTop++;
    minHeap[heapTop] = a;
    heapifyUp(heapTop);
}

void Packer::removeFromHeap()
{
    minHeap[1] = minHeap[heapTop];
    heapTop--;
    heapifyDown(1);
}

// 深度优先搜索译码
void Packer::depthFirstSearch(int depth, PathInfo tph, int point)
{
    // 走到了叶子节点
    if (point < 256) {
        pathInfos[point] = tph;
        return;
    }
    tph.pathLength++;
    // 保存bit串
    tph.pathBits[depth] = 0;
    depthFirstSearch(depth + 1, tph, indexInfos[point - 256].leftChild);
    tph.pathBits[depth] = 1;
    depthFirstSearch(depth + 1, tph, indexInfos[point - 256].rightChild);
}

void Packer::writeBinary(ll x, int len)
{
    // x是要被写入的数据
    // len是要写入多少个bit
    for (int i = 1; i <= len; i++) {
        bitCache = (bitCache << 1) + ((x >> (len - i)) & 1);
        bitCachePosition++;
        if (bitCachePosition == 8) {
            bitCachePosition = 0;
            outFileStream.put(bitCache);
        }
    }
}

// 清空缓存
void Packer::flushBitCache()
{
    // 清空缓存区
    if (bitCachePosition == 0)
        return;
    bitCache = bitCache << (8 - bitCachePosition);
    outFileStream.put(bitCache);
}

void Packer::extractFileName(std::string& dest, const std::string& source)
{
    // 从一个包含文件路径的字符串中提取出文件名。
    size_t pos = source.find_last_of("/\\");
    dest = source.substr(pos + 1);
}

Packer::Packer()
{
    // 堆顶标志
    heapTop = 0;
    // 一个字节有256个数
    nextAvailableIndex = 256;
    // Huffman的总权重
    totalWeight = 0;
    bitCachePosition = 0;
    points.resize(511);
    minHeap.resize(2048);
}

Packer::~Packer()
{
    // 清理资源
    // 关闭输入文件流和输出文件流
    if (fileStream.is_open())
        fileStream.close();
    if (outFileStream.is_open())
        outFileStream.close();
}

void Packer::compressFiles(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "No file\n";
        return;
    }

    // 修改后
    extractFileName(currentFileName, argv[1]);
    // 去掉后缀标签
    currentFileName = currentFileName.substr(0, currentFileName.length() - 4);
    std::string outputFileName = string(currentFileName) + ".myzip";
    outFileStream.open(outputFileName, std::ios::binary);
    if (!outFileStream.is_open()) {
        std::cout << "Failed to open file : "  + outputFileName + "\n";
        return;
    }

    for (int i = 0; i < 511; i++)
        // 初始化为i
        points[i].index = i;

    std::cout << "Counting Files Bytes (" << argc - 1 << " Files)\n";
    unsigned char ch;
    for (int Fi = 1; Fi < argc; Fi++) {
        // 根据命令行参数解压对应的文件
        // 打开当前需要解压的文件，文件名称为argv[F1]
        extractFileName(currentFileName, argv[Fi]);
        fileStream.open(argv[Fi], std::ios::binary);

        if (fileStream.is_open()) {
            // 获取字符，统计频率
            ch = fileStream.get();
            while (fileStream) {
                totalWeight++;
                points[ch].weight++;
                ch = fileStream.get();
            }
        } else {
            std::cout << "Failed to open file : " << currentFileName << "\n";
            return;
        }
        fileStream.close();
    }

    // 通过字符频率构建Huffman Tree
    for (int i = 0; i < 256; i++)
        insertIntoHeap(points[i]);

    // 填充Huffman Tree的510个节点
    // indexInfos前256个元素全为非叶子节点。
    // indexInfos[510-256]为Huffman Tree的树根
    while (nextAvailableIndex < 511) {
        // 获取最小堆中的两个元素，构建Huffman Tree
        PointInfo a = minHeap[1];
        removeFromHeap();
        indexInfos[nextAvailableIndex - 256].leftChild = a.index;
        points[nextAvailableIndex].weight = a.weight;
        a = minHeap[1];
        removeFromHeap();
        indexInfos[nextAvailableIndex - 256].rightChild = a.index;
        points[nextAvailableIndex].weight += a.weight;
        insertIntoHeap(points[nextAvailableIndex]);
        nextAvailableIndex++;
    }

    // 在压缩文件中存放Huffman Tree
    // 使用深度优先搜索（DFS）遍历 Huffman 树，生成每个字节的编码路径。
    tempPathInfo.pathLength = 0;
    depthFirstSearch(0, tempPathInfo, 510);
    // 将 Huffman 树的左孩子和右孩子信息写入输出文件。
    for (int i = 0; i < 255; i++) {
        writeBinary(indexInfos[i].leftChild, 9);
        writeBinary(indexInfos[i].rightChild, 9);
    }
    // 写入被压缩的文件数量
    writeBinary(argc - 1, 32);

    for (int Fi = 1; Fi < argc; Fi++) {
        /**
         * @brief 压缩每一个文件。
         */
        extractFileName(currentFileName, argv[Fi]);
        fileStream.open(argv[Fi], std::ios::binary);
        if (fileStream.is_open()) {
            // 字节个数
            ll wi = 0;
            double pct = 0;
            std::cout << "Packing File " << currentFileName << " (" << Fi << "/" << argc - 1 << ")\n";
            std::cout << "Counting";
            ch = fileStream.get();
            while (fileStream) {
                // 统计字节个数
                wi++;
                ch = fileStream.get();
            }

            // 写入当前文件名称长度和文件名称
            int len = currentFileName.length();
            writeBinary(len, 8);
            for (int i = 0; i < len; i++)
                writeBinary(currentFileName[i], 8);

            // 以long long形式写入文件大小
            writeBinary(wi, 64);
            fileStream.clear();
            // 将文件流 fileStream 的读取位置移动到文件的开头
            fileStream.seekg(0, std::ios::beg);
            for (ll p = 0; p < wi; p++) {
                if (int(pct * 100) != int(double(p + 1) / double(wi) * 100)) {
                    // 输出压缩的进程
                    std::cout << "\rPacking: " << int(double(p + 1) / double(wi) * 100) << "%";
                    pct = double(p + 1) / double(wi);
                }
                // 压缩每一个char
                ch = fileStream.get();
                for (int i = 0; i < pathInfos[ch].pathLength; i++) {
                    writeBinary(pathInfos[ch].pathBits[i] ? 1 : 0, 1);
                }
            }
            fileStream.close();
            std::cout << "\rDone!            \n";
        } else {
            std::cout << "Failed to open file : " << currentFileName << "\n";
            return;
        }
    }
    flushBitCache();
    outFileStream.close();
}