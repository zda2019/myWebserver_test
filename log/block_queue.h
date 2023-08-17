//循环数组实现阻塞队列

#ifndef BLOCK_QUEUE_H
#define BLOCK_QUEUE_H

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "../lock/locker.h"

using namespace std;

template<class T>
class block_queue
{
private:
    locker m_mutex;
    cond m_cond;

    T *m_array;
    int m_size;
    int m_max_size;
    int m_front;
    int m_back;
public:
    //构造函数
    block_queue(int max_size = 1000)
    {
        if (max_size <= 0)
        {
            exit(-1);
        }

        m_max_size = max_size;
        m_array = new T[max_size];
        m_size = 0;
        m_front = -1;
        m_back = -1;
    }

    void clear()
    {

    }





    ~block_queue();
};

block_queue::block_queue(/* args */)
{
}

block_queue::~block_queue()
{
}









#endif