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
	* @param    pucBuff    �������Ƶ�����Դ             IN
	* @param    uiBuffSize Ҫд��ĳ���                 IN
	* @param    pcFileNm   Ŀ���ļ���,��Ҫ�ṩ����·��   IN
	* @return   �Ǹ���,����д��ĳ���;����,�д�����
	*/
	size_t UTILSAPI write_data_hex(unsigned char* pucBuff, size_t uiBuffSize, const char* pcFileNm);

	/*@brief ��Դ�ļ��ж�ȡָ����С���ݵ��ڴ����
	* @param    pucBuff     ��д����ڴ�飬����ǰ������ڴ�     INOUT
	* @param    uiBuffSize  ���������ݵĳ���                    IN
	* @param    pcFileNm    Դ�ļ�������·��                    IN
	* @return �Ǹ���,���ض���ĳ��ȴ�С;����,�д�����
	*/
	size_t UTILSAPI read_data_hex(unsigned char* pucBuff, size_t uiBuffSize, const char* pcFileNm);

	/*@brief ��ȡ���app·����ƥ�䵽���ļ���
	 *@param  addr           �ļ�·�� ���APP��·��                      IN
	 *@param  pattern	     ����ƥ��ģ�� �ɰ���*���ߣ�                   IN
	 *@param  name_list      ���ֻ���·������ַ ����ǰ������ڴ��С       INOUT
	 *@param  name_size      ��������Ԥ���ĳ���                          IN
	 *@param  name_max_count �ļ����ĸ�������Ҫ��ǰ֪���ж����ļ���        IN
	 *@return ����ֵΪ�ҵ����ļ�����
	 */
	int UTILSAPI list_matched_filename_app(const char* folder, const char* pattern, char* name_list, int name_size, int name_max_count);

	/*@brief �ڿ���̨��ӡ���app·����ƥ�䵽���ļ���
	* @param  folder     �ļ������APP��·��						IN
	* @param  pattern    ����									IN
	* @return ����ƥ�䵽���ļ�������,����0��ʾû��ƥ�䵽�κ��ļ���
	*/
	int UTILSAPI print_matched_filename_app(const char* folder, const char* pattern);

	/*@brief һ���Զ����ĺ���������ö�����app·����ƥ�䵽���ļ���,Ҫ�ǵ��ͷ�name_list�з�����ڴ�
	 *@param  folder         �ļ�·�� ���APP��·��																					IN
	 *@param  pattern	     ����ƥ��ģ�� �ɰ���*���ߣ�																				IN
	 *@param  name_list      ���ֻ���·������ַ������ʱ����һ��ָ��ĵ�ַ���ǵ��ͷ��ں����з�����ڴ棨���ò���ôд����֪��ҪԤ�ȷ�������ڴ棩OUT
	 *@param  name_size      ÿ�����ֵĳ���																							IN
	 *@param  name_count     �ļ����ĸ��������ں����и�ֵ��																			OUT
	 *@return �Ǹ�ֵΪ�ҵ����ļ����������Ϊ��ֵ�������쳣
	 *@author bob
	 */
	int UTILSAPI auto_list_filename_app(const char* folder, const char* pattern, char** name_list, int16_t name_size, int* name_count);


	/*@brief �������app·���ļ���ͼƬ��
	*@param folder   app�е��ļ���												IN
	*@param rowdata  ͼƬ��������													IN
	*@param pre_name �ļ���ǰ׺�������ΪNULL����1.bmp��2.bmp��3.bmp...�ķ�ʽ����	IN
	*@param width    ͼƬ��														IN
	*@param height   ͼƬ��														IN
	*@return ����ֵ������
	*/
	int UTILSAPI save_gray_bmp_app(const char* folder, const char* pre_name, unsigned char* rowdata, int16_t width, int16_t height);

	/**@brief ͳ�����app·���ļ����ļ�������
	*@param  folder  Ӧ�ó����е��ļ���					IN
	*@param  pattern �ļ�ƥ��ģ�� �ɰ���*���ߣ�			IN
	*@return ����:�������д�����,�Ǹ���:ƥ�䵽���ļ�����
	*/
	int UTILSAPI count_filename_app(const char* folder, const char* pattern);

	/*
	* @brief    ��APP�н����ļ���
	* @param    filename �轨���ļ��е�����					IN
	* @return   ���ظ���,�����ļ����з�������;�����㣬���ɳɹ�
	*/
	int UTILSAPI creat_dir_in_app(const char* filename);

	/*
	* @brief    ����ָ��·�����ļ���
	* @param    fullpath ָ����ȫ·��					IN
	* @return   ����:�����ļ����з�������;0:���ɳɹ�
	*/
	int UTILSAPI mkdirs(const char* fullpath);

	/**@brief ��ȡapp�����ļ���·��
	*@param   char*  app_path app�����ļ��е�·��,��Ҫ��ǰ������ڴ�,������ڴ治С��,FILENAME_MAX	INOUT
	*@return  ����:�����з�������,0:��������
	*/
	int UTILSAPI get_app_path(char* app_path);

	/**@brief ��ָ���ļ����ؽ��ڴ�
	*@param filename Ҫ��ȡ���ļ���												IN
	*@param buff     �贫�����ָ��,�����ļ����ڴ��,�ں����ڷ���,ʹ������Ҫ�ֶ����	OUT
	*@param int      ���ض�ȡ�ļ��ĳ���											OUT
	*@return 0:�ɹ����ؽ��ڴ�,����:�����˴���
	*/
	int UTILSAPI load_file(const char* file_path, unsigned char** buff, size_t* file_len);


	/*
	*@brief ��δ�ӹ���ԭʼ���ݼ���һ��8λ�Ҷ�ͼ��ͷ
	*
	*@param     pixData                 ԭʼ����								IN
	*@param     width                   ͼƬ��								IN
	*@param     height                  ͼƬ��								IN
	*@param     desData                 �ڴ��м���ͷ�����ݿ�,����ǰ������ڴ��	INOUT
	*@return ������
	*@author pipawancui
	 **/
	int UTILSAPI add8GreyBmpHead(BYTE* pixData, int16_t width, int16_t height, BYTE* desData);

	/*
	* @brief ��ԭʼ���ݼ���8λ�Ҷ�ͷ�������һ���ļ���
	* @param    pixData     ԭʼ����			IN
	* @param    width       ͼƬ��			IN
	* @param    height      ͼƬ��			IN
	* @param    filepath    ������ļ�·��	IN
	* @return ������
	*/
	int UTILSAPI add8GreyBmpHead2File(BYTE* pixData, int width, int height, const char* desFile);





#ifdef __cplusplus
}
#endif


