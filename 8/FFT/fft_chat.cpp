#include <iostream>
#include <fftw3.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void fft_64(const vector<double>& x, vector<complex<double>>& out) {
    if (x.size() != 64) {
        throw invalid_argument("Input length must be 64");
    }

    fftw_complex* in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 64);
    fftw_complex* out_fftw = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 64);
    fftw_plan p = fftw_plan_dft_1d(64, in, out_fftw, FFTW_FORWARD, FFTW_ESTIMATE);

    for (size_t i = 0; i < 64; ++i) {
        in[i][0] = x[i];
        in[i][1] = 0.0;
    }

    fftw_execute(p);

    out.resize(64);
    for (size_t i = 0; i < 64; ++i) {
        out[i] = complex<double>(out_fftw[i][0], out_fftw[i][1]);
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out_fftw);
}

int main() {
    srand(time(0));
    vector<double> x(64);
    for (auto& val : x) {
        val = static_cast<double>(rand()) / RAND_MAX;
    }

    vector<complex<double>> fft_result;
    fft_64(x, fft_result);

    for (const auto& val : fft_result) {
        cout << val << endl;
    }

    return 0;
}
