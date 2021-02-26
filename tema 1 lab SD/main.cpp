#include <random>
#include <iostream>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bits.h>
#include <string>
#include <functional>
#include <fstream>

using namespace std;
using namespace std::chrono;

ifstream fin("in.in");

#define MAX_SIZE 100000000

int frec[MAX_SIZE] = {0};
int i_arr[MAX_SIZE];
int c_arr[MAX_SIZE];
int _size, _max;

std::mt19937 gen(time(0));

std::uniform_int_distribution<int> rng(0, 0);

int* generate_random_array(int arr[], int s){
    for (int i = 0; i < s; i++){
        //cout << typeid(arr).name() << ' ';
        arr[i] = rng(gen);
    }
}

int* generate_almost_sorted_array(int arr[], int s){
    generate_random_array(arr, s);

    sort(arr,arr+s);

    std::uniform_int_distribution<int> r_size(0, s-1);
    for (int i = 0; i < max(1,s/10); i++){
        int poz1 = r_size(gen);
        int poz2 = r_size(gen);

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

void str_sort(int* arr, int s){
    sort(arr,arr+s);
}

void bubble_sort(int arr[], int s){
    for (int i = 0; i < s; i++){
        for (int j = 0; j < s-i; j++){
            if (arr[j] > arr[j+1]){
                int aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
        }
    }
}

void count_sort(int* arr, int s){
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
}

void quick(int* arr,int l,int r){
    if (l < r){
        std::uniform_int_distribution<int> r_size(l, r);
        int poz_random = r_size(gen);
        int pivot = arr[poz_random];
        vector<int> mici;
        vector<int> egale;
        vector<int> mari;
        for (int i = l; i<= r; i++)
            if (arr[i] < pivot)
                mici.push_back(arr[i]);
            else if (arr[i] > pivot)
                mari.push_back(arr[i]);
            else
                egale.push_back(arr[i]);

        int k = l;
        for (int i = 0; i < mici.size(); i++)
            arr[k++] = mici[i];
        for (int i = 0; i < egale.size(); i++)
            arr[k++] = egale[i];
        for (int i = 0; i < mari.size(); i++)
            arr[k++] = mari[i];

        quick(arr,l,l+mici.size()-1);
        quick(arr,l+mici.size()+egale.size(),r);
    }
}

void quicksort(int* arr, int s){
    quick(arr,0,s-1);
}

void combine(int* arr, int l, int mij, int r){
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

void merges(int* arr, int l, int r){
    if (l < r){
        int mij = l + (r-l)/2;
        merges(arr,l,mij);
        merges(arr,mij+1,r);

        combine(arr,l,mij,r);
    }
}

void mergesort(int* arr, int s){

    merges(arr,0,s-1);
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

void radixsort(int arr[], int s){
    int maxim = get_max(arr,s);
    int nr_bites = log2(maxim)+1;

    radix(arr,0,s-1,nr_bites);
}

void radix_suff(int arr[], int l, int r, int pos, int maxim){
    if (1 << pos > maxim) return;
    vector <int> has_0;
    vector <int> has_1;
    for (int i=l; i <= r; i++){
        if (arr[i] & 1 << pos)
            has_1.push_back(arr[i]);
        else
            has_0.push_back(arr[i]);
    }
    int k = l;
    for (int i =0; i < has_0.size();i++)
        arr[k++] = has_0[i];
    for (int i =0; i < has_1.size();i++)
        arr[k++] = has_1[i];

    radix_suff(arr,l,r,pos+1,maxim);
}

void radixsort_suff(int arr[], int s){

    int maxim = get_max(arr,s);

    radix_suff(arr,0,s-1,0,maxim);
}

int main()
{
    bool a_crapat = false;

    vector<pair<string,function<void(int*, int)>>> sort_types;

    sort_types.push_back(make_pair("STL Sort", str_sort));
    sort_types.push_back(make_pair("Quicksort", quicksort));
    sort_types.push_back(make_pair("Mergesort", mergesort));
    sort_types.push_back(make_pair("Count sort", count_sort));
    sort_types.push_back(make_pair("Radix sort", radixsort));
    sort_types.push_back(make_pair("Radix sort suffix", radixsort_suff));
    sort_types.push_back(make_pair("Bubble sort", bubble_sort));

    vector<pair<string,function<int*(int[], int)>>> arr_types;

    arr_types.push_back(make_pair("Random array", generate_random_array));
    arr_types.push_back(make_pair("Almost sorted array", generate_almost_sorted_array));
    arr_types.push_back(make_pair("Reversed almost sorted array", generate_reversed_almost_sorted_array));
    arr_types.push_back(make_pair("Constant array", generate_const_array));

    int t;
    fin >> t;
    for (int i = 0; i < t; i++){
        fin >> _size >> _max;
        rng = std::uniform_int_distribution<int>(0, _max);

        for (auto sort_type:sort_types){
            cout << "\n\n - - - - - - - - - - - - - - " << sort_type.first << ":\n\n";

            for (auto arr_type:arr_types){
                cout << " Mod de construire vector: " << arr_type.first << '\n';
                cout << " Construire vector...\r";
                arr_type.second(i_arr, _size);
                unsigned __int64 _start = get_milliseconds();
                //print_arr(arr,_size);

                cout << " Sortare vector...   \r";
                sort_type.second(i_arr, _size);
                //print_arr(arr,_size);
                unsigned __int64 _end = get_milliseconds();
                cout << " Durata in milisecunde --> " << _end - _start << '\n';
                if (is_sorted(i_arr, _size))
                    cout << " Sortat\n\n";
                else{
                    cout << "Nesortat\n\n";
                    a_crapat = true;
                }
            }
        }
    }
    if (a_crapat)
        cout << "RIP";
}
