// ParseBin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <stdio.h>

typedef struct {
    UINT32 vertexCount;
    UINT32 featureCount;
} GeometryHeader;

typedef struct {
    FLOAT x;
    FLOAT y;
    FLOAT z;
} VertexPosition;


void parseVertex(LPVOID pBuf) {
    UCHAR* pTemp = (UCHAR*)pBuf;
    GeometryHeader* pHeader = (GeometryHeader*)pTemp;
    printf("%d, %d", pHeader->vertexCount, pHeader->featureCount);
    pTemp = (UCHAR*)pBuf + sizeof(GeometryHeader);
    for (int i = 0; i < pHeader->vertexCount; ++i) {
        VertexPosition* pPos = (VertexPosition*)pTemp;
        printf("%f, %f, %f\n", pPos->x, pPos->y, pPos->z);
        pTemp += sizeof(VertexPosition);
    }
}

int main()
{
    HANDLE hFile = CreateFile("0.bin", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("open file failtd");
        exit(-1);
    }

    HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hFileMap == NULL) {
        printf("create file map failed");
        ::CloseHandle(hFile);
        ::exit(-1);
    }

    DWORD dwSize = ::GetFileSize(hFile, NULL);

    LPVOID pBuff = ::MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);

    parseVertex(pBuff);


    ::UnmapViewOfFile(pBuff);

    ::CloseHandle(hFileMap);
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
