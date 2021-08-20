// utils_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "utils.h"



#pragma comment(lib,"utils.lib")



int main()
{
    //std::cout << "Hello World!\n";
    // char app_path[FILENAME_MAX];
    //get_app_path(app_path);
    //printf("%s\n", app_path);
    unsigned char* buffer = (unsigned char*)malloc(sizeof(BYTE) * 500 * 200);
    read_data_hex(buffer, 500 * 200, "raw.data");
    save_gray_bmp_app("222\\222", NULL, buffer, 500, 200);
    save_gray_bmp_app("333", "fff", buffer, 500, 200);
    print_matched_filename_app(NULL,"*.*");
}


