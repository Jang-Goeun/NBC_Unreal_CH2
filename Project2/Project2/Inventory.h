#pragma once
#include <iostream>
#include <string>

/**
 * @brief 아이템을 저장하고 관리하는 템플릿 인벤토리 클래스
 * @tparam T 인벤토리에 저장할 아이템의 타입
 */
template <typename T>
class Inventory
{
private:
    T* pItems_;     // 아이템을 저장하는 동적 배열 포인터
    int capacity_;  // 인벤토리의 최대 수용량
    int size_;      // 현재 저장된 아이템의 종류 개수
    int totalCount_; // 전체 아이템 총 수량

public:
    /**
     * @brief Inventory 클래스의 생성자
     * @param capacity 인벤토리의 초기 최대 수용량 (기본값: 10)
     */
    Inventory(int capacity = 10);

    /**
     * @brief Inventory 클래스의 복사 생성자
     * @param other 복사할 원본 인벤토리 객체
     */
    Inventory(const Inventory& other);

    /**
     * @brief 대입 연산자 오버로딩
     * @param other 대입할 원본 인벤토리 객체
     * @return Inventory& 자기 자신에 대한 참조
     */
    Inventory& operator=(const Inventory& other);

    /**
     * @brief Inventory 클래스의 소멸자
     */
    ~Inventory();

    /**
     * @brief 인벤토리에 아이템을 추가. 이미 있는 아이템이면 수량만 증가
     * @param item 추가할 아이템 객체 (중복 시 내부에서 메모리 해제)
     */
    void AddItem(const T& item);

    /**
     * @brief 이름으로 아이템의 인벤토리 내 인덱스를 찾음
     * @param name 찾을 아이템의 이름
     * @return int 찾은 인덱스 (없으면 -1)
     */
    int FindItem(const std::string& name);

    /**
     * @brief 특정 인덱스의 아이템을 마지막 요소와 교체하여 제거
     * @param index 제거할 아이템의 인덱스
     */
    void RemoveItem(int index);

    /**
     * @brief 인벤토리 내의 모든 아이템 정보를 출력
     */
    void PrintAllItems();

    /**
    *  @brief 현재 인벤토리에 담긴 모든 아이템의 총 수량을 계산하여 업데이트
    */
    void UpdateTotalCount();

    /**
    *  @brief 인벤토리 확장 함수
    *  @param newCapacity: 확장 크기
    */
    void Resize(int newCapacity);

    /**
     * @brief 현재 인벤토리에 저장된 아이템의 종류 개수를 반환
     * @return int 현재 아이템 개수
     */
    int GetSize();

    /**
     * @brief 인벤토리의 최대 수용량을 반환
     * @return int 최대 수용량
     */
    int GetCapacity();

    /**
     * @brief 특정 인덱스의 아이템 객체를 반환
     * @param index 가져올 인덱스
     * @return T 아이템 객체
     */
    T GetItem(int index);
};

template <typename T>
Inventory<T>::Inventory(int capacity) : capacity_(capacity), size_(0), totalCount_(0)
{
    pItems_ = new T[capacity_];
}

template <typename T>
Inventory<T>::Inventory(const Inventory& other)
{
    capacity_ = other.capacity_;
    size_ = other.size_;
    pItems_ = new T[capacity_];
    for (int i = 0; i < size_; ++i)
    {
        pItems_[i] = other.pItems_[i];
    }
}

template <typename T>
Inventory<T>& Inventory<T>::operator=(const Inventory& other)
{
    if (this == &other) return *this;
    delete[] pItems_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    pItems_ = new T[capacity_];
    for (int i = 0; i < size_; ++i)
    {
        pItems_[i] = other.pItems_[i];
    }
    return *this;
}

template <typename T>
Inventory<T>::~Inventory() {
    delete[] pItems_;
}

template <typename T>
int Inventory<T>::FindItem(const std::string& name)
{
    for (int i = 0; i < size_; ++i)
    {
        if (pItems_[i]->getName() == name) return i;
    }
    return -1;
}

template <typename T>
void Inventory<T>::AddItem(const T& item)
{
    if (item == nullptr) return;

    // 1. 이미 인벤토리에 있는지 확인
    int index = FindItem(item->getName());

    if (index != -1)
    {
        // 이미 있다면 수량만 증가시키고, 새로 전달받은 객체는 해제
        pItems_[index]->addCount(item->getCount());
        totalCount_ += item->getCount();
        delete item; 
    }
    else
    {
        if (totalCount_ >= capacity_)
        {
            std::cout << "\nAdding item... (" << totalCount_ << "/" << capacity_ << " full)" << std::endl;
            std::cout << "-> Inventory auto-expanded! (" << capacity_ << " -> " << capacity_ * 2 << ")" << std::endl;
            std::cout << "-> Item added" << std::endl;
            Resize(capacity_ * 2);
        }

        // 2. 없다면 새로 추가
        pItems_[size_] = item;
        totalCount_ += item->getCount();
        ++size_;
    }
}

template <typename T>
void Inventory<T>::RemoveItem(int index)
{
    if (index >= 0 && index < size_)
    {
        totalCount_ -= pItems_[index]->getCount();
        pItems_[index] = pItems_[size_ - 1];
        pItems_[size_ - 1] = nullptr; 
        size_--;
    }
}

template <typename T>
void Inventory<T>::PrintAllItems()
{
    std::cout << "[ Inventory (" << totalCount_ << "/" << capacity_ << ") ]" << std::endl;
    for (int i = 1; i <= size_; ++i)
    {
        std::cout << i << ". ";
        pItems_[i - 1]->printInfo();
    }
}

template <typename T>
void Inventory<T>::UpdateTotalCount()
{
    totalCount_ = 0;
    for (int i = 0; i < size_; ++i)
        totalCount_ += pItems_[i]->getCount();
}

template <typename T>
void Inventory<T>::Resize(int newCapacity)
{
    // 새 배열 할당
    T* newPItems_ = new T[newCapacity];

    // 기존 데이터 복사
    for (int i = 0; i < size_; ++i)
    {
        newPItems_[i] = pItems_[i];
    }

    // 기존 배열 해제
    delete[] pItems_;

    pItems_ = newPItems_;
    capacity_ = newCapacity;
}

template <typename T>
int Inventory<T>::GetSize()
{
    return size_;
}

template <typename T>
int Inventory<T>::GetCapacity()
{
    return capacity_;
}

template <typename T>
T Inventory<T>::GetItem(int index)
{
    if (index >= 0 && index < size_) return pItems_[index];
    return nullptr;
}
