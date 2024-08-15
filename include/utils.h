#pragma once

#include <direct.h>
#include <corecrt_io.h>
#include <Windows.h>
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>





#ifdef UTILS_DLL_EXPORT
#ifdef UTILSAPI_EXPORTS
#define UTILSAPI   __declspec( dllexport ) __stdcall
#else 
#define UTILSAPI   __declspec( dllimport ) __stdcall
#endif
#else
#define UTILSAPI 
#endif








/* bits表示一个位，要转换成字节必须  bits/8   但是这样可能产生问题，
例如该字节是32个字节则占4位，那么33个字节呢，
按上面的办法把33--64个字节的图像字节，都认为它占8位。
所以如果不到32的整数   加一个31再除32乘8便可以解决零头化为4的倍数了。 */
#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)

typedef struct _BMPFILEHEAD
{
	//uint16_t bfType;      //文件类型，必须为 "BM"(0x4D42)
	uint32_t bfSize;     //文件大小
	uint16_t bfReserved1; //保留字，不考虑
	uint16_t bfReserved2; //保留字，同上
	uint32_t bfOffBits;  //实际位图数据的偏移字节数，即前三个部分长度之和
} MY_BMPFILEHEAD;
//上面定义的结构体长度刚好为12，4的倍数 bfType拿出来

typedef struct _BMPFILETYPE
{
	uint16_t bfType; //文件类型，必须为 "BM"(0x4D42)
} MY_BMPFILETYPE;

typedef struct _BMPINFOHEAD
{
	uint32_t biSize;         //指定此结构体的长度，为40
	uint32_t biWidth;         //位图宽
	uint32_t biHeight;        //位图高
	uint16_t biPlanes;        //平面数，为1
	uint16_t biBitCount;      //采用颜色位数，可以是1，2，4，8，16，24，新的可以是32
	uint32_t biCompression;  //压缩方式，可以是0，1，2，其中0表示不压缩
	uint32_t biSizeImage;    //实际位图数据占用的字节数
	uint32_t biXPelsPerMeter; //X方向分辨率
	uint32_t biYPelsPerMeter; //Y方向分辨率
	uint32_t biClrUsed;      //使用的颜色数，如果为0，则表示默认值(2^颜色位数)
	uint32_t biClrImportant; //重要颜色数，如果为0，则表示所有颜色都是重要的
} MY_BMPINFOHEAD;

typedef struct _RGBQUAD
{
	//public:
	uint8_t rgbBlue;     //蓝色分量
	uint8_t rgbGreen;    //绿色分量
	uint8_t rgbRed;      //红色分量
	uint8_t rgbReserved; //保留值,必须为0
} RGBQUAD_s;



