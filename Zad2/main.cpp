//DOC:
// https://gmplib.org/manual/Headers-and-Libraries.html#Headers-and-Libraries
//
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <gmpxx.h>



#define uli unsigned long int
#define mpq_vec std::vector<mpq_class>
#define uli_vec std::vector<uli>

char buf[100000];

void print_mpq(mpq_class mpq, uli d) {
    mpf_class mpq_f(mpq, 100000000); // XXX unit of this precision is not clear, I assumed big one is enough
    mpf_ptr mpq_fptr = mpq_f.get_mpf_t();

    int actualPrinted;
    gmp_sprintf(buf, "%.*Ff%n", d + 1, mpq_fptr, &actualPrinted);
    printf("%.*s\n", actualPrinted - 1, buf);
}

void kolmogorov(mpq_vec& sequence, uli d) {
    mpq_class kPlusMax;
    mpq_class kMinusMax;
    uli n = sequence.size();

    {
        unsigned long int j, jBest = 0;
        for (j = 1; j <= n; j++) {

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


    print_mpq(kPlusMax, d);
    print_mpq(kMinusMax, d);
}

class Hi {
public:

    Hi(/* sorted vec */ mpq_vec& seq, uli d)
    : seq(seq), d(d), k(10), Y() {
    }

    void execute() {
        populateY();
        mpq_class V = calculateV();
        print_mpq(V, d);
    }
private:
    mpq_vec& seq;
    uli d;
    int k;
    uli_vec Y;

    mpq_class getAi(int i) {
        return (mpq_class) i * (mpq_class) i / (mpq_class) 100;
    }

    mpq_class getPi(int i) {
        return getAi(i) - getAi(i - 1);
    }

    void populateY() {
        Y.assign(k + 1, 0);
        //iterate over seq and count
        uli currentI = 1;
        mpq_class bound = getAi(currentI);
        for (mpq_vec::iterator it = seq.begin(); it != seq.end(); ++it) {
            /* std::cout << *it; ... */
            double _it = it->get_d();
            double _bound = bound.get_d();
            //            printf("OUTER it: %f bound: %f\n", _it, _bound);
            while (*it >= bound) {
                currentI++;
                bound = getAi(currentI);
                _bound = bound.get_d();
                //                printf("INNER it: %f bound: %f\n", _it, _bound);
            }
            if (currentI > k) {
                break;
            }
            //            printf("element %f qualified into Y%d (<%f)\n", _it, currentI, _bound);
            Y[currentI]++;
        }
    }

    mpq_class calculateV() {
        mpq_class n = seq.size();
        mpq_class V = 0;
        for (int i = 1; i <= k; i++) {
            mpq_class nPi = n * getPi(i);
            mpq_class up = Y[i] - nPi;
            V += (up * up) / nPi;
        }
        return V;
    }
};

int main(int argc, char *argv[]) {
    uli d;
    std::string segment;
    std::stringstream converter;

    mpq_vec sequence;
    sequence.reserve(10000);

    converter << argv[1];
    converter >> d;

    while (std::cin >> segment) {
        mpq_class elem(segment);
        elem.canonicalize();
        sequence.push_back(elem);
    }

    std::sort(sequence.begin(), sequence.end());

    Hi hiExecutor(sequence, d);
    hiExecutor.execute();

    kolmogorov(sequence, d);

    return 0;
}
