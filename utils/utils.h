#pragma once

#include <direct.h>
#include <corecrt_io.h>
#include <iostream>
#include <Windows.h>


typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;

/* bits表示一个位，要转换成字节必须  bits/8   但是这样可能产生问题，
例如该字节是32个字节则占4位，那么33个字节呢，
按上面的办法把33--64个字节的图像字节，都认为它占8位。
所以如果不到32的整数   加一个31再除32乘8便可以解决零头化为4的倍数了。 */
#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)

typedef struct _BMPFILEHEAD
{
    //WORD bfType;      //文件类型，必须为 "BM"(0x4D42)
    DWORD bfSize;     //文件大小
    WORD bfReserved1; //保留字，不考虑
    WORD bfReserved2; //保留字，同上
    DWORD bfOffBits;  //实际位图数据的偏移字节数，即前三个部分长度之和
} BMPFILEHEAD;
//上面定义的结构体长度刚好为12，4的倍数 bfType拿出来

typedef struct _BMPFILETYPE
{
    WORD bfType; //文件类型，必须为 "BM"(0x4D42)
} BMPFILETYPE;

typedef struct _BMPINFOHEAD
{
    DWORD biSize;         //指定此结构体的长度，为40
    LONG biWidth;         //位图宽
    LONG biHeight;        //位图高
    WORD biPlanes;        //平面数，为1
    WORD biBitCount;      //采用颜色位数，可以是1，2，4，8，16，24，新的可以是32
    DWORD biCompression;  //压缩方式，可以是0，1，2，其中0表示不压缩
    DWORD biSizeImage;    //实际位图数据占用的字节数
    LONG biXPelsPerMeter; //X方向分辨率
    LONG biYPelsPerMeter; //Y方向分辨率
    DWORD biClrUsed;      //使用的颜色数，如果为0，则表示默认值(2^颜色位数)
    DWORD biClrImportant; //重要颜色数，如果为0，则表示所有颜色都是重要的
} BMPINFOHEAD;

typedef struct _RGBQUAD
{
    //public:
    BYTE rgbBlue;     //蓝色分量
    BYTE rgbGreen;    //绿色分量
    BYTE rgbRed;      //红色分量
    BYTE rgbReserved; //保留值,必须为0
} RGBQUAD_s;

size_t write_data_hex(unsigned char* pucBuff, size_t uiBuffSize,const char* pcFileNm);

size_t read_data_hex(unsigned char* pucBuff, size_t uiBuffSize,const char* pcFileNm);

/*@brief 枚举相对app路径下匹配到的文件名
 *@param  const char* addr           文件路径 相对APP的路径
 *@param  const char* pattern	     名字匹配模板 可包含*或者？
 *@param  char*       name_list      名字缓存路径基地址 需提前分配好内存大小
 *@param  int         name_size      每个名字的长度
 *@param              name_max_count 文件名的个数，已经知道有多少文件了
*/
int list_matched_filename_app(const char* folder, const char* pattern, char* name_list, size_t name_size, int name_max_count);

/*@brief 打印相对app路径下匹配到的文件名
*@param  const char* folder     文件夹相对APP的路径
*@param  const char* pattern    名字
*/
int print_matched_filename_app(const char* folder, const char* pattern);

/*@brief 创建相对app路径文件的图片，
*@param const char*  folder   app中的文件夹
*@param char*        rowdata  图片具体数据
*@param char*        pre_name 文件的前缀名，如果为NULL，则按1.bmp，2.bmp，3.bmp...的方式生成
*@param int          width    图片宽
*@param int          height   图片高
*/
int save_gray_bmp_app(const char* folder, const char* pre_name, unsigned char* rowdata, size_t width, size_t height);

/**@brief 统计相对app路径文件下文件的数量
*@param  const char*  folder  app中的文件夹
*@param  const char*  pattern 文件匹配模板 可包含*或者？
*@return 异常为小于0的数,非负数为文件的个数
*/
int count_filename_app(const char* folder, const char* pattern);

/*
*在APP中建立文件夹
*/
int creat_dir_in_app(const char* filename);

/*
* 生成指定路径的文件夹
*/
void mkdirs(const char* fullpath);

/**@brief 获取app所在文件夹路径
*@param INOUT  char*  app_path app所在文件夹的路径，分配的内存不小于,FILENAME_MAX
*@return  是否获取成功
*/
int get_app_path(char* app_path);

/*
* 函数名: add8GreyBmpHead
* 给未加工的原始数据加上一个8位灰度图的头
* 参数:
* 参数名         参数类型      IN/OUT/INOUT      备注
* pixData        BYTE *        IN               原始数据
* width          int           IN               图片高
* height         int           IN               图片宽
* desData        BYTE *        OUT              内存中加完头的数据块
* 返回值：
* 类型：int
* 取值：0:成功,其它:无
* 其它：by pipawancui
 **/
int add8GreyBmpHead(BYTE* pixData, size_t width,size_t height, BYTE* desData);









