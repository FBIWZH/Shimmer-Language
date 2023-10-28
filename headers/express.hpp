#pragma once
#include                   <stack>
#include                     <any>
#include                  <string>
#include                   <cmath>
#include              "define.hpp"
namespace shimmer
{
    using std::stack;
    using std::string;
    class expression
    {  
    private:
        typedef std::any T;
        inline bool delim(char c){ return c==' '||c=='\t';}
        inline bool is_op(char c)
        { 
            return 
                c=='+'||c=='-'||c=='*'||c=='/'||
                c=='='||c=='!'||c=='>'||c=='<'||
                c=='|'||c=='&'||c=='^';
        }
        inline bool is_unary(char c){return c=='+'||c=='-'||c=='!';}
        inline int priority(string op,bool ary=0) 
        {
            if(ary)return 10;
            if (op=="+"||op=="-") return 1;
            if (op=="*"||op=="/") return 2;
            if (op=="**") return 100;
            if (op=="||"||op=="&&")return -1;
            if (op=="|"||op=="&"||op=="^")return -2;
            if (op=="=="||op=="!="||op==">"||op=="<"||op=="<="||op==">=")return 0;
            return -100;
        }

        void process_op(stack<T>& st, string op,bool ary=0) 
        {
            if (ary) 
            {
                T l=st.top();
                st.pop();
                if(typeid(HyperInt)==l.type())
                {
                    if(op=="+")st.push(toint(l));
                    else if(op=="-")st.push(-toint(l));
                    else if(op=="!")st.push(toint(l)==0?1:0);
                }
                
            } 
            else 
            {
                T r=st.top();
                st.pop();
                T l=st.top();
                st.pop();
                if(typeid(HyperInt)==l.type()&&typeid(HyperInt)==r.type())
                {
                    if(op=="+")st.push(toint(l)+toint(r));
                    else if(op=="-")st.push(toint(l)-toint(r));
                    else if(op=="*")st.push(toint(l)*toint(r));
                    else if(op=="%")st.push(toint(l)%toint(r));
                    else if(op=="/")st.push(toint(l)/toint(r));
                    else if(op=="**")st.push(pow(toint(l),toint(r)));
                    else if(op=="==")st.push(HyperInt(int(toint(l)==toint(r))));
                    else if(op=="!=")st.push(HyperInt(int(toint(l)!=toint(r))));
                    else if(op=="||")st.push(toint(l).to_int64()||toint(r).to_int64());
                    else if(op=="&&")st.push(toint(l).to_int64()&&toint(r).to_int64());
                    else if(op=="<")st.push(HyperInt(int(toint(l)<toint(r))));
                    else if(op==">")st.push(HyperInt(int(toint(l)>toint(r))));
                    else if(op=="<=")st.push(HyperInt(int(toint(l)<=toint(r))));
                    else if(op==">=")st.push(HyperInt(int(toint(l)>=toint(r))));
                    else if(op=="|")st.push(toint(l)|toint(r));
                    else if(op=="&")st.push(toint(l)&toint(r));
                    else if(op=="^")st.push(toint(l)^toint(r));
                }
                else if((typeid(HyperInt)==l.type()&&typeid(double)==r.type()))
                {
                    if(op=="+")st.push((double)(int(toint(l).to_int64())+todb(r)));
                    else if(op=="-")st.push((double)(int(toint(l).to_int64())-todb(r)));
                    else if(op=="*")st.push((double)(int(toint(l).to_int64())*todb(r)));
                    else if(op=="/")st.push((double)(int(toint(l).to_int64())/todb(r)));
                    else if(op=="**")st.push((double)(pow(int(toint(l).to_int64()),todb(r))));
                    else if(op=="==")st.push(HyperInt((double)(int(toint(l).to_int64())==todb(r))));
                    else if(op=="!=")st.push(HyperInt((double)(int(toint(l).to_int64())!=todb(r))));
                    else if(op=="||")st.push(toint(l).to_int64()||todb(r));
                    else if(op=="&&")st.push(toint(l).to_int64()&&todb(r));
                    else if(op=="<")st.push(HyperInt(int(toint(l)<todb(r))));
                    else if(op==">")st.push(HyperInt(int(toint(l)>todb(r))));
                    else if(op=="<=")st.push(HyperInt(int(toint(l)<=todb(r))));
                    else if(op==">=")st.push(HyperInt(int(toint(l)>=todb(r))));
                }
                else if(typeid(HyperInt)==r.type()&&typeid(double)==l.type())
                {
                    if(op=="+")st.push((double)(todb(l)+int(toint(r).to_int64())));
                    else if(op=="-")st.push((double)(int(-toint(r).to_int64())+todb(l)));
                    else if(op=="*")st.push((double)(int(toint(r).to_int64())*todb(l)));
                    else if(op=="/")st.push((double)(todb(l)/int(toint(r).to_int64())));
                    else if(op=="**")st.push((double)(pow(todb(l),int(toint(r).to_int64()))));
                    else if(op=="==")st.push(HyperInt((double)(int(toint(r).to_int64())==todb(l))));
                    else if(op=="!=")st.push(HyperInt((double)(int(toint(r).to_int64())!=todb(l))));
                    else if(op=="||")st.push(todb(l)||toint(r).to_int64());
                    else if(op=="&&")st.push(todb(l)&&toint(r).to_int64());
                    else if(op=="<")st.push(HyperInt(int(HyperInt(todb(l))<toint(r))));
                    else if(op==">")st.push(HyperInt(int(HyperInt(todb(l))>toint(r))));
                    else if(op=="<=")st.push(HyperInt(int(HyperInt(todb(l))<=toint(r))));
                    else if(op==">=")st.push(HyperInt(int(HyperInt(todb(l))>=toint(r))));
                }
                else if((typeid(double)==l.type()&&typeid(double)==r.type()))
                {
                    if(op=="+")st.push((double)(todb(l)+todb(r)));
                    else if(op=="-")st.push((double)(todb(l)-todb(r)));
                    else if(op=="*")st.push((double)(todb(l)*todb(r)));
                    else if(op=="/")st.push((double)(todb(l)/todb(r)));
                    else if(op=="**")st.push((double)(pow(todb(l),todb(r))));
                    else if(op=="==")st.push(HyperInt((double)(todb(l)==todb(r))));
                    else if(op=="!=")st.push(HyperInt((double)(todb(l)!=todb(r))));
                    else if(op=="||")st.push(todb(l)||todb(r));
                    else if(op=="&&")st.push(todb(l)&&todb(r));
                    else if(op=="<")st.push(HyperInt(int(todb(l)<todb(r))));
                    else if(op==">")st.push(HyperInt(int(todb(l)>todb(r))));
                    else if(op=="<=")st.push(HyperInt(int(todb(l)<=todb(r))));
                    else if(op==">=")st.push(HyperInt(int(todb(l)>=todb(r))));
                }
                else if((typeid(string)==l.type()&&typeid(string)==r.type()))
                {
                    if(op=="+")st.push((varTo<std::string>(l)+varTo<std::string>(r)));
                    else if(op=="==")st.push(HyperInt(varTo<std::string>(l)==varTo<std::string>(r)));
                    else if(op=="!=")st.push(HyperInt(varTo<std::string>(l)!=varTo<std::string>(r)));
                    else if(op=="<")st.push(HyperInt(int(varTo<std::string>(l)<varTo<std::string>(r))));
                    else if(op==">")st.push(HyperInt(int(varTo<std::string>(l)>varTo<std::string>(r))));
                    else if(op=="<=")st.push(HyperInt(int(varTo<std::string>(l)<=varTo<std::string>(r))));
                    else if(op==">=")st.push(HyperInt(int(varTo<std::string>(l)>=varTo<std::string>(r))));
                }
                else{std::cout<<"error: cannot calculate this expression."<<std::endl;}
            }
        }

