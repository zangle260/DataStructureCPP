#pragma once 

#include "Common.h"

typedef int Rank;
#define DEFAULT_CAPACITY 3

template<typename T>
class Vector
{
private:
    Rank _size;
    int _capacity;
    T* _elem;
protected:
    void copyFrom(T* const A, Rank lo, Rank hi)
    {
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;

        while (lo < hi)
        {
            _elem[_size++] = A[lo++];
        }
    }

    void expand()
    {
        if (_size < _capacity)
            return;

        if (_capacity < DEFAULT_CAPACITY)
            _capacity = DEFAULT_CAPACITY;

        T* oldElem = _elem;

        _elem = new T[_capacity <<= 1];

        for (int i = 0; i < _size; i++)
        {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }

    void shrink()
    {
        if (_capacity < DEFAULT_CAPACITY << 1)
            return;

        if (_size << 2 > _capacity)
            return;

        T* oldElem = _elem;

        _elem = new T[_capacity >>= 1];
        for (int i = 0; i < size; i++)
        {
            _elem[i] = oldElem[i];
        }

        delete[] oldElem;
    }

    bool bubble(Rank lo, Rank hi)
    {
        bool sorted = true;
        while (++lo < hi)
        {
            if (_elem[lo - 1] > _elem[lo])
            {
                sorted = false;
                std::swap(_elem[lo - 1], _elem[lo]);
            }
        }
        return sorted;
    }

    void bubbleSort(Rank lo, Rank hi)
    {
        while (!bubble(lo, hi--));
    }

    void merge(Rank lo, Rank mi, Rank hi) 
    {
        //合并后的向量A[0, hi-lo) = _elem[lo, hi) 
        T* A = _elem + lo; 

        //前子区间B[0, lb) = A[lo, mi) , 复制前子区间
        int lb = mi - lo; 
        T* B = new T[lb];
        for (Rank i = 0; i < lb; B[i] = A[i++]) {}

        //后子区间C[0, lc) = A[mi, hi)
        int lc = hi - mi;
        T* C = _elem + mi;

        Rank i = 0, j = 0, k = 0;
        while( (j < lb) && (k < lc))
        {
            while ((j < lb) && B[j] <= C[k])
                A[i++] = B[j++];
            while ((k < lc) && C[k] <= B[j])
                A[i++] = C[k++];
        }
        while (j < lb)
            A[i++] = B[j++];

        delete[] B;    
    }

    void mergeSort(Rank lo, Rank hi)
    {
        if (hi - lo < 2)
        {
            return; 
        }
        int mi = (hi + lo) >> 1; 

        mergeSort(lo, mi); 
        mergeSort(mi, hi); 
        merge(lo, mi, hi);
    }

    Rank partition(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);
public:
    Vector(int c = DEFAULT_CAPACITY)
    {
        _elem = new T[_capacity = c];
        _size = 0;
    }

    Vector(T* A, Rank lo, Rank hi)
    {
        copyFrom(A, lo, hi);
    }

    Vector(T* A, Rank n)
    {
        copyFrom(A, 0, n);
    }

    Vector(Vector<T> const& V, Rank lo, Rank hi)
    {
        copyFrom(V._elem, lo, hi);
    }

    Vector(Vector<T> const& V)
    {
        copyFrom(V._elem, 0, V._size);
    }

    ~Vector()
    {
        delete[] _elem;
    }
public:
    Rank size() const
    {
        return _size;
    }

    bool empty() const
    {
        return _size <= 0;
    }

    int disordered() const
    {
        int n = 0; 
        for (int i = 1; i < _size; i++)
        {
            if (_elem[i - 1] > _elem[i])
                n++; 
        }
        return n; 
    }

    Rank find(T const& e) const
    {
        return find(e, 0, (Rank)_size);
    }

    Rank find(T const& e, Rank lo, Rank hi) const
    {
        while ((lo < hi--) && (_elem[hi] != e))
        {}

        return hi;
    }

    Rank search(T const& e) const
    {
        return (0 >= _size) ? -1 : search(e, (Rank)0, (Rank)_size);
    }

    Rank search(T const* e, Rank lo, Rank hi) const
    {
        return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi); 
    }

