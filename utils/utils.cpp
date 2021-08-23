// utils.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include "utils.h"

size_t write_data_hex(unsigned char* pucBuff, size_t uiBuffSize,const char* pcFileNm)
{
    FILE* fp;
    fopen_s(&fp, pcFileNm, "wb+");
    if (NULL == fp)
    {
        printf("file open Fail!\n");
        return -1;
    }

    //
    //for (size_t i = 0; i < uiBuffSize; i++)
    //{
    //    fwrite(pucBuff + i, sizeof(char), 1, fp);
    //}

    size_t iRet = fwrite(pucBuff, uiBuffSize, 1, fp);
    fclose(fp);
    return iRet;
}

size_t read_data_hex(unsigned char* pucBuff, size_t uiBuffSize,const char* pcFileNm)
{
    FILE* fp;;
    fopen_s(&fp, pcFileNm, "rb");
    if (NULL == fp)
    {
        printf("file [%s] open Fail!\n", pcFileNm);
        return -1;
    }
    size_t iRet = fread(pucBuff, sizeof(char), uiBuffSize, fp);
    fclose(fp);
    return iRet;
}

int list_matched_filename_app(const char* folder, const char* pattern, char* name_list, size_t name_size, int name_max_count)
{
    struct _finddata_t file_info;
    intptr_t hFile;
    int index = 0;
    char temp_path[FILENAME_MAX] = { 0 };
    char app_path[FILENAME_MAX] = { 0 };

    GetModuleFileNameA(NULL, app_path, FILENAME_MAX);
    strrchr(app_path, '\\')[1] = 0;

    if (folder != NULL) {
        sprintf_s(temp_path, "%s%s\\%s", app_path, folder, pattern);
    }else{
         sprintf_s(temp_path, "%s%s", app_path, pattern);
    }


    //printf("%s\n",temp_path);
    if ((hFile = _findfirst(temp_path, &file_info)) == -1L) {
       // printf("NO files in directory!\n");
        return 0;//没有找到任何文件
    }
    else {
        do {
            memcpy(name_list + index * name_size, file_info.name, name_size);
            index++;
        } while ((_findnext(hFile, &file_info) == 0) && (index < name_max_count));
    };
    _findclose(hFile);
    return index;
}

int print_matched_filename_app(const char* folder, const char* pattern)
{
    struct _finddata_t file_info;
    intptr_t hFile;
    int index = 0;
    char temp_path[FILENAME_MAX] = { 0 };
    char app_path[FILENAME_MAX] = { 0 };

    GetModuleFileNameA(NULL, app_path, FILENAME_MAX);
    strrchr(app_path, '\\')[1] = 0;

    if (folder != NULL) {
        sprintf_s(temp_path, "%s%s\\%s", app_path, folder, pattern);
    }
    else {
        sprintf_s(temp_path, "%s%s", app_path, pattern);
    }

    //printf("%s\n", temp_path);
    
    if ((hFile = _findfirst(temp_path, &file_info)) == -1L) {
        // printf("NO files in directory!\n");
        return 0;//没有找到任何文件
    }
    else {
        do {
            index++;
            printf("NO.%d %s\n", index, file_info.name);
        } while (_findnext(hFile, &file_info) == 0);
    };
    _findclose(hFile);
    return index;
}

int auto_list_filename_app(const char* folder, const char* pattern, char** name_list, int name_size, int* name_count)
{
    *name_count = count_filename_app(folder, pattern);
     if (*name_count < 0)
     {
        *name_count = 0;//保证为非负数
        return -1;//返回异常值
     }
     *name_list = (char*)malloc(*name_count * name_size);
     return list_matched_filename_app(folder, pattern, *name_list, name_size, *name_count);
}

int save_gray_bmp_app(const char* folder, const char* pre_name, unsigned char* rowdata, size_t width, size_t  height)
{
    long img_head = 1078;
    char app_path[FILENAME_MAX];
    char full_path[FILENAME_MAX];
    get_app_path(app_path);
    //printf("%s\n", app_path);
    creat_dir_in_app(folder);//保证有这个文件夹
    int num = count_filename_app(folder, "*.bmp");
    unsigned char* des_data = (unsigned char*)malloc(sizeof(unsigned char) * (width * height + img_head));

    add8GreyBmpHead(rowdata, width, height, des_data);//这里可以改进为直接往文件写数据

    if (pre_name == NULL) {//如果没有指定用户名则按1、2、3这样的方式命名
        sprintf_s(full_path, "%s%s\\%d.bmp", app_path, folder, num + 1);
        //printf("%s\n", full_path);
    }
    else {
        sprintf_s(full_path, "%s%s\\%s.bmp", app_path, folder, pre_name);
        //printf("%s\n", full_path);
    }

    write_data_hex(des_data, width * height + img_head, full_path);

    free(des_data);
    return 0;
}

