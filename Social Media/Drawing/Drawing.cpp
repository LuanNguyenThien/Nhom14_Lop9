#include "graphics.h"
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
typedef pair<int, int> ii;
const int oo = INT_MAX;

struct Node
{
    int distance;
    int p_start;
    int p_end;
    Node* next;
};

struct List
{
    Node* top;

    void init()
    {
        top = NULL;
    }

    Node* newNode(int p)
    {
        Node* temp = new Node;
        temp->p_start = p;
        temp->next = NULL;
        return temp;
    }

    Node* newNode2(int p1, int p2, int d)
    {
        Node* temp = new Node;
        temp->distance = d;
        temp->p_start = p1;
        temp->p_end = p2;
        temp->next = NULL;
        return temp;
    }

    void push(int p)
    {
        Node* temp = newNode(p);
        temp->next = top;
        top = temp;
        return;
    }

    void push_back(int p1, int p2, int d)
    {
        Node* start = top;
        Node* temp = newNode2(p1, p2, d);
        if (top == NULL)
        {
            temp->next = top;
            top = temp;
            return;
        }
        while (start->next != NULL)
            start = start->next;
        temp->next = start->next;
        start->next = temp;
    }

    void pop()
    {
        Node* temp = top;
        top = top->next;
        free(temp);
    }

    Node* peek()
    {
        return top;
    }

    bool check_bool()
    {
        return top == NULL;
    }

};

struct Priority_queue
{
    Node* top;

    void init()
    {
        top = NULL;
    }

    Node* newNode(int d, int p)
    {
        Node* temp = new Node;
        temp->distance = d;
        temp->p_end = p;
        temp->next = NULL;
        return temp;
    }

    void push(int d, int p)
    {
        Node* start = top;
        Node* temp = newNode(d, p);
        if (top == NULL)
        {
            temp->next = top;
            top = temp;
            return;
        }
        if (top->distance >= temp->distance)
        {
            temp->next = top;
            top = temp;
        }
        else
        {
            while (start->next != NULL && start->next->distance < temp->distance)
                start = start->next;
            temp->next = start->next;
            start->next = temp;
        }
    }

    void push_back(int d, int p)
    {
        Node* start = top;
        Node* temp = newNode(d, p);
        if (top == NULL)
        {
            temp->next = top;
            top = temp;
            return;
        }
        while (start->next != NULL)
            start = start->next;
        temp->next = start->next;
        start->next = temp;
    }

    void pop()
    {
        Node* temp = top;
        top = top->next;
        free(temp);
    }

    Node* peek()
    {
        return top;
    }

    bool check_bool()
    {
        return top == NULL;
    }
};

int number_point, number_way;
int From[1001];
List a[1001];
Priority_queue List_road[1001];

int d[101][101];
int s_min[1001];

void dijkstra(int firstpoint)
{
    Priority_queue pq;
    pq.init();
    for (int i = 1; i <= number_point; i++)
        s_min[i] = oo;
    s_min[firstpoint] = 0;
    pq.push(0, firstpoint);
    while (!pq.check_bool())
    {
        int u = pq.peek()->p_end;
        int du = pq.peek()->distance;
        pq.pop();

        if (du != s_min[u])
            continue;

        Node* temp = new Node;
        temp = List_road[u].top;
        while (temp != NULL)
        {
            int v = temp->p_end;
            int uv = temp->distance;;
            if (s_min[v] > du + uv)
            {
                From[v] = u;
                s_min[v] = du + uv;
                pq.push(s_min[v], v);
            }
            temp = temp->next;
        }
    }
}

void truy_vet(int second_point, int first_point, int mang[100][100])
{
    int u = second_point;
    int dem1 = 0;
    mang[second_point - 1][dem1] = second_point;
    dem1++;
    while (u != first_point)
    {
        a[second_point].push(u);
        u = From[u];
    }
    a[second_point].push(first_point);
    while (a[second_point].top->next != NULL)
    {
        mang[second_point - 1][dem1] = a[second_point].peek()->p_start;
        dem1++;
        a[second_point].pop();
    }
    mang[second_point - 1][dem1] = a[second_point].peek()->p_start;
    dem1++;
    a[second_point].pop();
    for (int i = dem1; i > 1; i--)
    {
        mang[second_point - 1][i] = mang[second_point - 1][i - 1];
    }
    mang[second_point - 1][1] = dem1 - 1;
}

class User
{
public:
    int x, y;
    int size;
    const char* a;
    bool tat_mo = 0;
    User(int X, int Y, int SIZE, const char* A)
    {
        x = X;
        y = Y;
        size = SIZE;
        a = A;
    }

    User() {}

