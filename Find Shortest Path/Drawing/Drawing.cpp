#include "graphics.h"
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ostream>
#include <string>
using namespace std;


int dolechx = 17;
int dolechy = 24;
//int r = 255;
//int b = 255;
//int g = 255;
int color = 10;
int sizecolor;

class point
{
    public:
        int x;
        int y;
        int size;
        const char* name;

        point(int a, int b, int c, const char* d)
        {
            x = a;
            y = b;
            size = c;
            name = d;
        }

        point()
        {
        }

        void create()
        {
            setcolor(color, sizecolor);
            for(int i=size;i>=0;i--)
                circle(x, y, i);
            drawText(x-dolechx, y-dolechy, name);
        }
};

class Line
{
    public:
        point A;
        point B;
        int tbx = (A.x + B.x) / 2;
        int tby = (A.y + B.y) / 2;

        Line(point a, point b) : A(a), B(b)
        {
            A = a;
            B = b;
        }

        void create()
        {
            setcolor(color, sizecolor);
            line(A.x, A.y, B.x, B.y);
        }
};

const int oo = 10000;
//typedef pair<int, int> ii;

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
            {
                start = start->next;
            }
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
int D_size = 0;
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
        //D_size++;

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

void truy_vet(int v, int first_point, int mang[], int& lenghtm)
{
    int u = v;
    while (u != first_point)
    {
        a[v].push(u);
        u = From[u];
    }
    a[v].push(first_point);
    while (a[v].top->next != NULL)
    {
        mang[lenghtm] = a[v].peek()->p_start;
        lenghtm++;
        a[v].pop();
    }
    mang[lenghtm] = a[v].peek()->p_start;
    lenghtm++;
    a[v].pop();
}


