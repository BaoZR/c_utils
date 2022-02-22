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




#define IN 
#define OUT 
#define INOUT 




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

/*@brief ��ָ����С���ڴ��д�뵽�����ļ���
* @param    pucBuff    �������Ƶ�����Դ
* @param    uiBuffSize Ҫд��ĳ���
* @param    pcFileNm   Ŀ���ļ���,��Ҫ�ṩ����·��
* @return   �Ǹ���,����д��ĳ���;����,�д�����
*/
size_t UTILSAPI write_data_hex(IN unsigned char* pucBuff, IN size_t uiBuffSize,IN const char* pcFileNm);

/*@brief ��Դ�ļ��ж�ȡָ����С���ݵ��ڴ����
* @param    pucBuff     ��д����ڴ�飬����ǰ������ڴ�
* @param    uiBuffSize  ���������ݵĳ���
* @param    pcFileNm    Դ�ļ�������·��
* @return �Ǹ���,���ض���ĳ��ȴ�С;����,�д�����
*/
size_t UTILSAPI read_data_hex(INOUT unsigned char* pucBuff,IN size_t uiBuffSize,IN const char* pcFileNm);

/*@brief ��ȡ���app·����ƥ�䵽���ļ���
 *@param  addr           �ļ�·�� ���APP��·��
 *@param  pattern	     ����ƥ��ģ�� �ɰ���*���ߣ�
 *@param  name_list      ���ֻ���·������ַ ����ǰ������ڴ��С
 *@param  name_size      ��������Ԥ���ĳ���
 *@param  name_max_count �ļ����ĸ�������Ҫ��ǰ֪���ж����ļ���
 *@return ����ֵΪ�ҵ����ļ�����
 */
int UTILSAPI list_matched_filename_app(IN const char* folder,IN const char* pattern,INOUT char* name_list,IN int name_size,IN int name_max_count);

/*@brief �ڿ���̨��ӡ���app·����ƥ�䵽���ļ���
* @param  folder     �ļ������APP��·��
* @param  pattern    ����
* @return ����ƥ�䵽���ļ�������,����0��ʾû��ƥ�䵽�κ��ļ���
*/
int UTILSAPI print_matched_filename_app(IN const char* folder,IN const char* pattern);

/*@brief һ���Զ����ĺ���������ö�����app·����ƥ�䵽���ļ���,Ҫ�ǵ��ͷ�name_list�з�����ڴ�
 *@param  folder         �ļ�·�� ���APP��·��
 *@param  pattern	     ����ƥ��ģ�� �ɰ���*���ߣ�
 *@param  name_list      ���ֻ���·������ַ������ʱ����һ��ָ��ĵ�ַ���ǵ��ͷ��ں����з�����ڴ棨���ò���ôд����֪��ҪԤ�ȷ�������ڴ棩
 *@param  name_size      ÿ�����ֵĳ���
 *@param  name_count     �ļ����ĸ��������ں����и�ֵ��
 *@return �Ǹ�ֵΪ�ҵ����ļ����������Ϊ��ֵ�������쳣
 *@author bob
 */
int UTILSAPI auto_list_filename_app(IN const char* folder,IN const char* pattern,OUT char** name_list,IN int16_t name_size,OUT int* name_count);


/*@brief �������app·���ļ���ͼƬ��
*@param folder   app�е��ļ���
*@param rowdata  ͼƬ��������
*@param pre_name �ļ���ǰ׺�������ΪNULL����1.bmp��2.bmp��3.bmp...�ķ�ʽ����
*@param width    ͼƬ��
*@param height   ͼƬ��
*@return ����ֵ������
*/
int UTILSAPI save_gray_bmp_app(IN const char* folder,IN const char* pre_name,IN unsigned char* rowdata,IN int16_t width,IN int16_t height);

/**@brief ͳ�����app·���ļ����ļ�������
*@param  folder  Ӧ�ó����е��ļ���
*@param  pattern �ļ�ƥ��ģ�� �ɰ���*���ߣ�
*@return ����:�������д�����,�Ǹ���:ƥ�䵽���ļ�����
*/
int UTILSAPI count_filename_app(IN const char* folder,IN const char* pattern);

/*
* @brief    ��APP�н����ļ���
* @param    filename �轨���ļ��е�����
* @return   ���ظ���,�����ļ����з�������;�����㣬���ɳɹ�
*/
int UTILSAPI creat_dir_in_app(IN const char* filename);

/*
* @brief    ����ָ��·�����ļ���
* @param    fullpath ָ����ȫ·��
* @return   ����:�����ļ����з�������;0:���ɳɹ�
*/
int UTILSAPI mkdirs(IN const char* fullpath);

/**@brief ��ȡapp�����ļ���·��
*@param   char*  app_path app�����ļ��е�·��,��Ҫ��ǰ������ڴ�,������ڴ治С��,FILENAME_MAX
*@return  ����:�����з�������,0:��������
*/
int UTILSAPI get_app_path(INOUT char* app_path);

/**@brief ��ָ���ļ����ؽ��ڴ�
*@param filename Ҫ��ȡ���ļ���
*@param buff     �贫�����ָ��,�����ļ����ڴ��,�ں����ڷ���,ʹ������Ҫ�ֶ����
*@param int      ���ض�ȡ�ļ��ĳ���
*@return 0:�ɹ����ؽ��ڴ�,����:�����˴���
*/
int UTILSAPI load_file(IN const char* file_path, OUT unsigned char** buff , OUT size_t* file_len);


/*
*@brief ��δ�ӹ���ԭʼ���ݼ���һ��8λ�Ҷ�ͼ��ͷ
* 
*@param     pixData                 ԭʼ����
*@param     width                   ͼƬ��
*@param     height                  ͼƬ��
*@param     desData                 �ڴ��м���ͷ�����ݿ�,����ǰ������ڴ��
*@return ������
*@author pipawancui
 **/
int UTILSAPI add8GreyBmpHead(IN BYTE* pixData,IN int16_t width,IN int16_t height,INOUT BYTE* desData);

/*
* @brief ��ԭʼ���ݼ���8λ�Ҷ�ͷ�������һ���ļ���
* @param    pixData     ԭʼ����
* @param    width       ͼƬ��
* @param    height      ͼƬ��
* @param    filepath    ������ļ�·��
* @return ������
*/
int UTILSAPI add8GreyBmpHead2File(IN BYTE* pixData,IN int width,IN int height,IN const char* desFile);





#ifdef __cplusplus
}
#endif


