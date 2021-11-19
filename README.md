# utils

这是一个工作中经常用到的，基于C语言封装的工具类库

# 函数介绍：

size_t write_data_hex(unsigned char* pucBuff, size_t uiBuffSize,const char* pcFileNm);

size_t read_data_hex(unsigned char* pucBuff, size_t uiBuffSize,const char* pcFileNm);

*@brief 枚举相对app路径下匹配到的文件名
int list_matched_filename_app(const char* folder, const char* pattern, char* name_list, size_t name_size, int name_max_count);

*@brief 打印相对app路径下匹配到的文件名
int print_matched_filename_app(const char* folder, const char* pattern);

*@brief 一个相对自动化的函数，可以枚举相对app路径下匹配到的文件名,要记得释放name_list中分配的内存
int auto_list_filename_app(const char* folder, const char* pattern, char** name_list, int name_size, int* name_count);

*@brief 创建相对app路径文件的图片
int save_gray_bmp_app(const char* folder, const char* pre_name, unsigned char* rowdata, size_t width, size_t height);

*@brief 统计相对app路径文件下文件的数量
int count_filename_app(const char* folder, const char* pattern);

*在APP中建立文件夹
int creat_dir_in_app(const char* filename);

*生成指定路径的文件夹
void mkdirs(const char* fullpath);

*@brief 获取app所在文件夹路径
int get_app_path(char* app_path);

*给未加工的原始数据加上一个8位灰度图的头
int add8GreyBmpHead(BYTE* pixData, size_t width,size_t height, BYTE* desData);

*@brief 将原始数据加上8位灰度头，输出到一个文件中
int add8GreyBmpHead2File(BYTE* pixData, size_t width, size_t height, const char* desFile);



