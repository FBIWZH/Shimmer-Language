#include                <iostream>
#include               <algorithm>
#include                   <cmath>
#include                     <map>
#include                  <vector>
#include                     <any>
#include                "hint.hpp"
#include 		   <bits/extc++.h>
#include 			   <windows.h>
#define toint std::any_cast<HyperInt>
#define todb std::any_cast<double>
#define varTo std::any_cast
typedef std::vector<std::any> list;
using __gnu_pbds::gp_hash_table;
namespace shimmer
{
    inline std::any solve(std::string s);
    struct result{std::any value;bool isok;};
    struct funct
    {
        gp_hash_table<std::string, std::vector<std::string> >mp;
        inline result lookup(std::string name)
        {
            auto pos=mp.find(name);
            if(pos==mp.end())return result{std::any(NULL),false};
            return result{pos->second,true};
        }
    }func;
    struct VARPOCESSER
    {
        gp_hash_table<std::string,std::any>vars;
        inline result lookup(std::string name)
        {
            auto pos=vars.find(name);
            if(pos==vars.end())return result{std::any(NULL),false};
            return result{pos->second,true};
        }
        inline void set(std::string name,std::any p)
        {
            auto pos=vars.find(name);
            if(pos==vars.end())vars.insert(std::pair<std::string,std::any>(name,p));
            else vars[name]=p;
            
        }
    }variable;
}
template<typename T>
inline int print(T x)
{
	std::cout<<x;
	return 1;
}
template<>
inline int print(std::any x)
{
	if(x.type()==typeid(int))
		{std::cout<<varTo<int>(x);return 1;}
    if(x.type()==typeid(HyperInt))
		{std::cout<<toint(x);return 1;}
	if(x.type()==typeid(long long))
		{std::cout<<varTo<long long>(x);return 1;}
	if(x.type()==typeid(float))
		{std::cout<<varTo<float>(x);return 1;}
	if(x.type()==typeid(double))
		{std::cout<<varTo<double>(x);return 1;}
	if(x.type()==typeid(std::string))
		{std::cout<<varTo<std::string>(x);return 1;}
	if(x.type()==typeid(char))
		{std::cout<<varTo<char>(x);return 1;}
	if(x.type()==typeid(char *))
		{std::cout<<varTo<char * >(x);return 1;}
    if(x.type()==typeid(std::vector<std::any>))
	{
        std::vector<std::any> t=varTo<std::vector<std::any>>(x);
        print('[');
        for(int i=0;i<t.size()-1;i++)print(t[i]),print(',');
        print(t[t.size()-1]);print(']');
        return 1;
    }
	return 0;
}
template<typename T,typename ...Args>
inline int print(T t,Args... args){return print(t)&print(args...);}
void COLOR_PRINT(const char* s, int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
    std::cout<<s;
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

	
std::string trim(const std::string& str) {
    	std::string::size_type pos = str.find_first_not_of(' ');
		if (pos == std::string::npos) {  //若找不到空格
			return str;
		}
		std::string::size_type pos2 = str.find_last_not_of(' ');
		if (pos2 != std::string::npos)
			return str.substr(pos, pos2 - pos + 1); //子串：第一个非空格作为起始位置
			                                        // 字符个数：pos2-pos+1
		return str.substr(pos);
	}