//DOC:
// https://gmplib.org/manual/Headers-and-Libraries.html#Headers-and-Libraries
//
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <gmp.h>
#include <gmpxx.h>

std::string removeTrailingZeros(std::string &x) {
    x.erase(x.find_last_not_of('0') + 1, std::string::npos);
    if ('.' == (*x.rbegin())) {
        x.erase(x.size() - 1);
    }
    return x;
}

std::string gmpToString(mpz_class number) {
    return std::string(mpz_get_str(NULL, 10, number.get_mpz_t()));
}

int main(int argc, char *argv[]) {
    unsigned long int n = 0, d;
    mpz_class acc, acc2, tmp, multiplicand, quotient;
    std::string x;
    std::stringstream convert;

    typedef std::map<unsigned long int, unsigned long int>::iterator pos_map_it;
    std::vector<std::string> sequence;
    std::map<unsigned long int, unsigned long int> posMap;
    unsigned long int period = 0;

    convert << argv[1];
    convert >> d;

    acc = 0;
    acc2 = 0;
    tmp = 0;
    multiplicand = 0;
    quotient = 0;

    while (std::cin >> x) {
        //: acc += tmp //średnia
        tmp = x;

        acc += tmp;

        //: acc2 += tmp*tmp  // wariancja do zpierwiastkowania
        acc2 += tmp*tmp;

        ++n;

        // 3) period
        sequence.push_back(x);

    }


    multiplicand = 10;
    mpz_pow_ui(multiplicand.get_mpz_t(), multiplicand.get_mpz_t(), d);

    // 1) mean
    tmp = acc*multiplicand;

    mpz_tdiv_q_ui(quotient.get_mpz_t(), tmp.get_mpz_t(), n);
    x = gmpToString(quotient);


    if (x.length() <= d) {
        x.insert(0, d - x.length() + 1, '0');
    }
    x.insert(x.length() - d, 1, '.');
    removeTrailingZeros(x);

    std::cout << x << std::endl;

    // 2) variance
    
    acc2 *= n;
    acc2 -= acc*acc;

    acc2 *= multiplicand;

    acc = n*n;
    


    mpz_tdiv_q(acc2.get_mpz_t(), acc2.get_mpz_t(), acc.get_mpz_t()); // [S(x^2)*n - (S(x))^2] / n^2

    x = gmpToString(acc2);

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

    std::vector<std::string>().swap(sequence);

    return 0;
}
