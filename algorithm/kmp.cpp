/**
 * kmp算法的重点是next数组的计算
 */
#include <iostream>
#include <string.h>

using namespace std;

void compute_prefix(int *next, char *p)
{// 计算next数组
    int i, n, k;
    n = strlen(p);
    next[1] = next[0] = 0;
    k = 0;
    for(i=2; i<n; ++i)
    {
        for(;k!=0 && p[k]!=p[i-1]; k=next[k]);
        if(p[k] == p[i-1])
            k++;
        next[i] = k;
    }
}

void kmp_match(char* text, char *p, int *next)
{
    int m, n, s, q;
    m = strlen(p);
    n = strlen(text);
    q = s = 0;

    while(s < n)
    {
        // p[q]==text[s]，则q++,s++
        // p[q]!=text[s]时，令q=next[q]再比较
        // next[q]的含义是，当p[q]!=text[s]时，再用p[next[q]]与text[s]比较
        // 直到q==0了，表示p[0]与text[s]都不一样，那就s++
        for(q=next[q]; q<m && s<n && p[q]==text[s]; q++, s++);
        if(q == 0)
        {
            s++;
        }
        else if(q==m)
        {
            cout<<"pattern occurs with shift"<< s-m<<endl;
            return; //find and return
        }

    }
}

int main()
{
    int next[101], n;
    char *p = "ababc";
    char *text = "ababccccababc";

    compute_prefix(next, p);
    cout<<"prefix: ";
    for(int i=0; i<strlen(p); ++i)
    {
        cout<<next[i]<<" ";
    }
    cout<<endl;
    kmp_match(text, p, next);
    return 0;
}
