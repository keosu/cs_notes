#include <algorithm>
#include <cstdint>
#include <cstring>
#include <random>
#include <vector>
#include <iostream>
void float2bfp16(const float *data, uint8_t *ret, int block_size = 8,
                 int sub_block_size = 8, int sub_block_shift_bits = 0) {
  int m_bfp = 16 - 9;
  int exp_bias = 127;
  std::vector<uint8_t> exp_data(block_size);

  // Extract exponent for each element
  for (int i = 0; i < block_size; ++i) {
    uint32_t u32_data;
    std::memcpy(&u32_data, &(data[i]), sizeof(float));
    uint8_t exp = (u32_data & 0x7F800000) >> 23;
    exp_data[i] = exp;
  }

  // Compute shared exponent
  uint8_t shared_exp = *std::max_element(exp_data.begin(), exp_data.end());
  ret[0] = shared_exp;

  for (int i = 0; i < block_size / sub_block_size; ++i) {
    uint8_t max_sub_exp =
        *std::max_element(exp_data.begin() + i * sub_block_size,
                          exp_data.begin() + (i + 1) * sub_block_size);
    int shift_upper_bound = (1 << sub_block_shift_bits) - 1;
    int shift =
        std::min(static_cast<int>(shared_exp - max_sub_exp), shift_upper_bound);

    for (int j = 0; j < sub_block_size; ++j) {
      float fp32_data = data[i * sub_block_size + j];
      float sign_mantissa =
          fp32_data /
          std::pow(2.0f, (shared_exp - exp_bias - shift + 1.0f - m_bfp));

      // Apply rounding logic
      int rounded_mantissa = static_cast<int>(std::round(sign_mantissa));

      // Clamp the result to fit within 8 bits (signed int8)
      rounded_mantissa = std::max(-128, std::min(127, rounded_mantissa));

      ret[i * sub_block_size + j + 1] = static_cast<int8_t>(rounded_mantissa);
    }
  }
}

auto gen(int M, int K, int N, int SK, int SN) {
  std::vector<float> weights(K * N);
  std::vector<float> bias(N);
  std::vector<uint8_t> ret(K * N * 9 / 8 + K / SK * N);

  auto init_random = [](std::vector<float> &vec, int max, int min) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    for (int i = 0; i < vec.size(); i++) {
      vec[i] = dis(gen);
    }
  };
  init_random(weights, 2, -2);

  for (size_t i = 0; i < N / SN; i++) {
    for (size_t j = 0; j < K / SK; j++) {
      auto src = weights.data() + j * SK * N + i * SN;
      auto dst = ret.data() + j * SK * N / 8 + i * SN / 8;
      float2bfp16(src, dst); 
    }
 
  }

  return ret;
}
int main(int argc, char **argv) {
//   auto wb = gen(32, 64, 128, 32, 64);

    float a = -3.14159;
    std::cout << a << std::endl;
    uint32_t val = *(uint32_t*)&a;

    uint32_t exp = (val >> 23) & 0xFF;
    uint32_t mantissa = val & 0x7FFFFF;
    uint32_t sign = (val >> 31) & 0x1;

    float c =  std::pow(-1, sign) * std::pow(2.0f, exp - 127.0f) * (1.0f + mantissa * std::pow(2.0f, -23.0f));

    std::cout << "man:" << std::dec << mantissa << std::endl;
    std::cout << "exp:" << std::dec << exp << std::endl;
    std::cout << std::hex << *(uint32_t*)&a << std::endl;
    std::cout << std::hex << c << std::endl;
    std::cout << std::hex << *(uint32_t*)&c << std::endl;
  return 0;
}