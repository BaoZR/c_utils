﻿// utils_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define UTILS_DLL_EXPORT
#include "../include/utils.h"

#include "../include/svpng.inc"
#include <time.h>
#include <string>
#include <Windows.h>
#include <memory>
#ifdef WIN64
    #ifdef _DEBUG
        #pragma comment(lib,"../x64/Debug/utils.lib")   
    #endif

    #ifdef NDEBUG
        #pragma comment(lib,"../x64/Release/utils.lib")
    #endif
#else
    #ifdef _DEBUG
        #pragma comment(lib,"../x86/Debug/utils.lib")
    #endif
    #ifdef NDEBUG
        #pragma comment(lib,"../x86/Release/utils.lib")
    #endif
#endif







int test(char** foo);

int main()
{
    std::unique_ptr<uint8_t[]> arr = std::unique_ptr<uint8_t[]>(new uint8_t[640 * 480]);
    //这是一个四个区块的黑白棋盘，左上角和右下角为白色，右上角和左下角为灰色
    memset(arr.get(), 255, 640 * 480);
    
    for (int row = 0; row < 480; row++) {
        for (int col = 0; col < 640; col++) {
            //注意到bmp是反过来读的
            if ((row <= 239 && col <= 319) || (row >= 240 && col >= 320) ){
                arr.get()[row * 640 + col] = 128;
            }
        }
    }



    
    save_gray_bmp_app("picture", NULL, arr.get(), 640, 480);
    add8GreyBmpHead2File(arr.get(), 640, 480, "123.bmp");


    //FILE* fp = fopen("rgb.png", "wb+");
    //svpng(fp, 500, 200, buff, 0);
    
    char* namelist = NULL;
    int name_count;
    int ret = auto_list_filename_app("picture", "*.bmp", &namelist, FILENAME_MAX, &name_count);
    std::unique_ptr<char> p2(namelist);
    printf("list result %d\n", ret);

    return 0;
}

//int auto_list_filename_app(const char* folder, const char* pattern, char** name_list, int name_size,int* name_count)
//{
//    
//    *name_count = count_filename_app(folder, pattern);
//    if (*name_count < 0)
//    {
//        *name_count = 0;//保证为非负数
//        return -1;//返回异常值
//    }
//    *name_list = (char*)malloc(*name_count * name_size);
//    return list_matched_filename_app(folder, pattern, *name_list, name_size, *name_count);
//}


int test(char** foo)
{
    *foo = (char*)malloc(0);
    memset(*foo, 1, 0);
    return 0;
}





