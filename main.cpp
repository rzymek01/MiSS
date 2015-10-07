//DOC:
// https://gmplib.org/manual/Headers-and-Libraries.html#Headers-and-Libraries
//
#include <iostream>
#include <sstream>
#include <gmp.h>

std::string removeTrailingZeros(const char *in) {
    std::string x(in);
    //@todo: std::string, remove 0 only after '.'
    return x.erase(x.find_last_not_of('0') + 1, std::string::npos);
}

int main(int argc, char *argv[]) {
    unsigned long int n = 0, d, rem;
    mpz_t acc, acc2, tmp, multiplicand, quotient;
    std::string x;
    std::stringstream convert;

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
    }

    mpz_init_set_ui(multiplicand, 10);
    mpz_pow_ui(multiplicand, multiplicand, d);

    // 1) mean
    mpz_mul(tmp, acc, multiplicand);
    mpz_tdiv_q_ui(quotient, tmp, n);
    char *result = mpz_get_str(NULL, 10, quotient);
    x = std::string(result);
    x.insert(x.length() - 1 - d, 1, '.');
    x = removeTrailingZeros(x.c_str());
    if ('.' == (*x.rbegin())) {
        x.pop_back();
    }
    //mpz_mul_ui(tmp, multiplicand, rem);
    //mpz_tdiv_q_ui(tmp, tmp, n);

    std::cout << x;
    //if (0 != mpz_sgn(tmp)) {
    //    std::cout << "." << removeTrailingZeros(mpz_get_str(NULL, 10, tmp));
    //}
    std::cout << std::endl;

    // 2) variance
    mpz_mul(acc, acc, acc);
    mpz_mul_ui(acc2, acc2, n);
    mpz_sub(acc2, acc2, acc);

    mpz_set_ui(acc, n);
    mpz_mul(acc, acc, acc); //n^2

    mpz_tdiv_qr(acc2, tmp, acc2, acc);  // [S(x^2)*n - (S(x))^2] / n^2
    result = mpz_get_str(NULL, 10, acc2);
    mpz_mul(tmp, multiplicand, tmp);
    mpz_tdiv_q(tmp, tmp, acc);

    std::cout << result;
    if (0 != mpz_sgn(tmp)) {
        std::cout << "." << removeTrailingZeros(mpz_get_str(NULL, 10, tmp));
    }
    std::cout << std::endl;

//    std::cout << "precision: " << d << std::endl;
//    std::cout << "count no.: " << n << std::endl;
//    std::cout << "acc2: " << acc2 << std::endl;
    return 0;
}
