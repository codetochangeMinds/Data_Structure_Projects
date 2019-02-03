#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int N;

// creating a structure consisting of 
// attribute of the flight
struct flight
{
    int city1;
    int city2;
    int departure_time;
    int arrival_time;
    string flight_no;
    int price;
};

struct maping
{
    bool bol;
    vector<flight> flights;
};

// 
vector<flight> in_row(int cty1, int cty2, maping **route, int prev_arr, int dep, vector<int> qck[])
{
    vector<flight> temps;
    if(qck[cty1].size()>0)
    {
        for(int j=0; j< qck[cty1].size(); j++)
        {
            for(int k=0; k<route[cty1][qck[cty1][j]].flights.size(); k++)
            {
                if(route[cty1][qck[cty1][j]].flights[k].departure_time - prev_arr >= 30 && route[cty1][qck[cty1][j]].flights[k].arrival_time < dep)
                {
                    temps.push_back(route[cty1][qck[cty1][j]].flights[k]);
                }
            }
        }
    }
    return temps;
}

// function to find the price of the trip
int prices(vector<int> init, int city1,int city2,maping **maps, int arr, int dep, int flag, vector<int> qk[])
{
    init.push_back(city1);
    int t = flag;

    if(city1!=city2)
    {
        vector<flight> temp;
        bool p=1;
        for(int y=0; y<init.size()-1; y++)
        {   if(city1==init[y])
            {   p=0;
                break;
            }
        }
    if(p=1)
    {   
        if(t == 1)
        {
            {
                temp = in_row(city1, city2, maps, arr-30, dep, qk);
                t =0;
            }
        }
        else
        {
            temp = in_row(city1, city2, maps, arr, dep, qk);
        }
    }
    if(temp.size()>0)
    {
        int myprice[temp.size()];
    
        for(int i= 0; i<temp.size(); i++)
        {
            myprice[i] = temp[i].price + prices( init, temp[i].city2 -1, city2, maps, temp[i].arrival_time, dep, t, qk);
        }
        int mini = 5000000;
        for(int i=0; i<temp.size(); i++)
        {
            if(myprice[i]<mini && myprice[i]>0)
                mini = myprice[i];
        }
        if(mini == 5000000)
            return -500000;
        else
            return mini;

    }
    else
        return -500000;}
    else
        return 0;
}

// driver program
// the given program reads from the file input.txt
// and invokes the function to find the minimum possible 
// price of the trip 
int main()
{
    ifstream fin;
    ofstream fout;
    // reading from the input.txt
    fin.open("input.txt");
    fin>>N;
    vector<int> quick[N];

    int line;
    fin>>line;
    flight data[line];
    for(int i=0; i<line; i++)
    {
        fin>>data[i].city1>>data[i].city2>>data[i].departure_time>>data[i].arrival_time>>data[i].flight_no>>data[i].price;
    }

   //maping maps[N][N];
    maping** maps = new maping*[N];
    for( int i = 0; i < N; i++ ) 
    {
        maps[i] = new maping[N];
    }
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            maps[i][j].bol = 0;
        }
    }

    for(int i=0; i<line; i++)
    {
            maps[data[i].city1 -1][data[i].city2 -1].bol=1;
            maps[data[i].city1 -1][data[i].city2 -1].flights.push_back(data[i]);
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(maps[i][j].bol == 1)
                quick[i].push_back(j);
        }
    }

    int q;
    fin>>q;
    for(int i=0; i<q; i++)
    {
        int t1,t2, t3, t4;
        fin>>t1>>t2>>t3>>t4;
        vector<int> temp;
        int min_price = prices( temp, t1 -1, t2 -1, maps, t3, t4, 1, quick);

        if(min_price>0)
            cout<<min_price<<"\n";
        else
            cout<<-1<<"\n";
    }
    fin.close();
}

