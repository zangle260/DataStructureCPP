#pragma once 

typedef int Rank; 

#define ListNodePosi(T) ListNode<T>* 

template <typename T>
struct ListNode
{
    T data; 
    ListNodePosi(T) pred; 
    ListNodePosi(T) succ; 

    ListNode() {} 
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL): data(e), pred(p), succ(s){}

    ListNodePosi(T) insertAsPred(T const& e)
    {
        ListNodePosi(T) x = new ListNode(e, pred, this); 
        pred->succ = x; 
        pred = x; 
        return x; 
    }

    ListNodePosi(T) insertAsSucc(T const& e)
    {
        ListNodePosi(T) x = new ListNode(e, this, succ); 
        succ->pred = x; 
        succ = x; 

        return x; 
    }
};


template<typename T>
class List
{
private:
    int _size; 
    ListNodePosi(T) header; 
    ListNodePosi(T) trailer; 
protected:
    void init() 
    {
        header = new ListNode<T>;
        trailer = new ListNode<T>;
        header->succ = trailer; header->pred = NULL;
        trailer->pred = header; trailer->succ = NULL;
        _size = 0;
    }
    int clear()
    {
        int oldSize = _size;
        while (0 < _size) 
            remove(header->succ); 
        return oldSize;
    }

    void copyNodes(ListNodePosi(T) p, int n)
    {
        init();
        while (n--)
        {
            insertAsLast(p->data);
            p = p->succ; 
        }
    }
    void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
    {
        ListNodePosi(T) pp = p->pred;
        while (0 < m)
            if ((0 < n) && (p->data <= q->data))
            {
                if (q == (p = p->succ)) break; n--;
            }
            else
            {
                insertBefore(p, L.remove((q = q->succ)->pred)); m--;
            }
        p = pp->succ;
    }

    void mergeSort(ListNodePosi(T)& p, int n)
    {
        if (n < 2) return; 
        int m = n >> 1; 
        ListNodePosi(T) q = p; 
        for (int i = 0; i < m; i++) 
            q = q->succ;
        mergeSort(p, m); mergeSort(q, n - m);
        merge(p, m, *this, q, n - m);
    }

    void selectionSort(ListNodePosi(T) p, int n)
    {
        ListNodePosi(T) head = p->pred;
        ListNodePosi(T) tail = p; 
        for (int i = 0; i < n; i++)
        {
            tail = tail->succ; 
        }

        while (1 < n)
        {
            ListNodePosi(T) max = selectMax(head->succ, n);
            insertBefore(tail, remove(max)); 
            tail = tail->pred; 
            n--; 
        }
    }
     
    void insertionSort(ListNodePosi(T) p, int n)
    {
        for (int r = 0; r < n; r++)
        {
            insertAfter(search(p->data, r, p), p->data);
            p = p->succ; 
            remove(p->pred);
        }
    }
public:
    List() 
    { 
        init(); 
    }

    List(List<T> const& L)
    {
        copyNodes(L.first(), L._size);
    }

    List(List<T> const& L, Rank r, int n)
    {
        copyNodes(L[r], n);
    }

    List(ListNodePosi(T) p, int n)
    {
        copyNodes(p, n);
    }

    ~List() 
    {
        clear(); 
        delete header; 
        delete trailer; 
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

    T& operator[](Rank r) const
    {
        ListNodePosi(T) p = first(); 
        while (0 < r--)
            p = p->succ; 
        return p->data; 
    }

    ListNodePosi(T) first() const
    {
        return header->succ; 
    }

    ListNodePosi(T) last() const
    {
        return header->pred; 
    }

    bool valid(ListNodePosi(T) p)
    {
        return p && (trailer != p);
    }

    int disordered();

    ListNodePosi(T) find(T const& e) const
    {
        return find(e, _size, trailer); 
    }


    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const
    {
        while (0 < n--)
        {
            if(e == ((p=p->pred)->data))
                return p; 
        }
        return nullptr; 
    }

    ListNodePosi(T) search(T const& e) const
    {
        return search(e, _size, trailer); 
    }

    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const
    {
        //assert(0 <= n && n <= rank(p));
        
        while (0 <= n--)
        {
            if (((p = p->pred)->data) <= e)
                break; 
        }

        return p; 
    }


    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n)
    {
        ListNodePosi(T) max = p; 
        for (ListNodePosi(T) cur = p; 1 < n; n--)
        {
            if(!lt((cur = cur->succ)->data, max->data))
            {
                max = cur; 
                return max; 
            }
        }
    }

    ListNodePosi(T) selectMax()
    {
        return selectMax(header->succ, _size);
    }

public:
    ListNodePosi(T) insertAsFirst(T const& e)
    {
        _size++; 
        return header->insertAsSucc(e);
    }

    ListNodePosi(T) insertAsLast(T const& e)
    {
        _size++; 
        return trailer->insertAsPred(e); 
    }

    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e)
    {
        _size++; 
        return p->insertAsPred(e); 
    }

    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e)
    {
        _size++; 
        return p->insertAsSucc(e);
    }

    T remove(ListNodePosi(T) p)
    {
        T e = p->data;
        p->pred->succ = p->succ; p->succ->pred = p->pred;
        delete p; 
        _size--; 
        return e;
    }
    void merge(List<T>& L)
    {
        merge(first(), size(), L, L.first(), L._size); 
    }

    void sort(ListNodePosi(T) p, int n)
    {
        switch (rand() % 3)
        {
        case 1:
            insertionSort(p, n); 
            break; 
        case 2:
            selectionSort(p, n);
            break;
        default:
            mergeSort(p, n);
            break;
        }
    }

    void sort()
    {
        sort(first(), _size); 
    }

    int deduplicate()
    {
        if (_size < 2)
            return 0; 

        int oldSize = _size; 

        ListNodePosi(T) p = header; 
        Rank r = 0; 

        while (trailer != (p = p->succ))
        {
            ListNodePosi(T) q = find(p->data, r, p);
            q ? remove(q) : r++;
        }

        return oldSize - _size;
    }
    int uniquify()
    {
        if (_size < 2)
            return 0; 

        int oldSize = _size;

        ListNodePosi(T) p; 
        ListNodePosi(T) q; 

        for (p = header, q = p->succ; trailer != q; p = q, q = q->succ)
        {
            if (p->data == q->data)
            {
                remove(q);
                q = p; 
            }
        }

        return oldSize - _size; 
    }

    void reverse(); 

    void traverse(void(*visit)(T&))
    {
        for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
        {
            visit(p->data);
        }
    }
    template<typename VST>
    void traverse(VST& vist)
    {
        for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
        {
            vist(p->data); 
        }
    }
};