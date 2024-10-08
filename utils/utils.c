﻿// utils.cpp : 定义静态库的函数。
//


#include "framework.h"
#define UTILSAPI_EXPORTS
#include "../include/utils.h"



size_t UTILSAPI write_data_hex(unsigned char* pucBuff, size_t uiBuffSize, const char* pcFileNm)
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

size_t UTILSAPI read_data_hex(unsigned char* pucBuff,size_t uiBuffSize,const char* pcFileNm)
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

int UTILSAPI list_matched_filename_app(const char* folder,const char* pattern,char* name_list,int name_size,int name_max_count)
{
    struct _finddata_t file_info;
    intptr_t hFile;
    int index = 0;
    char temp_path[FILENAME_MAX] = { 0 };
    char app_path[FILENAME_MAX] = { 0 };

    GetModuleFileNameA(NULL, app_path, FILENAME_MAX);
    strrchr(app_path, '\\')[1] = 0;

    if (folder != NULL) {
        sprintf_s(temp_path, FILENAME_MAX,"%s%s\\%s", app_path, folder, pattern);
    }else{
         sprintf_s(temp_path, FILENAME_MAX, "%s%s", app_path, pattern);
    }


    //printf("%s\n",temp_path);
    if ((hFile = _findfirst(temp_path, &file_info)) == -1L) {
       // printf("NO files in directory!\n");
        return 0;//没有找到任何文件
    }
    else {
        do {
            memcpy(name_list + index * name_size, file_info.name, (size_t)name_size);
            index++;
        } while ((_findnext(hFile, &file_info) == 0) && (index < name_max_count));
    };
    _findclose(hFile);
    return index;
}

int UTILSAPI print_matched_filename_app(const char* folder,const char* pattern)
{
    struct _finddata_t file_info;
    intptr_t hFile;
    int index = 0;
    char temp_path[FILENAME_MAX] = { 0 };
    char app_path[FILENAME_MAX] = { 0 };

    GetModuleFileNameA(NULL, app_path, FILENAME_MAX);
    strrchr(app_path, '\\')[1] = 0;

    if (folder != NULL) {
        sprintf_s(temp_path, FILENAME_MAX,"%s%s\\%s", app_path, folder, pattern);
    }
    else {
        sprintf_s(temp_path, FILENAME_MAX, "%s%s", app_path, pattern);
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

int UTILSAPI auto_list_filename_app(const char* folder,const char* pattern,char** name_list,int16_t name_size,int* name_count)
{
    *name_count = count_filename_app(folder, pattern);
     if (*name_count < 0)
     {
        *name_count = 0;//保证为非负数
        return -1;//返回异常值
     }
     *name_list = (char*)malloc((size_t)(*name_count * name_size));
     memset(*name_list,0, *name_count * name_size);
     return list_matched_filename_app(folder, pattern, *name_list, name_size, *name_count);
}

int UTILSAPI save_gray_bmp_app(const char* folder,const char* pre_name,unsigned char* rowdata,int16_t width,int16_t  height)
{
    int img_head = 1078;
    char app_path[FILENAME_MAX];
    char full_path[FILENAME_MAX];
    get_app_path(app_path);
    //printf("%s\n", app_path);
    creat_dir_in_app(folder);//保证有这个文件夹
    int num = count_filename_app(folder, "*.bmp");
    unsigned char* des_data = (unsigned char*)malloc(sizeof(unsigned char) * (size_t)(width * height + img_head));

    add8GreyBmpHead(rowdata, width, height, des_data);//这里可以改进为直接往文件写数据

    if (pre_name == NULL) {//如果没有指定用户名则按1、2、3这样的方式命名
        sprintf_s(full_path, FILENAME_MAX,"%s%s\\%d.bmp", app_path, folder, num + 1);
        //printf("%s\n", full_path);
    }
    else {
        sprintf_s(full_path, FILENAME_MAX, "%s%s\\%s.bmp", app_path, folder, pre_name);
        //printf("%s\n", full_path);
    }

    write_data_hex(des_data, (size_t)(width * height + img_head), full_path);

    free(des_data);
    return 0;
}

int UTILSAPI count_filename_app(const char* folder,const char* pattern)
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

    sprintf_s(temp_path, FILENAME_MAX, "%s%s\\%s", app_path, folder, pattern);

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

int UTILSAPI get_app_path(char* app_path)
{
    if (GetModuleFileNameA(NULL, app_path, FILENAME_MAX) < 0)
    {
        return -1;
    }
    strrchr(app_path, '\\')[1] = 0;
    return 0;
}

int UTILSAPI load_file(const char* file_path, unsigned char** buff, size_t* file_len)
{
    FILE* pFile;
    long lSize;
    size_t result;
    errno_t ret;
    /* 若要一个字节不漏地读入整个文件，只能采用二进制方式打开 */
    ret = fopen_s(&pFile, file_path, "rb");
    if (ret < 0 || pFile == 0)
    {
        fputs("File error", stderr);
        return ret;
    }

    /* 获取文件大小 */
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    *file_len = lSize;


    rewind(pFile);

    /* 分配能够存储整个文件的内存大小 */
    *buff = (unsigned char*)malloc(sizeof(char) * lSize);
    if (*buff == NULL)
    {
        fputs("Memory error", stderr);
        fclose(pFile);
        return -1;
    }
    memset(*buff, 0, sizeof(char) * lSize);

    /* 将文件拷贝到buffer中 */
    result = fread(*buff, 1, sizeof(char) * lSize, pFile);
    if (result != lSize)
    {
        fputs("Reading error", stderr);
        free(*buff);
        fclose(pFile);
        return -1;
    }
    /* 现在整个文件已经在buffer中 */

    fclose(pFile);

    return 0;
}



int UTILSAPI creat_dir_in_app(const char* filename)
{
    int ret = 0;
    char path[FILENAME_MAX];
    ret =  get_app_path(path);
    if (ret < 0) return -1;//发生错误直接返回

    sprintf_s(path, FILENAME_MAX,"%s%s", path, filename);
    //printf("%s\n", path);
    ret = mkdirs(path);
    return ret;
}

int UTILSAPI mkdirs(const char* fullpath)
{
    size_t i,len;
    char str[FILENAME_MAX] = { 0 };
    strncpy_s(str, FILENAME_MAX, fullpath, FILENAME_MAX);

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

                    return -1;
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
           return -1;
        }
    }
    return 0;
}


