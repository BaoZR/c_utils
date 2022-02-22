// utils_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#ifdef _DEBUG
#include <vld.h>
#endif
#define UTILS_DLL_EXPORT
#include "../include/utils.h"

#include "../include/svpng.inc"
#include <time.h>




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
    srand((int)time(NULL));
    BYTE* buff = (BYTE*)malloc(500 * 200);

    for (int i = 0; i < 500 * 200; i++) {
        int t = rand() % 256;
        char c = t;
        memcpy_s(buff + i, 1, &c, 1);
    }
    save_gray_bmp_app("picture", NULL, buff, 500, 200);
    //FILE* fp = fopen("rgb.png", "wb+");
    //svpng(fp, 500, 200, buff, 0);
    free(buff);
    //char* g = nullptr;
    //test(&g);
    //std::unique_ptr<char> p(g);
    char app_path[FILENAME_MAX] = { 0 };
    size_t buff_len;
    unsigned char* buf = NULL;
    get_app_path(app_path);
    strcat_s(app_path, FILENAME_MAX, "utils.dll");
    load_file(app_path, &buf, &buff_len);
    strcat_s(app_path, FILENAME_MAX, "2");
    write_data_hex(buf, buff_len, app_path);
    free(buf);
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





