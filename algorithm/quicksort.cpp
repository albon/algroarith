/**
 * 快速排序
 */
#include <iostream>
#include <stdlib.h>

using namespace std;

void swap(int data[], int a, int b)
{
    data[a] = data[a] ^ data[b];
    data[b] = data[a] ^ data[b];
    data[a] = data[a] ^ data[b];
}

void output(int data[], int len)
{
    if(data == NULL)
        return;
    for(int i=0; i<len; ++i)
        cout<<data[i]<<"\t";
    cout<<endl;
}

// from 和 to表示需要排序的起始点
// 从大道小排序
void quicksort(int data[], int from, int to)
{
    if(data == NULL)
        return;
    if(from >= to)
    {
        return;
    }

    int start = from, endp = to;
    int temp = data[from];
    while(start<endp)
    {
        while(start<endp && data[endp]<temp)
            --endp;
        if(start<endp)
        {
            data[start] = data[endp];
            ++start;
        }
        while(start<endp && data[start]>=temp)
            ++start;
        if(start<endp)
        {
            data[endp] = data[start];
            --endp;
        }
    }
    data[start] = temp;

    quicksort(data, from, start-1);
    quicksort(data, start+1, to);
}



int main()
{
    int data[9] = {11, 2, 3, 44, 666, 77, 9, 322, 980};

    quicksort(data, 0, 8);

    output(data, 8);
    return 0;
}