int count_filename_app(const char* folder, const char* pattern)
{
    struct _finddata_t file_info;
    intptr_t hFile;
    int count = 0;
    char temp_path[FILENAME_MAX] = { 0 };
    char app_path[FILENAME_MAX] = { 0 };

    if (GetModuleFileNameA(NULL, app_path, FILENAME_MAX) < 0)
    {
        return -1;
    }
    strrchr(app_path, '\\')[1] = 0;

    sprintf_s(temp_path, "%s%s\\%s", app_path, folder, pattern);

    if ((hFile = _findfirst(temp_path, &file_info)) == -1L) {
        //printf("NO files in directory!\n");
        return 0;
    }
    else {
        do {
            count++;
        } while (_findnext(hFile, &file_info) == 0);
    };
    _findclose(hFile);
    return count;
}

int get_app_path(char* app_path)
{
    if (GetModuleFileNameA(NULL, app_path, FILENAME_MAX) < 0)
    {
        return -1;
    }
    strrchr(app_path, '\\')[1] = 0;
    return 0;
}

int creat_dir_in_app(const char* filename)
{
    char path[FILENAME_MAX];
    get_app_path(path);
    sprintf_s(path, "%s%s", path, filename);
    //printf("%s\n", path);
    mkdirs(path);
    return 0;
}

void mkdirs(const char* fullpath)
{
    int i, len;
    char str[FILENAME_MAX] = { 0 };
    strncpy_s(str, fullpath, FILENAME_MAX);

    len = strlen(str);
    int j = 0;
    for (i = 0; i < len; i++) {
        if (str[i] == '\\') {
            j++;
            str[i] = '\0';
            if (_access(str, 0) != 0) {
                //printf("创建第%d级别目录 p=[%s]\n", j, str);
                if (_mkdir(str) < 0) {
                    printf("mkdir fail\n");
                    return;
                }
            }
            str[i] = '\\';
        }
    }
    if (len > 0 && _access(str, 0) != 0)
    {
        //printf("最后一级目录=%s\n", str);
        if (_mkdir(str) < 0) {
            printf("mkdir fail\n");
        }
    }
    return;
}



int add8GreyBmpHead(BYTE* pixData, size_t width, size_t height, BYTE* desData)
{
    BYTE bitCount = 8, color = 128;

    BMPFILETYPE bft;
    BMPFILEHEAD bfh;
    BMPINFOHEAD bih;
    RGBQUAD_s rgbquad[256];
    DWORD LineByte, ImgSize;
    LineByte = WIDTHBYTES(width * bitCount); //计算位图一行的实际宽度并确保它为32的倍数
    ImgSize = height * LineByte;             //图片像素大小

    size_t desData_size = sizeof(BMPFILETYPE) + sizeof(BMPFILEHEAD) +
        sizeof(BMPINFOHEAD) + sizeof(rgbquad) + width * height;

    for (int p = 0; p < 256; p++)
    {
        rgbquad[p].rgbBlue = (BYTE)p;
        rgbquad[p].rgbGreen = (BYTE)p;
        rgbquad[p].rgbRed = (BYTE)p;
        rgbquad[p].rgbReserved = (BYTE)0;
    }
    //bmp file's type
    bft.bfType = 0x4d42;

    //bmp fileheader's info
    bfh.bfSize = (DWORD)(54 + 4 * 256 + ImgSize);
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = (DWORD)(54 + 4 * 256);

    //bmp file's infoheader
    bih.biSize = 40; //本位图信息头的长度，为40字节
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biPlanes = 1;
    bih.biBitCount = bitCount; //位图颜色位深
    bih.biCompression = 0;     //是否压缩:0不压缩
    bih.biSizeImage = ImgSize; //像素数据大小;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed = 0;      //用到的颜色数,为0则是 2^颜色位深
    bih.biClrImportant = 0; //重要的颜色数,为0则全部都重要

    if (desData)
    {
        //write bmp file's type
        memcpy_s(desData, sizeof(BMPFILETYPE), &bft, sizeof(BMPFILETYPE));
        desData += sizeof(BMPFILETYPE);
        //write bmp file's header info
        memcpy_s(desData, sizeof(BMPFILEHEAD), &bfh, sizeof(BMPFILEHEAD));
        desData += sizeof(BMPFILEHEAD);
        //write bmp file's infoheader
        memcpy_s(desData, sizeof(BMPINFOHEAD), &bih, sizeof(BMPINFOHEAD));
        desData += sizeof(BMPINFOHEAD);
        //write bmp file's RGBQUAD data
        memcpy_s(desData, sizeof(rgbquad), &rgbquad, sizeof(rgbquad));
        desData += sizeof(rgbquad);
        //writing pix data to file
        memcpy_s(desData, width * height, pixData, width * height);
    }

    return 0;
}
