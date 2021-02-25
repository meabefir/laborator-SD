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

template <typename t>
class Arr{
    vector<pair<string,function<void()>>> arr_types;

    public:
    // stiu ca astea de obicei se fac private cu setere si getere dar nu aici
    int _size;
    int _max;
    t *data;

        Arr(int _s, int _m){
            _size = _s;
            _max = _m;
            data = new t[_size];
        }

        Arr(Arr &other){
            _size = other._size;
            data = new t[_size];
            for (int i = 0; i < _size; i++)
                data[i] = other.data[i];
        }

        ~Arr(){
            delete []data;
        }

        void init(t value){
            for (int i = 0; i < _size; i++)
                data[i] = value;
        }

        void print(){
            for (int i = 0; i < _size; i++)
                cout << data[i] << ' ';
            cout << '\n';
        }

        void swp(int pos1, int pos2){
            t aux = data[pos1];
            data[pos1] = data[pos2];
            data[pos2] = aux;
        }

        t& operator[] (int pos){
            return data[pos];
        }

        void set_pos(int pos, t value){
            data[pos] = value;
        }
};

float get_random_float() {
            float random = ((float) rand()) / (float) RAND_MAX;
            return random;
        }

template <typename t>
t get_random_value(uniform_int_distribution<int> rng, t arr[]){
    if (*typeid(t).name() == 'i')
        return rng(gen);
    else if (*typeid(t).name() == 'f')
        return get_random_float();
    else if (*typeid(t).name() == 'c')
        return rand()%26+97;
}

template <typename t>
void generate_random_array(t arr[], int s, int maxim){
    std::uniform_int_distribution<int> rng(0, maxim);
    for (int i = 0; i < s; i++){
        arr[i] = get_random_value(rng,arr);
    }
}

template <typename t>
void generate_almost_sorted_array(t arr[], int s, int maxim){
    generate_random_array(arr, s, maxim);

    sort(arr,arr+s);

    std::uniform_int_distribution<int> r_size(0, s-1);
    for (int i = 0; i < max(1,s/10); i++){
        int poz1 = r_size(gen);
        int poz2 = r_size(gen);

        t aux = arr[poz1];
        arr[poz1] = arr[poz2];
        arr[poz2] = aux;
    }
}

template <typename t>
void generate_reversed_almost_sorted_array(t arr[], int s, int maxim){
    generate_almost_sorted_array(arr, s, maxim);

    for (int i = 0; i < s/2; i++){
        t aux = arr[i];
        arr[i] = arr[s-i-1];
        arr[s-i-1] = aux;
    }
}

template <typename t>
void generate_const_array(t arr[], int s){
    for (int i = 0; i < s; i++)
        arr[i] = 0;
}


template <typename t>
bool is_sorted(t& arr, int s){
    for (int i = 0; i < s-1; i++){
        if (arr[i] > arr[i+1]) return false;
    }
    return true;
}

template <typename t>
void print_arr(t arr){
    cout << '\n';
    for (int i =0; i < arr._size; i++)
        cout << arr.data[i] << ' ';
}

