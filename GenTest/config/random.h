/******************************************************************************
 * Project: Random Generator Template
 * Author: Phan Thanh Hung - hungg261
 * Created (dd-mm-yyyy): 01-11-2025
 * Description:
 *      Template for random generation.
 * Version: > C++14
 ******************************************************************************/
#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

namespace RandomGen{

struct NumberGen{
    mt19937 rng;
    long long seed;

    NumberGen(){ rng.seed(seed = chrono::steady_clock::now().time_since_epoch().count()); }
    NumberGen(long long _seed) : seed(_seed){ rng.seed(_seed); }

    bool operator == (const NumberGen &other) const{ return this->seed == other.seed; }

    void setSeed(int _seed){ seed = _seed; rng.seed(_seed); }

    //////////////////////////////////////////////////////////

    /// Random integer in [L; R]
    template <typename U = int>
    typename enable_if<is_integral<U>::value, U>::type
    Rand(U L, U R){
        assert(L <= R);
        return uniform_int_distribution<U>(L, R)(rng);
    }

    /// Random real in [L; R]
    template <typename U = double>
    typename enable_if<is_floating_point<U>::value, U>::type
    Rand(U L, U R){
        assert(L <= R);
        return uniform_real_distribution<U>(L, R)(rng);
    }

    /// Random between 0 and 1
    bool RandBool(){ return Rand(0, 1); }

    /// Random real between [0; 1]
    template <typename U = double>
    typename enable_if<is_floating_point<U>::value, U>::type
    Rand(){ return Rand<U>(0, 1); }

    /// Random __int128 in [L; R]
    __int128 Rand128(__int128 L, __int128 R){
        unsigned __int128 range = R - L + 1;
        unsigned __int128 x = ((unsigned __int128)rng() * rng() << 64) | rng();
        return L + (x % range);
    }

    /// Random bigint in [L; R]
    string BigRand(string L, string R){
        auto strip = [](string s){
            bool neg = false;
            if (s[0] == '-') neg = true, s = s.substr(1);
            s.erase(0, s.find_first_not_of('0'));
            if (s.empty()) s = "0";
            return (neg && s != "0" ? "-" : "") + s;
        };

        auto cmp = [](const string &a, const string &b){
            if (a[0] == '-' && b[0] != '-') return -1;
            if (a[0] != '-' && b[0] == '-') return 1;
            bool neg = (a[0] == '-');
            string A = neg ? a.substr(1) : a, B = neg ? b.substr(1) : b;
            if (A.size() != B.size()) return (A.size() < B.size()) ^ neg ? -1 : 1;
            if (A == B) return 0;
            return (A < B) ^ neg ? -1 : 1;
        };

        auto addAbs = [](string a, string b){
            if (a.size() < b.size()) swap(a, b);
            reverse(a.begin(), a.end());
            reverse(b.begin(), b.end());
            int carry = 0;
            for (int i = 0; i < (int)a.size(); i++){
                int d = (a[i] - '0') + (i < (int)b.size() ? b[i] - '0' : 0) + carry;
                a[i] = '0' + (d % 10);
                carry = d / 10;
            }
            if (carry) a.push_back('0' + carry);
            reverse(a.begin(), a.end());
            return a;
        };

        auto subAbs = [](string a, string b){
            reverse(a.begin(), a.end());
            reverse(b.begin(), b.end());
            int carry = 0;
            for (int i = 0; i < (int)a.size(); i++){
                int d = (a[i] - '0') - (i < (int)b.size() ? b[i] - '0' : 0) - carry;
                if (d < 0) d += 10, carry = 1; else carry = 0;
                a[i] = '0' + d;
            }
            while (a.size() > 1 && a.back() == '0') a.pop_back();
            reverse(a.begin(), a.end());
            return a;
        };

        auto randSameLen = [&](const string &A, const string &B){
            string res;
            bool tightL = true, tightR = true;
            for (int i = 0; i < (int)A.size(); i++){
                int low = tightL ? A[i] - '0' : 0;
                int high = tightR ? B[i] - '0' : 9;
                int d = Rand(low, high);
                res.push_back('0' + d);
                if (d != low) tightL = false;
                if (d != high) tightR = false;
            }
            return res;
        };

        auto randPositive = [&](string L, string R){
            L = strip(L);
            R = strip(R);
            if (cmp(L, R) > 0) swap(L, R);
            if (L.size() == R.size()) return randSameLen(L, R);
            int len = Rand((int)L.size(), (int)R.size());
            if (len == (int)L.size()) return randSameLen(L, string(R.size() - L.size(), '9') + R);
            if (len == (int)R.size()) return randSameLen(string(L.size(), '0') + L, R);
            string res(len, '0');
            res[0] = '1' + Rand(0, 8);
            for (int i = 1; i < len; i++) res[i] = '0' + Rand(0, 9);
            return res;
        };

        if (L == R) return L;
        bool negL = (L[0] == '-'), negR = (R[0] == '-');
        string absL = negL ? L.substr(1) : L;
        string absR = negR ? R.substr(1) : R;

        if (negL && !negR){
            if (Rand(0, 1)){
                string x = randPositive("0", absR);
                return x;
            } else{
                string x = randPositive("0", absL);
                if (x == "0") return x;
                return "-" + x;
            }
        }

        if (!negL && !negR) return randPositive(L, R);
        if (negL && negR){
            if (cmp(absL, absR) < 0) swap(absL, absR);
            return "-" + randPositive(absR, absL);
        }

        return "0";
    }
};

struct StringGen{
    mt19937 rng;
    long long seed;