#ifdef __cplusplus
extern "C"
{
#endif

	/*@brief 将指定大小的内存块写入到给定文件中
	* @param    pucBuff    将被复制的数据源             IN
	* @param    uiBuffSize 要写入的长度                 IN
	* @param    pcFileNm   目标文件名,需要提供完整路径   IN
	* @return   非负数,返回写入的长度;负数,有错误发生
	*/
	size_t UTILSAPI write_data_hex(unsigned char* pucBuff, size_t uiBuffSize, const char* pcFileNm);

	/*@brief 从源文件中读取指定大小内容到内存块中
	* @param    pucBuff     待写入的内存块，需提前分配好内存     INOUT
	* @param    uiBuffSize  待读入内容的长度                    IN
	* @param    pcFileNm    源文件的完整路径                    IN
	* @return 非负数,返回读入的长度大小;负数,有错误发生
	*/
	size_t UTILSAPI read_data_hex(unsigned char* pucBuff, size_t uiBuffSize, const char* pcFileNm);

	/*@brief 提取相对app路径下匹配到的文件名
	 *@param  addr           文件路径 相对APP的路径                      IN
	 *@param  pattern	     名字匹配模板 可包含*或者？                   IN
	 *@param  name_list      名字缓存路径基地址 需提前分配好内存大小       INOUT
	 *@param  name_size      单个名字预留的长度                          IN
	 *@param  name_max_count 文件名的个数，需要提前知道有多少文件了        IN
	 *@return 返回值为找到的文件个数
	 */
	int UTILSAPI list_matched_filename_app(const char* folder, const char* pattern, char* name_list, int name_size, int name_max_count);

	/*@brief 在控制台打印相对app路径下匹配到的文件名
	* @param  folder     文件夹相对APP的路径						IN
	* @param  pattern    名字									IN
	* @return 返回匹配到的文件名数量,返回0表示没有匹配到任何文件名
	*/
	int UTILSAPI print_matched_filename_app(const char* folder, const char* pattern);

	/*@brief 一个自动化的函数，可以枚举相对app路径下匹配到的文件名,要记得释放name_list中分配的内存
	 *@param  folder         文件路径 相对APP的路径																					IN
	 *@param  pattern	     名字匹配模板 可包含*或者？																				IN
	 *@param  name_list      名字缓存路径基地址，传参时传入一个指针的地址，记得释放在函数中分配的内存（不得不这么写，不知道要预先分配多少内存）OUT
	 *@param  name_size      每个名字的长度																							IN
	 *@param  name_count     文件名的个数，会在函数中赋值。																			OUT
	 *@return 非负值为找到的文件个数，如果为负值则发生了异常
	 *@author bob
	 */
	int UTILSAPI auto_list_filename_app(const char* folder, const char* pattern, char** name_list, int16_t name_size, int* name_count);


	/*@brief 创建相对app路径文件的图片，
	*@param folder   app中的文件夹												IN
	*@param rowdata  图片具体数据													IN
	*@param pre_name 文件的前缀名，如果为NULL，则按1.bmp，2.bmp，3.bmp...的方式生成	IN
	*@param width    图片宽														IN
	*@param height   图片高														IN
	*@return 返回值无意义
	*/
	int UTILSAPI save_gray_bmp_app(const char* folder, const char* pre_name, unsigned char* rowdata, int16_t width, int16_t height);

	/**@brief 统计相对app路径文件下文件的数量
	*@param  folder  应用程序中的文件夹					IN
	*@param  pattern 文件匹配模板 可包含*或者？			IN
	*@return 负数:函数中有错误发生,非负数:匹配到的文件个数
	*/
	int UTILSAPI count_filename_app(const char* folder, const char* pattern);

	/*
	* @brief    在APP中建立文件夹
	* @param    filename 需建立文件夹的名字					IN
	* @return   返回负数,生成文件夹中发生错误;返回零，生成成功
	*/
	int UTILSAPI creat_dir_in_app(const char* filename);

	/*
	* @brief    生成指定路径的文件夹
	* @param    fullpath 指定的全路径					IN
	* @return   负数:生成文件夹中发生错误;0:生成成功
	*/
	int UTILSAPI mkdirs(const char* fullpath);

	/**@brief 获取app所在文件夹路径
	*@param   char*  app_path app所在文件夹的路径,需要提前分配好内存,分配的内存不小于,FILENAME_MAX	INOUT
	*@return  负数:函数中发生错误,0:正常返回
	*/
	int UTILSAPI get_app_path(char* app_path);

	/**@brief 将指定文件加载进内存
	*@param filename 要读取的文件名												IN
	*@param buff     需传入二级指针,缓存文件的内存块,在函数内分配,使用完需要手动清除	OUT
	*@param int      返回读取文件的长度											OUT
	*@return 0:成功加载进内存,负数:发生了错误
	*/
	int UTILSAPI load_file(const char* file_path, unsigned char** buff, size_t* file_len);


	/*
	*@brief 将未加工的原始数据加上一个8位灰度图的头，同时图片会做上下翻转，因为bmp在按行读取的时候从最后一行读取到第一行
	*
	*@param     pixData                 原始数据										IN
	*@param     width                   图片宽										IN
	*@param     height                  图片高										IN
	*@param     desData                 内存中加完头的数据块,需提前分配好足够的内存块	INOUT
	*@return 无意义
	*@author pipawancui
	 **/
	int UTILSAPI add8GreyBmpHead(uint8_t* pixData, int width, int height, uint8_t* desData);

	/*
	* @brief 将原始数据加上8位灰度头，输出到一个文件中，图片会先输出最后一行，从下往上，按行输出，直到输出到第一行
	* @param    pixData     原始数据			IN
	* @param    width       图片宽			IN
	* @param    height      图片高			IN
	* @param    filepath    输出的文件路径	IN
	* @return 无意义
	*/
	int UTILSAPI add8GreyBmpHead2File(uint8_t* pixData, int width, int height, const char* desFile);





#ifdef __cplusplus
}
#endif


