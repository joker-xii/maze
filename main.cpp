#include "maze.h"
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    if (argc < 3)
        cout << "Arguments count mismatch, expected " << 2 << " numbers, got " << argc - 1 << endl;

    int N = atoi(argv[1]), M = atoi(argv[2]);
    cout << "Get maze of [" << N << "x" << M << "]" << endl;
    maze m(N, M);
    cout << m;
    if (argc == 4) {
        ofstream ofs(argv[3]);
        ofs << m;
        ofs.close();
        cout << "Printed maze to file:" << argv[3] << endl;
    }
    return 0;
}
