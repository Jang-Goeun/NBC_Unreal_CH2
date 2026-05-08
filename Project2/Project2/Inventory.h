#pragma once
#include <iostream>

template <typename T>

class Inventory {
private:
    T* pItems_;
    int capacity_;
    int size_;

public:
    // 기본 생성자
    Inventory(int capacity = 10) : capacity_(capacity), size_(0) {
        pItems_ = new T[capacity_];
    }

    // 복사 생성자
    Inventory(const Inventory& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        pItems_ = new T[capacity_];

        for (int i = 0; i < size_; ++i) {
            pItems_[i] = other.pItems_[i];
        }
    }

    // 대입 연산자 오버로딩
    Inventory& operator=(const Inventory& other) {
        if (this == &other) return *this;
        delete[] pItems_; 

        capacity_ = other.capacity_;
        size_ = other.size_;
        pItems_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            pItems_[i] = other.pItems_[i];
        }
        return *this;
    }

    // 소멸자
    ~Inventory() { delete[] pItems_; }

    // 아이템 추가 메서드
    void AddItem(const T& item) {
        // 아이템 추가
        if (size_ < capacity_) {
            pItems_[size_] = item;
            ++size_;
        }
        // 아이템 추가 실패
        else {
            std::cout << "Inventory is full!" << std::endl;
        }
    }

    // 마지막 아이템 제거 메서드
    void RemoveLastItem() {
        // 마지막 아이템 제거
        if (size_ > 0) {
            size_--;
        }
        // 아이템 제거 실패
        else {
            std::cout << "Inventory is empty!" << std::endl;
        }
    }

    // 모든 아이템 출력 메서드
    void PrintAllItems() {
        std::cout << "[ Inventory (" << size_ << "/" << capacity_ <<") ]" << std::endl;

        // 아이템 정보 출력
        for (int i = 1; i <= size_; ++i) {
            std::cout << i << ". ";
            pItems_[i - 1]->printInfo();
        }
    }

    // 인벤토리 요소 개수 반환 메서드
    int GetSize() { return size_; }

    // 인벤토리 크기 반환 메서드
    int GetCapacity() { return capacity_; }
};
