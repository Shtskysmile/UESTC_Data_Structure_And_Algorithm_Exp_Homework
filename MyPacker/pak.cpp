#include "Packer.hpp"
using namespace std;
int main(int argc, char* argv[])
{
    Packer paker;
    paker.compressFiles(argc, argv);
    return 0;
}