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

bool rating(char current, char top) {
    map<char, int> precedence = {{'-', 1}, {'+', 1}, {'/', 2}, {'*', 2}, {'!', 3}, {'^',3}};
    int c1 = precedence[current];
    int c2 = precedence[top];
    if (c1 < c2)
        return false;
    return true;
}

bool isopperator(char c) {
    set<char> a = {'+', '-', '*','^', '!', '/'};
    if (a.find(c) != a.end())
        return true;
    return false;
}

int factorial(int num){
    int ans=1;
    for(int i=2;i<=num;i++){
        ans*=i;
    }
    return ans;
}

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
        else if(isopperator(current))
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

float calculate(stack postfix){
    stack result;
    int counter=0;
    while(!postfix.isEmpty()){
        float top=postfix.pop();
        if(isopperator(top)){
            float a=result.pop();
            float b;
            if(top!='!')
                b=result.pop();

            if(top=='^'){
                result.push(pow(b,a));
            }
            else if(top=='+'){
                result.push(b+a);
            }
            else if(top=='-'){
                result.push(b-a);
            }
            else if(top=='/'){
                result.push(b/a);
            }
            else if(top=='*'){
                result.push(b*a);
            }
            else if(top=='!'){
                result.push(factorial(a));
            }
            if(postfix.top()=='-') {
                counter++;
                postfix.pop();
            }
        }
        else{
            result.push(top);
        }
    }
    if(counter%2==0)
        return result.top();
    return result.top()*(-1);
}
int main() {
    string expression;
    cout << "Enter a postfix expression: ";
    getline(cin, expression);
    vector<char> expre(expression.begin(), expression.end());
    stack postfixStack = converttopostfix(expre);
    if(postfixStack.isEmpty())
    {
        main();
    }
    float result = calculate(postfixStack);
    cout << "Result: " << result << endl;
    return 0;
}