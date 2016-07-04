//
//  ZStack.hpp
//  Array
//
//  Created by 邹智鹏 on 16/7/4.
//  Copyright © 2016年 Frank. All rights reserved.
//

#ifndef ZStack_hpp
#define ZStack_hpp

#include <stdio.h>
#include "ZLinkedList.hpp"

namespace ZTemplate {
    template<class T>
    class ZStack : protected ZLinkedList<T> {
    public:
        ZStack<T>();
        /**
         * 压栈
         */
        void push(T val);
        
        /**
         * 出栈
         */
        T popup();
        
        /**
         * 虚析构
         */
        virtual ~ZStack(){}
        
        /**
         * 是否空栈
         */
        bool empty() const;
        
        /**
         * 获取栈中元素个数
         * @return 返回个数
         */
        z_size count() const;
    };
    
    template<class T>
    ZStack<T>::ZStack() : ZLinkedList<T>(){
        
    }
    
    template<class T>
    void ZStack<T>::push(T val) {
        this->push_back(val);
    }
    
    template<class T>
    T ZStack<T>::popup() {
        return this->pop(this->_length - 1);
    }
    
    template<class T>
    bool ZStack<T>::empty() const {
        return this->isEmpty();
    }
    
    template<class T>
    z_size ZStack<T>::count() const {
        return this->_length;
    }
}

#endif /* ZStack_hpp */
