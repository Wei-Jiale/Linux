#include<iostream>
#include<mutex>

using namespace std;

namespace WJL{
    template<class T>
    class shared_ptr{
    public:
        // 构造函数
        shared_ptr(T* ptr)
            :_ptr(ptr)
            ,_pcount(new int(1))
            ,_pmutex(new mutex)
        {}
        
        // 拷贝构造
        shared_ptr(shared_ptr<T>& sp)
            :_ptr(sp._ptr)
            ,_pcount(sp._pcount)
            ,_pmutex(sp._pmutex)
        {
            add_ref_count();
        }

        // 增加引用计数
        void add_ref_count(){
            // 引用计数操作需要加锁
            _pmutex->lock();
            ++(*_pcount);
            _pmutex->unlock();
        }
        
        // 赋值
        shared_ptr<T>& operator=(shared_ptr<T>& sp){
            if(this != &sp){
                // 释放手中的资源
                release();
                // 一起管理资源
                _ptr = sp._ptr;
                _pcount = sp._pcount;
                _pmutex = sp._pmutex;

                add_ref_count();
            }

            return *this;
        }

        // 释放资源
        void release(){
            bool flag = false;
            _pmutex->lock();
            // 对引用计数进行判断
            if(--(*_pcount) == 0){
                if(_ptr){
                    delete _ptr;
                    _ptr = nullptr;
                }

                delete _pcount;
                _pcount = nullptr;
                flag = true;
            }
            _pmutex->unlock();
            
            if(flag == true){
                delete _pmutex;
                _pmutex = nullptr;
            }
        }

        // 析构函数
        ~shared_ptr(){
            release();
        }

        T* operator->(){
            return _ptr;
        }

        T& operator*(){
            return *_ptr;
        }

    private:
        T* _ptr;
        int* _pcount; // 引用计数
        mutex* _pmutex; // 互斥锁
    };
}
