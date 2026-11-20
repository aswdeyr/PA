#include <immintrin.h> // Cabecera para Intel Intrinsics (AVX2, FMA)
#include <stdio.h>
#include <stdlib.h>



void Multi(const float* restrict A, const float* restrict B, float* restrict C, int N) {

    for (int i = 0; i < N * N; ++i) {
        C[i] = 0.0f;
    }


    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            __m256 a_vec = _mm256_set1_ps(A[i * N + k]);
            for (int j = 0; j < N; j += 8) {
                __m256 b_vec = _mm256_loadu_ps(&B[k * N + j]);
                __m256 c_vec = _mm256_loadu_ps(&C[i * N + j]);
                c_vec = _mm256_fmadd_ps(a_vec, b_vec, c_vec);
                _mm256_storeu_ps(&C[i * N + j], c_vec);
            }
        }
    }
}