    void add()
    {
        PEN = getPen(PS_SOLID, 2, RGB(116, 108, 107));
        fillcircle(x, y, size);
        PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255));
        fillcircle(x, y - 12, size - 60);
        PEN = getPen(PS_SOLID, 2, RGB(116, 108, 107));
        fillcircle(x, y - 12, size - 65);
        PEN = getPen(PS_SOLID, 3, RGB(255, 255, 255));
        //fillcircle(x, y+45, size-15);
        arc(x - 30 - 10, y + 45 - 30 + 10 + 10, x + 30 + 10, y + 45 + 30 + 10 - 10 + 10, x + 30 + 10, y + 45 + 10 + 10, x - 30 - 10, y + 45 + 10 + 10);
        drawText(x - 16, y - 24 + 25, a, 255, 255, 255);
    }
    void add(int r, int g, int b)
    {
        PEN = getPen(PS_SOLID, 2, RGB(r, g, b));
        fillcircle(x, y, size);
        PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255));
        fillcircle(x, y - 12, size - 60);
        PEN = getPen(PS_SOLID, 2, RGB(r, g, b));
        fillcircle(x, y - 12, size - 65);
        PEN = getPen(PS_SOLID, 3, RGB(255, 255, 255));
        //fillcircle(x, y+45, size-15);
        arc(x - 30 - 10, y + 45 - 30 + 10 + 10, x + 30 + 10, y + 45 + 30 + 10 - 10 + 10, x + 30 + 10, y + 45 + 10 + 10, x - 30 - 10, y + 45 + 10 + 10);
        drawText(x - 16, y - 24 + 25, a, 255, 255, 255);
    }
};
void xuat_ra(char const* A[])
{
    int x = -110; int y = 400 - 10;
    PEN = getPen(PS_SOLID, 15, RGB(255, 214, 109));
    fillbigrectangle(150 + x + 50, 100 + y + 200 - 50, 900 + x, y + 500 - 50 + 100 + 80);
    fillcircle(x + 200 + 50, y + 500 - 50 + 100 + 80, 100);
    fillcircle(x + 850, y + 500 - 50 + 100 + 80, 100);
    fillbigrectangle(x + 200 + 50, y + 500 - 50 + 80, x + 850, y + 550 + 50 + 80);
    fillcircle(x + 200 + 50, y + 250, 100);
    fillcircle(x + 850, y + 250, 100);
    fillbigrectangle(x + 200 + 50, y + 250 - 50, x + 850, y + 250);
    // drawText(x + 300 - 16-20, y + 300 - 27-50, "DANH SACH DE CU", 114, 161, 157);
    RECT pos1;
    pos1.left = x + 300 - 16 - 20 + 500 - 50 - 30;
    pos1.top = y + 300 - 27 - 50 + 500 - 30 - 30 - 50;
    pos1.right = 300;
    pos1.bottom = 300;
    printText("DANH SACH DE CU", pos1, 30, 11, 31, 58, 255, 214, 109);
    PEN = getPen(PS_SOLID, 15, RGB(202, 154, 104));
    fillrectangle(150 + x + 50 + 50, y + 300, 900 + x - 50, y + 350);
    drawText(x + 550 - 16, y + 325 - 27, A[0], 255, 255, 255);
    drawText(x + 550 - 16 - 200, y + 325 - 27, "1.     ", 255, 255, 255);
    fillrectangle(150 + x + 50 + 50, y + 350 + 20, 900 + x - 50, y + 400 + 20);
    drawText(x + 550 - 16, y + 325 - 27 + 70, A[1], 255, 255, 255);
    drawText(x + 550 - 16 - 200, y + 325 - 27 + 70, "2.     ", 255, 255, 255);
    fillrectangle(150 + x + 50 + 50, y + 400 + 40, 900 + x - 50, y + 450 + 40);
    drawText(x + 550 - 16, y + 325 - 27 + 140, A[2], 255, 255, 255);
    drawText(x + 550 - 16 - 200, y + 325 - 27 + 140, "3.     ", 255, 255, 255);
    fillrectangle(150 + x + 50 + 50, y + 450 + 60, 900 + x - 50, y + 500 + 60);
    drawText(x + 550 - 16, y + 325 - 27 + 210, A[3], 255, 255, 255);
    drawText(x + 550 - 16 - 200, y + 325 - 27 + 210, "4.     ", 255, 255, 255);
    fillrectangle(150 + x + 50 + 50, y + 500 + 80, 900 + x - 50, y + 550 + 80);
    drawText(x + 550 - 16, y + 325 - 27 + 280, A[4], 255, 255, 255);
    drawText(x + 550 - 16 - 200, y + 325 - 27 + 280, "5.     ", 255, 255, 255);
}
void back_ground()
{
    gotoxy(35, 14);
    Sleep(1);
    int x = -110, y = -10;
    PEN = getPen(PS_SOLID, 15, RGB(11, 31, 58));
    fillbigrectangle(0, 0, 2400, 1500);
    PEN = getPen(PS_SOLID, 15, RGB(255, 255, 255));
    fillbigrectangle(1100 + x, 100 + y + 200 - 50, 2300 + x, 1400 + y - 100 - 100);
    fillcircle(1100 + x + 50, 1400 + y - 100 - 100, 100);
    fillcircle(2300 + x - 50, 1400 + y - 100 - 100, 100);
    fillbigrectangle(1100 + x + 50, 1400 + y - 100 - 100, 2300 + x - 50, 1400 + y - 100 - 100 + 50);
    PEN = getPen(PS_SOLID, 15, RGB(202, 154, 104));//Màu trên -10
    fillcircle(1100 + x + 50, y + 300 - 50, 100);
    fillcircle(2300 + x - 50, y + 300 - 50, 100);
    fillbigrectangle(1100 + x + 50, y + 250 - 50, 2300 + x - 50, y + 350 - 50);
    //drawText(x + 1550 - 15 + 30 + 30 + 30, y + 250 - 24, "BIEU DO TUONG TAC", 106, 153, 150);
    RECT pos1;
    pos1.left = x + 1550 - 15 + 30 + 30 + 30 + 500 - 50 - 30 + 1000 - 50;
    pos1.top = y + 250 - 24 - 30 - 30 - 50 + 30 + 30 + 20 + 10;
    pos1.right = 300;
    pos1.bottom = 300;
    printText("BIEU DO TUONG TAC", pos1, 30, 11, 31, 58, 202, 154, 104);
    PEN = getPen(PS_SOLID, 15, RGB(255, 214, 109));
    fillbigrectangle(150 + x + 50, 100 + y + 200 - 50, 900 + x, y + 500 - 50);
    fillcircle(x + 200 + 50, y + 500 - 50, 100);
    fillcircle(x + 850, y + 500 - 50, 100);
    fillbigrectangle(x + 200 + 50, y + 500 - 50, x + 850, y + 550 - 50);
    fillcircle(x + 200 + 50, y + 250, 100);
    fillcircle(x + 850, y + 250, 100);
    fillbigrectangle(x + 200 + 50, y + 250 - 50, x + 850, y + 250);
    //drawText(x + 300 - 16, y + 300 - 27, "CONNECT", 114, 161, 157);
   // drawText(x + 300 - 16, y + 300 - 17 + 100 + 20, "NAME: ", 154, 201, 197);
    RECT pos2;
    pos2.left = x + 300 - 16 + 500 - 50 - 30 + 1000 - 50 - 500 - 500;
    pos2.top = y + 300 - 27 - 30 - 30 - 50 + 30 + 30 + 20 + 10;
    pos2.right = 300;
    pos2.bottom = 300;
    printText("CONNECT", pos2, 40, 11, 31, 58, 255, 214, 109);
    RECT pos3;
    pos3.left = x + 300 - 16 + 30 + 500 - 50 - 30 + 1000 - 50 - 1500;
    pos3.top = y + 300 - 17 + 100 + 20 + 30 - 30 - 50 + 30 + 30 + 20 + 10 + 100;
    pos3.right = 300;
    pos3.bottom = 300;
    printText("NAME:", pos3, 25, 11, 31, 58, 255, 214, 109);
    PEN = getPen(PS_SOLID, 15, RGB(202, 154, 104));
    fillcircle(x + 400, y + 420, 20);
    fillcircle(x + 800, y + 420, 20);
    fillrectangle(x + 400, y + 420 - 10, x + 800, y + 420 + 10);
}
void mang_xa_hoi(char& nhap_ban_phim)
{
    Priority_queue Luu_KQ;
    Luu_KQ.init();

    vector<ii> KQ;

    int p_start, p_end, distance;
    List ways;
    ways.init();

    number_point = 20;
    number_way = 30;
    ways.push_back(2, 3, 5); ways.push_back(3, 4, 7); ways.push_back(4, 7, 6);
    ways.push_back(1, 5, 6); ways.push_back(7, 10, 8); ways.push_back(5, 10, 3);
    ways.push_back(2, 6, 9); ways.push_back(6, 9, 20); ways.push_back(9, 12, 14);
    ways.push_back(7, 13, 8); ways.push_back(12, 13, 18); ways.push_back(13, 17, 13);
    ways.push_back(8, 14, 18); ways.push_back(16, 20, 17); ways.push_back(11, 15, 19);
    ways.push_back(11, 19, 16); ways.push_back(4, 1, 5); ways.push_back(7, 5, 6);
    ways.push_back(11, 6, 14); ways.push_back(19, 15, 12); ways.push_back(15, 12, 6);
    ways.push_back(19, 18, 18); ways.push_back(18, 12, 11); ways.push_back(18, 16, 7);
    ways.push_back(9, 4, 17); ways.push_back(16, 13, 14); ways.push_back(13, 10, 5);
    ways.push_back(10, 8, 9); ways.push_back(17, 14, 13); ways.push_back(20, 17, 19);


    for (int i = 1; i <= number_point; i++)
    {
        List_road[i].init();
        a[i].init();
    }

    Node* temp = new Node;
    temp = ways.peek();
    while (number_way > 1)
    {
        p_start = temp->p_start;
        p_end = temp->p_end;
        distance = temp->distance;
        //d[p_start][p_end] = d[p_end][p_start] = temp->distance;
        List_road[p_start].push(distance, p_end);
        List_road[p_end].push(distance, p_start);
        number_way--;
        temp = temp->next;
    }
    //d[p_start][p_end] = d[p_end][p_start] = temp->distance;
    p_start = temp->p_start;
    p_end = temp->p_end;
    distance = temp->distance;
    List_road[p_start].push(distance, p_end);
    List_road[p_end].push(distance, p_start);

    /*for(int i=0;i<=number_point;i++)
    {

        for(int j=0;j<=number_point;j++)
        {
            if(i==0)
            {
                string s = to_string(j);
                while(s.length()<=4)
                    s+= " ";
                cout << s ;
            }
            else if(j==0)
            {
                string s = to_string(i);
                while(s.length()<=4)
                    s+= " ";
                cout << s ;
            }
            else
            {
                string s = to_string(d[i][j]);
                while(s.length()<=4)
                    s+= " ";
                cout << s ;
            }
        }
        std::cout<<std::endl<<std::endl;
    }*/

    /*Node* temp1 = List_road[first_point].top;
    while(temp1!=NULL)
    {
        dem++;
        temp1 = temp1->next;
    }
    dem++;*/



    /*cout<<endl<<dem<<endl;
    while(dem>0)
    {
        Luu_KQ.top = Luu_KQ.top->next;
        dem--;
    }
    dem = 5;
    cout<<endl;
    while(dem>0)
    {
        cout<<Luu_KQ.peek()->p_end<<"  ";
        Luu_KQ.pop();
        dem--;
    }*/

    // cout<<"d("<<first_point<<"->"<<second_point<<")"<<" = "<<s_min[second_point]<<"\t";

    // truy_vet(second_point, first_point);

    /*dijkstra();
    for (int i = 1; i <= number_point; i++)
    {
        cout<<"d(1->"<<i<<")"<<" = "<<s_min[i]<<"\t";
        truy_vet(i);
        cout<<endl;
    }*/


    class Conect
    {
    public:
        int x1, y1, x2, y2;
        int lechx, lechy;
        const char* TS;
        int tdx, tdy;
        Conect(User A, User B, const char* ts)
        {
            x1 = A.x; y1 = A.y;
            x2 = B.x; y2 = B.y;
            TS = ts;
            tdx = (x1 + x2) / 2; tdy = (y1 + y2) / 2;
            int canh_huyen = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
            lechx = (A.size - 40) * (abs(x2 - x1)) / (canh_huyen);
            lechy = (A.size - 40) * (abs(y2 - y1)) / (canh_huyen);
        }
        Conect() {}
        void add()
        {
            PEN = getPen(PS_SOLID, 10, RGB(200, 200, 200));
            if (x1 <= x2 && y1 <= y2)
            {
                line(x1 + lechx, y1 + lechy, x2 - lechx, y2 - lechy);
            }
            else
            {
                line(x1 + lechx, y1 - lechy, x2 - lechx, y2 + lechy);
            }
            PEN = getPen(PS_SOLID, 10, RGB(150, 150, 150));
            fillcircle(tdx, tdy, 15);
            //fillrectangle(tdx - 5, tdy - 5, tdx + 18, tdy + 5);
            drawText(tdx - 16, tdy - 24, TS, 0, 0, 0);
        }
        void add(int r, int g, int b)
        {
            PEN = getPen(PS_SOLID, 10, RGB(r, g, b));
            if (x1 <= x2 && y1 <= y2)
            {
                line(x1 + lechx, y1 + lechy, x2 - lechx, y2 - lechy);
            }
            else
            {
                line(x1 + lechx, y1 - lechy, x2 - lechx, y2 + lechy);
            }
            PEN = getPen(PS_SOLID, 10, RGB(150, 150, 150));
            fillcircle(tdx, tdy, 15);
            drawText(tdx - 16, tdy - 24, TS, 0, 0, 0);
        }

    };
    class Emoji_Like
    {
    public:
        int x, y;
        Emoji_Like(User X)
        {
            x = X.x + 35 + 10;
            y = X.y - 50 - 5 - 10;
        }
        void add()
        {
            PEN = getPen(PS_SOLID, 3, RGB(87, 140, 252));
            fillcircle(x + 15, y + 5, 48);
            PEN = getPen(PS_SOLID, 3, RGB(255, 255, 255));
            fillrectangle(x, y, x + 6, y + 16);
            fillrectangle(x + 10, y, x + 24, y + 16);
            fillrectangle(x + 24, y, x + 27, y + 4); fillcircle(x + 27, y + 2, 4);
            fillrectangle(x + 24, y + 4, x + 26, y + 8); fillcircle(x + 26, y + 6, 4);
            fillrectangle(x + 24, y + 8, x + 25, y + 12); fillcircle(x + 25, y + 10, 4);
            fillrectangle(x + 24, y + 12, x + 25, y + 16); fillcircle(x + 24, y + 14, 4);
            line(x + 10, y, x + 18, y - 8); line(x + 18, y, x + 22, y - 8);
            fillcircle(x + 21, y - 8, 4);
            line(x + 10, y, x + 18, y);
            line(x + 12, y - 2, x + 19, y - 2);
            line(x + 15, y - 4, x + 20, y - 4);
            line(x + 17, y - 6, x + 21, y - 6);
        }

    };
    class Emoji_Love
    {
    public:
        int x, y;
        Emoji_Love(User X)
        {
            x = X.x + 50 - 6 + 10;
            y = X.y - 50 - 3 - 10;
        }
        void add()
        {
            PEN = getPen(PS_SOLID, 3, RGB(247, 81, 101));
            fillcircle(x + 6, y + 3, 48);
            PEN = getPen(PS_SOLID, 3, RGB(255, 255, 255));
            fillcircle(x, y, 12);
            fillcircle(x + 12, y, 12);
            line(x - 5, y + 2, x + 6, y + 16); line(x + 17, y + 2, x + 6, y + 16);
            line(x - 5, y + 3, x + 17, y + 3);
            line(x - 2, y + 6, x + 14, y + 6);
            line(x + 1, y + 9, x + 11, y + 9);
            line(x + 4, y + 12, x + 8, y + 12);
            line(x + 6, y + 15, x + 6, y + 15);
        }
    };
    class Emoji_Wow
    {
    public:
        int x, y;
        Emoji_Wow(User X)
        {
            x = X.x + 50 + 10 + 10;
            y = X.y - 50 - 10 - 10;
        }
        void add()
        {
            PEN = getPen(PS_SOLID, 4, RGB(0, 0, 0));
            fillcircle(x, y, 50);
            PEN = getPen(PS_SOLID, 3, RGB(254, 218, 108));
            fillcircle(x, y, 48);
            PEN = getPen(PS_SOLID, 3, RGB(39, 45, 57));
            fillellip(x - 6, y + 34, x + 6, y + 50);
            fillellip(x - 15, y - 3 + 26, x - 9, y + 6 + 26);
            fillellip(x + 9, y - 3 + 26, x + 15, y + 6 + 26);
            PEN = getPen(PS_SOLID, 2, RGB(39, 45, 57));
            arc(x - 15, y - 9 + 26, x - 9, y + 2 + 26, x - 10, y - 9 + 26, x - 15, y - 9 + 26);
            arc(x + 9, y - 9 + 26, x + 15, y + 2 + 26, x + 15, y - 9 + 26, x + 10, y - 9 + 26);
        }
    };
    class say_hi
    {
    public:
        int x, y;
        say_hi(User X)
        {
            x = X.x + 50;
            y = X.y - 50;
        }
        void add()
        {
            PEN = getPen(PS_SOLID, 3, RGB(87, 140, 252));
            fillcircle(x, y, 48);
            drawText(x - 5 - 16, y - 24, "Hi", 255, 255, 255);

        }
    };
    class o_xuat
    {
    public:
        int x, y;
        const char* a;
        o_xuat(int X, int Y, const char* A)
        {
            a = A;
            x = X; y = Y;
        }
        void add()
        {
            for (int i = -300; i <= 0; i = i + 10)
            {
                if (i < -100)
                {
                    Sleep(50);
                }
                else
                {
                    Sleep(100);
                }
                PEN = getPen(PS_SOLID, 3, RGB(87, 140, 252));
                fillrectangle(x + i, y, x + 300 + i, y + 100);
                PEN = getPen(PS_SOLID, 3, RGB(255, 255, 252));
                fillcircle(x + 50 + i, y + 50, 50);
                drawText(x + 50 - 16 + i, y + 50 - 24, a, 0, 0, 0);
            }
        }
    };
    back_ground();
    int Ox = -250;
    int Oy = -50;
    User A(1450 - Ox, 350 - Oy, 100, "A"); A.add(); User B(800 - Ox, 400 - Oy, 100, "B"); B.add(); User C(1050 - Ox, 400 - Oy, 100, "C"); C.add();
    User D(1250 - Ox, 450 - Oy, 100, "D"); D.add(); User E(1650 - Ox, 450 - Oy, 100, "E"); E.add(); User F(950 - Ox, 550 - Oy, 100, "F"); F.add();
    User G(1450 - Ox, 550 - Oy, 100, "G"); G.add(); User H(1800 - Ox, 550 - Oy, 100, "H"); H.add(); User I(1150 - Ox, 600 - Oy, 100, "I"); I.add();
    User J(1650 - Ox, 700 - Oy, 100, "J"); J.add(); User K(850 - Ox, 750 - Oy, 100, "K"); K.add(); User L(1250 - Ox, 750 - Oy, 100, "L"); L.add();
    User M(1450 - Ox, 800 - Oy, 100, "M"); M.add(); User N(1850 - Ox, 800 - Oy, 100, "N"); N.add(); User O(1050 - Ox, 850 - Oy, 100, "O"); O.add();
    User P(1350 - Ox, 950 - Oy, 100, "P"); P.add(); User Q(1650 - Ox, 950 - Oy, 100, "Q"); Q.add(); User R(1150 - Ox, 1000 - Oy, 100, "R"); R.add();
    User S(950 - Ox, 1050 - Oy, 100, "S"); S.add(); User T(1500 - Ox, 1100 - Oy, 100, "T"); T.add();

    Conect BC(B, C, "5"); BC.add(); Conect CD(C, D, "7"); CD.add(); Conect DG(D, G, "6"); DG.add();
    Conect AE(A, E, "6"); AE.add(); Conect GJ(G, J, "8"); GJ.add(); Conect EJ(E, J, "3"); EJ.add();
    Conect BF(B, F, "9"); BF.add(); Conect FI(F, I, "20"); FI.add(); Conect IL(I, L, "14"); IL.add();
    Conect GM(G, M, "8"); GM.add(); Conect LM(L, M, "18"); LM.add(); Conect MQ(M, Q, "13"); MQ.add();
    Conect HN(H, N, "18"); HN.add(); Conect PT(P, T, "17"); PT.add(); Conect KO(K, O, "19"); KO.add();
    Conect KS(K, S, "16"); KS.add(); Conect DA(D, A, "5"); DA.add(); Conect GE(G, E, "6"); GE.add();
    Conect KF(K, F, "14"); KF.add(); Conect SO(S, O, "12"); SO.add(); Conect OL(O, L, "6"); OL.add();
    Conect SR(S, R, "18"); SR.add(); Conect RL(R, L, "11"); RL.add(); Conect RP(R, P, "7"); RP.add();
    Conect ID(I, D, "17"); ID.add(); Conect PM(P, M, "14"); PM.add(); Conect MJ(M, J, "5"); MJ.add();
    Conect JH(J, H, "9"); JH.add(); Conect QN(Q, N, "13"); QN.add(); Conect TQ(T, Q, "19"); TQ.add();

    int dem = 0;
    int first_point;
    char test;
    cin >> test;
    gotoxy(0, 0);
    PEN = getPen(PS_SOLID, 15, RGB(11, 31, 58));
    Sleep(1);
    fillrectangle(0, 0, 50, 550);
    Sleep(1);
    first_point = (int)(test)-64;
    dijkstra(first_point);
    int luu_tru[100][100];
    for (int i = 1; i <= number_point; i++)
    {
        Luu_KQ.push(s_min[i], i);
        truy_vet(i, first_point, luu_tru);
    }

    Node* temp1 = Luu_KQ.top;
    while (temp1 != NULL)
    {
        KQ.push_back(ii(temp1->distance, temp1->p_end));
        temp1 = temp1->next;
    }

    Node* temp2 = List_road[first_point].top;
    while (temp2 != NULL)
    {
        std::vector<ii>::iterator it;
        it = find(KQ.begin(), KQ.end(), ii(temp2->distance, temp2->p_end));
        int temp = it - KQ.begin();
        KQ.erase(KQ.begin() + temp);
        temp2 = temp2->next;
    }
    KQ.erase(KQ.begin());
    dem = 5;
    int ket_qua[100];
    int ket_qua_lenght = 0;
    while (dem > 0)
    {
        ket_qua[ket_qua_lenght] = KQ.front().second;
        ket_qua_lenght++;
        KQ.erase(KQ.begin());
        dem--;
    }
    int xu_li_so_lieu[100][100];
    int mang_lenght_xu_li[100];
    for (int i = 0; i < ket_qua_lenght; i++)
    {
        int kq = ket_qua[i];
        for (int j = 0; j < number_point; j++)
        {
            if (kq == luu_tru[j][0])
            {
                mang_lenght_xu_li[i] = luu_tru[j][1];
                for (int k = 0; k < mang_lenght_xu_li[i]; k++)
                {
                    xu_li_so_lieu[i][k] = luu_tru[j][k + 2];
                }
            }
        }
    }
    User de_cu_user[100][100];
    Conect de_cu_conect[100][100];
    int bang_mau_RGB[15] = { 255,0,0,255,193,0,255,235,0,50,205,50,50,50,205 };
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < mang_lenght_xu_li[i]; j++)
        {
            switch (xu_li_so_lieu[i][j])
            {
            case 1:
                de_cu_user[i][j] = A;
                break;
            case 2:
                de_cu_user[i][j] = B;
                break;
            case 3:
                de_cu_user[i][j] = C;
                break;
            case 4:
                de_cu_user[i][j] = D;
                break;
            case 5:
                de_cu_user[i][j] = E;
                break;
            case 6:
                de_cu_user[i][j] = F;
                break;
            case 7:
                de_cu_user[i][j] = G;
                break;
            case 8:
                de_cu_user[i][j] = H;
                break;
            case 9:
                de_cu_user[i][j] = I;
                break;
            case 10:
                de_cu_user[i][j] = J;
                break;
            case 11:
                de_cu_user[i][j] = K;
                break;
            case 12:
                de_cu_user[i][j] = L;
                break;
            case 13:
                de_cu_user[i][j] = M;
                break;
            case 14:
                de_cu_user[i][j] = N;
                break;
            case 15:
                de_cu_user[i][j] = O;
                break;
            case 16:
                de_cu_user[i][j] = P;
                break;
            case 17:
                de_cu_user[i][j] = Q;
                break;
            case 18:
                de_cu_user[i][j] = R;
                break;
            case 19:
                de_cu_user[i][j] = S;
                break;
            case 20:
                de_cu_user[i][j] = T;
                break;
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < mang_lenght_xu_li[i] - 1; j++)
        {
            if ((de_cu_user[i][j].a == B.a && de_cu_user[i][j + 1].a == C.a) || (de_cu_user[i][j].a == C.a && de_cu_user[i][j + 1].a == B.a))
            {
                de_cu_conect[i][j] = BC;
            }
            if ((de_cu_user[i][j].a == C.a && de_cu_user[i][j + 1].a == D.a) || (de_cu_user[i][j + 1].a == C.a && de_cu_user[i][j].a == D.a))
            {
                de_cu_conect[i][j] = CD;
            }
            if ((de_cu_user[i][j].a == D.a && de_cu_user[i][j + 1].a == G.a) || (de_cu_user[i][j + 1].a == D.a && de_cu_user[i][j].a == G.a))
            {
                de_cu_conect[i][j] = DG;
            }
            if ((de_cu_user[i][j].a == A.a && de_cu_user[i][j + 1].a == E.a) || (de_cu_user[i][j + 1].a == A.a && de_cu_user[i][j].a == E.a))
            {
                de_cu_conect[i][j] = AE;
            }
            if ((de_cu_user[i][j].a == G.a && de_cu_user[i][j + 1].a == J.a) || (de_cu_user[i][j + 1].a == G.a && de_cu_user[i][j].a == J.a))
            {
                de_cu_conect[i][j] = GJ;
            }
            if ((de_cu_user[i][j].a == E.a && de_cu_user[i][j + 1].a == J.a) || (de_cu_user[i][j + 1].a == E.a && de_cu_user[i][j].a == J.a))
            {
                de_cu_conect[i][j] = EJ;
            }
            if ((de_cu_user[i][j].a == B.a && de_cu_user[i][j + 1].a == F.a) || (de_cu_user[i][j + 1].a == B.a && de_cu_user[i][j].a == F.a))
            {
                de_cu_conect[i][j] = BF;
            }
            if ((de_cu_user[i][j].a == F.a && de_cu_user[i][j + 1].a == I.a) || (de_cu_user[i][j + 1].a == F.a && de_cu_user[i][j].a == I.a))
            {
                de_cu_conect[i][j] = FI;
            }
            if ((de_cu_user[i][j].a == I.a && de_cu_user[i][j + 1].a == L.a) || (de_cu_user[i][j + 1].a == I.a && de_cu_user[i][j].a == L.a))
            {
                de_cu_conect[i][j] = IL;
            }
            if ((de_cu_user[i][j].a == G.a && de_cu_user[i][j + 1].a == M.a) || (de_cu_user[i][j + 1].a == G.a && de_cu_user[i][j].a == M.a))
            {
                de_cu_conect[i][j] = GM;
            }
            if ((de_cu_user[i][j].a == L.a && de_cu_user[i][j + 1].a == M.a) || (de_cu_user[i][j + 1].a == L.a && de_cu_user[i][j].a == M.a))
            {
                de_cu_conect[i][j] = LM;
            }
            if ((de_cu_user[i][j].a == M.a && de_cu_user[i][j + 1].a == Q.a) || (de_cu_user[i][j + 1].a == M.a && de_cu_user[i][j].a == Q.a))
            {
                de_cu_conect[i][j] = MQ;
            }
            if ((de_cu_user[i][j].a == H.a && de_cu_user[i][j + 1].a == N.a) || (de_cu_user[i][j + 1].a == H.a && de_cu_user[i][j].a == N.a))
            {
                de_cu_conect[i][j] = HN;
            }
            if ((de_cu_user[i][j].a == P.a && de_cu_user[i][j + 1].a == T.a) || (de_cu_user[i][j + 1].a == P.a && de_cu_user[i][j].a == T.a))
            {
                de_cu_conect[i][j] = PT;
            }
            if ((de_cu_user[i][j].a == K.a && de_cu_user[i][j + 1].a == O.a) || (de_cu_user[i][j + 1].a == K.a && de_cu_user[i][j].a == O.a))
            {
                de_cu_conect[i][j] = KO;
            }
            if ((de_cu_user[i][j].a == K.a && de_cu_user[i][j + 1].a == S.a) || (de_cu_user[i][j + 1].a == K.a && de_cu_user[i][j].a == S.a))
            {
                de_cu_conect[i][j] = KS;
            }
            if ((de_cu_user[i][j].a == D.a && de_cu_user[i][j + 1].a == A.a) || (de_cu_user[i][j + 1].a == D.a && de_cu_user[i][j].a == A.a))
            {
                de_cu_conect[i][j] = DA;
            }
            if ((de_cu_user[i][j].a == G.a && de_cu_user[i][j + 1].a == E.a) || (de_cu_user[i][j + 1].a == G.a && de_cu_user[i][j].a == E.a))
            {
                de_cu_conect[i][j] = GE;
            }
            if ((de_cu_user[i][j].a == K.a && de_cu_user[i][j + 1].a == F.a) || (de_cu_user[i][j + 1].a == K.a && de_cu_user[i][j].a == F.a))
            {
                de_cu_conect[i][j] = KF;
            }
            if ((de_cu_user[i][j].a == S.a && de_cu_user[i][j + 1].a == O.a) || (de_cu_user[i][j + 1].a == S.a && de_cu_user[i][j].a == O.a))
            {
                de_cu_conect[i][j] = SO;
            }
            if ((de_cu_user[i][j].a == O.a && de_cu_user[i][j + 1].a == L.a) || (de_cu_user[i][j + 1].a == O.a && de_cu_user[i][j].a == L.a))
            {
                de_cu_conect[i][j] = OL;
            }
            if ((de_cu_user[i][j].a == S.a && de_cu_user[i][j + 1].a == R.a) || (de_cu_user[i][j + 1].a == S.a && de_cu_user[i][j].a == R.a))
            {
                de_cu_conect[i][j] = SR;
            }
            if ((de_cu_user[i][j].a == R.a && de_cu_user[i][j + 1].a == L.a) || (de_cu_user[i][j + 1].a == R.a && de_cu_user[i][j].a == L.a))
            {
                de_cu_conect[i][j] = RL;
            }
            if ((de_cu_user[i][j].a == R.a && de_cu_user[i][j + 1].a == P.a) || (de_cu_user[i][j + 1].a == R.a && de_cu_user[i][j].a == P.a))
            {
                de_cu_conect[i][j] = RP;
            }
            if ((de_cu_user[i][j].a == I.a && de_cu_user[i][j + 1].a == D.a) || (de_cu_user[i][j + 1].a == I.a && de_cu_user[i][j].a == D.a))
            {
                de_cu_conect[i][j] = ID;
            }
            if ((de_cu_user[i][j].a == P.a && de_cu_user[i][j + 1].a == M.a) || (de_cu_user[i][j + 1].a == P.a && de_cu_user[i][j].a == M.a))
            {
                de_cu_conect[i][j] = PM;
            }
            if ((de_cu_user[i][j].a == M.a && de_cu_user[i][j + 1].a == J.a) || (de_cu_user[i][j + 1].a == M.a && de_cu_user[i][j].a == J.a))
            {
                de_cu_conect[i][j] = MJ;
            }
            if ((de_cu_user[i][j].a == J.a && de_cu_user[i][j + 1].a == H.a) || (de_cu_user[i][j + 1].a == J.a && de_cu_user[i][j].a == H.a))
            {
                de_cu_conect[i][j] = JH;
            }
            if ((de_cu_user[i][j].a == Q.a && de_cu_user[i][j + 1].a == N.a) || (de_cu_user[i][j + 1].a == Q.a && de_cu_user[i][j].a == N.a))
            {
                de_cu_conect[i][j] = QN;
            }
            if ((de_cu_user[i][j].a == T.a && de_cu_user[i][j + 1].a == Q.a) || (de_cu_user[i][j + 1].a == T.a && de_cu_user[i][j].a == Q.a))
            {
                de_cu_conect[i][j] = TQ;
            }
        }
    }
    say_hi hi(de_cu_user[0][0]); hi.add();
    /*for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < mang_lenght_xu_li[i]; j++)
        {
            cout << de_cu_user[i][j].a;
        }
        cout << endl;
    }*/

    de_cu_user[0][0].tat_mo = 1;
    const char* mang_luu_ten[1000];
    for (int i = 0; i < 5; i++)
    {
        int j;
        for (j = 0; j < mang_lenght_xu_li[i]; j++)
        {
            if (de_cu_user[i][j].tat_mo == 0)
            {
                de_cu_user[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                Sleep(100);
            }
            if (j == mang_lenght_xu_li[i] - 1)
            {
                de_cu_user[i][j].tat_mo = 1;
                for (int i1 = 0; i1 < 5; i1++)
                {
                    for (int j1 = 0; j1 < mang_lenght_xu_li[i1]; j1++)
                    {
                        if (de_cu_user[i1][j1].a == de_cu_user[i][j].a)
                        {
                            de_cu_user[i1][j1].tat_mo = 1;
                        }
                    }
                }
                de_cu_user[i][j].tat_mo = 1;
            }
            if (j != mang_lenght_xu_li[i] - 1)
            {
                de_cu_conect[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                Sleep(100);
            }
        }
        if (i % 3 == 0)
        {
            Emoji_Like like(de_cu_user[i][mang_lenght_xu_li[i] - 1]); like.add();
        }
        else if (i % 3 == 1)
        {
            Emoji_Love love(de_cu_user[i][j - 1]); love.add();
        }
        else
        {
            Emoji_Wow wow(de_cu_user[i][j - 1]); wow.add();
        }
        mang_luu_ten[i] = de_cu_user[i][j - 1].a;
        for (j = 0; j < mang_lenght_xu_li[i] - 1; j++)
        {
            if (j != 0 && de_cu_user[i][j].tat_mo == 0)
            {
                de_cu_user[i][j].add();
                Sleep(100);
            }
            de_cu_conect[i][j].add();
            Sleep(100);
        }
    }
    xuat_ra(mang_luu_ten);
    int x = -110; int y = 400 - 10 + 530;
    PEN = getPen(PS_SOLID, 15, RGB(255, 214, 109));
    fillbigrectangle(150 + x + 50 + 50, 100 + y + 200 - 50, 900 + x - 50, 100 + 100 + y + 200 - 50);
    fillcircle(150 + x + 50 + 50, 100 + y + 200 - 50 + 50, 100);
    fillcircle(900 + x - 50, 100 + y + 200 - 50 + 50, 100);
    PEN = getPen(PS_SOLID, 15, RGB(11, 31, 58));
    fillrectangle(x + 550 - 100, 100 + y + 200 - 50, x + 550 + 100, 100 + y + 200 - 50 + 50 + 50);
    PEN = getPen(PS_SOLID, 15, RGB(255, 214, 109));
    fillcircle(x + 550 - 100, 100 + y + 200 - 50 + 50, 100);
    //drawText(x + 350-16-30, 100 + y + 200 - 50 + 50-27, "RESET  (esc)", 106, 153, 150);
    RECT pos1;
    pos1.left = x + 350 - 16 - 30 + 30 + 30 + 500 - 50 - 30 + 1000 - 50 - 1200 - 250;
    pos1.top = y + 100 + y + 200 - 50 + 50 - 27 + 30 - 30 - 50 + 30 + 30 + 20 + 10 + 10;
    pos1.right = 300;
    pos1.bottom = 300;
    printText("RESET  (esc)", pos1, 25, 11, 31, 58, 255, 214, 109);
    fillcircle(x + 550 + 100, 100 + y + 200 - 50 + 50, 100);
    //drawText(x + 750-16-30, 100 + y + 200 - 50 + 50-27, "END  (x)", 106, 153, 150);
    RECT pos2;
    pos2.left = x + 750 - 16 - 30 + 30 + 30 + 500 - 50 - 30 + 1000 - 50 - 1200 - 250 + 300 + 100;
    pos2.top = 100 + y + 200 + y - 50 + 50 - 27 + 30 - 30 - 50 + 30 + 30 + 20 + 10 + 10;
    pos2.right = 300;
    pos2.bottom = 300;
    printText("END  (x)", pos2, 25, 11, 31, 58, 255, 214, 109);
    nhap_ban_phim = _getch();
    int i = 0, j = -1;
    while (nhap_ban_phim != 'x')
    {
        for (j = 0; j < mang_lenght_xu_li[i] - 1; j++)
        {
            if (j != 0 && de_cu_user[i][j].tat_mo == 0)
            {
                de_cu_user[i][j].add();
                Sleep(100);
            }
            de_cu_conect[i][j].add();
            Sleep(100);
        }
        if (nhap_ban_phim != '1' && nhap_ban_phim != '2' && nhap_ban_phim != '3' && nhap_ban_phim != '4' && nhap_ban_phim != '5')
        {
            break;
            mang_xa_hoi(nhap_ban_phim);
        }
        if (nhap_ban_phim == '1')
        {
            i = 0;
            for (j = 0; j < mang_lenght_xu_li[i]; j++)
            {
                if (de_cu_user[i][j].tat_mo == 0)
                {
                    de_cu_user[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
                if (j != mang_lenght_xu_li[i] - 1)
                {
                    de_cu_conect[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
            }
            nhap_ban_phim = _getch();
            continue;
        }
        if (nhap_ban_phim == '2')
        {
            i = 1;
            for (j = 0; j < mang_lenght_xu_li[i]; j++)
            {
                if (de_cu_user[i][j].tat_mo == 0)
                {
                    de_cu_user[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
                if (j != mang_lenght_xu_li[i] - 1)
                {
                    de_cu_conect[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
            }
            nhap_ban_phim = _getch();
            continue;
        }
        if (nhap_ban_phim == '3')
        {
            i = 2;
            for (j = 0; j < mang_lenght_xu_li[i]; j++)
            {
                if (de_cu_user[i][j].tat_mo == 0)
                {
                    de_cu_user[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
                if (j != mang_lenght_xu_li[i] - 1)
                {
                    de_cu_conect[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
            }
            nhap_ban_phim = _getch();
            continue;
        }
        if (nhap_ban_phim == '4')
        {
            i = 3;
            for (j = 0; j < mang_lenght_xu_li[i]; j++)
            {
                if (de_cu_user[i][j].tat_mo == 0)
                {
                    de_cu_user[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
                if (j != mang_lenght_xu_li[i] - 1)
                {
                    de_cu_conect[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
            }
            nhap_ban_phim = _getch();
            continue;
        }
        if (nhap_ban_phim == '5')
        {
            i = 4;
            for (j = 0; j < mang_lenght_xu_li[i]; j++)
            {
                if (de_cu_user[i][j].tat_mo == 0)
                {
                    de_cu_user[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
                if (j != mang_lenght_xu_li[i] - 1)
                {
                    de_cu_conect[i][j].add(bang_mau_RGB[i * 3 + 0], bang_mau_RGB[i * 3 + 1], bang_mau_RGB[i * 3 + 2]);
                    Sleep(100);
                }
            }
            nhap_ban_phim = _getch();
            continue;
        }
    }
}
class i_con
{
public:
    int x, y;
    i_con(int X, int Y)
    {
        x = X;
        y = Y;
    }
    void add()
    {
        PEN = getPen(PS_SOLID, 15, RGB(11, 31, 58));
        fillcircle(x, y - 60, 15);
        for (int i = 0; i < 25; i++)
        {
            arc(x - 24 + i + 5, y - 15 + 5, x + 25 - i - 5, y + 45 + 5, x + 25 + i, y + 15, x - 25 - i, y + 15);
        }

    }
};

int main()
{
    int k;
    initgraph();
    int a = 11, b = 31, c = 58;
    for (int i = 0; i < 98; i++)
    {
        a = (int)((float)a + 2.44);
        b = (int)((float)b + 1.83);
        c = (int)((float)c + 0.51);
        PEN = getPen(PS_SOLID, 15, RGB(a, b, c));
        circle(450, 700, 1700 - 20 * i);
        Sleep(10);
    }
    int x = 400; int y = 770;
    i_con logo1(x, y), logo2(x + 100, y), logo3(x + 50, y - 86);
    logo1.add(); logo2.add(); logo3.add();
    RECT pos1;
    pos1.left = x + 300 - 16 - 20 + 500 - 50 - 30 - 500 + 10;
    pos1.top = y + 300 - 27 - 50 + 500 - 30 - 30 - 50 + 50 + 30;
    pos1.right = 300;
    pos1.bottom = 300;
    printText("CONNECT", pos1, 40, a, b, c, 11, 31, 58);
    Sleep(20);
    RECT pos2;
    pos2.left = x + 300 - 16 - 20 + 500 - 50 - 30 - 500 + 10;
    pos2.top = y + 300 - 27 - 50 + 500 - 30 - 30 - 50 + 50 + 30 + 200;
    pos2.right = 300;
    pos2.bottom = 300;
    printText("Open full screen mode and press enter", pos2, 30, 0, 0, 0, 255, 255, 255);
    _getch();
    Sleep(100);


    while (true)
    {
        char ket_thuc;
        mang_xa_hoi(ket_thuc);
        if (ket_thuc == 'x')
        {
            PEN = getPen(PS_SOLID, 15, RGB(33, 36, 77));
            rectangle(0, 0, 2400, 1500);
            return 0;
        }
        system("cls");
    }
    return 0;
}