    Rank fibSearch(T* A, T const& e, Rank lo, Rank hi)
    {
        Fib fib(hi - lo); 
        while (lo < hi)
        {
            while (hi - lo < fib.get())
            {
                fib.prev(); 
            }

            Rank mi = lo + fib.get() - 1;

            if (e < A[mi])
            {
                hi = mi;
            }
            else if (e > A[mi])
            {
                lo = mi + 1;
            }
            else
                return mi;
        }
        return -1;
    }

    Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
    {
        while (1 < hi - lo)
        {
            Rank mi = (lo + hi) >> 1; 
            (e < A[mi]) ? hi = mi : lo = mi; 
        }

        return (e == A[lo]) ? lo : -1; 
    }

    T& operator[](Rank r) const
    {
        return _elem[r];
    }

    Vector<T>& operator=(Vector<T> const& V)
    {
        if (_elem)
            delete[] _elem;
        copyFrom(V._elem, 0, V.size());
        return *this;
    }

    T remove(Rank r)
    {
        T e = _elem[r]; 
        remove(r, r + 1); 
        return e; 
    }
    int remove(Rank lo, Rank hi)
    {
        if (lo == hi)
            return 0; 
        while (hi < _size )
        {
            _elem[lo++] = _elem[hi++];
        }
        _size = lo; 
        shrink(); 
        return hi - lo;
    }
    Rank insert(Rank r, T const& e)
    {
        expand();
        for (int i = _size; i > r; i--)
        {
            _elem[i] = _elem[i - 1];
        }

        _elem[r] = e;
        _size++;

        return r;
    }

    Rank insert(T const& e) { return insert(_size, e); }
    void sort(Rank lo, Rank hi)
    {
        //switch (rand() % 4)
        //{
        //case 1: bubbleSort(lo, hi);
        //    break; 
        //case 2: mergeSort(lo, hi); 
        //    break; 
        //case 3: heapSort(lo, hi);
        //    break; 
        //default:
        //    quickSort(lo, hi);
        //    break; 
        //}
        bubbleSort(lo, hi); 
    }

    void sort() { sort(0, _size); }

    void unsort(Rank lo, Rank hi)
    {
        T* V = _elem + lo;
        for (Rank i = hi - lo; i > 0; i--)
        {
            swap(V[i - 1], V[rand() % i]);
        }
    }

    void unsort() 
    { 
        unsort(0, _size); 
    }

    int deduplicate()
    {
        int oldSize = _size; 
        Rank i = 1; 
        while (i < _size)
        {
            (0 > find(_elem[i], 0, i)) ? i++ : remove(i);
        }
        return oldSize - _size; 
    }

    int uniquify()
    {
        Rank i = 0, j = 0; 
        while (++j < _size)
        {
            if (_elem[i] != _elem[j])
                _elem[++j] = _elem[j]; 
        }
        _size = ++i; 
        shrink(); 
        return j - i; 
    }

    void traverse(void(*visit)(T&))
    {
        for (int i = 0; i < _size; i++)
        {
            visit(_elem[i]); 
        }
    }

    template<typename VST>
    void traverse(VST& visit)
    {
        for (int i = 0; i < _size; i++)
        {
            visit(_elem[i]);
        }
    }

    void permute(Vector<T>& V)
    {
        for (int i = V.size(); i > 0; i--)
        {
            swap(V[i - 1], V[rand() % i]);
        }
    }
};

template<typename T>
static bool lt(T* a, T* b)
{
    return *a < *b;
}

template<typename T>
static bool lt(T& a, T& b)
{
    return a < b;
}

template<typename T>
static bool eq(T* a, T* b)
{
    return *a == *b;
}

template<typename T>
static bool eq(T& a, T& b)
{
    return a == b;
}

template<typename T> 
class VST
{
public:
    virtual void operator()(T& e) { e++; }
};

template<typename T>
void increase(Vector<T>& V)
{
    VST<T> v;
    V.traverse( v );
}

template<typename T>
void printElem(T& e)
{
    std::cout << e << " ";
}

template<typename T>
void print(Vector<T>& V)
{
    V.traverse(printElem);
    std::cout << std::endl; 
}




