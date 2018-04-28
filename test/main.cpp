#include <iostream>

class gameobj
{
protected:
    int a;
    int inc()
    {
        a++;
        return 0;
    }
public:
    virtual int iinc() = 0;
};

class bb : public gameobj
{
public:
    virtual int iinc() override
    {
        inc();
        a--;
        std::cout << a << "posadhf\n";
        return 0;
    }
};






#include <stdio.h>

class h
{
public:
    void my_int_func(int x)
    {
        printf( "%d\n", x );
    }
    void (h::*foo)(int) = &h::my_int_func;
};


int main()
{
//    void (*foo)(int);
    h H;
//    H.foo = &my_int_func;

    /* call my_int_func (note that you do not need to write (*foo)(2) ) */
    (H.*H.foo)( 2 );
    /* but if you want to, you may */
//    H.(*foo)( 2 );

    return 0;
}
