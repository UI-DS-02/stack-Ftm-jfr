#include <iostream>
#include <valarray>
#include <set>
#include <map>

using namespace std;

class Node {
public:
    float data;
    Node* pre;

    explicit Node(float d) {
        data = d;
        pre = nullptr;
    }
};

class Stack {
protected:
    int Size;
    Node* Top;

public:
    Stack() {
        Size = 0;
        Top = nullptr;
    }
    virtual void push(float data) = 0;
    virtual float top() = 0;
    virtual float pop() = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};
void errorhandeling() {
    cout<<"wrong input\n";
}
class stack : public Stack {
public:
    void push(float data) override {
        Node* temp=new Node(data);
        temp->pre=Top;
        Top=temp;
        Size++;
    }

    float top() override {
        if(Top)
            return Top->data;
    }



    float pop() override {
        Node* temp=Top;

        Top=Top->pre;
        float d=temp->data;
        delete temp;
        Size--;
        return d;
    }

    int size() override {
        return Size;
    }

    bool isEmpty() override {
        if(Size==0)
            return true;
        return false;
    }
};
stack converttopostfix(vector<char> expresion){
    stack s;
    stack postfix;
    stack postfixx;
    int pcounter[2]={0,0};
    for(int i=0;i<expresion.size();i++){
        float current = expresion[i];

        if(current == '(')
        {
            pcounter[0]++;
            s.push('(') ;
        }
        else if(current == ')')
        {
            pcounter[1]++;
            while (s.top()!='('&&!s.isEmpty()){
                postfix.push(s.pop());
            }
            if(s.isEmpty())
            {
                errorhandeling();
                return postfixx;
            }
            s.pop();
        }
        else if(current=='-' && isdigit(expresion[i+1]))
        {
            string f="-";
            f=current;
            i++;
            while(isdigit(expresion[i])||expresion[i]=='.')
            {

                f+=expresion[i];
                i++;
            }
            i--;
            if(f.length()>1) {
                float tem = stof(f);
                postfix.push(tem);
            }
            else{
                postfix.push((current)-48*(-1));
            }
        }
        else if(isopperan(current))
        {
            if(rating(current,s.top())){
                s.push(current);
            } else{
                while(!s.isEmpty() && !rating(current,s.top())){
                    postfix.push(s.pop());
                }
                s.push(current);
            }
        }
        else
        {
            string f;
            f=current;
            i++;
            while(isdigit(expresion[i])||expresion[i]=='.')
            {

                f+=expresion[i];
                i++;
            }
            i--;
            if(f.length()>1) {
                float tem = stof(f);
                postfix.push(tem);
            }
            else{
                postfix.push(current-48);
            }
        }
    }

    if(pcounter[0]!=pcounter[1]) {
        errorhandeling();
        return postfixx;
    }

    while(!s.isEmpty()){
        postfix.push(s.pop());
    }


    for(int i=postfix.size()-1;i>=0;i--){
        postfixx.push(postfix.pop());
    }
    return postfixx;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