    NumberGen numGen;

    string LOWER_CHAR = "abcdefghijklmnopqrstuvwxyz";
    string UPPER_CHAR = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string NUM_CHAR = "0123456789";
    string SPECIAL_CHAR = "`~!@#$%^&*()_+{}|:\"<>?-=[]\\;',./";
    string ALL_CHAR = LOWER_CHAR + UPPER_CHAR + NUM_CHAR + SPECIAL_CHAR;

    StringGen(){ rng.seed(seed = chrono::steady_clock::now().time_since_epoch().count()); }
    StringGen(long long _seed) : seed(_seed){ rng.seed(_seed); }

    bool operator == (const StringGen &other) const{ return this->seed == other.seed; }

    void setSeed(int _seed){ seed = _seed; rng.seed(_seed); }

    //////////////////////////////////////////////////////////

    /// Random character in a string
    char RandChar(const string& range){ return range[numGen.Rand(0, (int) range.size() - 1)]; }
    char RandChoice(const string& object){ return RandChar(object); }

    /// Random string with custom characters
    string RandString(int len, const string& range){
        string res;
        while(len--) res = res + RandChar(range);
        return res;
    }

    /// Shuffle string
    string Shuffle(const string& original){
        string res = original;
        shuffle(begin(res), end(res), rng);
        return res;
    }
};

struct VectorGen{
    mt19937 rng;
    long long seed;

    NumberGen numGen;

    VectorGen(){ rng.seed(seed = chrono::steady_clock::now().time_since_epoch().count()); }
    VectorGen(long long _seed) : seed(_seed){ rng.seed(_seed); }

    bool operator == (const VectorGen &other) const{ return this->seed == other.seed; }

    void setSeed(int _seed){ seed = _seed; rng.seed(_seed); }

    //////////////////////////////////////////////////////////

    /// Pick a random element
    template<typename T>
    T Choice(const vector<T>& cont){
        return cont[numGen.Rand(0, (int) cont.size() - 1)];
    }

    /// Pick a random element from index L to R
    template<typename T>
    T Choice(const vector<T>& cont, int L, int R){
        return cont[numGen.Rand(L, R)];
    }

    /// Shuffle vector
    template<typename T>
    vector<T> Shuffle(const vector<T>& cont){
        vector<T> res = cont;
        shuffle(res.begin(), res.end(), rng);
        return res;
    }
};

}

#endif // RANDOM_H

