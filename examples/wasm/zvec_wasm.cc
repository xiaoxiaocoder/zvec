#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <emscripten/emscripten.h>

#include "zvec/ailego/math/distance.h"
#include "zvec/ailego/math/normalizer.h"

using namespace zvec::ailego;

extern "C" {

EMSCRIPTEN_KEEPALIVE
float zvec_squared_euclidean_f32(const float *lhs, const float *rhs,
                                 size_t dim) {
  return Distance::SquaredEuclidean(lhs, rhs, dim);
}

EMSCRIPTEN_KEEPALIVE
float zvec_euclidean_f32(const float *lhs, const float *rhs, size_t dim) {
  return Distance::Euclidean(lhs, rhs, dim);
}

EMSCRIPTEN_KEEPALIVE
float zvec_inner_product_f32(const float *lhs, const float *rhs, size_t dim) {
  return Distance::InnerProduct(lhs, rhs, dim);
}

EMSCRIPTEN_KEEPALIVE
float zvec_cosine_f32(const float *lhs, const float *rhs, size_t dim) {
  return Distance::Cosine(lhs, rhs, dim);
}

EMSCRIPTEN_KEEPALIVE
float zvec_norm_l2_f32(const float *vec, size_t dim) {
  return Normalizer::Norm2(vec, dim);
}

EMSCRIPTEN_KEEPALIVE
void zvec_normalize_l2_f32(float *vec, size_t dim) {
  Normalizer::Normalize2(vec, dim);
}

EMSCRIPTEN_KEEPALIVE
float *zvec_malloc_f32(size_t count) {
  return static_cast<float *>(malloc(count * sizeof(float)));
}

EMSCRIPTEN_KEEPALIVE
void zvec_free(void *ptr) {
  free(ptr);
}

}
