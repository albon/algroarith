/**
 * 链地址法-Hash
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;
// 哈希结点
template<class T> struct Hash_Node {
    T* data;            // 数据
    int key;            // 键值
    Hash_Node<T> *next; // 下一个结点
    Hash_Node(T* p, int k)
    {
        key = k;
        data = p;
        next = NULL;
    }
};
// 哈希Map
template<class T> class Hash_Map {
public:
    Hash_Map(int capacity)
    {
        hash_array = (hash_node* *) malloc(sizeof(hash_node*) * capacity);
        memset(hash_array, 0, sizeof(hash_node*) * capacity);
        size = capacity;
    }
    //  插入一条数据
    void insertData(int key, T* data)
    {
        hash_node* hn = new hash_node(data, key);
        int index = key % size;
        hn->next = hash_array[index];
        hash_array[index] = hn;
    }
    // 获取一条数据
    T* getData(int key)
    {
        int index = key % size;
        hash_node* p = hash_array[index];
        while(p)
        {
            if(p->key == key)
                return p->data;
            else
                p = p->next;
        }
        return NULL;
    }
    // 移除结点，并返回其中数据
    T* removeData(int key)
    {
        int index = key % size;
        hash_node* p = hash_array[index];
        if(p == NULL)
            return NULL;
        if(p->key == key)
        {
            hash_array[index] = p->next;
            T* tmp = p->data;
            delete p;
            p = NULL;
            return tmp;
        }
        hash_node* q = p;
        p = p->next;
        while(p)
        {
            if(p->key == key)
            {
                q->next = p->next;
                T* tmp = p->data;
                delete p;
                p = NULL;
                return tmp;
            }
        }
        return NULL;
    }
private:
    typedef Hash_Node<T> hash_node;
    hash_node* *hash_array;
    int size;
};

template<class T> struct Link_Node
{
    Link_Node(T* p, int k)
    {
        data = p;
        key = k;
        prev = NULL;
        next = NULL;
    }
    T* data;            // 存储数据
    int key;            // 关键字
    Link_Node* prev;
    Link_Node* next;
};
// 双向循环链表
template<class T> class DbLinkedList
{
public:
    typedef Link_Node<T> link_node;
    DbLinkedList()
    {
        head = NULL;
    }
    // 将结点插入头部
    void insertToHead(link_node* node)
    {
        if(head == NULL)
        {
            head = node;
            node->prev = node;
            node->next = node;
        }
        else
        {   // 如果已经有了结点，就插入循环链表头结点前面
            link_node* next = head;
            link_node* prev = head->prev;

            node->prev = prev;
            node->next = next;

            next->prev = node;
            prev->next = node;

            head = node;
        }
    }
    void deleteNode(link_node* node)
    {
        if(node->prev == node)
        {
            head = NULL;
            cout << "head = NULL" <<endl;
        }
        else
        {
            if(head == node)
                head = node->next;
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }
    // 移动某结点到头部
    void moveToHead(link_node* node)
    {
        if(head == node)
            return;
        deleteNode(node);
        insertToHead(node);
    }
    // 返回头结点
    link_node* getHeadNode()
    {
        return head;
    }
    // 返回尾结点
    link_node* getTailNode()
    {
        if(head)
        {
            return head->prev;
        }
        return NULL;
    }
    // 按序输出所有key
    void output()
    {
        if(head == NULL)
            return;
        cout<<"list: ";
        link_node* p = head;
        do
        {
            cout<<p->key<<" ";
            p = p->next;
        }while(p!=head);
        cout<<endl;
    }
private:
    link_node* head;
};

// 以LRU策略更新和提取数据
class LRU_Cache
{
public:
    LRU_Cache(int capacity)
    {
        hash_map = new Hash_Map<DbLinkedList<int>::link_node>(capacity);
        dList = new DbLinkedList<int>();
        this->capacity = capacity;
        count = 0;
    }

    int getData(int key)
    {   // 获取key对应的值
        DbLinkedList<int>::link_node* data = hash_map->getData(key);
        // 输出当前链表
        dList->output();
        if(data == NULL)
        {// 没有找到，模拟生成一个，实际中是需要到硬盘或内存中取的
            if(capacity > count)
            {// 如果不满，则取一个，放到链表头部、哈希表中
                DbLinkedList<int>::link_node* ln = new DbLinkedList<int>::link_node(new int(key), key);
                hash_map->insertData(key, ln);
                dList->insertToHead(ln);
                cout<<"not found, insert ";
                ++count;
                return * (ln->data);
            }
            else
            {// 满了，取出链表尾部结点，删除(同时删除链表和哈希表中指针)，将新结点放入链表头部和哈希表中
                DbLinkedList<int>::link_node* tail = dList->getTailNode();
                // 更新哈希表
                hash_map->removeData(tail->key);
                * (tail->data) = key;
                tail->key = key;
                hash_map->insertData(tail->key, tail);

                dList->moveToHead(tail);
                cout<<"not found, relace ";
                return * (tail->data);
            }
        }
        else
        {// 如果找到了，只需扔到链表最前面
            dList->moveToHead(data);
            cout<<"found ";
            return *(data->data);
        }
    }
private:
    int capacity;
    int count;
    DbLinkedList<int>* dList;
    Hash_Map<DbLinkedList<int>::link_node>* hash_map;
};

int main()
{
    LRU_Cache l_c(11);
    for(int i=0; i<20; ++i)
    {
        int data = l_c.getData(rand()%30);
        cout<<data<<endl;
    }
/**    Hash_Map<int> hm(11);
    hm.insertData(5, new int(55) );

    int *data = hm.getData(5);
    cout<< *data<<endl;

    data = hm.removeData(5);
    cout<< *data<<endl;

    data = hm.removeData(5);
    if(data)
    cout<< *data<<endl;

    DbLinkedList<int> dl;
    Link_Node<int> linkNode1(new int(15), 5);
    Link_Node<int> linkNode2(new int(12), 2);
    Link_Node<int> linkNode3(new int(17), 7);
    dl.insertToHead(&linkNode1);
    dl.output();
    dl.insertToHead(&linkNode2);
    dl.output();
    dl.insertToHead(&linkNode3);
    dl.output();



    Link_Node<int>* head = dl.getHeadNode();
    cout<< *head->data<<endl;
    Link_Node<int>* tail = dl.getTailNode();
    cout<< *tail->data<<endl;

    dl.moveToHead(tail);

    DbLinkedList<int>::link_node *ln = dl.getTailNode();
    cout<< *ln->data <<endl;
    */
    return 0;
}
