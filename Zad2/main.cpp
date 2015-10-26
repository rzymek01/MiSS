//DOC:
// https://gmplib.org/manual/Headers-and-Libraries.html#Headers-and-Libraries
//
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <gmp.h>
#include <gmpxx.h>

mpz_class gmpDiv(mpz_class a, mpz_class b) {
    mpz_class ret;
    mpz_tdiv_q(ret.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
    return ret;
}

std::string gmpToString(mpz_class number) {
    return std::string(mpz_get_str(NULL, 10, number.get_mpz_t()));
}

struct Frac {
    mpz_class up;
    mpz_class down;

    inline bool operator<(const Frac& other) {
        return (this->up * other.down < this->down * other.up);
    }

    std::string prec(unsigned long int precision) {
        double up2 = up.get_d();
        double down2 = down.get_d();
        std::string ret = gmpToString(gmpDiv(up * pow(10, precision), down));


        return ret;
    }
};

std::string removeTrailingZeros(std::string &x) {
    x.erase(x.find_last_not_of('0') + 1, std::string::npos);
    if ('.' == (*x.rbegin())) {
        x.erase(x.size() - 1);
    }
    return x;
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

    Frac *max = NULL;
    {

        unsigned long int j, jBest = 0;
        for (j = 1; j <= n; j++) {

            // j/n - F(x_j) = j/n - a/b = (bj-an)/(bn)
            Frac &FXjn = sequence[j - 1];
            mpz_class &a = FXjn.up;
            mpz_class &b = FXjn.down;
            Frac newFrac; // (bj-an) / (bn))
            newFrac.up = b * j - a*n;
            //todo sometimes it gets 0 which is weird...
            newFrac.down = b*n;
            double up2 = newFrac.up.get_d();
            double down2 = newFrac.down.get_d();
            if (max == NULL || *max < newFrac) {
                max = &newFrac;
                jBest = j;
            }

        }
        int a = 5;
    }


    std::cout << max->prec(d);



    for (std::vector<Frac>::iterator i = sequence.begin(); i != sequence.end(); ++i)
        std::cout << gmpToString(i->up) << '/' << gmpToString(i->down) << " = " << gmpToString(gmpDiv(i->up * 10000, i->down)) << std::endl;


    return 0;
}
