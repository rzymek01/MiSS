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

mpf_class PI_CONST = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282925409171536436789259036001133053054882046652138414695194151160943305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912983367336244065664308602139494639522473719070217986094370277053921717629317675238467481846766940513200056812714526356082778577134275778960917363717872146844090122495343014654958537105079227968925892354201995611212902196086403441815981362977477130996051870721134999999837297804995105973173281609631859502445945534690830264252230825334468503526193118817101000313783875288658753320838142061717766914730359825349042875546873115956286388235378759375195778185778053217122680661300192787661119590921642019893809525720106548586327886593615338182796823030195203530185296899577362259941389124972177528347913151557485724245415069595082953311686172785588907509838175463746493931925506040092770167113900984882401285836160356370766010471018194295559619894676783744944825537977472684710404753464620804668425906949129331367702898915210475216205696602405803815019351125338243003558764024749647326391419927260426992279678235478163600934172164121992458631503028618297455570674983850549458858692699569092721079750930295532116534498720275596023648066549911988183479775356636980742654252786255181841757467289097777279380008164706001614524919217321721477235014144197356854816136115735255213347574184946843852332390739414333454776241686251898356948556209921922218427255025425688767179049460165346680498862723279178608578438382796797668145410095388378636095068006422512520511;


void print_mpf(mpf_class mpf, uli d) {
    mpf_ptr mpf_ptr = mpf.get_mpf_t();
    int actualPrinted;
    gmp_sprintf(buf, "%.*Ff%n", d + 1, mpf_ptr, &actualPrinted);
    printf("%.*s\n", actualPrinted - 1, buf);
}
void print_mpq(mpq_class mpq, uli d) {
    mpf_class mpq_f(mpq); // XXX unit of this precision is not clear, I assumed big one is enough
    print_mpf(mpq_f, d);
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

class Pi {
public:

    Pi(mpq_vec& seq, uli d) : seq(seq), d(d) {
    }

    void execute() {
        uli N = 0;
        mpf_class qPI = PI_CONST / 4;
        mpq_class cx = 0.5;
        mpq_class cy = 0.5;
        mpq_class r = 0.5;
        for (mpq_vec::iterator it = seq.begin(); it != seq.end(); it += 2) {
            mpq_class x = *it;
            mpq_class y = *(it + 1);

            // is (a,b) contained in circle (.5,.5) r=0.5?
            if ((x - cx)*(x - cx)+(y - cy)*(y - cy) <= r * r) {
                N++;
            }
        }
        mpf_class P = 2 * N / (mpf_class) seq.size();

        mpf_class result = (P - qPI);
        if (result < 0) {
            result = -result;
        }
        print_mpf(result, d);
    }
private:
    mpq_vec& seq;
    uli d;
};

int main(int argc, char *argv[]) {
    mpf_set_default_prec(100000000);
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

    Pi piExecutor(sequence, d);
    piExecutor.execute();

    return 0;
}
