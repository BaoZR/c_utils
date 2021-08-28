// utils_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "utils.h"
#include <vld.h>


#pragma comment(lib,"utils.lib")

//int auto_list_filename_app(const char* folder, const char* pattern, char** name_list,int name_size,int* name_count);

int test(char** foo);

int main()
{
    //std::cout << "Hello World!\n";
    // char app_path[FILENAME_MAX];
    //get_app_path(app_path);
    //printf("%s\n", app_path);
    //unsigned char* buffer = (unsigned char*)malloc(sizeof(BYTE) * 500 * 200);
    //read_data_hex(buffer, 500 * 200, "raw.data");
    //save_gray_bmp_app("222\\222", NULL, buffer, 500, 200);
    //save_gray_bmp_app("333", "fff", buffer, 500, 200);
    
    //print_matched_filename_app(NULL,"*");

    //char* namelist = nullptr;
    //
    //int name_count = 0;
    //auto_list_filename_app("333", "*.bmp", &namelist,FILENAME_MAX,&name_count);
    //std::unique_ptr<char> p(namelist);
    //for (int i = 0; i < name_count; i++) {
    //    printf_s("NO.%d %s\n", i, namelist + i * FILENAME_MAX);
    //}
    BYTE buff[524289];
    read_data_hex(buff, 524289, "C:\\1.wav");
    write_data_hex(buff, 524289, "C:\\2.wav");

    //char* g = nullptr;
    //test(&g);
    //std::unique_ptr<char> p(g);
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





