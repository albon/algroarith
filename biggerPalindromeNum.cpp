/**
 * given an int N;
 * Find the smallest palindrome greater than N
 */

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

int findPalindromeNum(int N)
{
    if(N < 10)
        return N;
    char num[20];
    sprintf(num, "%d", N);
    int len = strlen(num);
    for(int i=0; i<len; ++i)
    {
        if(num[i] != '9')
            break;
        else if(i == len-1)
        {
            sprintf(num, "%d", N+1);
            len++;
        }
    }


    int right = 0;
    int left = 0;
    for(int i=(len-1)/2, j=len/2; i>=0 && j<len; --i, ++j)
    {
        right *= 10;
        right += (num[j]-'0');

        left *= 10;
        left += (num[i]-'0');
    }

    int left_r = 0;
    for(int i=0; i<(len+1)/2; ++i)
    {
        left_r = left_r*10 + num[i] - '0';
    }
    if(right >= left)
    {
        left_r += 1;
    }


    // rotate(left) + left
    sprintf(num, "%d", left_r);
    int leftLen = strlen(num);
    int lastLen = 2*leftLen - (len & 1);
    for(int i=leftLen-1; i>=0;  --i)
    {
        num[lastLen-i-1] = num[i];
    }
    num[lastLen] = 0;

    int rval;
    sscanf(num, "%d", &rval);

    return rval;

}

int main()
{
    int N = 1234567;
    int rval = findPalindromeNum(N);
    cout<<rval<<endl;
    return 0;
}
