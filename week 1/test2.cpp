#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int b = 20;
    
    cout << "有换行符的输出:" << endl;
    cout << a << " " << b << endl;  // 使用 endl（相当于 \n）
    cout << "这是下一行内容" << endl;
    
    cout << "\n没有换行符的输出:" << endl;
    cout << a << " " << b;          // 不使用换行符
    cout << "这是下一行内容";
    
    return 0;
}