int main()
{
    //THUẬT TOÁN
   
    int p_start, p_end, distance;
    List ways;
    ways.init();
    number_point = 11;
    number_way = 16;
    ways.push_back(1, 9, 5);
    ways.push_back(1, 2, 4);
    ways.push_back(1, 5, 7);
    ways.push_back(2, 8, 2);
    ways.push_back(5, 8, 8);
    ways.push_back(8, 10, 2);
    ways.push_back(5, 10, 9);
    ways.push_back(9, 3, 2);
    ways.push_back(9, 8, 5);
    ways.push_back(8, 3, 5);
    ways.push_back(8, 6, 6);
    ways.push_back(10, 11, 12);
    ways.push_back(6, 4, 9);
    ways.push_back(3, 6, 7);
    ways.push_back(3, 7, 7);
    ways.push_back(7, 4, 7);

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
    //free(temp);

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

    // VẼ
    while(true)
    {
        //r = 255; g = 255; b = 0;
        //color = 10;
        int kc = 400;
        initgraph();
        color = 15;
        sizecolor = 2;

        //Khoi tao point

        point _1(50 + kc, 200, 50, "1");
        point _2(150 + kc, 300, 50, "2");
        point _3(250 + kc, 50, 50, "3");
        point _4(500 + kc, 250, 50, "4");
        point _5(150 + kc, 450, 50, "5");
        point _6(400 + kc, 150, 50, "6");
        point _7(450 + kc, 50, 50, "7");
        point _8(250 + kc, 250, 50, "8");
        point _9(150 + kc, 100, 50, "9");
        point _10(350 + kc, 400, 50, "10");
        point _11(500 + kc, 350, 50, "11");


        //Khoi tao line va ve line + trong so
        // VANDE: Duong KA khong giong mau cac duong khac
        Line _1_2(_1, _2); _1_2.create(); drawText(_1_2.tbx - dolechx + 10, _1_2.tby - dolechy - 10, "4");
        Line _1_5(_1, _5); _1_5.create(); drawText(_1_5.tbx - dolechx - 7, _1_5.tby - dolechy + 11, "7");
        Line _1_9(_1, _9); _1_9.create(); drawText(_1_9.tbx - dolechx - 9, _1_9.tby - dolechy - 9, "5");
        Line _2_8(_2, _8); _2_8.create(); drawText(_2_8.tbx - dolechx - 8, _2_8.tby - dolechy - 9, "2");
        Line _3_6(_3, _6); _3_6.create(); drawText(_3_6.tbx - dolechx + 8, _3_6.tby - dolechy - 8, "7");
        Line _3_7(_3, _7); _3_7.create(); drawText(_3_7.tbx - dolechx, _3_7.tby - dolechy + - 5, "7");
        Line _3_8(_3, _8); _3_8.create(); drawText(_3_8.tbx - dolechx + 12, _3_8.tby - dolechy, "5");
        Line _3_9(_3, _9); _3_9.create(); drawText(_3_9.tbx - dolechx - 8, _3_9.tby - dolechy - 9, "2");
        Line _4_6(_4, _6); _4_6.create(); drawText(_4_6.tbx - dolechx - 9, _4_6.tby - dolechy + 9, "9");
        Line _4_7(_4, _7); _4_7.create(); drawText(_4_7.tbx - dolechx - 7, _4_7.tby - dolechy + 11, "7");
        Line _5_8(_5, _8); _5_8.create(); drawText(_5_8.tbx - dolechx - 9, _5_8.tby - dolechy - 9, "8");
        Line _5_10(_5, _10); _5_10.create(); drawText(_5_10.tbx - dolechx + 10, _5_10.tby - dolechy - 10, "9");
        Line _6_8(_6, _8); _6_8.create(); drawText(_6_8.tbx - dolechx - 9, _6_8.tby - dolechy - 9, "6");
        Line _8_9(_8, _9); _8_9.create(); drawText(_8_9.tbx - dolechx - 7, _8_9.tby - dolechy + 11, "5");
        Line _8_10(_8, _10); _8_10.create(); drawText(_8_10.tbx - dolechx - 7, _8_10.tby - dolechy + 11, "2");
        Line _10_11(_10, _11); _10_11.create(); drawText(_10_11.tbx - dolechx - 7, _10_11.tby - dolechy - 11, "12");

        //Ve point (de khong bi de boi ve line) 
        // VANDE: Vong K khong giong mau cac vong khac

        _1.create(); _2.create(); _3.create();
        _4.create(); _5.create(); _6.create(); _7.create();
        _8.create(); _9.create(); _10.create(); _11.create();


        //Nhap
        int first_point, second_point;
        cout << endl << endl;
        for (int i = 0; i <= 3; i++)
        {
            cout << " ";
        }
        cout << "START: "; cin >> first_point;
        while (first_point < 1 || first_point>11)
        {
            cout << "Nhap sai. Nhap lai. " << endl;
            for (int i = 0; i <= 3; i++)
            {
                cout << " ";
            }
            cout << "START: "; cin >> first_point;
        }
        for (int i = 0; i <= 3; i++)
        {
            cout << " ";
        }
        cout << "END: " << "  "; cin >> second_point;
        while (second_point < 1 || second_point>11)
        {
            cout << "Nhap sai. Nhap lai. " << endl;
            for (int i = 0; i <= 3; i++)
            {
                cout << " ";
            }
            cout << "END: " << " "; cin >> second_point;
        }


        //Xử lí thuật toán
        int mangtam[1000];
        int lenghtm = 0;
        dijkstra(first_point);
        truy_vet(second_point, first_point, mangtam, lenghtm);

        //Vẽ đường đi
        point mangpoint[1000];
        for (int i = 0; i < lenghtm; i++)
        {
            switch (mangtam[i])
            {
            case 1:
                mangpoint[i] = _1;
                break;
            case 2:
                mangpoint[i] = _2;
                break;
            case 3:
                mangpoint[i] = _3;
                break;
            case 4:
                mangpoint[i] = _4;
                break;
            case 5:
                mangpoint[i] = _5;
                break;
            case 6:
                mangpoint[i] = _6;
                break;
            case 7:
                mangpoint[i] = _7;
                break;
            case 8:
                mangpoint[i] = _8;
                break;
            case 9:
                mangpoint[i] = _9;
                break;
            case 10:
                mangpoint[i] = _10;
                break;
            case 11:
                mangpoint[i] = _11;
                break;
            }
        }

        for (int i = 0; i < lenghtm; i++)
        {
            color = 8; 
            if (i < lenghtm - 1)
            {
                if (i == 0)
                {
                    sizecolor = 5;
                    Line xx(mangpoint[0], mangpoint[1]); xx.create();
                }
                sizecolor = 5;
                Line xx(mangpoint[i], mangpoint[i + 1]); xx.create();
            }
            mangpoint[i].create();
            Sleep(200);
        }

        for (int i = 0; i <= 3; i++)
        {
            cout << " ";
        }
        cout << "Do dai duong di ngan nhat la: ";
        cout << s_min[second_point];
        Sleep(1000);

        string s;
        cout << "\n\nBan co muon tiep tuc khong? (Yes/No)\n";
        for (int i = 0; i <= 3; i++)
        {
            cout << " ";
        }
        cin >> s;
        if (s == "No")
            break;
    }
    system("pause");
    return 0;
}