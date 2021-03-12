#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <string>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <bits.h>
#include <bitset>
#include <map>

using namespace std;

ifstream f ("in.in");

std::mt19937 gen(time(0));

int max_size,max_value;

unsigned __int64 get_milliseconds(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

template <class t>
t get_max(vector<t> &arr){
    if (typeid(t) == typeid(string))
        return NULL;
    t _max = arr[0];
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] > _max)
            _max = arr[i];
    return _max;
}

string gen_random_string(const int len) {
    string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    return tmp_s;

}

void generate_random(vector<int> &v){
    std::uniform_int_distribution<int> u_int(0, max_value);

    for (int i = 0; i < v.size(); i++)
        v[i] = u_int(gen);
}

void generate_random(vector<double> &v){
    std::uniform_real_distribution<double> u_double(0.0, 100);

    for (int i = 0; i < v.size(); i++)
        v[i] = u_double(gen);
}

void generate_random(vector<string> &v){
    for (int i = 0; i < v.size(); i++)
        v[i] = gen_random_string(rand()%(int)log10(max_value)+1);
}

template <class t>
void swap(t* a, t* b)
{
    t aux = *a;
    *a = *b;
    *b = aux;
}

template <class t>
void generate_almost_sorted(vector<t> &arr){
    generate_random(arr);
    sort(arr.begin(),arr.end());
    std::uniform_int_distribution<int> random_pos (0,arr.size()-1);

    for (int i = 0; i < max((int)arr.size()/20,1); i++){
        int pos1 = random_pos(gen);
        int pos2 = random_pos(gen);
        swap(&arr[pos1],&arr[pos2]);
    }
}

template <class t>
void generate_reversed_almost_sorted(vector<t> &arr){
    generate_random(arr);
    sort(arr.begin(),arr.end(),greater<t>());
    std::uniform_int_distribution<int> random_pos (0,arr.size()-1);

    for (int i = 0; i < max((int)arr.size()/20,1); i++){
        int pos1 = random_pos(gen);
        int pos2 = random_pos(gen);
        swap(&arr[pos1],&arr[pos2]);
    }
}

void generate_const(vector<int> &v){
    std::uniform_int_distribution<int> u_int(0, max_value);
    int val = u_int(gen);

    for (int i = 0; i < v.size(); i++)
        v[i] = val;
}

void generate_const(vector<double> &v){
    std::uniform_real_distribution<double> u_double(0.0, 100);
    double val = u_double(gen);

    for (int i = 0; i < v.size(); i++)
        v[i] = val;
}

void generate_const(vector<string> &v){
    string val = gen_random_string(rand()%(int)log10(max_value)+1);

    for (int i = 0; i < v.size(); i++)
        v[i] = val;
}

template <class t>
bool is_sorted(vector<t> &v){
    for (int i = 0; i < v.size()-1; i++)
        if (v[i] > v[i+1])
            return false;
    return true;
}

template <class t>
void stl_sort(vector<t> &arr){
    sort(arr.begin(),arr.end());
}

template <class t>
void quickk(vector<t> &arr,int l,int r,vector<t> &copie){
    if (l < r){
        std::uniform_int_distribution<int> r_size(l, r);
        int poz_random = r_size(gen);
        t pivot = arr[poz_random];
        int ll = l;
        int rr = r;
        int egale = 0;
        for (int i = l; i<= r; i++)
            if (arr[i] < pivot)
                copie[ll++] = arr[i];
            else if (arr[i] > pivot)
                copie[rr--] = arr[i];
            else
                egale++;

        for (int i = 0; i < egale; i++)
            copie[rr--] = pivot;

        int k = l;
        for (int i = l; i <= r; i++)
            arr[k++] = copie[i];

        quickk(arr,l,ll-1,copie);
        quickk(arr,ll+egale,r,copie);
    }
}

template <class t>
void quick_sort(vector<t> &arr){
    vector<t> copie(arr.size());
    quickk(arr,0,arr.size()-1,copie);
}

template <class t>
void combine(vector<t> &arr, int l, int mij, int r, vector<t> &st, vector<t> &dr){
    int idx_st = 0, idx_dr = 0;
    for (int i = l; i <= mij; i++){
        st[idx_st++] = arr[i];
    }
    for (int i = mij+1; i <= r; i++){
        dr[idx_dr++] = arr[i];
    }

    int i = 0, j = 0, k = l;
    while (i < idx_st && j < idx_dr){
        if (st[i] < dr[j])
            arr[k++] = st[i++];
        else
            arr[k++] = dr[j++];
    }
    while (i < idx_st)
        arr[k++] = st[i++];
    while (j < idx_dr)
        arr[k++] = dr[j++];
}

template <class t>
void merges(vector<t> &arr, int l, int r, vector<t> &st, vector<t> &dr){
    if (l < r){
        int mij = l + (r-l)/2;
        merges(arr,l,mij,st,dr);
        merges(arr,mij+1,r,st,dr);

        combine(arr,l,mij,r,st,dr);
    }
}

template <class t>
void merge_sort(vector<t> &arr){
    vector<t> st(arr.size()/2+1);
    vector<t> dr(arr.size()/2+1);
    merges(arr,0,arr.size()-1,st,dr);
}

void radix_sort(vector<string> &arr){
    cout << "Data type not supported!\n";
    return;
}

void radix_sort(vector<double> &arr){
    cout << "Data type not supported!\n";
    return;
}

