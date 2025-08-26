#include <iostream>
#include <algorithm>
using namespace std;

class Item
{
private:
    string name;
    int price;

public:
    Item(string name = "unknown", int price = 0)
    {
        this->name = name;
        this->price = price;
    }

    int GetPrice() const
    {
        return price;
    }


    void PrintInfo() const {
        cout << "[이름 : " << name << ", 가격 : " << price << "G]" << endl;
    }
};


//두 Item 객체를 받아 가격을 기준으로 어떤 것이 먼저 와야 하는 지 판단
bool compareItemsByPrice(const Item& a, const Item& b)
{
    return a.GetPrice() < b.GetPrice();
}

//인벤토리 만들기_템플릿 이용
template <typename T>
class Inventory
{
private:
    T* pItems;
    int capacity;
    int size;

public:

    //생성자
    Inventory(int capacity = 10)
    {
        this->capacity = capacity;
        size = 0;
        pItems = new T[capacity];
    }

    //소멸자
    ~Inventory() 
    {
        delete[] pItems;
        pItems = nullptr;
    }

    void AddItem(const T& item) // 인벤토리가 찼을 때 2배로 capacity 늘리기
    {
        if (size < capacity) 
        {
            pItems[size++] = item;
        }
        if (size >= capacity)
        {
            if (size == capacity)
            {
                cout << "인벤토리가 꽉 찼습니다!" << endl;
            }
            // capacity를 두 배로 늘리기
            capacity *= 2;
            T* newItems = new T[capacity];

            // 기존 아이템 복사
            for (int i = 0; i < size; ++i)
            {
                newItems[i] = pItems[i];
            }

            // 기존 메모리 해제 후 교체
            delete[] pItems;
            pItems = newItems;
        }
    }

    void RemoveLastItem()
    {
        if (size >0)
        {
            size--;
        }
        else
        {
            cout << "인벤토리가 비어있습니다." << endl;
        }

    }
   
    int GetSize() const
    {
        return size;
    }

    int GetCapacity() const
    {
        return capacity;

    }
  
    void PrintAllItems() const
    {
        if (size == 0) {
            cout << "(비어있음)" << endl;
            return;
        }
        for (int i = 0; i < size; ++i)
        {
            pItems[i].PrintInfo();
        }
    }
    //도전 기능--------------------------------------------------------
    
    //복사 생성자 및 대입(Assign) 함수 구현
    Inventory(const Inventory<T>& other)
    {
        capacity = other.capacity;
        size = other.size;
        pItems = new T[capacity];
        for (int i = 0; i < size; ++i) 
        {
            pItems[i] = other.pItems[i];
        }
        cout << "인벤토리 복사 완료" << endl;
    }
    
    void Assign(const Inventory<T>&);
    
    //함수 추가
    void Resize(int newCapacity)
    {
        this->capacity = newCapacity;
    }

    //함수 추가  
    void SortItems()
    {
        sort(pItems, pItems + size, compareItemsByPrice);
        for (int j = 0; j < size; j++)
        {
            pItems[j].PrintInfo();
        }
    }
};

int main() 
{
    //인벤토리 생성
    Inventory<Item> InventoryT(5);
    //아이템 추가    
    InventoryT.AddItem(Item("포션", 200));
    InventoryT.AddItem(Item("검", 150));
    InventoryT.AddItem(Item("방패",130));
    InventoryT.AddItem(Item("창", 110));

    //출력
    cout << " < 인 벤 토 리 > " << endl;
    InventoryT.PrintAllItems();
    cout << endl << " 아이템 목록 정렬(가격 오름차순) " << endl;
    InventoryT.SortItems();


    return 0;
}