unsigned __int64 get_milliseconds(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

template <typename t>
t get_max(t arr[], int s){
    t maxim = arr[0];
    for (int i =1; i < s; i++){
        if (arr[i] > maxim)
            maxim = arr[i];
    }
    return maxim;
}

template <typename t>
void stl_sort(t& arr, int s){
    sort(arr.data,arr.data+s);
}

template <typename t>
void bubble_sort(t arr[], int s){
    for (int i = 0; i < s; i++){
        for (int j = 0; j < s-i; j++){
            if (arr[j] > arr[j+1]){
                t aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
        }
    }
}

template <typename t>
void count_sort(t arr[], int s){
    if (*typeid(t).name() == 'f'){
        cout << " Count sort nu poate sorta floats! \n";
        return;
    }
    t maxim = get_max(arr,s);

    Arr<int> frec(maxim,s);
    frec.init(0);

    //for (int i =0; i <= maxim; i++)
    //    frec[i] = 0;

    for (int i = 0; i < s; i++)
        frec.set_pos((int)arr[i],frec[(int)arr[i]]+1);

    int k = 0;
    for (int i = 0; i <= maxim; i++){
        for (int j = 1; j <= frec[i];j++)
            arr[k++] = i;
    }
}

template <typename t>
void quick(t arr[],int l,int r){
    if (l < r){
        std::uniform_int_distribution<int> r_size(l, r);
        int poz_random = r_size(gen);
        t pivot = arr[poz_random];
        vector<t> mici;
        vector<t> egale;
        vector<t> mari;
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

template <typename t>
void quicksort(t arr[], int s){
    quick(arr,0,s-1);
}

template <typename t>
void combine(t arr[], int l, int mij, int r){
    vector <t> st;
    vector <t> dr;

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

template <typename t>
void merges(t& arr, int l, int r){
    if (l < r){
        int mij = l + (r-l)/2;
        merges(arr,l,mij);
        merges(arr,mij+1,r);

        combine(arr,l,mij,r);
    }
}

template <typename t>
void mergesort(t& arr, int s){
    merges(arr,0,s-1);
}

template <typename t>
void radix(t arr[], int l, int r, int pos){
    if (pos < 0) return;
    if (l >= r) return;
    vector <t> has_0;
    vector <t> has_1;
    for (int i=l; i <= r; i++){
        if ((int)arr[i] & (1<<pos))
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

template <typename t>
void radixsort(t arr[], int s){
    if (*typeid(t).name() == 'f'){
        cout << " Radix nu merge pentru floats! \n";
        return;
    }
    t maxim = get_max(arr,s);
    int nr_bites = log2(maxim)+1;

    radix(arr,0,s-1,nr_bites);
}

template <typename t>
void radix_suff(t arr[], int l, int r, int pos, int maxim){
    if (1 << pos > maxim) return;
    vector <t> has_0;
    vector <t> has_1;
    try {
        for (int i=l; i <= r; i++){
            if ((int)arr[i] & 1 << pos)
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
    } catch (int x){return;}
}

template <typename t>
void radixsort_suff(t arr[], int s){
    if (*typeid(t).name() == 'f'){
        cout << " Radix nu merge pentru floats! \n";
        return;
    }

    t maxim = get_max(arr,s);

    radix_suff(arr,0,s-1,0,maxim);
}

int main()
{
    srand(time(0));
    int generate_nr = 4;
    int sortari_nr = 7;


    int t;
    fin >> t;
    for (int i = 0; i < t; i++){
        fin >> _size >> _max;
        rng = std::uniform_int_distribution<int>(0, _max);
        Arr<char> v(_size,_max); ///////////////////////////////////////////////////////////////////

        for (int i = 1; i <= generate_nr; i++){
            switch(i){
            case 1:
                generate_random_array(v.data,v._size,v._max);
                cout << " - - - - - - Elemente random:\n\n";
                break;
            case 2:
                generate_almost_sorted_array(v.data,v._size,v._max);
                cout << " - - - - - - Elemente aproape random:\n\n";
                break;
            case 3:
                generate_reversed_almost_sorted_array(v.data,v._size,v._max);
                cout << " - - - - - - Elemente aproape random in ordine inversa:\n\n";
                break;
            case 4:
                generate_const_array(v.data,v._size);
                cout << " - - - - - - Vector constant:\n\n";
                break;
            }

            for (int j = 1; j <= sortari_nr; j++){
                Arr<char> copie(v); ///////////////////////////////////////////////////////////////////

                unsigned __int64 _start = get_milliseconds();
                switch(j){
                case 1:
                    cout << " STL sort ";
                    stl_sort(copie,copie._size);
                    break;
                case 2:
                    cout << " Quicksort ";
                    quicksort(copie.data,copie._size);
                    break;
                case 3:
                    cout << " Mergesort ";
                    mergesort(copie.data,copie._size);
                    break;
                case 4:
                    cout << " Radixsort ";
                    radixsort(copie.data,copie._size);
                    break;
                case 5:
                    cout << " Radixsort sufix ";
                    radixsort_suff(copie.data,copie._size);
                    break;
                case 6:
                    cout << " Count sort ";
                    count_sort(copie.data,copie._size);
                    break;
                case 7:
                    cout << " Bubble sort ";
                    bubble_sort(copie.data,copie._size);
                    break;
                }
                unsigned __int64 _end = get_milliseconds();
                unsigned __int64 _total = _end - _start;

                cout << "--> " << _total << " ms" << '\n';

            }
            cout << "\n\n";
        }
    }


    return 0;
}