template <class t>
void radix(vector<t> &arr, int l, int r, int pos){
    if (pos < 0) return;
    if (l >= r) return;
    int aux_st = l;
    int aux_dr = r;
    int bit_st, bit_dr;
    while (aux_st < aux_dr){
        bit_st = arr[aux_st] & (1 << pos);
        bit_dr = arr[aux_dr] & (1 << pos);

        if (bit_st && bit_dr){
            swap(&arr[aux_st],&arr[--aux_dr]);
            aux_dr --;
        } else if (!bit_st && !bit_dr){
            swap(&arr[++aux_st],&arr[aux_dr]);
            aux_st ++;
        } else if (bit_st && !bit_dr){
            swap(&arr[aux_st++],&arr[aux_dr--]);
        } else if (!bit_st && bit_dr){
            aux_st ++;
            aux_dr --;
        }
    }
    int ii = l;
    while (!(arr[ii] & (1 << pos)) && ii <= r)
        ii ++;
    ii--;

    radix(arr,l,ii,pos-1);
    radix(arr,ii+1,r,pos-1);
}

template <class t>
void radix_sort(vector<t> &arr){
    t _max = get_max(arr);
    int _max_pos = log2(_max)+1;

    radix(arr,0,arr.size()-1,_max_pos);
}

template <class t>
void radix_suff(vector<t> &arr, int l, int r, int pos, t maxim, vector<t> &has_0, vector<t> &has_1){
    if (1 << pos > maxim) return;
    int idx_0 = 0;
    int idx_1 = 0;
    for (int i=l; i <= r; i++){
        if (arr[i] & 1 << pos)
            has_1[idx_1++] = arr[i];
        else
            has_0[idx_0++] = arr[i];
    }
    int k = l;
    for (int i =0; i < idx_0;i++)
        arr[k++] = has_0[i];
    for (int i =0; i < idx_1;i++)
        arr[k++] = has_1[i];

    radix_suff(arr,l,r,pos+1,maxim,has_0,has_1);
}

void radix_sort_suff(vector<string> &arr){
    cout << "Data type not supported!\n";
    return;
}

void radix_sort_suff(vector<double> &arr){
    cout << "Data type not supported!\n";
    return;
}

template <class t>
void radix_sort_suff(vector<t> &arr){
    if (typeid(t) != typeid(int)){
        cout << "Data type not supported!\n";
        return;
    }
    t maxim = get_max(arr);
    vector<t> has_0(arr.size());
    vector<t> has_1(arr.size());
    radix_suff(arr,0,arr.size()-1,0,maxim,has_0,has_1);
}

template <class t>
void bubble_sort(vector<t> &arr){
    if (arr.size() > 10000){
        cout << " It would take too long for bubble sort to sort this!\n";
        return;
    }
    for (int i = 0; i < arr.size()-1; i++)
        for (int j = 0; j < arr.size()-1-i; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j],&arr[j+1]);
}

void count_sort(vector<int> &arr){
    int _max = get_max(arr);

    vector<int> freq(_max+1,0);
    for (int i = 0; i < arr.size(); i++)
        freq[arr[i]] ++;

    int k = 0;
    for (int i = 0; i < freq.size(); i++)
        for (int j = 0; j < freq[i]; j++)
            arr[k++] = i;
}

template <class t>
void count_sort(vector<t> &arr){
    map<t,int> freq;
    for (int i = 0; i < arr.size(); i++){
        if (freq.find(arr[i]) == freq.end())
            freq[arr[i]] = 1;
        else
            freq[arr[i]] ++;
    }
    int k = 0;
    for (auto p: freq){
        for (int i = 0; i < p.second; i++)
            arr[k++] = p.first;
    }
}


int main()
{
    int sort_types = 7;
    int generate_types = 4;

    srand(time(0));
    int t;
    f >> t;
    for (int tt = 0; tt < t; tt++){
        f >> max_size >> max_value;
        vector<double> arr(max_size);

        for (int generate_type = 1; generate_type <= generate_types; generate_type++){
            switch(generate_type){
            case 1:
                cout << " - - - - Randomly generated vectors: \n";
                generate_random(arr);
                break;
            case 2:
                cout << " - - - - Almost sorted vectors: \n";
                generate_almost_sorted(arr);
                break;
            case 3:
                cout << " - - - - Almost reversed sorted vectors: \n";
                generate_reversed_almost_sorted(arr);
                break;
            case 4:
                cout << " - - - - Constant vector: \n";
                generate_const(arr);
                break;
            }

            for (int sort_type = 1; sort_type <= sort_types; sort_type++){
                vector<double> copie(arr);

                unsigned __int64 _start = get_milliseconds();
                switch(sort_type){
                case 1:
                    cout << " --- STL sort ";
                    stl_sort(copie);
                    break;
                case 2:
                    cout << " --- Quick Sort ";
                    quick_sort(copie);
                    break;
                case 3:
                    cout << " --- Merge Sort ";
                    merge_sort(copie);
                    break;
                case 4:
                    cout << " --- Radix Sort ";
                    radix_sort(copie);
                    break;
                case 5:
                    cout << " --- Radix Sort Suffix ";
                    radix_sort_suff(copie);
                    break;
                case 6:
                    cout << " --- Count Sort ";
                    count_sort(copie);
                    break;
                case 7:
                    cout << " --- Bubble Sort ";
                    bubble_sort(copie);
                    break;
                }
                unsigned __int64 _end = get_milliseconds();
                unsigned __int64 _total = _end - _start;
                cout << " --> " << _total << " ms (" << (is_sorted(copie) ? "sorted" : "not sorted") << ") \n";
            }
            cout << "\n\n";
        }
        cout << "\n\n\n\n\n";
    }

    return 0;
}
