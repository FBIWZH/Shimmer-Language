#include"express.hpp"
namespace shimmer
{
    bool startwith(string f,string son)
    {
        if(f.size()<son.size())return false;
        for(int i=0;i<son.size();i++)
            if(f[i]!=son[i])return false;
        return true;
    }
    inline std::any eval(std::string s)
    {
        expression e;
        e.setstr(s);
        return e.evaluate();
    }
    inline void isif(std::string s)
    {
        s.erase(s.begin(),s.begin()+2);
        trim(s);
            s.erase(s.end()-1);
            std::any k=eval(s);
            bool f=0;
            if(k.type()==typeid(string)||k.type()==typeid(std::vector<std::any>))
            {
                std::cout<<"Error: the type of the `if` can not be `string` or `list`.";
                return ;
            }
            if(k.type()==typeid(int))
                {f=varTo<int>(k)!=0;}
            if(k.type()==typeid(HyperInt))
                {f=toint(k)!=0;}
            if(k.type()==typeid(long long))
                {f=varTo<long long>(k)!=0;}
            if(k.type()==typeid(float))
                {f=varTo<float>(k)!=0;}
            if(k.type()==typeid(double))
                {f=varTo<double>(k)!=0;}
            
    }
    std::any qread()
    {
        
        std::string s;
        freopen("CON","r",stdin);
        std::cin>>s;
        std::any x=eval(s);
        freopen(fina,"r",stdin);
        return x;
    }
    inline std::any solve(std::string s)
    {
        //std::cout<<s<<std::endl;
        if(!(startwith(s,"$"))&&!s.empty())
        {
            if(startwith(s,"print"))
            {
                int b=1;
                int i=5;
                string t;
                while(s[i]==' '||s[i]=='\t'||s[i]=='(')i++;
                while(b&&i<s.size())
                {
                    if(s[i]==')')b--;
                    else if(s[i]=='(')b++;
                    t+=s[i++];
                }
                t.erase(t.size()-1,t.size());
                string tp;b=0;
                for(int j=0;j<t.size();j++)
                {
                    if(t[j]==','&&(!b))
                    {
                        print(shimmer::solve(tp),eval("ends"));
                        tp.clear();
                    }
                    else tp+=t[j],b+=int(t[j]=='(')-int(t[j]==')');
                }
                print(shimmer::solve(tp));
            }
            else if(startwith(s,"fn"))
            {
                int b=1;
                int i=2;
                string t,token;
                while(s[i]==' '||s[i]=='\t')i++;
                while((isalpha(s[i])||s[i]=='_'||(s[i]>='0'&&s[i]<='9'))&&i<(int)s.size())token+=s[i++];i++;
                while(b&&i<s.size())
                {
                    if(s[i]==')')b--;
                    else if(s[i]=='(')b++;
                    t+=s[i++];
                }
                t.erase(t.size()-1,t.size());
                std::vector<std::any> res;
                string tp;
                for(int j=0;j<t.size();j++)
                {
                    if(t[j]==',')
                    {
                        func.mp[trim(token)].push_back(trim(tp));
                        tp.clear();
                    }
                    else tp+=t[j];
                }
                func.mp[trim(token)].push_back(trim(tp));
                string all,tll;
                while(std::getline(std::cin,tll))
                {
                    if(trim(tll)=="end")break;
                    all+=trim(tll)+'\n';
                }
                func.mp[trim(token)].push_back(all);
            }
            else if(startwith(trim(s),"if"))
            {
                isif(s);
            }
            else if(trim(s)=="exit()")return result{NULL,NULL};
            else return eval(s);
        }
        return 0;
    }
}