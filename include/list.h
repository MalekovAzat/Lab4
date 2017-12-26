#ifndef __AISD_LIST__
#define __AISD_LIST__

#include <iostream>
using namespace std;

typedef int DataType;

struct Node
{
private:
  DataType data;
  Node* next;
public:
  Node(){ DataType data=0;next=NULL;};
  Node(Node& obj_1);
  void operator=(Node& obj_1);
  void SetDatValue(DataType Val){data=Val;};
  void SetNextNode(Node* obj_1){next=obj_1;};
  const DataType GetDat(){return data;};
  Node* GetNextNode(){return next;};
  
  //void SetNextLink(Node next_node){next=next_node;};
  // здесь могут быть конструкторы, методы, деструктор Node
};

class List
{
private:
  Node* Head_node;
  int Size;
public:
  List();
  List(const List& list2);
  List& operator=(const List& list2);
  ~List();
  bool operator==(const List& list2) const;
  void InserToHead(const DataType& d); // вставить элемент d первым
  void InserToTail(const DataType& d); // вставить элемент d последним
  void InsertAfter(Node* node, const DataType& d); // вставить элемент d после звена node
  void Delete(const DataType& d); // удалить звено со значением data = d
  Node* Search(const DataType& d); // найти указатель на звено со значением data = d
  void Clean(); // удалить все звенья
  int GetSize(){return Size;} const ; // узнать число звеньев в списке
  Node* GetHead() const; // получить указатель на первое звено списка

  void Inverse(); // инвертировать список, т.е. звенья должны идти в обратном порядке
  List Merge(Node* node, const List& list2); // создать список3, добавив список2 в текущий список после указателя node  
  List Merge(const List& list2); // создать список3, добавив в конец текущего списка список2

  friend ostream& operator<<(ostream& os,  List& l);// friend ostream& operator<<(ostream& os, const List& l);
};

#endif