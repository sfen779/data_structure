//哈希函数的构造方法：1）数字分析法 2）平方取中法，求关键字的目的是扩大差别 3）折叠法 将关键字分割成位数相同的几部分 位移叠加 间界叠加
//需要掌握：保留余数法，简单易用 把余数作为存储地址
//冲突解决
//222018321102110 冯朔 哈希表C++实现
//链接法实现哈希表

#include <iostream>
#include <cstdlib>
#include <string>
 
using namespace std;
 
class Hash
{
private:
    struct item
    {
        string name;
        string drink;
        item* next;
 
        item(): name("empty"), drink("empty"), next(nullptr) {}
        item(string n, string d): name(n), drink(d), next(nullptr) {}
    };
    static const int tableSize = 10;  // 存储量可改变
    item* HashTable[tableSize];
 
public:
    int hashFunction(string key);
    Hash();
    ~Hash();
    void AddItem(string name, string drink);
    int NumberOfItemsInIndex(int index);
    void PrintTable();
    void PrintItemsInIndex(int index);
    void FindDrink(string name);
    void RemoveItem(string name);
 
};
Hash::Hash()
{
    for (int i = 0; i < tableSize; ++i)
    {
        HashTable[i] = new item();
        HashTable[i]->name = "empty";
        HashTable[i]->drink = "empty";
        HashTable[i]->next = nullptr;
    }
}
 
Hash::~Hash()
{
 
}
 
int Hash::hashFunction(string key)
{
    int sum = 0;
    int index;
 
    for (size_t i = 0; i < key.size(); ++i)
    {
        sum += static_cast<int>(key[i]);
    }
 
    index = sum % tableSize;
 
    cout << "key[0] = " << key[0] << endl;
    cout << "key[0] = " << static_cast<int>(key[0]) << endl;
    cout << "key[1] = " << key[1] << endl;
    cout << "key[2] = " << key[2] << endl;
    cout << "sum = " << sum << endl;
    cout << "index = " << index << endl << endl;
 
    return index;
}
 
void Hash::AddItem(string name, string drink)
{
    int index = hashFunction(name);
 
    if (HashTable[index]->name == "empty")
    {
        HashTable[index]->name = name;
        HashTable[index]->drink = drink;
    }
    else
    {
        item* p = HashTable[index];
        item* n = new item(name, drink);
 
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = n;
    }
}
 
int Hash::NumberOfItemsInIndex(int index)
{
    int count = 0;
    if (HashTable[index]->name == "empty")
    {
        return count;
    }
    else
    {
        count++;
        item* p = HashTable[index];
        while (p->next != nullptr)
        {
            count++;
            p = p->next;
        }
    }
    return count;
}
 
void Hash::PrintTable()
{
    int number;
    for (int i = 0; i < tableSize; ++i)
    {
        cout << "i = " << i << ": " << endl;
        number = NumberOfItemsInIndex(i);
        cout << "index = " << i << ": " << endl;
        cout << HashTable[i]->name << ", " << HashTable[i]->drink << endl;
        cout << "# of items = " << number << endl << endl;
    }
}
 
void Hash::PrintItemsInIndex(int index)
{
    item* p = HashTable[index];
    if (p->name == "empty")
    {
        cout << "index = " << index << "is empty";
    }
    else
    {
        cout << "index " << index << " contains the following items \n";
        while (p != nullptr)
        {
            cout << p->name << ", " << p->drink <<endl;
            p = p->next;
        }
    }
}
 
void Hash::FindDrink(string name)
{
    int index = hashFunction(name);
    bool FindName = false;
 
    string drink;
    item* p = HashTable[index];
    while (p != nullptr)
    {
        if (p->name == name)
        {
            FindName = true;
            drink = p->drink;
        }
        p = p->next;
    }
    if (FindName)
    {
        cout << "Favorite drink " << drink << endl;
    }
    else
    {
        cout << name << "'s info was not fount in the hash table.\n";
    }
}
 
void Hash::RemoveItem(string name)
{
    int index = hashFunction(name);
 
    item* delPtr;
    item* p1;
    item* p2;
 
    // case0: bucket is empty
    if (HashTable[index]->name == "empty" &&
        HashTable[index]->drink == "empty")
    {
        cout << name << " was not found in the hash table" << endl;
    }
    // case1: only one item contained in the bucket, and that item has matching name
    else if (HashTable[index]->name == name &&
             HashTable[index]->next == nullptr)
    {
        HashTable[index]->name = "empty";
        HashTable[index]->drink = "empty";
        cout << name << " was removed from the hash table" << endl;
    }
    // case 2: match is located in the first item in the bucket and there are more items in the bucket
    else if (HashTable[index]->name == name)
    {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr;
        cout << name << " was removed from the hash table" << endl;
    }
    // case 3: the bucket contains items, but first item is not a match
    else
    {
        p1 = HashTable[index]->next;
        p2 = HashTable[index];
        while (p1 != nullptr && p1->name != name)
        {
            p2 = p1;
            p1 = p1->next;
        }
        // case 3.1: no match
        if (p1 == nullptr)
        {
            cout << name << " was not found in the hash table. \n";
        }
        //case 3.2: match is found
        else
        {
            delPtr = p1;
            p1 = p1->next;
            p2->next = p1;
            delete delPtr;
            cout << name << " was removed from the hash table" << endl;
        }
    }
}
int main()
{
    Hash hash;
    string name1 = " ";
    string name2 = " ";
    hash.PrintTable();
 
    hash.AddItem("Paul", "Locha");
    hash.AddItem("Kim", "Iced Mocha");
    hash.AddItem("Anni", "Strawberry Smoothy");
    hash.AddItem("Sara", "Passion Tea");
    hash.AddItem("Mike", "Tea");
    hash.AddItem("steve", "Apple cider");
    hash.AddItem("Sill", "Root beer");
    hash.AddItem("Bill", "Lochs");
    hash.AddItem("Susan", "Cola");
    hash.AddItem("Joe", "Green Tea");
 
    hash.PrintTable();
    hash.PrintItemsInIndex(0);
 
    while (name1 != "exit")
    {
        cout << "search for: ";
        cin >> name1;
        if (name1 != "exit")
        {
            hash.FindDrink(name1);
        }
    }
 
    cout << endl;
 
    while (name2 != "exit")
    {
        cout << "Remove: ";
        cin >> name2;
        if (name2 != "exit")
        {
            hash.RemoveItem(name2);
        }
    }
 
    hash.PrintTable();
    hash.PrintItemsInIndex(0);
 
    return 0;
}
