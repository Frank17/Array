//
//  ZQueue.hpp
//  Array
//
//  Created by 邹智鹏 on 16/7/4.
//  Copyright © 2016年 Frank. All rights reserved.
//

#ifndef ZQueue_hpp
#define ZQueue_hpp

#include "ZLinkedList.hpp"

#include <stdio.h>

namespace ZTemplate {
    template<class T>
    class ZQueue : protected ZLinkedList<T> {
    public:
        ZQueue<T>();
        virtual ~ZQueue<T>(){}
        
        /**
         * 入队
         * @param val 要入队的值
         */
        void enqueue(const T &val);
        
        /**
         * 出队
         */
        T dequeue();
        
        /**
         * 队列是否空
         * @return 返回是否空队列
         */
        bool empty() const;
        
        /**
         * 获取队列元素个数
         * @return 返回队列中元素个数
         */
        z_size count() const;
    };
    
    template<class T>
    ZQueue<T>::ZQueue() : ZLinkedList<T>() {
        
    }
    
    template<class T>
    void ZQueue<T>::enqueue(const T &val) {
        this->push_back(val);
    }
    
    template<class T>
    T ZQueue<T>::dequeue() {
        return this->pop(0);
    }
    
    template<class T>
    bool ZQueue<T>::empty() const {
        return this->isEmpty();
    }
    
    template<class T>
    z_size ZQueue<T>::count() const {
        return this->_length;
    }
}

#endif /* ZQueue_hpp */
