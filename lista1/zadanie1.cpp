#include <bits/stdc++.h>
#include <unistd.h>
#include <chrono>
using namespace std;
vector<vector<int>> board(4,vector<int>(4));
auto t1 = chrono::steady_clock::now();
bool isSolvable(vector<int> V)
{
    int count = 0;
    for(int i = 0 ;i < V.size();i++)
    {
        for(int j = i+1; j < V.size(); j++)
        {
            if(V[i] > V[j])count++;
        }
    }
    return (count%2 == 0);
}

vector<vector<int>> randboard()
{
    vector<int> V(15);
    vector<vector<int>> Brd(0);
    for(int i = 1; i <= 15; i++)
        V[i-1] = i;
    random_shuffle(V.begin(), V.end());
    V.push_back(16);
    
    if(!isSolvable(V))Brd = randboard();
    else 
    {
        vector<int> A,B,C,D;
        A.push_back(V[0]); A.push_back(V[1]); A.push_back(V[2]); A.push_back(V[3]);

        B.push_back(V[4]); B.push_back(V[5]); B.push_back(V[6]); B.push_back(V[7]); 

        C.push_back(V[8]); C.push_back(V[9]); C.push_back(V[10]); C.push_back(V[11]); 

        D.push_back(V[12]); D.push_back(V[13]); D.push_back(V[14]); D.push_back(V[15]); 
        Brd.push_back(A); Brd.push_back(B); Brd.push_back(C); Brd.push_back(D); 
        cerr<<"Starting board: \n";
        for(int i = 0; i < Brd.size(); i++)
        {
            for(int j = 0; j < Brd[i].size(); j++)
            {
                cerr<<Brd[i][j]<<" ";
            }
            cerr<<"\n";
        }
        cerr<<"///////////////\n";

    }
    return Brd;
}

int eval1(vector<vector<int>> B)
{
    int count = 0;
    vector<int> V;
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            int val = i*4+j+1;
            if(B[i][j] != val)
            {
                count++;
            }
        }
    }
    for(int i = 0 ;i < V.size();i++)
    {
        if(V[i] != i+1)count+= (16 - V[i])*(16 - V[i]);
    }
    return -count;
}

