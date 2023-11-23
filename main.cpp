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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
