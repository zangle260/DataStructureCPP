#pragma once 

#include <algorithm>

#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )

#define sibling(p) /*兄弟*/ \
   ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )

#define uncle(x) /*叔叔*/ \
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )

#define FromParentTo(x) /*来自父亲的引用*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1) 
typedef enum {RB_RED, RB_BLACK}  RBColor;  

template<typename T> 
struct BinNode
{
    T data; 
    BinNodePosi(T) parent;
    BinNodePosi(T) lc; 
    BinNodePosi(T) rc; 

    int height;
    int npl; 

    RBColor color; 

    BinNode(): parent(NULL), lc(NULL), rc(NULL), 
        height(0), npl(0), color(RB_RED)
    {}
   
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
        int h = 0, int l = 1, RBColor c = RB_RED):
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c)
    {}

    int size(); 

    BinNodePosi(T) insertAsLC(T const& e)
    {
        this->lc = new BinNode(e, this); 
        return this->lc; 
    }

    BinNodePosi(T) insertAsRC(T const& e)
    {
        this->rc = new BinNode(e, this); 
        return this->rc; 
    }

    BinNodePosi(T) succ(); 

    template<typename VST> 
    void travLevel(VST&);
    template<typename VST>
    void travPre(VST&);
    template<typename VST>
    void travIn(VST& visit)
    {
        switch (rand() % 5) { //此处暂随机选择以做测试，共五种选择
        case 1: travIn_I1(this, visit); break; //迭代版#1
        case 2: travIn_I2(this, visit); break; //迭代版#2
        case 3: travIn_I3(this, visit); break; //迭代版#3
        case 4: travIn_I4(this, visit); break; //迭代版#4
        default: travIn_R(this, visit); break; //递归版
        }
    }
    template<typename VST>
    void travPost(VST&);

    template<typename VST>
    void travIn_R(BinNodePosi(T) x, VST& vist)
    {

    }

    template<typename VST>
    void travIn_I1(BinNodePosi(T) x, VST& vist)
    {

    }

    template<typename VST>
    void travIn_I2(BinNodePosi(T) x, VST& vist)
    {

    }

    template<typename VST>
    void travIn_I3(BinNodePosi(T) x, VST& vist)
    {

    }

    template<typename VST>
    void travIn_I4(BinNodePosi(T) x, VST& vist)
    {

    }

    bool operator< (BinNode const& bn)
    {
        return (data < bn.data); 
    }

    bool operator== (const BinNode& bn)
    {
        return (data == bn.data);
    }

    BinNodePosi(T) zig(); 
    BinNodePosi(T) zag();
};

template <typename T>
class BinTree
{
protected:
    int _size; 
    BinNodePosi(T) _root; 

    virtual int updateHeight(BinNodePosi(T) x)
    {
        return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
    }
    void updateHeightAbove(BinNodePosi(T) x)
    {
        while (x) 
        { 
            updateHeight(x); 
            x = x->parent; 
        }
    }
public:
    BinTree() : _size(0), _root(nullptr) 
    {
    }

    ~BinTree() 
    { 
        if (0 < _size)
           remove(_root); 
    }

    int size() const
    {
        return _size; 
    }

    bool empty() const
    {
        return !_root; 
    }

    BinNodePosi(T) root() const
    {
        return _root;
    }

    BinNodePosi(T) insertAsRoot(T const& e)
    {
        _size = 1; 
        return _root = new BinNode<T>(e);
    }
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e)
    {
        _size++; 
        x->insertAsLC(e); 
        updateHeightAbove(x); 
        return x->lc;
    }
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e)
    {
        _size++; 
        x->insertAsRC(e); 
        updateHeightAbove(x); 
        return x->rc; 
    }

    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S)
    {
        if (x->lc = S->_root) 
            x->lc->parent = x; 
        _size += S->_size; 
        updateHeightAbove(x); 
        S->_root = NULL; 
        S->_size = 0; 
        release(S); 
        S = NULL; 
        return x; 
    }

    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S)
    {
        if (x->rc = S->_root)
            x->rc->parent = x; 
        _size += S->_size; 
        updateHeightAbove(x);
        S->_root = NULL; 
        S->_size = 0; 
        release(S); 
        S = NULL; 
        return x;
    }

    void release(T x)
    {
        //
    }

    void release(BinNodePosi(T) x)
    {
        if (x)
            delete x; 
    }

    int removeAt(BinNodePosi(T) x) 
    { 
        if (!x) return 0; 
        int n = 1 + removeAt(x->lc) + removeAt(x->rc); 
        release(x->data); 
        release(x); 
        return n;
    }

    int remove(BinNodePosi(T) x)
    {
        FromParentTo(*x) = NULL; 
        updateHeightAbove(x->parent);
        int n = removeAt(x); 
        _size -= n; 
        return n;         
    }

    template<typename VST>
    void travLevel(VST& visit)
    {
        if (_root)
            _root->travLevel(visit); 
    }

    template<typename VST>
    void travPre(VST& visit)
    {
        if (_root)
            _root->travPre(visit); 
    }

    template<typename VST>
    void travIn(VST& visit)
    {
        if (_root)
            _root->travIn(visit);
    }

    template<typename VST>
    void travPost(VST& visit)
    {
        if (_root)
            _root->travPost(visit); 
    }

    bool operator<(BinTree<T> const& t)
    {
        return _root && t._root && (_root < t.root); 
    }

    bool operator==(BinTree<T> const& t)
    {
        return _root && t._root && (_root == t._root);
    }

    template<typename VST>
    void travPre_R(BinNodePosi(T) x, VST& visit)
    {
        if (!x) 
            return;
        visit(x->data);
        travPre_R(x->lChild, visit);
        travPre_R(x->rChild, visit);
    }

    template<typename VST>
    void travPost_R(BinNodePosi(T) x, VST& visit)
    {
        if (!x) 
            return;
        travPost_R(x->lChild, visit);
        travPost_R(x->rChild, visit);
        visit(x->data);
    }

    template<typename VST>     
    void travIn_R(BinNodePosi(T) x, VST& visit)
    {
        if (!x) 
            return;
        travIn_R(x->lChild, visit);
        visit(x->data);
        travIn_R(x->rChild, visit);
    }
};