void grey_image_rotate_90_degree(unsigned char* psrc, unsigned char* pdst, int* col /*w*/, int* row /*h*/)
{
    int r, c;
    int col_temp = *col;
    int row_temp = *row;
    int cxrow_temp;

    for (c = 0; c < col_temp; c++) {
        cxrow_temp = c * row_temp;
        for (r = 0; r < row_temp; r++) {
            pdst[cxrow_temp + (row_temp - r - 1)] = psrc[r * col_temp + c];
        }
    }

    *row = *col;
    *col = row_temp;
}


int UTILSAPI add8GreyBmpHead(uint8_t* pixData,int width,int height,uint8_t* desData)
{
    UINT32 bitCount = 8, color = 128;

    MY_BMPFILETYPE bft;
    MY_BMPFILEHEAD bfh;
    MY_BMPINFOHEAD bih;
    RGBQUAD_s rgbquad[256];
    int LineByte, ImgSize;
    LineByte = WIDTHBYTES(width * bitCount); //计算位图一行的实际宽度并确保它为32的倍数
    ImgSize = height * LineByte;             //图片像素大小

    size_t desData_size = sizeof(MY_BMPFILETYPE) + sizeof(MY_BMPFILEHEAD) +
        sizeof(MY_BMPINFOHEAD) + sizeof(rgbquad) + width * height;

    for (int p = 0; p < 256; p++)
    {
        rgbquad[p].rgbBlue = (uint8_t)p;
        rgbquad[p].rgbGreen = (uint8_t)p;
        rgbquad[p].rgbRed = (uint8_t)p;
        rgbquad[p].rgbReserved = (uint8_t)0;
    }
    //bmp file's type
    bft.bfType = 0x4d42;

    //bmp fileheader's info
    bfh.bfSize = (uint32_t)(54 + 4 * 256 + ImgSize);
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = (uint32_t)(54 + 4 * 256);

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
        memcpy_s(desData, sizeof(MY_BMPFILETYPE), &bft, sizeof(MY_BMPFILETYPE));
        desData += sizeof(MY_BMPFILETYPE);
        //write bmp file's header info
        memcpy_s(desData, sizeof(MY_BMPFILEHEAD), &bfh, sizeof(MY_BMPFILEHEAD));
        desData += sizeof(MY_BMPFILEHEAD);
        //write bmp file's infoheader
        memcpy_s(desData, sizeof(MY_BMPINFOHEAD), &bih, sizeof(MY_BMPINFOHEAD));
        desData += sizeof(MY_BMPINFOHEAD);
        //write bmp file's RGBQUAD data
        memcpy_s(desData, sizeof(rgbquad), &rgbquad, sizeof(rgbquad));
        desData += sizeof(rgbquad);
        //writing pix data to memory
        for (int row = 0; row < height; ++row) {

            memcpy_s(&desData[row * width], width, &pixData[(height - 1 - row) *width] , width);
        }

    }

    return 0;
}

