#include<iostream>
using namespace std;

namespace WJL{
    template<class T>
    class auto_ptr{
    public:
        // 构造函数保存资源
        auto_ptr(T* ptr)
            :_ptr(ptr)
        {}

        // 析构函数释放资源
        ~auto_ptr(){
            if(_ptr){
                delete _ptr;
                _ptr = nullptr;
            }
        }

        // 管理权转移
        auto_ptr(auto_ptr<T>& ap)
            :_ptr(ap._ptr)
        {
            ap._ptr = nullptr;
        }

        auto_ptr<T>& operator=(auto_ptr<T>& ap){
            // 自己给自己赋值不被允许
            if(this != ap){
                auto_ptr<T> Temp(ap);
                
                T* ptr = Temp._ptr;
                Temp._ptr = _ptr;
                _ptr = ptr;
            }

            return *this;
        }

        // 重载operator->
        T* operator->(){
            return _ptr;
        }

        // 重载operator*
        T& operator*(){
            return *_ptr;
        }

    private:
        // 首先得有一个指针
        T* _ptr;
    };
}
