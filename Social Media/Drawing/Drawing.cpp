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
void mang_xa_hoi()
{
    Priority_queue Luu_KQ;
    Luu_KQ.init();

    vector<ii> KQ;

    int p_start, p_end, distance;
    List ways;
    ways.init();

    number_point = 20;
    number_way = 30;
    ways.push_back(2, 3, 165); ways.push_back(3, 4, 7); ways.push_back(4, 7, 0);
    ways.push_back(1, 5, 0); ways.push_back(7, 10, 15); ways.push_back(5, 10, 1);
    ways.push_back(2, 6, 23); ways.push_back(6, 9, 20); ways.push_back(9, 12, 54);
    ways.push_back(7, 13, 170); ways.push_back(12, 13, 8); ways.push_back(13, 17, 70);
    ways.push_back(8, 14, 98); ways.push_back(16, 20, 0); ways.push_back(11, 15, 34);
    ways.push_back(11, 19, 76); ways.push_back(4, 1, 100); ways.push_back(7, 5, 51);
    ways.push_back(11, 6, 54); ways.push_back(19, 15, 78); ways.push_back(15, 12, 120);
    ways.push_back(19, 7, 189); ways.push_back(18, 12, 6); ways.push_back(18, 16, 76);
    ways.push_back(9, 4, 98); ways.push_back(16, 13, 0); ways.push_back(13, 10, 61);
    ways.push_back(10, 8, 52); ways.push_back(17, 14, 27); ways.push_back(20, 17, 19);


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

    class User
    {
    public:
        int x, y;
        int size;
        const char* a;
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
            PEN = getPen(PS_SOLID, 2, RGB(0, 0, 0));
            fillcircle(x, y, size);
            PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255));
            fillcircle(x, y - 12, size - 60);
            PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255));
            fillcircle(x, y + 45, size - 15);
            drawText(x - 16, y - 24 + 25, a, 0, 0, 0);
        }
        void add(int r, int g, int b)
        {
            PEN = getPen(PS_SOLID, 2, RGB(r, g, b));
            fillcircle(x, y, size);
            PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255));
            fillcircle(x, y - 12, size - 60);
            PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255));
            fillcircle(x, y + 45, size - 15);
            drawText(x - 16, y - 24 + 25, a, 0, 0, 0);
        }
    };
    
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
        void add()
        {
            PEN = getPen(PS_SOLID, 10, RGB(178, 178, 178));
            if (x1 <= x2 && y1 <= y2)
            {
                line(x1 + lechx, y1 + lechy, x2 - lechx, y2 - lechy);
            }
            else
            {
                line(x1 + lechx, y1 - lechy, x2 - lechx, y2 + lechy);
            }
            PEN = getPen(PS_SOLID, 10, RGB(255, 255, 255));
            fillrectangle(tdx - 5, tdy - 5, tdx + 18, tdy + 5);
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
            PEN = getPen(PS_SOLID, 10, RGB(255, 255, 255));
            fillrectangle(tdx - 5, tdy - 5, tdx + 18, tdy + 5);
            drawText(tdx - 16, tdy - 24, TS, 0, 0, 0);
        }

    };
    class Emoji_Like
    {
    public:
        int x, y;
        Emoji_Like(User X)
        {
            x = X.x + 50;
            y = X.y - 50;
        }
        void add()
        {
            PEN = getPen(PS_SOLID, 3, RGB(0, 0, 0));
            //circle(x, y, 35);
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
            x = X.x + 50;
            y = X.y - 50;
        }
        void add()
        {
            PEN = getPen(PS_SOLID, 3, RGB(0, 0, 0));
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
            x = X.x + 50;
            y = X.y - 50;
        }
        void add()
        {
            PEN = getPen(PS_SOLID, 3, RGB(0, 0, 0));
            fillcircle(x, y, 48);
            PEN = getPen(PS_SOLID, 3, RGB(255, 0, 0));
            fillellip(x - 6, y + 32, x + 6, y + 50);
            fillellip(x - 15, y - 3 + 26, x - 9, y + 6 + 26);
            fillellip(x + 9, y - 3 + 26, x + 15, y + 6 + 26);
            arc(x - 15, y - 9 + 26, x - 9, y + 2 + 26, x - 10, y - 9 + 26, x - 15, y - 9 + 26);
            arc(x + 9, y - 9 + 26, x + 15, y + 2 + 26, x + 15, y - 9 + 26, x + 10, y - 9 + 26);
        }
    };

    rectangle(0, 0, 2400, 1500);
    PEN = getPen(PS_SOLID, 10, RGB(0, 0, 0));
    line(300, 0, 300, 1500);
    User A(1450, 350, 100, "A"); A.add(); User B(800, 400, 100, "B"); B.add(); User C(1050, 400, 100, "C"); C.add();
    User D(1250, 450, 100, "D"); D.add(); User E(1650, 450, 100, "E"); E.add(); User F(950, 550, 100, "F"); F.add();
    User G(1450, 550, 100, "G"); G.add(); User H(1800, 550, 100, "H"); H.add(); User I(1150, 600, 100, "I"); I.add();
    User J(1650, 700, 100, "J"); J.add(); User K(850, 750, 100, "K"); K.add(); User L(1250, 750, 100, "L"); L.add();
    User M(1450, 800, 100, "M"); M.add(); User N(1850, 800, 100, "N"); N.add(); User O(1050, 850, 100, "O"); O.add();
    User P(1350, 950, 100, "P"); P.add(); User Q(1650, 960, 100, "Q"); Q.add(); User R(1150, 1000, 100, "R"); R.add();
    User S(950, 1050, 100, "S"); S.add(); User T(1500, 1100, 100, "T"); T.add();

    Conect BC(B, C, "165"); BC.add(); Conect CD(C, D, "7"); CD.add(); Conect DG(D, G, "0"); DG.add();
    Conect AE(A, E, "0"); AE.add(); Conect GJ(G, J, "15"); GJ.add(); Conect EJ(E, J, "1"); EJ.add();
    Conect BF(B, F, "23"); BF.add(); Conect FI(F, I, "20"); FI.add(); Conect IL(I, L, "54"); IL.add();
    Conect GM(G, M, "170"); GM.add(); Conect LM(L, M, "8"); LM.add(); Conect MQ(M, Q, "70"); MQ.add();
    Conect HN(H, N, "98"); HN.add(); Conect PT(P, T, "0"); PT.add(); Conect KO(K, O, "34"); KO.add();
    Conect KS(K, S, "76"); KS.add(); Conect DA(D, A, "100"); DA.add(); Conect GE(G, E, "51"); GE.add();
    Conect KF(K, F, "54"); KF.add(); Conect SO(S, O, "78"); SO.add(); Conect OL(O, L, "120"); OL.add();
    Conect SR(S, R, "189"); SR.add(); Conect RL(R, L, "6"); RL.add(); Conect RP(R, P, "76"); RP.add();
    Conect ID(I, D, "98"); ID.add(); Conect PM(P, M, "0"); PM.add(); Conect MJ(M, J, "61"); MJ.add();
    Conect JH(J, H, "52"); JH.add(); Conect QN(Q, N, "27"); QN.add(); Conect TQ(T, Q, "19"); TQ.add();
    Emoji_Wow Like(A); Like.add();

    int dem = 0;
    int first_point;
    char test;
    cout << "Nhap diem goc: ";
    cin >> first_point;
    //first_point = (int)(test) - 43;
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

    for (auto v : KQ)
    {
        cout << v.first << " " <<v.second;
        cout << endl;
    }

    Node* temp2 = List_road[first_point].top;
    while (temp2 != NULL)
    {
        std::vector<ii>::iterator it;
        it = find(KQ.begin(), KQ.end(), ii(temp2->distance, temp2->p_end));
        int temp = it - KQ.begin();
        cout << temp<<endl;
        //KQ.erase(KQ.begin() + temp);
        temp2 = temp2->next;
    }
    /*KQ.erase(KQ.begin());
    dem = 5;
    int ket_qua[100];
    int ket_qua_lenght = 0;
    while (dem > 0)
    {
        ket_qua[ket_qua_lenght] = KQ.front().second;
        ket_qua_lenght++;
        KQ.erase(KQ.begin());
        dem--;
    }*/

    /*int xu_li_so_lieu[100][100];
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
    cout << 1111;
    User de_cu[100][100];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < mang_lenght_xu_li[i]; j++)
        {
            cout << xu_li_so_lieu[i][j] << " ";
            switch (xu_li_so_lieu[i][j])
            {
            case 1:
                de_cu[i][j] = A;
                break;
            case 2:
                de_cu[i][j] = B;
                break;
            case 3:
                de_cu[i][j] = C;
                break;
            case 4:
                de_cu[i][j] = D;
                break;
            case 5:
                de_cu[i][j] = E;
                break;
            case 6:
                de_cu[i][j] = F;
                break;
            case 7:
                de_cu[i][j] = G;
                break;
            case 8:
                de_cu[i][j] = H;
                break;
            case 9:
                de_cu[i][j] = I;
                break;
            case 10:
                de_cu[i][j] = J;
                break;
            case 11:
                de_cu[i][j] = K;
                break;
            case 12:
                de_cu[i][j] = L;
                break;
            case 13:
                de_cu[i][j] = M;
                break;
            case 14:
                de_cu[i][j] = N;
                break;
            case 15:
                de_cu[i][j] = O;
                break;
            case 16:
                de_cu[i][j] = P;
                break;
            case 17:
                de_cu[i][j] = Q;
                break;
            case 18:
                de_cu[i][j] = R;
                break;
            case 19:
                de_cu[i][j] = S;
                break;
            case 20:
                de_cu[i][j] = T;
                break;
            }
        }
    }
    int i;
    for (i = 0; i < 5; i++);
    {
        for (int j = 0; j < mang_lenght_xu_li[i]; j++)
        {
            de_cu[i][j].add(255, 150, 175);

        }
    }*/

}



int main()
{
    int k;
    initgraph();
    _getch();
    mang_xa_hoi();
    Sleep(100000);
    system("cls");
    return 0;
}

