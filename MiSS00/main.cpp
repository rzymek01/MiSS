//DOC:
// https://gmplib.org/manual/Headers-and-Libraries.html#Headers-and-Libraries
//
#include <iostream>
#include <gmp.h>

std::string removeTrailingZeros(const char *in) {
    std::string x(in);
    return x.erase(x.find_last_not_of('0') + 1, std::string::npos);
}

int main() {
    unsigned long int n = 0, d, rem;
    mpz_t acc, acc2, tmp, multiplicand, quotient;
    std::string x;
    mpz_init(acc);
    mpz_init(acc2);
    mpz_init(tmp);
    mpz_init(multiplicand);
    mpz_init(quotient);

    std::cin >> d;

    while (std::cin >> x) {
        mpz_set_str(tmp, x.c_str(), 10);
        mpz_add(acc, acc, tmp);
        mpz_addmul(acc2, tmp, tmp);
        ++n;
    }

    mpz_init_set_ui(multiplicand, 10);
    mpz_pow_ui(multiplicand, multiplicand, d);

    // 1) mean
    rem = mpz_tdiv_qr_ui(quotient, tmp, acc, n);
    char *result = mpz_get_str(NULL, 10, quotient);
    mpz_mul_ui(tmp, multiplicand, rem);
    mpz_tdiv_q_ui(tmp, tmp, n);

    std::cout << result;
    if (0 != mpz_sgn(tmp)) {
        std::cout << "." << removeTrailingZeros(mpz_get_str(NULL, 10, tmp));
    }
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