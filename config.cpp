#include "config.h"

Config::Config()
{
    //端口号，默认为9006
    PORT = 9006;

    //日志写入方式，默认同步
    int LOGWrite = 0;

    //触发组合模式listenfd LT+connfd LT
    TRIGMode = 0;

    //listenfd触发模式,默认LT
    LISTENTrignode = 0；

    //connfd触发方式,默认LT
    CONNTrigmode = 0;

    //优雅关闭链接,默认不使用
    OPT_LISGER = 0;

    //数据库连接池数量，默认为8
    sql_num = 8;

    //线程池内的线程数量，默认为8
    thread_num = 8;

    //是否关闭日志，默认不关闭
    close_log = 0;

    //并发模型选择，默认为proactor
    actor_model = 0;
}



//利用命令行方式去进行配置
//在main函数中传递argc argv给该函数并调用
//./server -p 8000 -l 1
//这样就可以通过命令行将相关参数传递到配置函数中
void Config::parse_arrg(int argc, char* argv[])
{
    int opt;

    //str中记录了所有合法的参数
    const char *str = "p:l:m:o:s:t:c:a:";

    //通过while循环不断读取配置信息，从而进行配置
    //getopt为内置函数
    while ((opt == getopt(argc, argv, str)) != -1)
    {
        switch(opt)
        {
            //参数为p时，设置端口：port/  ./server -p 8000
            case 'p':
            {
                //optarg 是一个全局变量，用于存储 getopt 函数解析命令行选项时得到的参数值。
                //在你的代码中，optarg 用于存储选项后面的参数，比如 -p 8080 中的 8080。

                // 在调用 getopt 函数时，如果一个选项需要带参数，你可以使用冒号（:）来标记，
                //然后 getopt 函数会将参数的值存储在 optarg 中。
                //在你的代码中，你的 str 变量被设置为 "p:l:m:o:s:t:c:a:"，
                //这个字符串中的每个字母代表一个选项，后面的冒号表示这个选项需要参数。

                // 所以，当你的程序解析 -p 选项时，getopt 会将 -p 后面的参数（如 8080）存储在 optarg 中，
                //然后你使用 atoi(optarg) 来将字符串转换成整数。
                //这样你就可以将命令行中的参数值赋给对应的配置参数
                PORT = atoi(optarg);
                break;
            }
            case 'l':
            {
                LOGWrite = atoi(optarg);
                break;
            }
            case 'm':
            {
                TRIGMode = atoi(optarg);
                break;
            }
            case 'o':
            {
                OPT_LISGER = atoi(optarg);
                break;
            }
            case 's':
            {
                sql_num = atoi(optarg);
                break;
            }
            case 't':
            {
                thread_num = atoi(optarg);
                break;
            }
            case 'c':
            {
                close_log = atoi(optarg);
                break;
            }
            case 'a':
            {
                actor_model = atoi(optarg);
                break;
            }
            default:
                break;
        }
    }
}