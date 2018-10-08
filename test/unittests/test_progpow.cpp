// ethash: C/C++ implementation of Ethash, the Ethereum Proof of Work algorithm.
// Copyright 2018 Pawel Bylica.
// Licensed under the Apache License, Version 2.0. See the LICENSE file.

#include <ethash/progpow-internal.hpp>

#include "helpers.hpp"

#include <gtest/gtest.h>


TEST(progpow, keccak_progpow_64)
{
    const uint32_t extra_1[4] = {};
    const auto h0 = progpow::keccak_progpow_64({}, 0, nullptr);
    const auto h1 = progpow::keccak_progpow_64({}, 0, extra_1);
    EXPECT_EQ(h0, h1);
    EXPECT_EQ(h0, 0xe531d45df404c6fb);

    const ethash::hash256 header_hash_2 =
        to_hash256("bc544c2baba832600013bd5d1983f592e9557d04b0fb5ef7a100434a5fc8d52a");
    const uint32_t extra_2[4] = {1, 2, 3, 4};
    const auto h2 = progpow::keccak_progpow_64(header_hash_2, 0x1ffffffff, extra_2);
    EXPECT_EQ(h2, 0x4e7abe6fa3fc5004);
}

TEST(progpow, init)
{
    auto state = progpow::init(0);

    EXPECT_EQ(state.rng_state.w, 59330765);
    EXPECT_EQ(state.rng_state.z, 1326152587);
    EXPECT_EQ(state.rng_state.jsr, 370724217);
    EXPECT_EQ(state.rng_state.jcong, 2204422678);

    std::array<int, 16> expected_sequance{{7, 12, 10, 5, 11, 4, 13, 6, 9, 1, 2, 15, 0, 8, 3, 14}};
    EXPECT_EQ(state.index_sequence, expected_sequance);
}