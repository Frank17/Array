//
//  ZLinkedList.hpp
//  Array
//
//  Created by 邹智鹏 on 16/7/3.
//  Copyright © 2016年 Frank. All rights reserved.
//

#ifndef ZLinkedList_hpp
#define ZLinkedList_hpp

#include <stdio.h>
#include <list>
#include "Sequence.hpp"
#include "Iterator.hpp"

namespace ZTemplate {
    /**
     * 链表节点类
     */
    template<class T>
    class ZLinkedListNode {
    public:
        /**
         * 默认构造函数，需要目的类型提供默认构造函数å
         */
        ZLinkedListNode<T>(){_nextNode = nullptr;}
        /**
         * 构造函数，用于构造一个链表节点，并为其制定一个节点值
         * @param data 要赋予的节点的值
         */
        ZLinkedListNode<T>(const T &data);
        /**
         * 构建指定前驱的链表节点
         * @param data 要指定节点的值
         * @param preNode 要指定的上一个节点
         */
        ZLinkedListNode<T>(const T &data, ZLinkedListNode &preNode);
        /**
         * 获取节点值
         * @return 返回该节点值的副本，为保证安全，应该相应的数据类型重载赋值和拷贝构造
         */
        const T data() const{return _data;}
        /**
         * 引用该节点的值
         * @return 返回节点值的引用
         */
        T &ref() {return _data;}
        
        /**
         * 获取下一个节点
         * @return 返回下一个节点
         */
        ZLinkedListNode<T> *nextNode(){return _nextNode;}
        
        /**
         * 下一个节点的引用
         * @return 返回下一个节点指针的引用
         */
        ZLinkedListNode<T> *&nextNodeRef(){return _nextNode;}
        
        /**
         * 设置下一个节点
         * @param nextNode 要设置的下一个节点
         */
        void setNextNode(ZLinkedListNode<T> *nextNode);
    protected:
        T _data;// 节点数据
        ZLinkedListNode<T> *_nextNode; // 下一个节点
    };
    
    /*以下为Node的实现*/
    template<class T>
    ZLinkedListNode<T>::ZLinkedListNode(const T &data) {
        _data = data;
        _nextNode = nullptr;
    }
    
    template<class T>
    ZLinkedListNode<T>::ZLinkedListNode(const T &data, ZLinkedListNode &preNode) {
        _data = data;
        // 连接节点
        preNode._nextNode = this;
        _nextNode = nullptr;
    }
    
    template<class T>
    void ZLinkedListNode<T>::setNextNode(ZLinkedListNode<T> *nextNode) {
        _nextNode = nextNode;
    }
    
    template<class T>
    class ZLinkedListIterator;
    
    /**
     * 链表类
     */
    template<class T>
    class ZLinkedList : public Sequence<T> {
    public:
        /**
         * 默认构造函数，为节省空间，不设置哨兵节点
         */
        ZLinkedList<T>();
        
        /**
         * 根据指定值创建链表，该值为链表头部
         * @param data 要指定的头部值
         */
        ZLinkedList<T>(const T& data);
        
        /**
         * 创建指定值的指定个数的链表
         * @param data 指定值
         * @param count 指定值的个数
         */
        ZLinkedList<T>(const T& data, z_size count);
        
        /**
         * 插入到最后一个位置
         */
        virtual void push_back(const T& val);
        /**
         * 从指定位置中，移除元素，并返回该元素的副本，若为指针，请自行进行内存管理
         * @param pos 元素位置
         * @return 返回该元素值
         */
        virtual T pop(const rank pos);
        /**
         * 访问指定位置的值
         * @param pos 元素所在的位置
         * @return 返回该位置的元素值
         */
        virtual const T &at(const rank pos) const;
        /**
         * 移除指定位置元素
         * @param pos 元素所在位置
         * @return 返回是否移除成功
         */
        virtual bool remove(const rank pos);
        
        /**
         * 获取迭代器
         * @return 返回迭代器
         */
        virtual Iterator<T> &iterator();
        /**
         * 重载访问器
         * @param pos 元素位置
         * @return 返回元素引用
         */
        virtual T& operator[](const rank pos);
        
        /**
         * 判断是否为空表
         */
        bool isEmpty() const;
        
        virtual ~ZLinkedList();
        
        z_size length() const{return _length;}
        
        //声明友元关系
        friend class ZLinkedListIterator<T>;
        
    protected:
        ZLinkedListNode<T> *_list_head; // 链表头结点
        ZLinkedListNode<T> *_list_tail; // 链表尾节点，冗余数据，为了加快尾插法的效率
        z_size _length;                 // 长度
        Iterator<T> *preIterator;       // 上一个迭代器，用于迭代器的释放
    };
    
    /**链表迭代器类*/
    template<class T>
    class ZLinkedListIterator : public Iterator<T>{
    public:
        /**
         * 构造函数
         */
        ZLinkedListIterator<T>(ZLinkedList<T> &list);
        /**
         * 下一个元素
         * @return 返回下一个迭代器
         */
        virtual Iterator<T> &next();
        
        /**
         * 获取迭代器值
         * @return 返回值
         */
        virtual const T data() const;
        
        /**
         * 是否含有下一个元素
         * @return 返回是否有后续元素
         */
        virtual bool hasNext() const;
        
