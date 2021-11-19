#pragma once

#include <direct.h>
#include <corecrt_io.h>
#include <iostream>
#include <Windows.h>



#ifdef DLL_EXPORT
    #ifdef UTILSAPI_EXPORTS
        #define UTILSAPI   __declspec( dllexport ) __stdcall
    #else 
        #define UTILSAPI   __declspec( dllimport ) __stdcall
    #endif 
#else
    #define UTILSAPI                    
#endif





/* bits��ʾһ��λ��Ҫת�����ֽڱ���  bits/8   �����������ܲ������⣬
������ֽ���32���ֽ���ռ4λ����ô33���ֽ��أ�
������İ취��33--64���ֽڵ�ͼ���ֽڣ�����Ϊ��ռ8λ��
�����������32������   ��һ��31�ٳ�32��8����Խ����ͷ��Ϊ4�ı����ˡ� */
#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)

typedef struct _BMPFILEHEAD
{
    //WORD bfType;      //�ļ����ͣ�����Ϊ "BM"(0x4D42)
    DWORD bfSize;     //�ļ���С
    WORD bfReserved1; //�����֣�������
    WORD bfReserved2; //�����֣�ͬ��
    DWORD bfOffBits;  //ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��
} BMPFILEHEAD;
//���涨��Ľṹ�峤�ȸպ�Ϊ12��4�ı��� bfType�ó���

typedef struct _BMPFILETYPE
{
    WORD bfType; //�ļ����ͣ�����Ϊ "BM"(0x4D42)
} BMPFILETYPE;

typedef struct _BMPINFOHEAD
{
    DWORD biSize;         //ָ���˽ṹ��ĳ��ȣ�Ϊ40
    LONG biWidth;         //λͼ��
    LONG biHeight;        //λͼ��
    WORD biPlanes;        //ƽ������Ϊ1
    WORD biBitCount;      //������ɫλ����������1��2��4��8��16��24���µĿ�����32
    DWORD biCompression;  //ѹ����ʽ��������0��1��2������0��ʾ��ѹ��
    DWORD biSizeImage;    //ʵ��λͼ����ռ�õ��ֽ���
    LONG biXPelsPerMeter; //X����ֱ���
    LONG biYPelsPerMeter; //Y����ֱ���
    DWORD biClrUsed;      //ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)
    DWORD biClrImportant; //��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��
} BMPINFOHEAD;

typedef struct _RGBQUAD
{
    //public:
    BYTE rgbBlue;     //��ɫ����
    BYTE rgbGreen;    //��ɫ����
    BYTE rgbRed;      //��ɫ����
    BYTE rgbReserved; //����ֵ,����Ϊ0
} RGBQUAD_s;



#ifdef __cplusplus
extern "C"
{
#endif

size_t UTILSAPI write_data_hex(unsigned char* pucBuff, size_t uiBuffSize,const char* pcFileNm);

size_t UTILSAPI read_data_hex(unsigned char* pucBuff, size_t uiBuffSize,const char* pcFileNm);

/*@brief ö�����app·����ƥ�䵽���ļ���
 *@param  const char* addr           �ļ�·�� ���APP��·��
 *@param  const char* pattern	     ����ƥ��ģ�� �ɰ���*���ߣ�
 *@param  char*       name_list      ���ֻ���·������ַ ����ǰ������ڴ��С
 *@param  int     name_size      ÿ�����ֵĳ���
 *@param              name_max_count �ļ����ĸ������Ѿ�֪���ж����ļ���
 *@return ����ֵΪ�ҵ����ļ�����
 */
int UTILSAPI list_matched_filename_app(const char* folder, const char* pattern, char* name_list, int name_size, int name_max_count);

/*@brief ��ӡ���app·����ƥ�䵽���ļ���
*@param  const char* folder     �ļ������APP��·��
*@param  const char* pattern    ����
*/
int UTILSAPI print_matched_filename_app(const char* folder, const char* pattern);

/*@brief һ������Զ����ĺ���������ö�����app·����ƥ�䵽���ļ���,Ҫ�ǵ��ͷ�name_list�з�����ڴ�
 *@param  const char* addr           �ļ�·�� ���APP��·��
 *@param  const char* pattern	     ����ƥ��ģ�� �ɰ���*���ߣ�
 *@param  char**      name_list      ���ֻ���·������ַ�����ں����з����ڴ棬�ǵ��ͷţ����ò���ôд����֪��ҪԤ�ȷ�������ڴ棩
 *@param  int16_t     name_size      ÿ�����ֵĳ���
 *@param  int*        name_max_count �ļ����ĸ��������ں����и�ֵ��
 *@return ����ֵΪ�ҵ����ļ����������Ϊ��ֵ�������쳣
 *@author bob
 */
int UTILSAPI auto_list_filename_app(const char* folder, const char* pattern, char** name_list, int16_t name_size, int* name_count);


/*@brief �������app·���ļ���ͼƬ��
*@param const char*  folder   app�е��ļ���
*@param char*        rowdata  ͼƬ��������
*@param char*        pre_name �ļ���ǰ׺�������ΪNULL����1.bmp��2.bmp��3.bmp...�ķ�ʽ����
*@param int          width    ͼƬ��
*@param int          height   ͼƬ��
*/
int UTILSAPI save_gray_bmp_app(const char* folder, const char* pre_name, unsigned char* rowdata, int16_t width, int16_t height);

/**@brief ͳ�����app·���ļ����ļ�������
*@param  const char*  folder  app�е��ļ���
*@param  const char*  pattern �ļ�ƥ��ģ�� �ɰ���*���ߣ�
*@return �쳣ΪС��0����,�Ǹ���Ϊ�ļ��ĸ���
*/
int UTILSAPI count_filename_app(const char* folder, const char* pattern);

/*
*��APP�н����ļ���
*/
int UTILSAPI creat_dir_in_app(const char* filename);

/*
* ����ָ��·�����ļ���
*/
void UTILSAPI mkdirs(const char* fullpath);

/**@brief ��ȡapp�����ļ���·��
*@param INOUT  char*  app_path app�����ļ��е�·����������ڴ治С��,FILENAME_MAX
*@return  �Ƿ��ȡ�ɹ�
*/
int UTILSAPI get_app_path(char* app_path);

/*
* ������: add8GreyBmpHead
* ��δ�ӹ���ԭʼ���ݼ���һ��8λ�Ҷ�ͼ��ͷ
* ����:
* ������         ��������      IN/OUT/INOUT      ��ע
* pixData        BYTE *        IN               ԭʼ����
* width          int           IN               ͼƬ��
* height         int           IN               ͼƬ��
* desData        BYTE *        OUT              �ڴ��м���ͷ�����ݿ�
* ����ֵ��
* ���ͣ�int
* ȡֵ��0:�ɹ�,����:��
* ������by pipawancui
 **/
int UTILSAPI add8GreyBmpHead(BYTE* pixData, int16_t width,int16_t height, BYTE* desData);

/*
* @brief ��ԭʼ���ݼ���8λ�Ҷ�ͷ�������һ���ļ���
* @param BYTE*          pixData     IN  ԭʼ����
* @param int            width       IN  ͼƬ��
* @param int            height      IN  ͼƬ��
* @param const char*    filepath    OUT ������ļ�·��
* @return ��
*/
int UTILSAPI add8GreyBmpHead2File(BYTE* pixData, int width, int height, const char* desFile);





#ifdef __cplusplus
}
#endif

