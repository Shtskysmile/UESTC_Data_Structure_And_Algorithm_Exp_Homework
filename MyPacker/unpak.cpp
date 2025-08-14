#include "UnPacker.hpp"
using namespace std;
int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "No file";
        return 1;
    }
    UnPacker unpak(argv[1]);
    unpak.unpack();
    return 0;
}