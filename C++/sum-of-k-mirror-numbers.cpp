// Time:  O(10^6), the most times of finding x is 665502 (k = 7, n = 30)
// Space: O(1)

class Solution {
public:
    long long kMirror(int k, int n) {
        const int base1 = k, base2 = 10;  // (10, k) is slower
        int64_t result = 0;
        vector<int> prefix_num(2, 1), cnt(2), total(2, base1 - 1);
        bool even = false;
        while (n--) {
            int64_t x;
            do {
                x = get_mirror(prefix_num[even]++, base1, even);
                if (++cnt[even] == total[even]) {
                    cnt[even] = 0;
                    total[even] *= base1;
                    even = !even;
                }
            } while (x != reverse(x, base2));
            result += x;
        }
        return result;
    }

private:
    int64_t get_mirror(int n, int base, bool even) {
        int64_t result = n;
        if (!even) {
            n /= base;
        }
        for (; n; n /= base) {
            result = result * base + (n % base);
        }
        return result;
    }

    int64_t reverse(int64_t n, int base) {
        int64_t result = 0;
        for (; n; n /= base) {
            result = result * base + n % base;
        }
        return result;
    }
};

// Time:  O(10^6), the most times of finding x is 665502 (k = 7, n = 30)
// Space: O(1)
class Solution2 {
public:
    long long kMirror(int k, int n) {
        string s = "0";
        int64_t result = 0;
        while (n--) {
            result += mirror_num(k, &s);
        }
        return result;
    }

private:
    int64_t mirror_num(int k, string *s) {
        int64_t result;
        do {
            result = next_num_in_base_k(k, s);
        } while (!is_mirror(to_string(result)));
        return result;
    }

    bool is_mirror(const string& s) {
        int left = 0, right = size(s) - 1;
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }
    
    int64_t next_num_in_base_k(int k, string *s) {
        int result = 0;
        for (int i = size(*s) / 2; i < size(*s); ++i) {
            if ((*s)[i] + 1 - k < '0') {
                (*s)[i] = (*s)[size(*s) - 1 - i] = (*s)[i] + 1;
                break;
            }
            (*s)[i] = (*s)[size(*s) - 1 - i] = '0';
        }
        if ((*s)[0] == '0') {
            s->back() = '1';
            s->insert(begin(*s), '1');
        }
        return to_int_from_base_k(*s, k);
    }

    int64_t to_int_from_base_k(const string& s, int k) {
        int64_t result = 0;
        for (int64_t i = size(s) - 1, base = 1; i >= 0; --i, base *= k) {
            result += (s[i] - '0') * base;
        }
        return result;
    }
};
