#ifndef CPPPACKER_H
#define CPPPACKER_H

#include <bits/stdc++.h>
typedef long long ll;

class Packer {
private:
    std::ifstream fileStream;
    std::ofstream outFileStream;

    struct PointInfo {
        int index;
        ll weight;
    };

    std::vector<PointInfo> points;
    std::vector<PointInfo> minHeap;

    struct IndexInfo {
        int leftChild;
        int rightChild;
    } indexInfos[255];

    struct PathInfo {
        bool pathBits[260];
        int pathLength;
    } pathInfos[256], tempPathInfo;

    int heapTop, nextAvailableIndex = 256;
    ll totalWeight;
    std::string currentFileName;
    unsigned char bitCache = 0;
    int bitCachePosition = 0;

    void heapifyUp(const int& st);
    void heapifyDown(const int& st);
    void insertIntoHeap(const PointInfo& a);
    void removeFromHeap();
    void depthFirstSearch(int depth, PathInfo tph, int point);
    void writeBinary(ll x, int len);
    void flushBitCache();
    void extractFileName(std::string& dest, const std::string& source);

public:
    Packer();
    ~Packer();
    void compressFiles(int argc, char* argv[]);
};

#endif // CPPPACKER_H
