#pragma once

__int64 fib(int n)
{
    return (2 > n) ? (__int64)n : fib(n - 1) + fib(n - 2); 
}

__int64 fib(int n, __int64& prev)
{
    if (0 == n)
    {
        prev = 1; 
        return 0; 
    }
    else
    {
        __int64 prevPrev; 
        prev = fib(n - 1, prevPrev); 
        return prev + prevPrev; 
    }
}

__int64 fibI(int n)
{
    __int64 f = 1, g = 0; 
    while (0 < n--)
    {
        f = f + g; 
        g = f - g; 
    }
    return g; 
}


class Fib { //Fibonacci������
private:
    int f, g; //f = fib(k - 1), g = fib(k)����Ϊint�ͣ��ܿ�ͻ���ֵ���
public:
    Fib(int n) //��ʼ��Ϊ��С��n����СFibonacci��
    {
        f = 1; g = 0; while (g < n) next();
    } //fib(-1), fib(0)��O(log_phi(n))ʱ��
    int get() { return g; } //��ȡ��ǰFibonacci�O(1)ʱ��
    int next() { g += f; f = g - f; return g; } //ת����һFibonacci�O(1)ʱ��
    int prev() { f = g - f; g -= f; return g; } //ת����һFibonacci�O(1)ʱ��
};