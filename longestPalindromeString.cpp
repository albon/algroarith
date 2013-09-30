/*
 * given two string abcdefedba, find a substring, which is palindrome
 * here it is defed
 * ºó×ºÊ÷
 */
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

struct Node {
    unsigned char c;
    Node* next[256];
    Node(unsigned char p) : c(p)
    {
        memset(next, 0, sizeof(next));
    }
};

void insertToTree(Node* head, char* str)
{
    Node* p = head;
    while(*str != 0)
    {
        unsigned char c = *str;
        if(p->next[c] == NULL)
        {
            p->next[c] = new Node(c);
        }
        p = p->next[c];
        ++str;
    }
}

void buildSuffixTree(Node* node, char* str)
{
    while(*str != 0)
    {
        insertToTree(node, str++);
    }
}

int findMaxSubString(Node* node, char* str)
{
    int len = 0;
    while(*str != 0 && node->next[*str]!=NULL)
    {
        node = node->next[*str];
        ++str;
        ++len;
    }
    return len;
}

char* findPalSubString(char* str)
{
    Node* head = new Node(0);
    buildSuffixTree(head, str);

    reverse(str, str+strlen(str));
    int maxLen = 0, pos = 0;
    for(int i=0; i<strlen(str); ++i)
    {
        int len = findMaxSubString(head, str+i);
        if(len > maxLen)
        {
            maxLen = len;
            pos = i;
        }
    }
    char* sub = new char[maxLen+1];
    memcpy(sub, str+pos, maxLen*sizeof(char));
    sub[maxLen] = 0;
    return sub;
}

int main()
{
    char str[] = "abcdefedba";
    char* sub = findPalSubString(str);

    cout<<sub<<endl;
    return 0;
}
