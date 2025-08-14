#ifndef UNPACKER_H
#define UNPACKER_H
#include <bits/stdc++.h>
typedef long long ll;
class UnPacker {
public:
    UnPacker(const std::string& filename);
    ~UnPacker();
    void unpack();

private:
    std::ifstream fileStream;
    std::ofstream outFileStream;
    struct IndexInfo {
        int leftChild;
        int rightChild;
    } indexInfos[255];
    ll totalWeight;
    int fileCount;
    unsigned char bitCache = 0;
    int bitCachePosition = 0;
    int point;
    std::string currentFileName;
    ll binin(int len);
};

#endif // UNPACKER_H
