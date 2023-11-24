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
    if (c1 <= c2)
        return false;
    return true;
}

bool isoperator(char c) {
    set<char> a = {'+', '-', '*','^', '!', '/'};
    if (a.find(c) != a.end())
        return true;
    return false;
}

void error_handling() {
    cout<<"Wrong Input\n";
}

int factorial(int num){
    int ans=1;
    for(int i=2;i<=num;i++){
        ans*=i;
    }
    return ans;
}

stack convert_to_postfix(string expresion){
    stack operatorStack;
    stack postfixStack;
    stack reversedPostfixStack;
    int parenthesesCounter[2]={0, 0};
    for(int i=0;i<expresion.size();i++){
        float current = expresion[i];

        if(current == '(')
        {
            parenthesesCounter[0]++;
            operatorStack.push('(') ;
        }
        else if(current == ')')
        {
            parenthesesCounter[1]++;
            while (operatorStack.top() != '(' && !operatorStack.isEmpty()){
                postfixStack.push(operatorStack.pop());
            }
            if(operatorStack.isEmpty())
            {
                error_handling();
                return reversedPostfixStack;
            }
            operatorStack.pop();
        }
        else if(current=='-' && isdigit(expresion[i+1]) && !isdigit(expresion[i-1]))
        {
            string number="-";
            number=current;
            i++;
            while(isdigit(expresion[i])||expresion[i]=='.')
            {

                number+=expresion[i];
                i++;
            }
            i--;
            if(number.length() > 1) {
                float tem = stof(number);
                postfixStack.push(tem);
            }
            else{
                postfixStack.push((current) - 48 * (-1));
            }
        }
        else if(isoperator(current))
        {
            if(isoperator(expresion[i + 1]) || (i + 1 == expresion.size() && expresion[i] != '!')) {
                error_handling();
                return reversedPostfixStack;
            }
            if(rating(current, operatorStack.top())){
                operatorStack.push(current);
            }
            else{
                while(!operatorStack.isEmpty() && !rating(current, operatorStack.top())){
                    postfixStack.push(operatorStack.pop());
                }
                operatorStack.push(current);
            }
        }
        else if(current == 'e' )
            postfixStack.push( 2.71828);

        else if(current == 'P' && expresion[i+1]=='I') {
            postfixStack.push(3.14);
            i++;
        }
        else
        {
            string number;
            number=current;
            i++;
            while(isdigit(expresion[i])||expresion[i]=='.')
            {

                number+=expresion[i];
                i++;
            }
            i--;
            if(number.length() > 1) {
                float tem = stof(number);
                postfixStack.push(tem);
            }
            else{
                postfixStack.push(current - 48);
            }
        }
    }

    if(parenthesesCounter[0] != parenthesesCounter[1]) {
        error_handling();
        return reversedPostfixStack;
    }

    while(!operatorStack.isEmpty()){
        postfixStack.push(operatorStack.pop());
    }

    for(int i= postfixStack.size() - 1; i >= 0; i--){
        reversedPostfixStack.push(postfixStack.pop());
    }
    return reversedPostfixStack;
}

float calculate(stack postfix){
    if(postfix.isEmpty())
        return 0.0;
    stack result;
    int counter=0;
    while(!postfix.isEmpty()){
        float top=postfix.pop();
        if(isoperator(top)){
            float a=result.pop();
            float b=0;
            if(top!='!' && !result.isEmpty())
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
            else if(postfix.top()=='-') {
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
    else
        return result.top()*(-1);
}

int main() {
    string expression;
    cout << "Enter a Intfix Expression: ";
    getline(cin, expression);
    stack postfixStack = convert_to_postfix(expression);
    if(!postfixStack.isEmpty())
    {
        float result = calculate(postfixStack);
        if(result==0.0)
            error_handling();
        else
            cout << "Result: " << result << endl;
    }
    main();
    return 0;
}