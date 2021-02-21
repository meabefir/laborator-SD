#include <random>
#include <iostream>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bits.h>

using namespace std;
using namespace std::chrono;

#define MAX_SIZE 10000000

int lowerBorder = 0;
int upperBorder = 1000000;
int frec[MAX_SIZE] = {0};
int arr[MAX_SIZE];

std::mt19937 gen(time(0));

std::uniform_int_distribution<int> dis(lowerBorder, upperBorder);
std::uniform_int_distribution<int> dis_size(0, MAX_SIZE-1);

int* generate_random_array(int arr[], int s){
    for (int i = 0; i < s; i++){
        arr[i] = dis(gen);
    }
    return arr;
}

int* generate_almost_sorted_array(int arr[], int s){
    int *_ = generate_random_array(arr, s);

    sort(_,_+s);

    for (int i = 0; i < max(1,s/10); i++){
        int poz1 = dis_size(gen);
        int poz2 = dis_size(gen);

        int aux = arr[poz1];
        arr[poz1] = arr[poz2];
        arr[poz2] = aux;
    }

    return arr;
}

int* generate_reversed_almost_sorted_array(int arr[], int s){
    int *_ = generate_almost_sorted_array(arr, s);

    for (int i = 0; i < s/2; i++){
        int aux = arr[i];
        arr[i] = arr[s-i-1];
        arr[s-i-1] = aux;
    }
    return arr;
}

int *generate_const_array(int arr[], int s){
    for (int i = 0; i < s; i++)
        arr[i] = 0;
    return arr;
}

bool is_sorted(int arr[], int s){
    for (int i = 0; i < s-1; i++){
        if (arr[i] > arr[i+1]) return false;
    }
    return true;
}

void print_arr(int arr[], int s){
    cout << '\n';
    for (int i =0; i < s; i++)
        cout << arr[i] << ' ';
}

unsigned __int64 get_milliseconds(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int get_max(int arr[], int s){
    int maxim = arr[0];
    for (int i =1; i < s; i++){
        if (arr[i] > maxim)
            maxim = arr[i];
    }
    return maxim;
}

unsigned __int64 bubble_sort(int arr[], int s){
    unsigned __int64 time1 = get_milliseconds();

    for (int i = 0; i < s; i++){
        for (int j = 0; j < s-i; j++){
            if (arr[j] > arr[j+1]){
                int aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
        }
    }

    unsigned __int64 time2 = get_milliseconds();
    unsigned __int64 total_time = time2 - time1;
    return total_time;
}

unsigned __int64 count_sort(int arr[], int s){
    unsigned __int64 time1 = get_milliseconds();

    int maxim = get_max(arr,s);

    for (int i =0; i <= maxim; i++)
        frec[i] = 0;
    for (int i = 0; i < s; i++)
        frec[arr[i]] ++;

    int k = 0;
    for (int i = 0; i <= maxim; i++){
        for (int j = 1; j <= frec[i];j++)
            arr[k++] = i;
    }

    unsigned __int64 time2 = get_milliseconds();
    unsigned __int64 total_time = time2 - time1;
    return total_time;
}

void quick(int arr[],int l,int r){
    if (l < r){
        int pivot = arr[l];
        vector<int> mici;
        vector<int> mari;
        for (int i = l; i<= r; i++)
            if (arr[i] < pivot)
                mici.push_back(arr[i]);
            else
                mari.push_back(arr[i]);
        for (int i = 0; i < mici.size(); i++)
            arr[i+l] = mici[i];
        for (int i = 0; i < mari.size(); i++)
            arr[i+mici.size()+l] = mari[i];

        quick(arr,l,l+mici.size());
        quick(arr,l+mici.size()+1,r);
    }
}

unsigned __int64 quicksort(int arr[], int s){
    unsigned __int64 time1 = get_milliseconds();

    quick(arr,0,s-1);

    unsigned __int64 time2 = get_milliseconds();
    unsigned __int64 total_time = time2 - time1;
    return total_time;
}

void combine(int arr[], int l, int mij, int r){
    vector <int> st;
    vector <int> dr;

    for (int i = l; i <= mij; i++){
        st.push_back(arr[i]);
    }
    for (int i = mij+1; i <= r; i++){
        dr.push_back(arr[i]);
    }

    int i = 0, j = 0, k = l;
    while (i < st.size() && j < dr.size()){
        if (st[i] < dr[j])
            arr[k++] = st[i++];
        else
            arr[k++] = dr[j++];
    }
    while (i < st.size())
        arr[k++] = st[i++];
    while (j < dr.size())
        arr[k++] = dr[j++];
}

void merges(int arr[], int l, int r){
    if (l < r){
        int mij = l + (r-l)/2;
        merges(arr,l,mij);
        merges(arr,mij+1,r);

        combine(arr,l,mij,r);
    }
}

unsigned __int64 mergesort(int arr[], int s){
    unsigned __int64 time1 = get_milliseconds();

    merges(arr,0,s-1);

    unsigned __int64 time2 = get_milliseconds();
    unsigned __int64 total_time = time2 - time1;
    return total_time;
}

void radix(int arr[], int l, int r, int pos){
    if (pos < 0) return;
    if (l >= r) return;
    vector <int> has_0;
    vector <int> has_1;
    for (int i=l; i <= r; i++){
        if (arr[i] & (1<<pos))
            has_1.push_back(arr[i]);
        else
            has_0.push_back(arr[i]);
    }
    int k = l;
    for (int i =0; i < has_0.size();i++)
        arr[k++] = has_0[i];
    for (int i =0; i < has_1.size();i++)
        arr[k++] = has_1[i];

    radix(arr,l,l+has_0.size()-1,pos-1);
    radix(arr,l+has_0.size(),r,pos-1);
}

unsigned __int64 radixsort(int arr[], int s){
    unsigned __int64 time1 = get_milliseconds();

    int maxim = get_max(arr,s);
    int nr_bites = log2(maxim)+1;

    radix(arr,0,s-1,nr_bites);

    unsigned __int64 time2 = get_milliseconds();
    unsigned __int64 total_time = time2 - time1;
    return total_time;
}

int main()
{
    generate_reversed_almost_sorted_array(arr, MAX_SIZE);
//print_arr(arr,MAX_SIZE);
    cout << "time is " << radixsort(arr, MAX_SIZE);
//print_arr(arr,MAX_SIZE);
    //print_arr(arr,MAX_SIZE);

    cout << '\n' << is_sorted(arr,MAX_SIZE);

    //for (int n=0; n<10; ++n)
    //    std::cout << dis(gen) << ' ';
}
