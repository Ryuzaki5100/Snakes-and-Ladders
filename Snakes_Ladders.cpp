#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
struct snake
{
    int start;
    int end;
};
struct ladder
{
    int start;
    int end;
};
int Roll_die()
{
    time_t nTime;
    srand((unsigned)time(&nTime));
    int res = rand() % 6 + 1;
    return res < 0 ? res + 6 : res;
}
template <class t>
int check(t a[], int n, int i)
{
    for (int k = 0; k < n; k++)
        if (a[k].start == i)
            return k;
    return -1;
}
void grid(int m, int n, int a, int b, snake s[], ladder l[], int x)
{
    for (int i = m * n - 1; i >= 0; i--)
    {
        if (i == a && a == b && a != -1)
            printf(" <1p2> ");
        else if (i == a && a != -1)
            printf(" <p-1> ");
        else if (i == b && b != -1)
            printf(" <p-2> ");
        else if (check(s, x, i) != -1)
            printf(" > S < ");
        else if (check(l, x, i) != -1)
            printf(" > L < ");
        else
            printf(" [%3d] ",i+1);
        if (i % n == 0)
           { cout << endl
                 << endl;
                 }
    }
}
int main()
{
    int m, n, x, choice;
    cout << "------------------SNAKES AND LADDERS------------------" << endl;
    cout << "Game Mode --\n\t1.Default Mode\n\t2.Custom Mode\n\tEnter the Game Mode type (1/2)" << endl;
    cin >> choice;
    if (choice == 1)
    {
        m = n = 10;
        x = 6;
    }
    else if (choice == 2)
    {
        cout << "Enter the number of rows and columns for the board game" << endl;
        cin >> m >> n;
        cout << "Enter the number of snakes and ladders to be set in the board" << endl;
        cin >> x;
    }
    else
    {
        cout << "Invalid Choice!!";
        return 0;
    }
    int a = -1, b = -1;
    snake s[x];
    ladder l[x];
    time_t nTime;
    srand((unsigned)time(&nTime));
    for (int i = 0; i < x; i++)
    {
        int temp = m * n - 1;
        s[i].start = (rand() % temp + 1 + temp) % temp;
        s[i].end = (rand() % temp + 1 + temp) % temp;
        if (s[i].start < s[i].end)
        {
            int t = s[i].end;
            s[i].end = s[i].start;
            s[i].start = t;
        }
        l[i].start = (rand() % temp + 1 + temp) % temp;
        l[i].end = (rand() % temp + 1 + temp) % temp;
        if (l[i].start > l[i].end)
        {
            int t = l[i].end;
            l[i].end = l[i].start;
            l[i].start = t;
        }
    }
    grid(m, n, a, b, s, l, x);
    while (1)
    {
        char p;
        cout << "Player 1 : Roll the die --> Press any key to roll " << endl;
        cin >> p;
        int roll = Roll_die();
        int temp = a + roll;
        cout << "\nPlayer 1 : has rolled a " << roll << " on the die!!" << endl;
        if (temp == m * n - 1)
        {
            cout << "Player 1 : wins !!" << endl;
            return 0;
        }
        else if (temp >= m * n)
            cout << "OOPS!! Player 1 : needs to get a " << m * n - a - 1 << " on the die to win!!" << endl;
        else
        {
            a = temp;
            if (check(s, x, a) != -1)
            {
                a = s[check(s, x, a)].end;
                cout << "\nOOPS!! Player 1 : has been eaten by snake : Gone back to Position : " << a << endl;
            }
            else if (check(l, x, a) != -1)
            {
                a = l[check(l, x, a)].end;
                cout << "\nBRAVO!! Player 1 : has taken the ladder : Upto to Position : " << a << endl;
            }
        }
        grid(m, n, a, b, s, l, x);
        cout << "Player 2 : Roll the die --> Press any key to roll " << endl;
        cin >> p;
        roll = Roll_die();
        temp = b + roll;
        cout << "\nPlayer 2 : has rolled a " << roll << " on the die!!" << endl;
        if (temp == m * n - 1)
        {
            cout << "Player 2 : wins !!" << endl;
            return 0;
        }
        else if (temp >= m * n)
            cout << "OOPS!! Player 2 : needs to get a " << m * n - b - 1 << " on the die to win!!" << endl;
        else
        {
            b = temp;
            if (check(s, x, b) != -1)
            {
                b = s[check(s, x, b)].end;
                cout << "\nOOPS!! Player 2 : has been eaten by snake : Gone back to Position : " << b << endl;
            }
            else if (check(l, x, b) != -1)
            {
                b = l[check(l, x, b)].end;
                cout << "\nBRAVO!! Player 2 : has taken the ladder : Upto to Position : " << b << endl;
            }
        }
        grid(m, n, a, b, s, l, x);
    }
}