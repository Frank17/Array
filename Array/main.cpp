//
//  main.cpp
//  Array
//
//  Created by 邹智鹏 on 16/7/3.
//  Copyright © 2016年 Frank. All rights reserved.
//

#include <iostream>
#include "Array.hpp"
#include "Iterator.hpp"
#include "ZLinkedList.hpp"
#include "ZStack.hpp"
#include "ZQueue.hpp"
using namespace ZTemplate;

class Student {
public:
    Student(){name = "", age = 0;}
    Student(std::string n, int a){name = n, age = a;}
    Student(const Student &stu){name = stu.name, age = stu.age;}
    void display() const{std::cout << "name:" << name << ",age:" << age << std::endl;}
private:
    std::string name;
    int age;
};

int main(int argc, const char * argv[]) {
    
    
    std::cout << "===============array==============" << std::endl;
    ZArray<Student> *array = new ZArray<Student>;
    array->push_back(Student("zz", 19));
    array->push_back(Student("ee", 20));
    Iterator<Student> &it = array->iterator();
    while (it.hasNext()) {
        it.data().display();
        it++;// 在重载中，有使用next()方法，则测试该方法即可
    }
    std::cout << " length: " << array->length() << std::endl;
    array->at(0).display();
    array->pop(0).display();
    std::cout << "    after length:" << array->length() << std::endl; // 在pop中，有对remove的调用，则只覆盖该方法即可
    
    std::cout << "=================linkedlist==================" << std::endl;
    
    ZLinkedList<Student> list;
    std::cout << "start: " << list.length() << std::endl;
    
    list.push_back(Student("zz", 19));
    list.push_back(Student("ee", 20));
    list.push_back(Student("ff", 21));
    
    Iterator<Student> *iterator = &list.iterator();
    std::cout << "--------------------" << std::endl;
    while (iterator->hasNext()) {
        iterator->data().display();
        (*iterator)++;
    }
    
    list.remove(0);
    // 注意对于迭代器而言，只要remove后，迭代器失效，需要重置
    
    std::cout << "--------------------" << std::endl;
    iterator = &list.iterator();
    while (iterator->hasNext()) {
        iterator->data().display();
        (*iterator)++;
    }
    std::cout << "--------------------" << std::endl;
    
    ZStack<Student> stack;
    stack.push(Student("aa", 14));
    stack.push(Student("bb", 18));
    stack.push(Student("cc", 15));
    stack.push(Student("dd", 16));
    std::cout << "count : " << stack.count() << std::endl;
    while (!stack.empty()) {
        stack.popup().display();
        std::cout << "---------------------" << std::endl;
    }
    
    
    std::cout << "================队列===============" << std::endl;
    
    ZQueue<Student> queue;
    queue.enqueue(Student("aa", 14));
    queue.enqueue(Student("bb", 15));
    queue.enqueue(Student("cc", 16));
    queue.enqueue(Student("dd", 17));
    queue.enqueue(Student("ee", 18));
    std::cout << "count : " << queue.count() << std::endl;
    while (!queue.empty()) {
        queue.dequeue().display();
        std::cout << "---------------------" << std::endl;
    }
    return 0;
}