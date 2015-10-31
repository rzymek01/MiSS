//DOC:
// https://gmplib.org/manual/Headers-and-Libraries.html#Headers-and-Libraries
//
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>

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

unsigned long int n, d;

void print_mpq(mpq_class mpq) {
    mpf_class mpq_f(mpq, 100000);
    mpf_ptr mpq_fptr = mpq_f.get_mpf_t();
    char buf[d+10];
    int actualPrinted;
    gmp_sprintf(buf, "%.*Ff%n", d+1, mpq_fptr, &actualPrinted);
    printf("%.*s\n", actualPrinted-1, buf);
    int a = 4;
}

int main(int argc, char *argv[]) {

    std::string line;
    std::stringstream converter;

    std::vector<mpq_class> sequence;

    converter << argv[1];
    converter >> d;

    for (n = 0; std::cin >> line; n++) {
        mpq_class elem(line);
        elem.canonicalize();
        sequence.push_back(elem);
    }


    std::sort(sequence.begin(), sequence.end());

    mpq_class kPlusMax;
    mpq_class kMinusMax;

    {

        unsigned long int j, jBest = 0;
        for (j = 1; j <= n; j++) {

            // j/n - F(x_j) = j/n - a/b = (bj-an)/(bn)
            mpq_class &FXjn = sequence[j - 1];
            mpq_class kPlusCandidate = ((mpq_class) j / (mpq_class) n) - FXjn;
            if (j == 1 || kPlusMax < kPlusCandidate) {
                kPlusMax = kPlusCandidate;
            }
            mpq_class kMinusCandidate = FXjn - (((mpq_class) j - 1) / (mpq_class) n);
            if (j == 1 || kMinusMax < kMinusCandidate) {
                kMinusMax = kMinusCandidate;
            }
        }
    }


    print_mpq(kPlusMax);
    print_mpq(kMinusMax);

    return 0;
}