        /**
         * 重载++
         */
        virtual Iterator<T>& operator++();
        virtual Iterator<T>& operator++(int);
        virtual ~ZLinkedListIterator<T>(){_list = nullptr;pointTo = nullptr;}
    protected:
        ZLinkedList<T> *_list;      // 迭代器绑定的表
        ZLinkedListNode<T> *pointTo;               // 当前游标
    };
    
    /* 迭代器的实现部分
     */
    template<class T>
    ZLinkedListIterator<T>::ZLinkedListIterator(ZLinkedList<T> &list) {
        _list = &list;
        pointTo = list._list_head;
    }
    
    template<class T>
    Iterator<T>& ZLinkedListIterator<T>::next() {
        pointTo = pointTo->nextNode();
        return *this;
    }
    
    template<class T>
    const T ZLinkedListIterator<T>::data() const{
        return pointTo->data();
    }
    
    template<class T>
    bool ZLinkedListIterator<T>::hasNext() const{
        return nullptr != pointTo;
    }
    
    template<class T>
    Iterator<T> & ZLinkedListIterator<T>::operator++() {
        next();
        return *this;
    }
    
    template<class T>
    Iterator<T> & ZLinkedListIterator<T>::operator++(int i) {
        Iterator<T> & tempIt = *(new ZLinkedListIterator<T>(*this));
        next();
        return tempIt;
    }
}

/*
 链表的实现
 */
template<class T>
ZTemplate::ZLinkedList<T>::ZLinkedList():Sequence<T>() {
    _list_head = nullptr;
    _length = 0;
    _list_tail = nullptr;
    preIterator = nullptr;
}

template<class T>
ZTemplate::ZLinkedList<T>::ZLinkedList(const T &data):Sequence<T>() {
    _list_head = new ZTemplate::ZLinkedListNode<T>(data);
    _length = 1;
    preIterator = nullptr;
    _list_tail = _list_head;
}

template<class T>
ZTemplate::ZLinkedList<T>::ZLinkedList(const T &data, ZTemplate::z_size count):Sequence<T>() {
    _list_head = new ZTemplate::ZLinkedListNode<T>(data);
    _length = count;
    preIterator = nullptr;
    ZTemplate::ZLinkedListNode<T> *curNode = _list_head; // 用于拼接节点
    for (int i = 0; i < count - 1; i++) {
        ZTemplate::ZLinkedListNode<T> *newNode = new ZTemplate::ZLinkedListNode<T>(data, *curNode); // 在构建时，直接追加至末尾
        curNode = newNode;
    }
    _list_tail = curNode;
}
template<class T>
void ZTemplate::ZLinkedList<T>::push_back(const T &val) {
    // 创建节点，直接插入尾部
    ++_length;
    if (_list_head == nullptr) { // 头为空
        _list_head = _list_tail = new ZLinkedListNode<T>(val);
    }else {
        _list_tail = new ZTemplate::ZLinkedListNode<T>(val, *_list_tail);
    }
}

template<class T>
T ZTemplate::ZLinkedList<T>::pop(const rank pos) {
    // 节点游标
    ZTemplate::ZLinkedListNode<T> *nodePointer = _list_head;
    for (int i = 0; i < pos; i++) {
        nodePointer = nodePointer->nextNode();
    }
    return nodePointer->data();
}

template<class T>
const T& ZTemplate::ZLinkedList<T>::at(const rank pos) const{
    // 节点游标
    ZTemplate::ZLinkedListNode<T> *nodePointer = _list_head;
    for (int i = 0; i < pos; i++) {
        nodePointer = nodePointer->nextNode();
    }
    return nodePointer->ref();
}

template<class T>
bool ZTemplate::ZLinkedList<T>::remove(const rank pos) {
    if (pos >= _length) {
        return false;
    }
    --_length;
    // 头结点删除
    if (0 == pos) {
        ZTemplate::ZLinkedListNode<T> *delNode = _list_head;
        _list_head = _list_head->nextNode();
        delete delNode;
        return true;
    }
    // 节点游标
    ZTemplate::ZLinkedListNode<T> *nodePointer = _list_head;
    for (int i = 0; i < pos - 1; i++) { // 遍历至pos之前的一个节点
        nodePointer = nodePointer->nextNode();
    }
    ZTemplate::ZLinkedListNode<T> *delNode = nodePointer->nextNode();// 待删除的节点
    nodePointer->setNextNode(nodePointer->nextNode()->nextNode());
    delete delNode;
    return true;
}

template<class T>
ZTemplate::Iterator<T> &ZTemplate::ZLinkedList<T>::iterator() {
    if (nullptr != preIterator) {
        delete preIterator;
    }
    Iterator<T> *_iterator = new ZTemplate::ZLinkedListIterator<T>(*this);
    preIterator = _iterator;
    return *_iterator;
}

template<class T>
T & ZTemplate::ZLinkedList<T>::operator[](const rank pos) {
    ZTemplate::ZLinkedListNode<T> *nodePointer = _list_head;
    for (int i = 0; i < pos; i++) {
        nodePointer = nodePointer->nextNode();
    }
    return nodePointer->ref();
}

template<class T>
bool ZTemplate::ZLinkedList<T>::isEmpty() const {
    return _length <= 0;
}

template<class T>
ZTemplate::ZLinkedList<T>::~ZLinkedList<T>() {
    while (!isEmpty()) {
        remove(0);
    }
}

#endif /* ZLinkedList_hpp */