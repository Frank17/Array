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
    return 0;
}