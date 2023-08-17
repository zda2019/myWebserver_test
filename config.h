//头文件保护预处理指令，防止在同一编译的单元多次包含相同头文件
//从而避免重复定义与编译错误
#ifndef CONFIG_H
#define CONFIG_H

#include "webserver.h"

using namespace std;

class Config
{
public:
    Config();
    ~Config(){};

    void parse_arrg(int argc, char* argv[]);

    //端口
    int PORT;

    //日志写入方式
    int LOGWrite;

    //触发组合模式
    int TRIGMode;

    //listenfd触发模式
    int CONNTrigmode;

    //优雅关闭链接
    int OPT_LISGER;

    //数据库连接池数量
    int sql_num;

    //线程池内的线程数量
    int thread_num;

    //是否关闭日志
    int close_log;

    //并发模型选择
    int actor_model;





};


#endif