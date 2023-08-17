#ifndef LOCKER_H
#define LOCKER_H

#include <exception>
#include <pthread.h>
#incldue <semaphore.h>

//定义了一个名为 sem 的类，用于封装对 POSIX 信号量的操作。
//封装的意义在于：
//      错误处理：封装的类可以在构造函数中检查信号量初始化的成功与否，如果初始化失败，可以抛出异常，从而在更高层次上处理错误。
//      资源管理：封装的类可以在析构函数中释放信号量的资源，确保在对象生命周期结束时，信号量得到适当的释放。
//      隐藏细节
class sem
{
public:
    //原始信号量初始化函数为sem_init
    //int sem_init __P ((sem_t *__sem, int __pshared, unsigned int __value));　
    //sem为指向信号量结构的一个指针；
    //pshared不为０时此信号量在进程间共享，否则只能为当前进程的所有线程共享；
    //value给出了信号量的初始值。
    sem()
    {
        if (sem_init(&m_sem, 0, 0) != 0)
        {
            throw std::exception();
        }
    }

    sem(int num)
    {
        if (sem_init(&m_sem, 0,num) != 0)
        {
            throw std::exception();
        }
    }

    //sem_desroy:释放信号量m_sem
    ~sem()
    {
        sem_desroy(&m_sem);
    }

    bool wait()
    {
        return sem_wait(&m_sem) == 0;
    }

    bool post()
    {
        return sem_post(&m_sem) == 0;
    }

private:
    //sem_t 是 POSIX 线程库（Pthreads）中用于表示信号量的数据类型。
    //它是一种用于线程同步的原语，用于管理共享资源的并发访问，
    //以及实现线程之间的同步和通信。

    //sem_t 是 POSIX 标准中定义的数据类型，由线程库提供支持。
    //它是在多线程编程环境中使用的一种机制，可以用于线程之间的同步和互斥。

    //在你的代码中，sem_t m_sem; 定义了一个 sem_t 类型的成员变量 m_sem，
    //用于表示信号量。通过调用 sem_init 函数来初始化信号量，
    //通过 sem_wait 和 sem_post 函数来实现对信号量的等待和递增操作。

    //注意，使用信号量需要包含头文件 <semaphore.h>，
    //这个头文件提供了与信号量相关的函数和数据类型的声明。
    //因此，在使用信号量之前，需要包含这个头文件以确保相关的声明可用
    
    sem_t m_sem;

}


class locker
{
public:
    locker()
    {
        if (pthread_mutex_init(&m_mutex, NULL) != 0)
        {
            throw std::exception();
        }
    }

    ~locker()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }

    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }

private:
    pthread_mutex_t m_mutex;
}


class cond
{
public:
    cond()
    {
        if (pthread_cond_init(&m_cond, NULL) != 0)
        {
            throw std::exception();
        }
    }

    ~cond()
    {
        pthread_cond_destory(&m_cond);
    }

    bool wait(pthread_mutex_t *m_mutex)
    {
        int ret = 0;
        ret = pthread_cond_wait(&m_cond, m_mutex);
        return ret == 0;
    }

    bool timewait(pthread_mutex_t *m_mutex, struct timesec t)
    {
        int ret = 0;
        ret = pthread_cond_timewait(&m_cond, m_mutex, &t);
        return ret == 0;
    }

    bool signal()
    {
        return pthread_cond_signal(&m_cond) == 0;
    }

    bool broadcast()
    {
        return pthread_cond_broadcast(&m_cond) == 0;
    }

private:
    pthread_cond_t m_cond;

}

#endif
