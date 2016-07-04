//
//  Array.hpp
//  Array
//
//  Created by 邹智鹏 on 16/7/3.
//  Copyright © 2016年 Frank. All rights reserved.
//

#ifndef Array_hpp
#define Array_hpp

#include <stdio.h>
#include <cstring>
#include "Sequence.hpp"

namespace ZTemplate {
    template<class T>
    class ZArrayIterator;
    template<class T>
    class ZArray : public Sequence<T>{
    public:
        /**
         * 默认构造
         */
        ZArray<T>();
        /**
         * 根据容量构造向量
         * @param capacity 容量
         */
        ZArray<T>(z_size capacity);
        /**
         * 插入到最后一个位置
         */
        virtual void push_back(const T &val);
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
         * 返回长度信息
         * @return 返回数组的有效长度
         */
        z_size length()const{return _length;}
        
        /**
         * 重载访问器
         * @param pos 元素位置
         * @return 返回元素引用
         */
        T& operator[](const rank pos);
        
        /**
         * 析构函数
         */
        ~ZArray<T>();
        friend class ZArrayIterator<T>;
    protected:
        T *_array; // 实际存储空间
        z_size _length; // 数组长度
        z_size capacity; // 最大容量
        Iterator<T> *_iterator; // 迭代器
        /**
         * 缩容
         */
        T *shink();
        /**
         * 扩容
         */
        T *expand();
    };
    /**迭代器类*/
    template<class T1>
    class ZArrayIterator : public Iterator<T1> {
    protected:
        rank pointTo;// 当前游标
        ZArray<T1> *_array;
    public:
        
        /**
         * 构造函数
         * @param array 用于遍历数组
         */
        ZArrayIterator<T1>(ZArray<T1> &arr):Iterator<T1>(){this->_array = &arr;}
        /**
         * 下一个元素
         * @return 返回下一个迭代器
         */
        virtual Iterator<T1> &next();
        
        /**
         * 获取迭代器值
         * @return 返回值
         */
        virtual const T1 data() const;
        
        /**
         * 是否含有下一个元素
         * @return 返回是否有后续元素
         */
        virtual bool hasNext();
        /**
         * 重置前置++
         */
        virtual Iterator<T1>& operator++();
        /**
         * 重载后置++
         */
        virtual Iterator<T1>& operator++(int);
    };
}
template<class T>
ZTemplate::ZArray<T>::ZArray():Sequence<T>() {
    static z_size size = 5;
    _array = new T[size];
    capacity = size;
    _length = 0;
    _iterator = new ZArrayIterator<T>(*this);
}

template<class T>
ZTemplate::ZArray<T>::ZArray(z_size capacity) {
    _array = new T[capacity];
    this->capacity = capacity;
    _length = 0;
    _iterator = new ZArrayIterator<T>(*this);
}

template<class T>
void ZTemplate::ZArray<T>::push_back(const T &val) {
    if (_length == capacity) {
        _array = expand();
    }
    _array[_length] = val;
    _length++;
}

template<class T>
T ZTemplate::ZArray<T>::pop(const rank pos) {
    T val =  _array[pos]; // 要返回的值
    remove(pos);
    return val;
}

template<class T>
const T& ZTemplate::ZArray<T>::at(const rank pos) const{
    return _array[pos];
}

template<class T>
bool ZTemplate::ZArray<T>::remove(const rank pos) {
    if (pos >= _length) {
        return false;
    }
    for (rank i = pos; i < _length - 1; i++) {
        _array[i] = _array[i + 1];
    }
    _length--;
    return true;
}

template<class T>
T* ZTemplate::ZArray<T>::shink() {
    T *newLocate = new T[capacity >> 1];
    for (int i = 0; i < _length; i++) {
        newLocate[i] = _array[i];
    }
    delete _array;
    _array = newLocate;
    return newLocate;
}

template<class T>
T * ZTemplate::ZArray<T>::expand() {
    T *newLocate = new T[capacity << 1];
    for (int i = 0; i < _length; i++) {
        newLocate[i] = _array[i];
    }
    delete _array;
    _array = newLocate;
    return _array;
}

template<class T>
ZTemplate::ZArray<T>::~ZArray<T>() {
    delete _array;
    _array = nullptr;
    _length = 0;
    capacity = 0;
}

template<class T>
T & ZTemplate::ZArray<T>::operator[](const rank pos) {
    return _array[pos];
}


template<class T1>
ZTemplate::Iterator<T1>& ZTemplate::ZArrayIterator<T1>::next() {
    pointTo++;
    return *this;
}

template<class T1>
bool ZTemplate::ZArrayIterator<T1>::hasNext() {
    return pointTo < _array->length();
}

template<class T1>
const T1 ZTemplate::ZArrayIterator<T1>::data() const {
    return _array->_array[pointTo];
}

template<class T>
ZTemplate::Iterator<T> &ZTemplate::ZArray<T>::iterator() {
    return *(new ZArrayIterator<T>(*this));
}

template<class T1>
ZTemplate::Iterator<T1> &ZTemplate::ZArrayIterator<T1>::operator++() {
    next();
    return *this;
}

template<class T1>
ZTemplate::Iterator<T1> &ZTemplate::ZArrayIterator<T1>::operator++(int i) {
    ZTemplate::Iterator<T1> &it = *(new ZArrayIterator<T1>(*this));
    next();
    return it;
}

#endif /* Array_hpp */