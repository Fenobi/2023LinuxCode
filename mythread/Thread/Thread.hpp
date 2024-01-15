#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <pthread.h>
#include <functional>
#include <cassert>

// header only 开源代码
class Thread;

class Contest
{
public:
    Thread *_this;
    void *_args;
public:
    Contest():_this(nullptr),_args(nullptr)
    {}
    ~Contest()
    {}
};

class Thread
{
public:
    typedef std::function<void *(void *)> func_t;
    const int num = 1024;

public:
    Thread(func_t func, void *args = nullptr, int number = 0) : _func(func), _args(args)
    {
        char buffer[num];
        snprintf(buffer, sizeof buffer, "thread-%d", number);
        _name = buffer;

        // 异常 == if:意料之外用
        // assert:意料之中用
        Contest *ctx = new Contest();
        ctx->_args = _args;
        ctx->_this = this;
        int n = pthread_create(&_tid, nullptr, start_routine, ctx);
        assert(n == 0); // 编译debug的方式发布的时候存在，releasse方式发布，assert就不存在了，n就是一个定义了，但是没有被使用的变量在有的编译器届会有warning
        (void)n;
    }

    // 在类内创建线程，想让线程执行对应的方法，需要将方法设置成static
    static void *start_routine(void *args) // 类内成员,有缺失参数this
    {
        Contest *ctx = static_cast<Contest *>(args);
        void* ret = ctx->_this->run(ctx->_args);
        delete ctx;
        return ret;
        // // 静态方法不能调用成员方法或者成员变量
        // return _func(_args);
    }

    // void start()
    // {
        
    // }

    void join()
    {
        int n = pthread_join(_tid, nullptr);
        assert(n == 0);
        (void)n;
    }

    void *run(void *args)
    {
        return _func(args);
    }

    ~Thread()
    {
        //do nothing
    }
private:
    std::string _name;
    func_t _func;
    void *_args;

    pthread_t _tid;
};


