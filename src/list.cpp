#include "../include/list.h"

Node::Node(Node& obj_1)
{
    data=obj_1.data;
    next=obj_1.next;
}

void Node::operator=( Node &obj_1)
{
    data=obj_1.data;
    next=obj_1.next;
}

List::List():Size(0),Head_node(NULL)
{
}

List::List(const List& list2):Size(0),Head_node(NULL)//не удается поставить константу из-за метода get head
{      
    Node* tmp(list2.GetHead());
    if(tmp)
    {
        Head_node=new Node;
        Node* obj= Head_node;
        while(tmp!=NULL)
        {
            obj->SetDatValue(tmp->GetDat());
            if(tmp->GetNextNode()!=NULL)
            {
                obj->SetNextNode(new Node);
                obj=obj->GetNextNode();
            }
            tmp=tmp->GetNextNode();
            Size+=1;
        }
    }
}

List::~List()
{
    Node* obj(GetHead());
    Node* obj_0=obj;
    while(obj!=NULL)
    {   
        obj_0=obj;
        obj=obj->GetNextNode();
        delete obj_0;
    }
}

bool List::operator==(const List& list2) const
{
    Node* obj_1(GetHead());
    Node* obj_2(list2.GetHead());
    if(Size!=list2.Size)
        return 0;
    while(obj_1!=NULL)
    {
        if(obj_1->GetDat()!=obj_2->GetDat())
        return 0;
        obj_1=obj_1->GetNextNode();
        obj_2=obj_2->GetNextNode();
    }
    return 1;
}
List& List::operator=(const List& list2)
{
    Node* tmp(list2.GetHead());
    if(&list2==this)
	{
		return *this;
	}
    if(tmp)
    {
        Size=0;
        Head_node=new Node;
        Node* obj=Head_node;
        while(tmp!=0)
        {
            obj->SetDatValue(tmp->GetDat());
            if(tmp->GetNextNode()!=NULL)
            {
                obj->SetNextNode(new Node);
                obj=obj->GetNextNode();
            }
            tmp=tmp->GetNextNode();
            Size+=1;
        }
        return *this;
    }
    Head_node=NULL;
    return *this;
}

void List::InserToHead(const DataType& d)
{
    if(!Size)
    {
        Head_node=new Node;
        Head_node->SetDatValue(d);
        Size+=1;
    }
    else
    {
        Node* tmp;
        tmp=Head_node;
        Head_node=new Node;
        Head_node->SetDatValue(d);
        Head_node->SetNextNode(tmp);
        Size+=1;
    }
}

void List::InserToTail(const DataType& d)
{
    if(!Size)
    {
        Head_node=new Node;
        Head_node->SetDatValue(d);
        Size+=1;
    }
    else 
    {
        Node* tmp(GetHead());
        while(tmp->GetNextNode()!=NULL)
            tmp=tmp->GetNextNode();
        Node* obj=new Node;
        // Node *obj; //в чем разница
        obj->SetDatValue(d);
        tmp->SetNextNode(obj);
        Size+=1;
    }
}

void List::InsertAfter(Node* node,const DataType& d)
{
    Node* tmp(GetHead());
    if(tmp==NULL)
        throw "Can't insert after for empty list";
    else 
        while(tmp->GetNextNode()!=NULL)
        {
            if(tmp==node)
            {
                Node* tmp_0=tmp->GetNextNode();
                Node* tmp_1=new Node;
                tmp_1->SetDatValue(d);
                tmp_1->SetNextNode(tmp_0);
                tmp->SetNextNode(tmp_1);
                Size+=1;
            }
            tmp=tmp->GetNextNode();
        }
}

void List::Delete(const DataType& d)// удалить звено со значением data = d
{
    
    Node* tmp(GetHead());
    if (tmp)
    {
        if(tmp->GetDat()==d)
            {
                Node* obj=Head_node->GetNextNode();
                delete Head_node;
                Head_node=obj;
                Size-=1;
            }
        else 
            while(tmp!=NULL)
            {
                if(tmp->GetNextNode()!=NULL)
                {

                    if(tmp->GetNextNode()->GetDat()==d)
                    {
                        Node* tmp_0= tmp->GetNextNode()->GetNextNode();
                        delete tmp->GetNextNode();
                        tmp->SetNextNode(tmp_0);
                        Size-=1;
                        break;
                    }
                }
                tmp=tmp->GetNextNode();
            }
    }
}

Node* List::Search(const DataType& d)// найти указатель на звено со значением data = d
{
    Node* tmp(GetHead());
    if(tmp)
        while(tmp!=NULL)
        {
            if(tmp->GetDat()==d)
                return tmp;
            tmp=tmp->GetNextNode();
        }
    return NULL;
}

void List::Clean()// удалить все звенья
{
    Node* obj(GetHead());
    Node* obj_0=obj;
    while(obj!=NULL)
    {   
        obj_0=obj;
        obj=obj->GetNextNode();
        delete obj_0;
    }
    Head_node=NULL;
    Size=0;
}

void List::Inverse()
{
    List obj(*this);
    Node* tmp=obj.GetHead();
    Clean();
    while(tmp!=NULL)
    {
        InserToHead(tmp->GetDat());
        tmp=tmp->GetNextNode();
    }
} // инвертировать список, т.е. звенья должны идти в обратном порядке
List List::Merge(Node* node, const List& list2)// создать список3, добавив список2 в текущий список после указателя node  
{   
    if(node!=NULL)
    {
        List tmp_l(*this);
        Node* tmp_0(list2.GetHead());
        Node* tmp_1=tmp_l.Search(node->GetDat());
        while(tmp_0!=NULL)
        {
            tmp_l.InsertAfter(tmp_1,tmp_0->GetDat());
            tmp_1=tmp_1->GetNextNode();
            tmp_0=tmp_0->GetNextNode();
        }
        return tmp_l;
    }
    else
        return *this;
} 

List List::Merge(const List& list2) // создать список3, добавив в конец текущего списка список2
{
    List tmp_l(*this);
    Node* tmp(tmp_l.GetHead());
    if(tmp!=NULL)
    {
        while(tmp->GetNextNode()!=NULL)
            tmp=tmp->GetNextNode();
        if(list2.Size>0)
        {
            Node* tmp_0(list2.GetHead());
            while(tmp_0!=NULL)
            {
                Node* obj=new Node;

                obj->SetDatValue(tmp_0->GetDat());
                tmp->SetNextNode(obj);
                tmp=tmp->GetNextNode();
                tmp_0=tmp_0->GetNextNode();
                tmp_l.Size+=1;
            }
            return tmp_l;
        }
        return tmp_l;
    }
    else 
        return List(list2);
}

Node* List::GetHead() const
{
    return Head_node;
}

ostream& operator<<(ostream& os,  List& l)
{
    Node* tmp(l.GetHead());
    while(tmp!=NULL)
    {   
        os<<tmp->GetDat()<<" "<<tmp<<" "<<tmp->GetNextNode()<<endl;
        if (tmp->GetNextNode()==NULL)
        {
            tmp=NULL;
        }
        else
            tmp=tmp->GetNextNode();
    }
    return os;
}