int eval2(vector<vector<int>> B)
{
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            int a = 0, b = 0;
            a = (B[i][j]-1)/4;
            b = (B[i][j]-1)%4;
            count += abs(a-i) + abs(b-j);
        }
    }

    return -count;
}
bool canSwap(int nx, int ny)
{
    if(nx >= 4)return false;
    if(nx < 0)return false;
    if(ny >= 4)return false;
    if(ny < 0)return false;
    return true;
}
vector<vector<int>> Swap(int x, int y, int nx, int ny, vector<vector<int>> B)
{
    int old = B[x][y];
    B[x][y] = B[nx][ny];
    B[nx][ny] = old;
    return B;
}
void printState(int num, int eval, int size,int len, vector<vector<int>> B)
{
    auto t2 = chrono::steady_clock::now();
    chrono::duration<double> diff = t2-t1;
    cerr<<num<<": "<<eval<<" size: "<<size<<" len: "<<len<<" time: "<<diff.count()<<"s\n";
    for(int i = 0; i< 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cerr<<B[i][j]<<" ";
        }
        cerr<<"\n";
    }
}
void printPath(int step, vector<vector<vector<int>>> travel)
{
    cout<<"liczba dwiedzonych stanow: "<<step<<"\nPokonana droga:\n";
    for(int s = 0; s < travel.size(); s++)
    {
        cout<<"Step = "<<s<<":\n";
        for(int i = 0; i < travel[s].size(); i++)
        {
            for(int j = 0; j < travel[s][i].size(); j++)
            {
                cout<<travel[s][i][j]<<" ";
            }
            cout<<"\n";
        }
    }
    cout<<"ilosc krokow do ulozenia: "<<travel.size()<<"\n";
}
void Astar(int mode, vector<vector<int>> B)
{
    set<vector<vector<int>>> S;
    priority_queue<pair<int,vector<vector<vector<int>>>>> Q;
    pair<int,vector<vector<vector<int>>>> c;
    vector<vector<vector<int>>> Start(0);
    if(mode == 0)
    {
        c.first = eval1(B);
    }
    else if(mode == 1)
    {
        c.first = eval2(B);
    }
    else 
    {
        return;
    }
    Start.push_back(B);
    c.second = Start;
    S.insert(B);
    Q.push(c);
    int i = 0;
    
    while(!Q.empty())
    {   
        i++;
        pair<int,vector<vector<vector<int>>>> cur = Q.top();
        Q.pop();
        if(cur.first == 0)
        {
            cout<<"Gotowe!\n";
            printPath(i, cur.second);
            return;
        }
        int num = 1000;
        bool db = true;
        if(db && (i%num == 0 || (i+1)%num == 0 || (i+2)%num == 0 || (i+3)%num == 0 || (i+4)%num == 0 || (i+5)%num == 0 || (i+6)%num == 0 || (i+7)%num == 0 || (i+8)%num == 0))
        {
            printState(i, -cur.first, Q.size(), cur.second.size() ,cur.second[cur.second.size()-1]);
        }
        int x, y;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(cur.second[cur.second.size()-1][i][j] == 16)
                {
                    x = i;
                    y = j;
                }
            }
        }
        vector<vector<int>> lastBoard = cur.second[cur.second.size()-1];
        pair<int,vector<vector<vector<int>>>> next;
        if(canSwap(x+1, y))
        {
            next.second = cur.second;
            next.second.push_back(Swap(x, y, x+1, y, lastBoard));
            if(S.find(next.second[next.second.size()-1]) == S.end())
            {

                if(mode == 0)
                {
                    next.first = eval1(next.second[next.second.size()-1]);
                }
                else
                {
                    next.first = eval2(next.second[next.second.size()-1]);
                }
                Q.push(next);
                S.insert(next.second[next.second.size()-1]);
            }
        }
        
        if(canSwap(x-1, y))
        {
            next.second = cur.second;
            next.second.push_back(Swap(x, y, x-1, y, lastBoard));
            if(S.find(next.second[next.second.size()-1]) == S.end())
            {

                if(mode == 0)
                {
                    next.first = eval1(next.second[next.second.size()-1]);
                }
                else
                {
                    next.first = eval2(next.second[next.second.size()-1]);
                }
                Q.push(next);
                S.insert(next.second[next.second.size()-1]);
            }
        }
        
        if(canSwap(x, y+1))
        {
            next.second = cur.second;
            next.second.push_back(Swap(x, y, x, y+1, lastBoard));
            if(S.find(next.second[next.second.size()-1]) == S.end())
            {

                if(mode == 0)
                {
                    next.first = eval1(next.second[next.second.size()-1]);
                }
                else
                {
                    next.first = eval2(next.second[next.second.size()-1]);
                }
                Q.push(next);
                S.insert(next.second[next.second.size()-1]);
            }
        }
        
        if(canSwap(x, y-1))
        {
            next.second = cur.second;
            next.second.push_back(Swap(x, y, x, y-1, lastBoard));
            if(S.find(next.second[next.second.size()-1]) == S.end())
            {

                if(mode == 0)
                {
                    next.first = eval1(next.second[next.second.size()-1]);
                }
                else
                {
                    next.first = eval2(next.second[next.second.size()-1]);
                }
                Q.push(next);
                S.insert(next.second[next.second.size()-1]);
            }
        }

    }
}


int main()
{
    srand(time(0) + getpid());
    //vector<vector<int>> startingBoard(4, vector<int>(4));
    vector<vector<int>> startingBoard = randboard();
    

    // startingBoard[0][0] =  1;
    // startingBoard[0][1] =  2;
    // startingBoard[0][2] =  3;
    // startingBoard[0][3] =  4;

    // startingBoard[1][0] =  5;
    // startingBoard[1][1] =  6;
    // startingBoard[1][2] =  7;
    // startingBoard[1][3] =  8;

    // startingBoard[2][0] =  10;
    // startingBoard[2][1] =  11;
    // startingBoard[2][2] =  12;
    // startingBoard[2][3] =  15;

    // startingBoard[3][0] =  9;
    // startingBoard[3][1] =  13;
    // startingBoard[3][2] =  14;
    // startingBoard[3][3] =  16;
    t1 = chrono::steady_clock::now();
    Astar(1, startingBoard);
    auto t2 = chrono::steady_clock::now();
    chrono::duration<double> diff = t2-t1;
    cerr<<"time passed: "<<diff.count()<<"s\n";
    // for(int i = 0; i< 4; i++)
    // {
    //     for(int j = 0; j < 4; j++)
    //     {
    //         cout<<startingBoard[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    // cout<<-eval2(startingBoard)<<"\n";

    return 0;
}