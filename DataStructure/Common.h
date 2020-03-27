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


class Fib { //Fibonacci数列类
private:
    int f, g; //f = fib(k - 1), g = fib(k)。均为int型，很快就会数值溢出
public:
    Fib(int n) //初始化为不小于n的最小Fibonacci项
    {
        f = 1; g = 0; while (g < n) next();
    } //fib(-1), fib(0)，O(log_phi(n))时间
    int get() { return g; } //获取当前Fibonacci项，O(1)时间
    int next() { g += f; f = g - f; return g; } //转至下一Fibonacci项，O(1)时间
    int prev() { f = g - f; g -= f; return g; } //转至上一Fibonacci项，O(1)时间
};