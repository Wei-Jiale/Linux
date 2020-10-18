#include<iostream>
using namespace std;

namespace WJL{
    template<class T>
    class unique_ptr{
    public:
        // 构造函数
        unique_ptr(T* ptr)
            :_ptr(ptr)
        {}

        // 析构函数
        ~unique_ptr(){
            if(_ptr){
                delete _ptr;
                _ptr = nullptr;
            }
        }

        // 禁止拷贝和赋值
        unique_ptr(unique_ptr<T>& up) = delete;
        unique_ptr<T>& operator=(unique_ptr<T>& up) = delete;

        T* operator->(){
            return _ptr;
        }

        T& operator*(){
            return *_ptr;
        }

    private:
       T* _ptr; 
    };
}
