#include <iostream>
#include <string.h>
using namespace std;

// Time Complexity:O(m+n):Worst Case->O(mn)
// Space Complexity:O(1)
// Rabin karp algorithm to find the pattern in the given string
#define d 256
void search(char pat[], int q, char txt[]) // q denotes the prime no which should be preferably large
{
    int m = strlen(pat);
    int n = strlen(txt);
    int i, j;
    int p = 0; // hash value of pattern
    int t = 0; // hash value of text
    int h = 1;
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;
    for (i = 0; i < m; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }
    for (i = 0; i < n - m; i++)
    {
        if (p == t) // if pattern matches with txt we print the index of the txt
        {
            bool flag = true;
            for (j = 0; j < m; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    flag = false;
                    break;
                }
                if (flag)
                    cout << i << endl;
            }
            if (j == m)
                cout << "pattern found at index:" << i << endl;
        }
        if (i < n - m) // when sliding window we subtract the leading val and add the trailing value for txt hash
        {
            t = (d * (t - txt[i] * h)) + txt[i + m] % q;
            if (t < 0)
                t = t + q;
        }
    }
}

int main()
{
    char txt[] = "AABBACAADAABAABA";
    char pat[] = "AABA";
    int q = 151;
    search(pat, q, txt);
    return 0;
}