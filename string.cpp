#include<iostream>
#include<cstring>
using namespace std;

namespace WJL{
    class string{
    public:
        // 构造函数
        string(char* str)
            :_str(new char[strlen(str) + 1])
        {
            strcpy(_str,str);   
        }

        // 析构函数
        ~string(){
            delete[] _str;
            _str = nullptr;
        }

        // 拷贝构造
        string(const string& s)
            :_str(nullptr)
        {
            string temp(s._str);
            swap(_str,temp._str);
        }

        // 赋值
        string& operator=(string s){
            swap(_str,s._str);
            return *this;
        }

        size_t size()const{
            return strlen(_str);
        }

        char& operator[](size_t i){
            return _str[i];
        }
    private:
        // string底层是一个字符数组
        char* _str;

    };
}