int UTILSAPI add8GreyBmpHead2File(uint8_t* pixData,int width,int height,const char* desFile)
{
    uint8_t bitCount = 8, color = 128;

    FILE* out;
    MY_BMPFILETYPE bft;
    MY_BMPFILEHEAD bfh;
    MY_BMPINFOHEAD bih;
    RGBQUAD rgbquad[256];
    int LineByte, ImgSize;
    LineByte = WIDTHBYTES(width * bitCount); //计算位图一行的实际宽度并确保它为32的倍数
    ImgSize = height * LineByte;             //图片像素大小

    for (int p = 0; p < 256; p++)
    {
        rgbquad[p].rgbBlue = (uint8_t)p;
        rgbquad[p].rgbGreen = (uint8_t)p;
        rgbquad[p].rgbRed = (uint8_t)p;
        rgbquad[p].rgbReserved = (uint8_t)0;
    }
    //bmp file's type
    bft.bfType = 0x4d42;

    //bmp fileheader's info
    bfh.bfSize = (uint32_t)(54 + 4 * 256 + ImgSize);
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = (uint32_t)(54 + 4 * 256);

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
    fopen_s(&out, desFile, "w+b");

    if (out)
    {
        //write bmp file's type
        fwrite(&bft, sizeof(MY_BMPFILETYPE), 1, out);
        //write bmp file's header info
        fwrite(&bfh, sizeof(MY_BMPFILEHEAD), 1, out);
        //write bmp file's infoheader
        fwrite(&bih, sizeof(MY_BMPINFOHEAD), 1, out);
        //write bmp file's RGBQUAD data
        fwrite(&rgbquad, sizeof(RGBQUAD), sizeof(rgbquad) / sizeof(RGBQUAD), out);
        //writing pix data to file
        for (int row = height - 1; row >= 0; row--) {
            fwrite(&pixData[row * height], width, sizeof(uint8_t), out);
        }

    }
    if (out)
        fclose(out);
    //--------------------------------------
    return 0;

    
}
//给24位的灰度图加头//该函数未经过测试
int UTILSAPI add24GreyBmpHead2File(uint8_t* pixData, int width, int height, const char* desFile)
{
    FILE* out;
    fopen_s(&out, desFile, "w+b");
    if (out == NULL)
    {
        return -1;
    }
    int m_nBitCount = 24;
    uint32_t m_nHeight = height;
    uint32_t m_nWidth = width;
    uint32_t lLineBytes24 = ((m_nWidth * 24 + 31) / 32 * 4);
    
    //建立一个位图文件头变量，并为此变量赋值
    BITMAPFILEHEADER bf;
    //位图是24位的，则位图像素数据的偏移地址就为位图的前两部分的字节数之和
    //即为：文件头+信息头
    bf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    //将位图文件头中的保留为都置零
    bf.bfReserved1 = 0;
    bf.bfReserved2 = 0;
    //如果位图为24位的，则位图文件大小就为位图的三部分之和
    //即为：文件头+信息头+像素数据
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + m_nHeight * lLineBytes24;
    //位图文件的类型为BM
    bf.bfType = ((uint16_t)'M' << 8 | 'B');
    //将位图文件头写入文件
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, out);

    //写入像素数据
    fwrite(pixData, m_nHeight * lLineBytes24, 1, out);
    //关闭文件
    fclose(out);
    return 0;
}

/******************************************************************************
*函数功能：将8位位图转换为24位位图 该函数未经过测试
*函数声明：
   int Bitmap8To24(
    uint8_t* srcImage,  -指向源图像的像素数据的指针
    uint8_t* dstImage,  -指向目的图像的像素数据的指针
    uint32_t imageWidth, -源图像的宽度(像素数)
    uint32_t imageHeight -源图像的高度(像素数)
    )
******************************************************************************/
int  Bitmap8To24(uint8_t* srcImage, uint8_t* dstImage, int imageWidth, int imageHeight);

int  Bitmap8To24(uint8_t* srcImage, uint8_t* dstImage, int imageWidth, int imageHeight)
{
    int lLineBytes24 = ((imageWidth * 24 + 31) / 32 * 4);
    int lLineBytes8 = ((imageWidth * 8 + 31) / 32 * 4);
    int n, j;
    for (int i = 0; i < imageHeight; i++)
    {
        for (j = 0, n = 0; j < lLineBytes8; j++, n++)
        {
            uint8_t gray = *(srcImage + lLineBytes8 * i + j);
            *(dstImage + lLineBytes24 * i + n) = gray;
            n++;
            *(dstImage + lLineBytes24 * i + n) = gray;
            n++;
            *(dstImage + lLineBytes24 * i + n) = gray;
        }
    }

    return 0;
}


/*可以翻转400*640的图片,不过没有考虑长度不为偶数的情况 */
void myflip(uint8_t* rawdata, size_t img_height, size_t img_width, uint8_t* desdata) {
    for (size_t i = 0; i < img_height; i++) {
        memcpy_s(desdata + ((img_height - 1L - i) * img_width), img_width, (rawdata + img_width * i), img_width);
    }
}