#include"include/list.h"

int main(void)
{
    List a;
    cout<<a.GetHead()<<endl;
    a.InserToHead(10);
    a.InserToHead(20);
    a.InserToTail(30);
    a.InserToTail(40);
    cout<<a<<endl;
    a.Clean();
    cout<<a.GetHead()<<endl;
    // cout<<a<<endl;
    // List b(a);
    // cout<<b<<endl;
    return 0;
}