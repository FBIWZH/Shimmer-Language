#include "headers\struct.hpp"
using namespace std;
wchar_t *GetWC(char *c)
{
    size_t cSize = strlen(c)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs (wc, c, cSize);

    return wc;
}
int main(int argc, char *argv[])
{
    shimmer::variable.set("ends"," ");
    if(argc==1){debug();return 0;}
    if(argc>2)
    {
        string arg=argv[1];
        if(arg=="-run")
        {
            for(int i=2;i<=argc;i++)
            {
                freopen(argv[i],"r",stdin);
                string str;
                while(std::getline(cin,str))
                {
                    any a=shimmer::solve(str);
                    if(a.type()==typeid(shimmer::result))break;
                }
            }
        }
        if(arg=="-c")
        {
            string arg2=argv[2];
            if(arg2=="-ffast")
            {
                
            }
            else
            {
                for(int i=2;i<=argc;i++)
                {
                    string s=argv[i];
                    s+="c";
                    freopen(argv[i],"r",stdin);
                    freopen(s.c_str(),"w",stdout);
                    string str;
                    while(cin)
                        std::getline(cin,str),cout<<trim(str)<<endl;
                }
            }
        }
    }
    return 0;
}