//
//  Iterator.hpp
//  Array
//
//  Created by 邹智鹏 on 16/7/3.
//  Copyright © 2016年 Frank. All rights reserved.
//

#ifndef Iterator_hpp
#define Iterator_hpp

#include <stdio.h>

namespace ZTemplate {
    template<class T>
    class Iterator {
    public:
        /**
         * 默认构造函数
         */
        Iterator<T>(){}
        
        /**
         * 下一个元素
         * @return 返回下一个迭代器
         */
        virtual Iterator<T> &next() = 0;
        
        /**
         * 获取迭代器值
         * @return 返回值
         */
        virtual const T data() const = 0;
        
        /**
         * 是否含有下一个元素
         * @return 返回是否有后续元素
         */
        virtual bool hasNext() const = 0;
        
        /**
         * 重载++
         */
        virtual Iterator<T>& operator++() = 0;
        virtual Iterator<T>& operator++(int) = 0;
        
        /**
         * 虚析构函数
         */
        virtual ~Iterator<T>(){}
    };
}

#endif /* Iterator_hpp */