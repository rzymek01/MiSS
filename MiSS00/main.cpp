//DOC:
// https://gmplib.org/manual/Headers-and-Libraries.html#Headers-and-Libraries
//
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <gmp.h>

std::string removeTrailingZeros(std::string &x) {
    x.erase(x.find_last_not_of('0') + 1, std::string::npos);
    if ('.' == (*x.rbegin())) {
        x.erase(x.size() - 1);
    }
    return x;
}

int main(int argc, char *argv[]) {
    unsigned long int n = 0, d;
    mpz_t acc, acc2, tmp, multiplicand, quotient;
    std::string x;
    std::stringstream convert;

    typedef std::map<unsigned long int, unsigned long int>::iterator pos_map_it;
    std::vector<std::string> sequence;
    std::map<unsigned long int, unsigned long int> posMap;
    unsigned long int period = 0;

    convert << argv[1];
    convert >> d;

    mpz_init(acc);
    mpz_init(acc2);
    mpz_init(tmp);
    mpz_init(multiplicand);
    mpz_init(quotient);

    while (std::cin >> x) {
        mpz_set_str(tmp, x.c_str(), 10);
        mpz_add(acc, acc, tmp);
        mpz_addmul(acc2, tmp, tmp);
        ++n;

        // 3) period
        sequence.push_back(x);

//        for (pos_map_it it = posMap.begin(); it != posMap.end(); ) {
//            if (x == sequence[it->second]) {
//                it->second = (it->second + 1) % (it->first);
//                it++;
//            } else {
//                posMap.erase(it++);
//            }
//        }
//
//        posMap[n] = 0;
    }

//    //<debug>
//    for (std::vector<std::string>::iterator it = sequence.begin(); it != sequence.end(); ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl;
//    //</debug>
//    period = posMap.begin()->first;
//
//    std::vector<std::string>().swap(sequence);
//    posMap.clear();
    //

    mpz_init_set_ui(multiplicand, 10);
    mpz_pow_ui(multiplicand, multiplicand, d);

    // 1) mean
    mpz_mul(tmp, acc, multiplicand);
    mpz_tdiv_q_ui(quotient, tmp, n);
    char *result = mpz_get_str(NULL, 10, quotient);
    x = std::string(result);

    if (x.length() <= d) {
        x.insert(0, d - x.length() + 1, '0');
    }
    x.insert(x.length() - d, 1, '.');
    removeTrailingZeros(x);

    std::cout << x << std::endl;

    // 2) variance
    mpz_mul(acc, acc, acc);
    mpz_mul_ui(acc2, acc2, n);
    mpz_sub(acc2, acc2, acc);
    mpz_mul(acc2, multiplicand, acc2);

    mpz_set_ui(acc, n);
    mpz_mul(acc, acc, acc); //n^2

    mpz_tdiv_q(acc2, acc2, acc);  // [S(x^2)*n - (S(x))^2] / n^2
    result = mpz_get_str(NULL, 10, acc2);
    x = std::string(result);

    if (x.length() <= d) {
        x.insert(0, d - x.length() + 1, '0');
    }
    x.insert(x.length() - d, 1, '.');
    removeTrailingZeros(x);

    std::cout << x << std::endl;

    // 3) period
    unsigned long int length = n / 2, idx, pos;
    for (period = 1; period <= length; ++period) {
        for (pos = 0, idx = 0; pos < n; ++pos) {
            if (sequence[pos] != sequence[idx]) {
                break;
            }
            idx = (idx + 1) % period;
        }
        if (pos == n) {
            break;
        }
    }
    if (period == length + 1) {
        period = n;
    }

    std::cout << period << std::endl;

    // clean-up
    mpz_clear(acc);
    mpz_clear(acc2);
    mpz_clear(tmp);
    mpz_clear(multiplicand);
    mpz_clear(quotient);

    std::vector<std::string>().swap(sequence);

    return 0;
}
