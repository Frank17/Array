//
//  Sequence.hpp
//  Array
//
//  Created by 邹智鹏 on 16/7/3.
//  Copyright © 2016年 Frank. All rights reserved.
//

#ifndef Sequence_hpp
#define Sequence_hpp

#include <stdio.h>
#include "Iterator.hpp"

namespace ZTemplate {
    
    typedef unsigned int z_size;    // 用于表示大小，为无符号整形
    typedef long rank;              // 用于表示秩
    template<class T>
    class Sequence {
    public:
        /**
         * 定义函数指针，用于表示两个值的比较, 若两个值相等，返回0，若val1 > val2 返回1, 否则返回-1
         */
        typedef int (*__FUNC_COMPARE_)(const T &val1, const T &val2);
        /**
         * 插入到最后一个位置
         */
        virtual void push_back(const T& val) = 0;
        /**
         * 从指定位置中，移除元素，并返回该元素的副本，若为指针，请自行进行内存管理
         * @param pos 元素位置
         * @return 返回该元素值
         */
        virtual T pop(const rank pos) = 0;
        /**
         * 访问指定位置的值
         * @param pos 元素所在的位置
         * @return 返回该位置的元素值
         */
        virtual const T &at(const rank pos) const = 0;
        /**
         * 移除指定位置元素
         * @param pos 元素所在位置
         * @return 返回是否移除成功
         */
        virtual bool remove(const rank pos) = 0;
        /**
         * 根据指定值，在序列中进行查找，若查找到符合条件的则进行移除
         */
        virtual bool remove(T &val1, __FUNC_COMPARE_ compare);
        
        /**
         * 获取迭代器
         * @return 返回迭代器
         */
        virtual Iterator<T> &iterator() = 0;
        /**
         * 重载访问器
         * @param pos 元素位置
         * @return 返回元素引用
         */
        virtual T& operator[](const rank pos) = 0;
    protected:
    };
}

template<class T>
bool ZTemplate::Sequence<T>::remove(T &val1, __FUNC_COMPARE_ compare) {
    Iterator<T> &curIterator = iterator();  // 获取到迭代器实例
    bool found = false;
    rank i = 0; // 秩
    while (!found && curIterator.hasNext()) {
        if (compare(val1, curIterator.data()) == 0) {
            // 两者值相等
            found = true;
            break;
        }
        i++;
        curIterator = curIterator.next();
    }
    return remove(i);// 移除指定位置
    
}

#endif /* Sequence_hpp */