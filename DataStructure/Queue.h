#pragma once 

#include "List.h" //��ListΪ����
template <typename T> class Queue : public List<T> { //����ģ���ࣨ�̳�Listԭ�нӿڣ�
public: //size()�� empty()�Լ��������Žӿھ���ֱ������
    void enqueue(T const& e) { insertAsLast(e); } //��ӣ�β���I��
    T dequeue() { return remove(first()); } //���ӣ��ײ�����
    T& front() { return first()->data; } //����    
};