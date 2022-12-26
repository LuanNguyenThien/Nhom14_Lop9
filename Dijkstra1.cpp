#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

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
        if(top == NULL)
        {
            temp->next = top;
            top = temp;
            return;
        }
        while(start->next != NULL)
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
    Node *top;
    
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
        if(top == NULL)
        {
            temp->next = top;
            top = temp;
            return;
        }
        if(top->distance >= temp->distance)
        {
            temp->next = top;
            top = temp;
        }
        else
        {
            while(start->next != NULL && start->next->distance < temp->distance)
                start = start->next;
            temp->next = start->next;
            start->next = temp;
        }
    }
    
    void push_back(int d, int p)
    {
        Node* start = top;
        Node* temp = newNode(d, p);
        if(top == NULL)
        {
            temp->next = top;
            top = temp;
            return;
        }
        while(start->next != NULL)
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

        Node *temp = new Node;
        temp = List_road[u].top;
        while(temp != NULL) 
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

void truy_vet(int second_point, int first_point)
{
    int u = second_point;
    while(u != first_point)
    {
        a[second_point].push(u);
        u = From[u];
    }
    a[second_point].push(first_point);
    while(a[second_point].top->next != NULL)
    {
        cout<<a[second_point].peek()->p_start<<"->";
        a[second_point].pop();
    }
    cout<<a[second_point].peek()->p_start;
    a[second_point].pop();
    cout<<endl;
}

int main()
{
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
    
    for(int i = 1; i <= number_point; i++)
    {
        List_road[i].init();
        a[i].init();
    }
    
    Node* temp = new Node;
    temp = ways.peek();
    while(number_way>1)
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

    int first_point;
    cout<<"Nhap diem goc: ";
    cin>>first_point;
    dijkstra(first_point);
    cout<<"\nTap hop cac duong di ngan nhat: \n\n";
    for (int i = 1; i <= number_point; i++)
    {
        cout<<"d("<<first_point<<"->"<<i<<")"<<" = "<<s_min[i]<<"\t";
        truy_vet(i, first_point);
        cout<<endl;
    }

    // cout<<"d("<<first_point<<"->"<<second_point<<")"<<" = "<<s_min[second_point]<<"\t";

    // truy_vet(second_point, first_point);

    /*dijkstra();
    for (int i = 1; i <= number_point; i++)
    {
        cout<<"d(1->"<<i<<")"<<" = "<<s_min[i]<<"\t";
        truy_vet(i);
        cout<<endl;
    }*/
    
}