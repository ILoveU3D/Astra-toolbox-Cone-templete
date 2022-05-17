#include<cstdio>
using namespace std;

template <typename T>
void readRaw(const char* fileName, T *p, long int length){
    FILE *f = fopen(fileName, "rb");
    fread(p, sizeof(T), length, f);
    fclose(f);
}

template <typename T>
void writeRaw(const char* fileName, T *p, long int length){
    FILE *f = fopen(fileName, "wb");
    fwrite(p, sizeof(T), length, f);
    fclose(f);
}