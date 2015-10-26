//DOC:
// https://gmplib.org/manual/Headers-and-Libraries.html#Headers-and-Libraries
//
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <gmp.h>
#include <gmpxx.h>

struct Frac {
    mpz_class up;
    mpz_class down;

    inline bool operator<(const Frac& other) {
        return (this->up * other.down < this->down * other.up);
    }
};

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

mpz_class gmpDiv(mpz_class a, mpz_class b) {
    mpz_class ret;
    mpz_tdiv_q(ret.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
    return ret;
}

int main(int argc, char *argv[]) {
    unsigned long int n, d;
    mpz_class acc, acc2, tmp, multiplicand, quotient;
    std::string x;
    std::stringstream convert;

    typedef std::map<unsigned long int, unsigned long int>::iterator pos_map_it;
    std::vector<Frac> sequence;
    unsigned long int period = 0;

    convert << argv[1];
    convert >> d;

    acc = 0;
    acc2 = 0;
    tmp = 0;
    multiplicand = 0;
    quotient = 0;

    for (n = 0; std::cin >> x; n++) {
        // prase fraction
        size_t a = x.find('/');
        Frac elem;
        elem.up = x.substr(0, a);
        elem.down = x.substr(a + 1, -1);
        //put fraction into sequence
        sequence.push_back(elem);

    }


    std::sort(sequence.begin(), sequence.end());

    for (std::vector<Frac>::iterator i = sequence.begin(); i != sequence.end(); ++i)
        std::cout << gmpToString(i->up) << '/' << gmpToString(i->down) << " = " << gmpToString(gmpDiv(i->up * 10000, i->down)) << std::endl;


    return 0;
}
