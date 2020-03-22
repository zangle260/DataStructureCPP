#pragma once 

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

    bool bubble(Rank lo, Rank hi);
    void bubbleSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi);
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

    int disordered() const;

    Rank find(T const& e) const
    {
        return find(e, 0, (Rank)_size);
    }

    Rank find(T const& e, Rank lo, Rank hi) const
    {
        while ((lo < hi--) && (_elem[hi] != e))
        {
            //
        }

        return hi;
    }

    Rank search(T const& e) const
    {
        return (0 >= _size) ? -1 : search(e, (Rank)0, (Rank)_size);
    }

    Rank search(T const* e, Rank lo, Rank hi) const;

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

    T remove(Rank r);
    int remove(Rank lo, Rank hi);
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
    void sort(Rank lo, Rank hi);
    void sort() { sort(0, _size); }

    void unsort(Rank lo, Rank hi)
    {
        T* V = _elem + lo;
        for (Rank i = hi - lo; i > 0; i--)
        {
            swap(V[i - 1], V[rand() % i]);
        }
    }

    void unsort() { unsort(0, _size); }
    int deduplicate();
    int uniquify();
    void traverse(void(*)(T&));
    template<typename VST>
    void traverse(VST&);
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
