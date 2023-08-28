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
    inline void isif()
    {
        
    }
    inline std::any eval(std::string s)
    {
        expression e;
        e.setstr(s);
        return e.evaluate();
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
                std::vector<std::any> res;
                string tp;
                for(int j=0;j<t.size();j++)
                {
                    if(t[j]==',')
                    {
                        print(shimmer::solve(tp),eval("ends"));
                        tp.clear();
                    }
                    else tp+=t[j];
                }
                print(shimmer::solve(tp),eval("ends"));
            }
            else if(startwith(s,"println"))
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
                std::vector<std::any> res;
                string tp;
                for(int j=0;j<t.size();j++)
                {
                    if(t[j]==',')
                    {
                        print(shimmer::solve(tp),eval("ends"));
                        tp.clear();
                    }
                    else tp+=t[j];
                }
                print(shimmer::solve(tp),eval("ends"),'\n');
            }
            else if(startwith(s,"fc"))
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
            else return eval(s);
        }
        return 0;
    }
}