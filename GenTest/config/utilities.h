/******************************************************************************
 * Project: Utilities Template
 * Author:
 * Created (dd-mm-yyyy):
 * Description: none
 * Version: >= C++14, Windows
 ******************************************************************************/
#ifndef UTILITIES_H
#define UTILITIES_H

#include <bits/stdc++.h>
using namespace std;

namespace Utilities {

    /// ===================== STRING UTILITIES =====================
    namespace String {

        /// Convert a number to a string
        inline string toString(long long num) {
            return to_string(num);
        }

        /// Remove leading and trailing whitespace from a string
        inline string trim(const string &s) {
            int l = 0, r = (int)s.size() - 1;
            while (l <= r && isspace(static_cast<unsigned char>(s[l]))) l++;
            while (r >= l && isspace(static_cast<unsigned char>(s[r]))) r--;
            return s.substr(l, r - l + 1);
        }

        /// Split a string into tokens by a given delimiter
        inline vector<string> split(const string &s, char delim = ' ') {
            vector<string> tokens;
            string token;
            stringstream ss(s);
            while (getline(ss, token, delim)) {
                tokens.push_back(token);
            }
            return tokens;
        }

        /// Join a list of strings with a delimiter
        inline string join(const vector<string> &arr, const string &delim = " ") {
            string res;
            for (size_t i = 0; i < arr.size(); i++) {
                if (i) res += delim;
                res += arr[i];
            }
            return res;
        }

        /// Convert all characters of a string to uppercase
        inline string toUpper(string s) {
            for (auto &c : s) c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
            return s;
        }

        /// Convert all characters of a string to lowercase
        inline string toLower(string s) {
            for (auto &c : s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            return s;
        }

        /// Remove everything from the last occurrence of `ch` (inclusive) to the end
        inline string removeFromLast(string s, char ch) {
            size_t pos = s.find_last_of(ch);
            if (pos != string::npos) {
                s.erase(pos);  // remove from that index to end
            }
            return s;
        }
    }

    /// ===================== NUMBER UTILITIES =====================
    namespace Number {

        /// Check if a number is prime
        inline bool isPrime(long long n) {
            if (n < 2) return false;
            for (long long i = 2; i * i <= n; i++)
                if (n % i == 0) return false;
            return true;
        }

        /// Compute the greatest common divisor (GCD) of two numbers
        inline long long gcd(long long a, long long b) {
            return b == 0 ? a : gcd(b, a % b);
        }

        /// Compute the least common multiple (LCM) of two numbers
        inline long long lcm(long long a, long long b) {
            return a / gcd(a, b) * b;
        }

        /// Format a number (e.g. 1234567 -> "1 234 567")
        inline string commaFormat(long long n, string delim = " ") {
            string s = to_string(n);
            int len = s.size();
            for (int i = len - 3; i > 0; i -= 3)
                s.insert(i, delim);
            return s;
        }
    }

    /// ===================== TIME UTILITIES =====================
    namespace Time {

        /// Get the current date and time as a formatted string (YYYY-MM-DD HH:MM:SS)
        inline string currentDateTime() {
            time_t now = time(nullptr);
            tm *ltm = localtime(&now);
            char buf[64];
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
            return string(buf);
        }
    }

} // namespace Utilities

#endif // UTILITIES_H