        string s;
    public:
        inline void setstr(string str){s=str;}
        T evaluate() 
        {
            if(s=="0")return HyperInt(0);
            stack<T> st;
            stack< std::pair<string,bool> > op;
            bool may_be_unary = true;
            for (int i=0;i<(int)s.size();i++) 
            {
                if(delim(s[i]))continue;
                if(s[i] == '(') 
                {
                    op.push( std::pair<string,bool>("(",0));
                    may_be_unary = true;
                } 
                else if(s[i] == ')')
                {
                    while (op.top().first!="(") 
                    {
                        process_op(st,  op.top().first,op.top().second);
                        op.pop();
                    }
                    op.pop();
                    may_be_unary = false;
                } 
                else if(is_op(s[i])) 
                { 
                    string cur_op;bool unary=0;
                    while(is_op(s[i]))cur_op+=s[i++];i--;
                    if(!st.empty())if(st.top().type()==typeid(string))may_be_unary=false;
                    if (may_be_unary && is_unary(cur_op[0]))unary=true;
                    while (!op.empty() &&
                            ((!unary && priority(op.top().first,op.top().second) >= priority(cur_op,unary)) ||
                            (unary && priority(op.top().first,op.top().second) > priority(cur_op,unary)))) 
                    {
                        process_op(st, op.top().first,op.top().second);
                        op.pop();
                    }
                    op.push(std::pair<string,bool>{cur_op,unary});
                    may_be_unary=true;
                } 
                else if(s[i]>='0'&&s[i]<='9')
                {
                    T number=HyperInt(0);
                    while(i<(int)s.size()&&isalnum(s[i]))
                        number=toint(number)*10+s[i++]-'0';
                    if(s[i]=='.')
                    {
                        number=double(int(toint(number).to_int64()));
                        i++;double x=10.0;
                        while(i<(int)s.size()&&isalnum(s[i]))
                            number=todb(number)+(s[i++]-'0')*1.0/x,x*=10;
                    }
                    --i;
                    st.push(number);
                    may_be_unary = false;
                }
                else if(s[i]=='[')
                {
                    int b=1;i++;
                    string t;
                    while(b&&i<s.size())
                    {
                        if(s[i]==']')b--;
                        else if(s[i]=='[')b++;
                        t+=s[i++];
                    }
                    t.erase(t.size()-1,t.size());
                    std::vector<std::any> res;
                    string tp;
                    for(int j=0;j<t.size();j++)
                    {
                        if(t[j]==',')
                        {
                            //std::cout<<tp<<std::endl;
                            expression r;
                            r.setstr(tp);
                            res.push_back(r.evaluate());
                            tp.clear();
                        }
                        else
                        {
                            tp+=t[j];
                        }
                    }
                    expression r;
                    r.setstr(tp);
                    res.push_back(r.evaluate());
                    tp.clear();
                    st.push(res);
                }
                else if(s[i]=='\"')
                {
                    string t="";i++;
                    for(;s[i]!='"';i++)
                    {
                        if(s[i]=='\\')
                        {
                            if(s[i+1]=='n')t+='\n',i++;
                            else if(s[i+1]=='t')t+='\t',i++;
                            else t+=s[++i];
                        }
                        
                        else t+=s[i];
                    }
                    st.push(t);
                }
                else
                {
                    string token="";
                    while((isalpha(s[i])||s[i]=='_'||(s[i]>='0'&&s[i]<='9'))&&i<(int)s.size())token+=s[i++];
                    while(delim(s[i]))i++;
                    if(s[i]=='(')
                    {
                        if(token=="input"){st.push(qread());i+=2;continue;}
                        i++;
                        auto m = func.lookup(token);
                        auto data = varTo< std::vector<string> > (m.value);
                        int b=1;
                        string t;
                        while(b&&i<s.size())
                        {
                            if(s[i]==')')b--;
                            else if(s[i]=='(')b++;
                            t+=s[i++];
                        }
                        
                        t.erase(t.size()-1,t.size());
                        string tp;int tot=0;
                        for(int j=0;j<t.size();j++)
                        {
                            if(t[j]==',')
                            {
                                expression r;
                                r.setstr(tp);
                                variable.set(data[tot++],r.evaluate());
                                r.evaluate();
                                tp.clear();
                            }
                            else
                            {
                                tp+=t[j];
                            }
                        }
                        
                        expression r;
                        r.setstr(tp);int k=0;
                        variable.set(data[tot++],r.evaluate());
                        tp.clear();string x=data[data.size()-1];
                        int qwe=1;
                        while(k<x.size())
                        {
                            string nexp;
                            while(x[k]!='\n'&&k<x.size())nexp+=x[k++];k++;
                            if(startwith(nexp,"return"))
                            {
                                string ret="";
                                for(int q=6;q<nexp.size();q++)ret+=nexp[q];
                                r.setstr(ret);
                                st.push(r.evaluate());
                                qwe=0;
                            }
                            else solve(nexp);
                        }
                        if(qwe)st.push(0);
                    }
                    else if(s[i]=='[')
                    {
                        result temp;i++;
                        temp=variable.lookup(token);
                        // if(temp.value.type()!=typeid(string)||
                        //     temp.value.type()!=typeid(std::vector<std::any>))
                        //     {result k={NULL,false};std::cout<<"Error: `[]`";return k;}
                        int b=1;
                        string t;
                        while(b&&i<s.size())
                        {
                            if(s[i]==']')b--;
                            else if(s[i]=='[')b++;
                            t+=s[i++];
                        }
                        t.erase(t.size()-1,t.size());
                        if(t.find(',')==-1)
                        {
                            expression r;
                            r.setstr(t);
                            if(s[i]=='='&&s[i+1]!='=')
                            {
                                result temp;i++;
                                temp=variable.lookup(token);
                                string subexp="";
                                while(i<(int)s.size())subexp+=s[i++];
                                expression x;
                                x.setstr(subexp);
                                if(temp.value.type()==typeid(string))
                                {
                                    string tp=std::any_cast<string>(temp.value);
                                    string sub=varTo<string>(x.evaluate());
                                    tp[int(toint(r.evaluate()).to_int64())]=sub[0];
                                    variable.set(token,tp);
                                    st.push(tp[int(toint(r.evaluate()).to_int64())]);
                                }
                                else if(temp.value.type()==typeid(std::vector<std::any>))
                                {
                                    std::vector<std::any> tp=std::any_cast< std::vector<std::any> >(temp.value);
                                    std::any sub=x.evaluate();
                                    tp[int(toint(r.evaluate()).to_int64())]=sub;
                                    variable.set(token,tp);
                                    st.push(sub);
                                }
                            }
                            else
                            if(temp.value.type()==typeid(string))
                            {
                                string tp=std::any_cast<string>(temp.value);
                                string sub="";sub+=tp[int(toint(r.evaluate()).to_int64())];
                                st.push(sub);
                            }
                            else if(temp.value.type()==typeid(std::vector<std::any>))
                            {
                                std::vector<std::any> tp=std::any_cast< std::vector<std::any> >(temp.value);
                                std::any sub=tp[int(toint(r.evaluate()).to_int64())];
                                st.push(sub);
                            }
                            
                        }
                    }
                    else if(s[i]=='='&&s[i+1]!='=')
                    {
                        result temp;i++;
                        temp=variable.lookup(token);
                        string subexp="";
                        while(i<(int)s.size())subexp+=s[i++];
                        expression r;
                        r.setstr(subexp);
                        variable.set(token,r.evaluate());
                        st.push(r.evaluate());
                    }
                    else
                    {
                        result temp;
                        temp=variable.lookup(token);
                        if(!temp.isok)
                        {
                            result k={NULL,false};
                            std::cout<<"Error: the '"<<token<<"' was not decleared in this scope.";
                            return k;
                        }
                        st.push(temp.value);
                    }
                    may_be_unary = false;
                    i--;
                }
            }

            while (!op.empty()) 
            {
                process_op(st, op.top().first,op.top().second);
                op.pop();
            }
            return st.top();
        }
    };
    
}

int debug()
{
	std::string str;
    COLOR_PRINT("shimmer alpha v0.1.0\ncreate by FBIWZH.\n",11);
    COLOR_PRINT(">>>",14);
    while(std::getline(std::cin,str))
    {
        std::any a=shimmer::solve(str);
        if(a.type()==typeid(shimmer::result))break;
        COLOR_PRINT("\n>>>",14);
    }
	return 0;
}