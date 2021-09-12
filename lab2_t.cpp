#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
#include <algorithm>
#include <functional>
#include <unistd.h>
using namespace std;

const int SIZE =10000;
int numbers[SIZE];
int ultimateArray[SIZE][SIZE];
int amountInEachSubArray;
int extra;
int readData()
{
    string inFileName = "/Users/bohdan_pikula/Desktop/Lab3/input.txt";
    ifstream inFile;
    inFile.open(inFileName.c_str());
    if (inFile.is_open())
    {
        int i = 0;
        while(i<SIZE)
        {
            inFile>>numbers[i];
            i++;
        }
        i=0;
        while(numbers[i]!=0 && i<SIZE)
        {
            // cout<<numbers[i]<<" ";
            i++;
        }
        inFile.close();
        return i;
    }
    else
    {
        cerr<<"Can't find input file " << inFileName <<endl;
        return 0;
    }
}

void lol(int i)
{
    cout << i << endl;
}

void sortRowWise(int m[], int n)
{
    cout << endl;
    int c = amountInEachSubArray;
    for (int j=0; j<c; j++)
    {
        for (int k=0;k<c-j-1;k++)
        {
            if (m[k]>m[k+1])
            {
                swap(m[k],m[k+1]);
            }
        }
    }
    ofstream outputFile;
    outputFile.open(to_string(n)+"_process.txt");
    for (int j=0;j<c;j++)
        outputFile<<m[j]<<" ";
    outputFile<<endl;
    outputFile.close();
}

void spawn(int n)
{
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    if(n)
    {
        if(fork()==0)
        {
            ofstream outputFile;
            outputFile.open(to_string(n)+"_process.txt");
            outputFile << "\nProcess " << n << endl;
            if (n==1) amountInEachSubArray+= extra;
            sortRowWise(ultimateArray[n-1],n);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            
            outputFile << "time elapsed for process " << n << " :" << chrono::duration_cast<chrono::microseconds>(end-begin).count() << " microseconds" << endl;
            outputFile.close();
            spawn(n-1);
        }
        else
            return;
    }
}

int main(int arg, char **argv)
{
    int total = readData();
    int N = atoi(argv[1]);
    cout << "Input the number of splits" << endl;
    extra = total%N;
    amountInEachSubArray = total/N;
    int counter = 0;
    for (int i = 0; i<N-1;i++)
    {
        for(int j = 0; j<amountInEachSubArray;j++)
        {
            ultimateArray[i][j] = numbers[counter];
            //cout << ultimateArray[i][j];
            counter++;
        }
        cout << endl; 
    }
    for(int j = 0; j<amountInEachSubArray+extra;j++)
        {
            ultimateArray[N-1][j] = numbers[counter];
            //cout << ultimateArray[N-1][j];
            counter++;
        }

    chrono::steady_clock::time_point begin[N];
    chrono::steady_clock::time_point end[N];
    thread myThreads[N];
    for(int i = 0; i<N-1; i++)
    {
        begin[i]=chrono::steady_clock::now();
        myThreads[i]= thread(sortRowWise,ultimateArray[i]);
    }
    amountInEachSubArray+=extra;
    begin[N-1]=chrono::steady_clock::now();
    myThreads[N-1]=thread(sortRowWise,ultimateArray[N-1]);

    for(int i = 0;i<N;i++)
    {
        myThreads[i].join();
        end[i]=chrono::steady_clock::now();
    }
    
    cout<<"Threads have finished"<<endl;
    for (int i =0; i<N;i++)
    cout << "time elapsed for thread " << i+1 << " :" << chrono::duration_cast<chrono::microseconds>(end[i]-begin[i]).count() << " microseconds" << endl;
    
    
    return 0;
} 