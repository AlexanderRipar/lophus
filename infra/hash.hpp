#ifndef HASH_INCLUDE_GUARD
#define HASH_INCLUDE_GUARD

#include "types.hpp"
#include "range.hpp"

#include <immintrin.h>

static constexpr u32 FNV1A_SEED = 2166136261;

static inline u32 fnv1a_step(u32 seed, byte next) noexcept
{
	return (seed * 16777619) ^ next;
}

static inline u32 fnv1a_step(u32 seed, Range<byte> next) noexcept
{
	u32 hash = seed;

	for (const byte c : next)
		hash = fnv1a_step(hash, c);

	return hash;
}

static inline u32 fnv1a(byte data) noexcept
{
	return fnv1a_step(FNV1A_SEED, data);
}

static inline u32 fnv1a(Range<byte> data) noexcept
{
	return fnv1a_step(FNV1A_SEED, data);
}





// ##########       Invocation        ##########
// Mode:  .  .  .  .  .  .  .  .  .  .  parse
// Entrypoint:  .  .  .  .  .  .  .  .  sample/cpp-translations/parse.cpp.lophus
// ##########   Throughput Metrics    ##########
// Bytes: .  .  .  .  .  .  .  .  .  .  37885395000
// Iterations:  .  .  .  .  .  .  .  .  15000
// Time:  .  .  .  .  .  .  .  .  .  .  174.096 s
// Average:  .  .  .  .  .  .  .  .  .  207.529 MiB/s
// Standard Deviation:   .  .  .  .  .    1.104 MiB/s
// Minimum 5-second window (1 rm):   .  205.353 MiB/s
// Maximum 5-second window (1 rm):   .  209.232 MiB/s
// ########## Identifier Pool Metrics ##########
// Used:  .  .  .  .  .  .  .  .  .  .  8553
// Committed:   .  .  .  .  .  .  .  .  32768
// Fingerprint collisions in Probe Seq: 154
// Rehashes:    .  .  .  .  .  .  .  .  0
// Rehashes due to probe seq overruns:  0
// Probe seq length distribution:
//          0 -     76 |#########################
//          1 -    241 |################################################################################
//          2 -    213 |######################################################################
//          3 -     54 |#################
//          4 -     21 |######
//          5 -      5 |#
//          6 -      5 |#
//          7 -      2 |#
// Run lengths (0 overlong):
//          1 -   3622 |################################################################################
//          2 -   1098 |########################
//          3 -    374 |########
//          4 -    152 |###
//          5 -     58 |#
//          6 -     39 |#
//          7 -      9 |#
//          8 -      7 |#
//          9 -      7 |#
//         10 -      1 |#
//         11 -      3 |#
//         12 -      4 |#
//         13 -      3 |#
//         14 -      2 |#
//         15 -      2 |#
//         16 -      0 |
//         17 -      0 |
//         18 -      1 |#
//         19 -      0 |
//         20 -      0 |
//         21 -      2 |#
//         22 -      0 |
//         23 -      1 |#
//         24 -      0 |
//         25 -      0 |
//         26 -      1 |#
static inline u32 strhash_fnv1a(const byte* begin, const byte* end) noexcept
{
	u32 hash = 2166136261;

	for (const byte* curr = begin; curr != end; ++curr)
		hash = (hash * 16777619) ^ *curr;

	return hash;
}

// ##########       Invocation        ##########
// Mode:  .  .  .  .  .  .  .  .  .  .  parse
// Entrypoint:  .  .  .  .  .  .  .  .  sample/cpp-translations/parse.cpp.lophus
// ##########   Throughput Metrics    ##########
// Bytes: .  .  .  .  .  .  .  .  .  .  37885395000
// Iterations:  .  .  .  .  .  .  .  .  15000
// Time:  .  .  .  .  .  .  .  .  .  .  170.264 s
// Average:  .  .  .  .  .  .  .  .  .  212.199 MiB/s
// Standard Deviation:   .  .  .  .  .    1.289 MiB/s
// Minimum 5-second window (1 rm):   .  209.832 MiB/s
// Maximum 5-second window (1 rm):   .  213.671 MiB/s
// ########## Identifier Pool Metrics ##########
// Used:  .  .  .  .  .  .  .  .  .  .  8553
// Committed:   .  .  .  .  .  .  .  .  32768
// Fingerprint collisions in Probe Seq: 255
// Rehashes:    .  .  .  .  .  .  .  .  0
// Rehashes due to probe seq overruns:  0
// Probe seq length distribution:
//          0 -    111 |############################################
//          1 -    200 |################################################################################
//          2 -    196 |##############################################################################
//          3 -     55 |######################
//          4 -     18 |#######
//          5 -      7 |##
//          6 -     11 |####
//          7 -      6 |##
//          8 -      4 |#
//          9 -      3 |#
//         10 -      2 |#
//         11 -      4 |#
// Run lengths (0 overlong):
//          1 -   3600 |################################################################################
//          2 -   1119 |########################
//          3 -    386 |########
//          4 -    129 |##
//          5 -     71 |#
//          6 -     31 |#
//          7 -     12 |#
//          8 -      9 |#
//          9 -      5 |#
//         10 -      4 |#
//         11 -      4 |#
//         12 -      4 |#
//         13 -      4 |#
//         14 -      0 |
//         15 -      2 |#
//         16 -      0 |
//         17 -      1 |#
//         18 -      1 |#
//         19 -      0 |
//         20 -      0 |
//         21 -      0 |
//         22 -      0 |
//         23 -      0 |
//         24 -      0 |
//         25 -      0 |
//         26 -      0 |
//         27 -      0 |
//         28 -      0 |
//         29 -      0 |
//         30 -      0 |
//         31 -      0 |
//         32 -      0 |
//         33 -      0 |
//         34 -      0 |
//         35 -      0 |
//         36 -      0 |
//         37 -      0 |
//         38 -      0 |
//         39 -      0 |
//         40 -      0 |
//         41 -      0 |
//         42 -      0 |
//         43 -      0 |
//         44 -      0 |
//         45 -      0 |
//         46 -      0 |
//         47 -      0 |
//         48 -      0 |
//         49 -      0 |
//         50 -      1 |#
static inline u32 strhash_unrolled_fnv1a(const byte* begin, const byte* end) noexcept
{
	const byte* curr = begin;

	const byte* const block_end = curr + ((end - begin) & ~static_cast<u64>(3));

	u32 hash0 = 2166136261;

	u32 hash1 = hash0;

	u32 hash2 = hash0;

	u32 hash3 = hash0;

	while (curr != block_end)
	{
		hash0 = (hash0 * 16777619) ^ curr[0];
		hash1 = (hash1 * 16777619) ^ curr[1];
		hash2 = (hash2 * 16777619) ^ curr[2];
		hash3 = (hash3 * 16777619) ^ curr[3];

		curr += 4;
	}

	const u32 hash01 = (hash0 * 16777619) ^ hash1;
	const u32 hash23 = (hash2 * 16777619) ^ hash3;
	u32 hash = (hash01 * 16777619) ^ hash23;

	while (curr != end)
	{
		hash = (hash * 16777619) ^ *curr;

		curr += 1;
	}

	return hash;
}

// ##########       Invocation        ##########
// Mode:  .  .  .  .  .  .  .  .  .  .  parse
// Entrypoint:  .  .  .  .  .  .  .  .  sample/cpp-translations/parse.cpp.lophus
// ##########   Throughput Metrics    ##########
// Bytes: .  .  .  .  .  .  .  .  .  .  37885395000
// Iterations:  .  .  .  .  .  .  .  .  15000
// Time:  .  .  .  .  .  .  .  .  .  .  173.690 s
// Average:  .  .  .  .  .  .  .  .  .  208.014 MiB/s
// Standard Deviation:   .  .  .  .  .    1.899 MiB/s
// Minimum 5-second window (1 rm):   .  204.790 MiB/s
// Maximum 5-second window (1 rm):   .  210.021 MiB/s
// ########## Identifier Pool Metrics ##########
// Used:  .  .  .  .  .  .  .  .  .  .  8553
// Committed:   .  .  .  .  .  .  .  .  32768
// Fingerprint collisions in Probe Seq: 6479
// Rehashes:    .  .  .  .  .  .  .  .  0
// Rehashes due to probe seq overruns:  0
// Probe seq length distribution:
//          0 -    107 |####################################
//          1 -    191 |################################################################
//          2 -     47 |###############
//          3 -    236 |################################################################################
//          4 -     13 |####
//          5 -    181 |#############################################################
//          6 -    102 |##################################
//          7 -     65 |######################
//          8 -     47 |###############
//          9 -     39 |#############
//         10 -     31 |##########
//         11 -     20 |######
//         12 -      7 |##
//         13 -      4 |#
//         14 -      3 |#
//         15 -      4 |#
//         16 -      3 |#
//         17 -      3 |#
//         18 -      3 |#
//         19 -      3 |#
//         20 -      3 |#
//         21 -      1 |#
//         22 -      2 |#
//         23 -      2 |#
//         24 -      1 |#
//         25 -      1 |#
//         26 -      2 |#
//         27 -      1 |#
//         28 -      1 |#
//         29 -      1 |#
//         30 -      1 |#
//         31 -      1 |#
//         32 -      1 |#
//         33 -      1 |#
//         34 -      1 |#
// Run lengths (0 overlong):
//          1 -   2275 |################################################################################
//          2 -    763 |##########################
//          3 -    307 |##########
//          4 -    210 |#######
//          5 -    120 |####
//          6 -     77 |##
//          7 -     50 |#
//          8 -     25 |#
//          9 -     25 |#
//         10 -     17 |#
//         11 -     12 |#
//         12 -     13 |#
//         13 -      7 |#
//         14 -      9 |#
//         15 -      4 |#
//         16 -      2 |#
//         17 -      6 |#
//         18 -      2 |#
//         19 -      5 |#
//         20 -      1 |#
//         21 -      2 |#
//         22 -      0 |
//         23 -      0 |
//         24 -      1 |#
//         25 -      1 |#
//         26 -      0 |
//         27 -      0 |
//         28 -      0 |
//         29 -      0 |
//         30 -      0 |
//         31 -      0 |
//         32 -      0 |
//         33 -      0 |
//         34 -      0 |
//         35 -      0 |
//         36 -      0 |
//         37 -      0 |
//         38 -      0 |
//         39 -      0 |
//         40 -      0 |
//         41 -      0 |
//         42 -      0 |
//         43 -      1 |#
static inline u32 strhash_ymm_fnv1a(const byte* begin, const byte* end) noexcept
{
	ASSERT_OR_IGNORE(begin != end);

	static constexpr const u8 MASK_MEMORY[64] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	};

	constexpr u64 STEP = sizeof(__m256i) / sizeof(u32);

	// Use the fnv1a factor here. No basis for this, just some number.
	const __m256i factors = _mm256_set1_epi32(16777619);

	const __m256i shuffle_mask = _mm256_set_epi8(
		0x80u, 0x80u, 0x80u, 0x07u, 0x80u, 0x80u, 0x80u, 0x06u,
		0x80u, 0x80u, 0x80u, 0x05u, 0x80u, 0x80u, 0x80u, 0x04u,
		0x80u, 0x80u, 0x80u, 0x03u, 0x80u, 0x80u, 0x80u, 0x02u,
		0x80u, 0x80u, 0x80u, 0x01u, 0x80u, 0x80u, 0x80u, 0x00u
	);

	const byte* curr = begin;

	__m256i hashes = _mm256_set1_epi32(2166136261);

	__m256i spread_bytes;

	do
	{
		const __m256i bytes = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(curr));

		// `_mm256_shuffle_epi8` cannot operator across 128-bit lanes, so we
		// duplicate the low 8 bytes of the low lane to the high lane (to be
		// exact, across all 8-byte blocks).
		const __m256i duplicated_bytes = _mm256_permute2x128_si256(bytes, bytes, 0);

		// Spread low eight bytes of loaded value into one dword each.
		spread_bytes = _mm256_shuffle_epi8(duplicated_bytes, shuffle_mask);

		hashes = _mm256_xor_si256(_mm256_mullo_epi32(hashes, factors), spread_bytes);

		curr += STEP;
	}
	while (curr < end);

	// Undo xoring of bytes past `end`.

	const __m256i valid_mask = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(MASK_MEMORY + (curr - end) * sizeof(u32)));

	const __m256i undo = _mm256_and_si256(spread_bytes, valid_mask);

	hashes = _mm256_xor_si256(hashes, undo);

	// Combine all hashes via pseudo-fnv1a (xoring in entire hashes, i.e. dwords instead of bytes)
	const __m256i hashes_upper_128 = _mm256_castsi128_si256(_mm256_extractf128_si256(hashes, 1));

	hashes = _mm256_xor_si256(_mm256_mullo_epi32(hashes, factors), hashes_upper_128);

	const __m256i hashes_upper_64 = _mm256_srli_si256(hashes, 64);

	hashes = _mm256_xor_si256(_mm256_mullo_epi32(hashes, factors), hashes_upper_64);

	const u64 hashes_int = _mm256_extract_epi64(hashes, 0);

	return static_cast<u32>((hashes_int * 16777619) ^ (hashes_int >> 32));
}

// ##########       Invocation        ##########
// Mode:  .  .  .  .  .  .  .  .  .  .  parse
// Entrypoint:  .  .  .  .  .  .  .  .  sample/cpp-translations/parse.cpp.lophus
// ##########   Throughput Metrics    ##########
// Bytes: .  .  .  .  .  .  .  .  .  .  37885395000
// Iterations:  .  .  .  .  .  .  .  .  15000
// Time:  .  .  .  .  .  .  .  .  .  .  166.754 s
// Average:  .  .  .  .  .  .  .  .  .  216.666 MiB/s
// Standard Deviation:   .  .  .  .  .  1.556 MiB/s
// Minimum 5-second window (1 rm):   .  213.900 MiB/s
// Maximum 5-second window (1 rm):   .  219.161 MiB/s
// ########## Identifier Pool Metrics ##########
// Used:  .  .  .  .  .  .  .  .  .  .  8553
// Committed:   .  .  .  .  .  .  .  .  32768
// Fingerprint collisions in Probe Seq: 7834
// Rehashes:    .  .  .  .  .  .  .  .  0
// Rehashes due to probe seq overruns:  0
// Probe seq length distribution:
//          0 -    110 |########################################
//          1 -     49 |##################
//          2 -     72 |##########################
//          3 -     27 |##########
//          4 -     45 |################
//          5 -    215 |################################################################################
//          6 -    164 |#############################################################
//          7 -    125 |##############################################
//          8 -     92 |##################################
//          9 -     57 |#####################
//         10 -     63 |#######################
//         11 -     58 |#####################
//         12 -     33 |############
//         13 -     25 |#########
//         14 -     21 |#######
//         15 -     15 |#####
//         16 -     17 |######
//         17 -     12 |####
//         18 -     10 |###
//         19 -     11 |####
//         20 -     17 |######
//         21 -     12 |####
//         22 -      8 |##
//         23 -     12 |####
//         24 -     10 |###
//         25 -      8 |##
//         26 -     10 |###
//         27 -     10 |###
//         28 -     12 |####
//         29 -     15 |#####
//         30 -     10 |###
//         31 -      8 |##
//         32 -     11 |####
//         33 -      9 |###
//         34 -      4 |#
//         35 -      3 |#
//         36 -      3 |#
//         37 -      2 |#
// Run lengths (2 overlong):
//          1 -   2050 |################################################################################
//          2 -    674 |##########################
//          3 -    293 |###########
//          4 -    170 |######
//          5 -     93 |###
//          6 -     77 |###
//          7 -     42 |#
//          8 -     34 |#
//          9 -     26 |#
//         10 -     18 |#
//         11 -     20 |#
//         12 -     11 |#
//         13 -      5 |#
//         14 -     10 |#
//         15 -      1 |#
//         16 -      5 |#
//         17 -      2 |#
//         18 -      5 |#
//         19 -      1 |#
//         20 -      2 |#
//         21 -      3 |#
//         22 -      2 |#
//         23 -      1 |#
//         24 -      0 |
//         25 -      1 |#
//         26 -      2 |#
//         27 -      1 |#
//         28 -      4 |#
//         29 -      1 |#
//         30 -      0 |
//         31 -      0 |
//         32 -      0 |
//         33 -      1 |#
//         34 -      0 |
//         35 -      0 |
//         36 -      0 |
//         37 -      0 |
//         38 -      0 |
//         39 -      0 |
//         40 -      0 |
//         41 -      0 |
//         42 -      1 |#
//         43 -      0 |
//         44 -      0 |
//         45 -      0 |
//         46 -      0 |
//         47 -      0 |
//         48 -      0 |
//         49 -      0 |
//         50 -      0 |
//         51 -      0 |
//         52 -      0 |
//         53 -      0 |
//         54 -      2 |#
//         55 -      0 |
//         56 -      0 |
//         57 -      0 |
//         58 -      0 |
//         59 -      1 |#
// Longest overlong run lengths:
//         142
//         95
static inline u32 strhash_ymm_mix(const byte* begin, const byte* end) noexcept
{
	static constexpr const u8 MASK_MEMORY[64] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};

	const byte* ptr = begin;

	// Use the fnv1a factor here. No basis for this, just some number.
	const __m256i factor = _mm256_set1_epi32(16777619);

	__m256i accumulator = _mm256_set1_epi32(2166136261);

	while (ptr + sizeof(__m256i) < end)
	{
		const __m256i curr = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));

		accumulator = _mm256_xor_si256(_mm256_mul_epu32(accumulator, factor), curr);

		ptr += sizeof(__m256i);
	}

	const __m256i mask = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(MASK_MEMORY + 32 - (end - ptr)));

	const __m256i curr = _mm256_and_si256(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr)), mask);

	accumulator = _mm256_xor_si256(_mm256_mul_epu32(accumulator, factor), curr);

	const __m128i lo_128 = _mm256_castsi256_si128(accumulator);

	const __m128i hi_128 = _mm256_extracti128_si256(accumulator, 1);

	const __m128i xor_128 = _mm_xor_si128(_mm_mul_epi32(lo_128, _mm256_castsi256_si128(factor)), hi_128);

	const u64 lo_64 = _mm_extract_epi64(xor_128, 0);
	const u64 hi_64 = _mm_extract_epi64(xor_128, 1);

	const u64 xor_64 = ((lo_64 * 16777619) ^ hi_64);

	return static_cast<u32>(xor_64) ^ static_cast<u32>(xor_64 >> 32);
}

// ##########       Invocation        ##########
// Mode:  .  .  .  .  .  .  .  .  .  .  parse
// Entrypoint:  .  .  .  .  .  .  .  .  sample/cpp-translations/parse.cpp.lophus
// ##########   Throughput Metrics    ##########
// Bytes: .  .  .  .  .  .  .  .  .  .  37885395000
// Iterations:  .  .  .  .  .  .  .  .  15000
// Time:  .  .  .  .  .  .  .  .  .  .  165.451 s
// Average:  .  .  .  .  .  .  .  .  .  218.372 MiB/s
// Standard Deviation:   .  .  .  .  .    1.116 MiB/s
// Minimum 5-second window (1 rm):   .  215.811 MiB/s
// Maximum 5-second window (1 rm):   .  219.560 MiB/s
// ########## Identifier Pool Metrics ##########
// Used:  .  .  .  .  .  .  .  .  .  .  8553
// Committed:   .  .  .  .  .  .  .  .  32768
// Fingerprint collisions in Probe Seq: 1817
// Rehashes:    .  .  .  .  .  .  .  .  0
// Rehashes due to probe seq overruns:  0
// Probe seq length distribution:
//          0 -     93 |################################
//          1 -     19 |######
//          2 -     35 |############
//          3 -     42 |##############
//          4 -     92 |################################
//          5 -    227 |################################################################################
//          6 -    136 |###############################################
//          7 -    122 |##########################################
//          8 -     88 |###############################
//          9 -     79 |###########################
//         10 -     73 |#########################
//         11 -     46 |################
//         12 -     43 |###############
//         13 -     39 |#############
//         14 -     35 |############
//         15 -     31 |##########
//         16 -     31 |##########
//         17 -     31 |##########
//         18 -     32 |###########
//         19 -     29 |##########
//         20 -     33 |###########
//         21 -     26 |#########
//         22 -     31 |##########
//         23 -     29 |##########
//         24 -     19 |######
//         25 -     15 |#####
//         26 -     12 |####
//         27 -     11 |###
//         28 -     10 |###
//         29 -     11 |###
//         30 -     12 |####
//         31 -     17 |#####
//         32 -     14 |####
//         33 -     12 |####
//         34 -      8 |##
//         35 -     10 |###
//         36 -     10 |###
//         37 -      6 |##
//         38 -      3 |#
//         39 -      5 |#
//         40 -      6 |##
//         41 -      6 |##
//         42 -      4 |#
//         43 -      2 |#
//         44 -      2 |#
//         45 -      1 |#
//         46 -      1 |#
//         47 -      1 |#
//         48 -      1 |#
// Run lengths (8 overlong):
//          1 -   1845 |################################################################################
//          2 -    552 |#######################
//          3 -    244 |##########
//          4 -    130 |#####
//          5 -     78 |###
//          6 -     62 |##
//          7 -     33 |#
//          8 -     38 |#
//          9 -     22 |#
//         10 -     25 |#
//         11 -     16 |#
//         12 -     14 |#
//         13 -      7 |#
//         14 -     13 |#
//         15 -      9 |#
//         16 -      2 |#
//         17 -      3 |#
//         18 -      5 |#
//         19 -      5 |#
//         20 -      2 |#
//         21 -      6 |#
//         22 -      2 |#
//         23 -      3 |#
//         24 -      0 |
//         25 -      1 |#
//         26 -      1 |#
//         27 -      1 |#
//         28 -      2 |#
//         29 -      0 |
//         30 -      2 |#
//         31 -      0 |
//         32 -      2 |#
//         33 -      2 |#
//         34 -      0 |
//         35 -      1 |#
//         36 -      0 |
//         37 -      1 |#
//         38 -      0 |
//         39 -      0 |
//         40 -      1 |#
//         41 -      0 |
//         42 -      0 |
//         43 -      1 |#
//         44 -      1 |#
//         45 -      1 |#
//         46 -      0 |
//         47 -      0 |
//         48 -      1 |#
//         49 -      0 |
//         50 -      0 |
//         51 -      0 |
//         52 -      0 |
//         53 -      0 |
//         54 -      0 |
//         55 -      0 |
//         56 -      0 |
//         57 -      0 |
//         58 -      0 |
//         59 -      1 |#
// Longest overlong run lengths:
//         86
//         90
//         70
//         75
//         101
//         70
//         65
//         76
static inline u32 strhash_ymm(const byte* begin, const byte* end) noexcept
{
	static constexpr const u8 MASK_MEMORY[64] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};

	const byte* ptr = begin;

	// Use the fnv1a factor here. No basis for this, just some number.
	const __m256i factor = _mm256_set1_epi32(16777619);

	__m256i accumulator = _mm256_setzero_si256();

	while (ptr + sizeof(__m256i) <= end)
	{
		const __m256i curr = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));

		accumulator = _mm256_xor_si256(_mm256_mul_epu32(accumulator, factor), curr);

		ptr += sizeof(__m256i);
	}

	// We have reached the end of the bytes we are hashing and do not
	// necessarily have 32 bytes left over. However, because of our padding
	// requirements we can certainly *load* 32 more bytes. We then simply set
	// the loaded bogus bytes to 0 by masking them out. Since we do not require
	// AVX512 and its mask registers, we have to make do with loading the mask
	// from memory.
	const __m256i mask = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(MASK_MEMORY + 32 - (end - ptr)));

	const __m256i curr = _mm256_and_si256(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr)), mask);

	accumulator = _mm256_xor_si256(_mm256_mul_epu32(accumulator, factor), curr);

	const __m128i lo_128 = _mm256_castsi256_si128(accumulator);
	const __m128i hi_128 = _mm256_extracti128_si256(accumulator, 1);

	const __m128i xor_128 = _mm_xor_si128(lo_128, hi_128);

	const u64 lo_64 = _mm_extract_epi64(xor_128, 0);
	const u64 hi_64 = _mm_extract_epi64(xor_128, 1);

	const u64 xor_64 = (lo_64 ^ hi_64);

	return static_cast<u32>(xor_64) ^ static_cast<u32>(xor_64 >> 32);
}

// ##########       Invocation        ##########
// Mode:  .  .  .  .  .  .  .  .  .  .  parse
// Entrypoint:  .  .  .  .  .  .  .  .  sample/cpp-translations/parse.cpp.lophus
// ##########   Throughput Metrics    ##########
// Bytes: .  .  .  .  .  .  .  .  .  .  37885395000
// Iterations:  .  .  .  .  .  .  .  .  15000
// Time:  .  .  .  .  .  .  .  .  .  .  168.600 s
// Average:  .  .  .  .  .  .  .  .  .  214.294 MiB/s
// Standard Deviation:   .  .  .  .  .    2.071 MiB/s
// Minimum 5-second window (1 rm):   .  211.377 MiB/s
// Maximum 5-second window (1 rm):   .  217.807 MiB/s
// ########## Identifier Pool Metrics ##########
// Used:  .  .  .  .  .  .  .  .  .  .  8553
// Committed:   .  .  .  .  .  .  .  .  32768
// Fingerprint collisions in Probe Seq: 2574
// Rehashes:    .  .  .  .  .  .  .  .  0
// Rehashes due to probe seq overruns:  0
// Probe seq length distribution:
//          0 -    214 |####################################################################
//          1 -    249 |################################################################################
//          2 -     86 |###########################
//          3 -     49 |###############
//          4 -    125 |########################################
//          5 -     42 |#############
//          6 -    176 |########################################################
//          7 -    142 |#############################################
//          8 -    132 |##########################################
//          9 -     95 |##############################
//         10 -     82 |##########################
//         11 -     73 |#######################
//         12 -     56 |#################
//         13 -     53 |#################
//         14 -     48 |###############
//         15 -     40 |############
//         16 -     44 |##############
//         17 -     42 |#############
//         18 -     37 |###########
//         19 -     29 |#########
//         20 -     34 |##########
//         21 -     32 |##########
//         22 -     28 |########
//         23 -     23 |#######
//         24 -     20 |######
//         25 -     15 |####
//         26 -     17 |#####
//         27 -     13 |####
//         28 -      9 |##
//         29 -      8 |##
//         30 -      8 |##
//         31 -     12 |###
//         32 -     10 |###
//         33 -      8 |##
//         34 -      5 |#
//         35 -      9 |##
//         36 -      7 |##
//         37 -      5 |#
//         38 -      2 |#
//         39 -      4 |#
//         40 -      4 |#
//         41 -      4 |#
//         42 -      3 |#
//         43 -      5 |#
//         44 -      3 |#
//         45 -      3 |#
//         46 -      2 |#
//         47 -      2 |#
//         48 -      2 |#
//         49 -      2 |#
//         50 -      3 |#
//         51 -      1 |#
//         52 -      1 |#
//         53 -      4 |#
//         54 -      4 |#
//         55 -      4 |#
//         56 -      3 |#
//         57 -      2 |#
//         58 -      4 |#
//         59 -      9 |##
//         60 -      4 |#
//         61 -      1 |#
// Run lengths (6 overlong):
//          1 -   1519 |################################################################################
//          2 -    455 |#######################
//          3 -    222 |###########
//          4 -    160 |########
//          5 -     83 |####
//          6 -     50 |##
//          7 -     42 |##
//          8 -     26 |#
//          9 -     22 |#
//         10 -     25 |#
//         11 -     19 |#
//         12 -     11 |#
//         13 -     15 |#
//         14 -      9 |#
//         15 -      7 |#
//         16 -      6 |#
//         17 -      2 |#
//         18 -      7 |#
//         19 -      3 |#
//         20 -      6 |#
//         21 -      3 |#
//         22 -      3 |#
//         23 -      3 |#
//         24 -      2 |#
//         25 -      0 |
//         26 -      1 |#
//         27 -      0 |
//         28 -      3 |#
//         29 -      1 |#
//         30 -      0 |
//         31 -      1 |#
//         32 -      0 |
//         33 -      2 |#
//         34 -      1 |#
//         35 -      1 |#
//         36 -      0 |
//         37 -      0 |
//         38 -      1 |#
//         39 -      1 |#
//         40 -      0 |
//         41 -      1 |#
//         42 -      0 |
//         43 -      1 |#
//         44 -      1 |#
//         45 -      1 |#
//         46 -      2 |#
//         47 -      0 |
//         48 -      0 |
//         49 -      0 |
//         50 -      0 |
//         51 -      4 |#
//         52 -      1 |#
//         53 -      0 |
//         54 -      0 |
//         55 -      1 |#
//         56 -      0 |
//         57 -      0 |
//         58 -      0 |
//         59 -      0 |
//         60 -      0 |
//         61 -      1 |#
//         62 -      1 |#
//         63 -      1 |#
// Longest overlong run lengths:
//         120
//         69
//         134
//         79
//         74
//         87
static inline u32 strhash_xmm(const byte* begin, const byte* end) noexcept
{
	static constexpr const u8 MASK_MEMORY[32] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};

	const byte* ptr = begin;

	// Use the fnv1a factor here. No basis for this, just some number.
	const __m128i factor = _mm_set1_epi32(16777619);

	__m128i accumulator = _mm_setzero_si128();

	while (ptr + sizeof(__m128i) < end)
	{
		const __m128i curr = _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));

		accumulator = _mm_xor_si128(_mm_mul_epu32(accumulator, factor), curr);

		ptr += sizeof(__m128i);
	}

	const __m128i unmasked_curr = _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr));

	const __m128i mask = _mm_loadu_si128(reinterpret_cast<const __m128i*>(MASK_MEMORY + sizeof(__m128i) - (end - ptr)));

	const __m128i curr = _mm_and_si128(unmasked_curr, mask);

	accumulator = _mm_xor_si128(_mm_mul_epu32(accumulator, factor), curr);

	const u64 lo = _mm_extract_epi64(accumulator, 0);
	const u64 hi = _mm_extract_epi64(accumulator, 1);

	const u64 xored = lo ^ hi;

	return static_cast<u32>(xored) ^ static_cast<u32>(xored >> 32) ^ 2166136261;
}

// ##########       Invocation        ##########
// Mode:  .  .  .  .  .  .  .  .  .  .  parse
// Entrypoint:  .  .  .  .  .  .  .  .  sample/cpp-translations/parse.cpp.lophus
// ##########   Throughput Metrics    ##########
// Bytes: .  .  .  .  .  .  .  .  .  .  37885395000
// Iterations:  .  .  .  .  .  .  .  .  15000
// Time:  .  .  .  .  .  .  .  .  .  .  159.015 s
// Average:  .  .  .  .  .  .  .  .  .  227.211 MiB/s
// Standard Deviation:   .  .  .  .  .    0.987 MiB/s
// Minimum 5-second window (1 rm):   .  225.484 MiB/s
// Maximum 5-second window (1 rm):   .  228.754 MiB/s
// ########## Identifier Pool Metrics ##########
// Used:  .  .  .  .  .  .  .  .  .  .  8553
// Committed:   .  .  .  .  .  .  .  .  32768
// Fingerprint collisions in Probe Seq: 0
// Rehashes:    .  .  .  .  .  .  .  .  0
// Rehashes due to probe seq overruns:  0
// Probe seq length distribution:
//          0 -    228 |################################################################################
//          1 -    199 |#####################################################################
//          2 -    162 |########################################################
//          3 -     22 |#######
//          4 -      6 |##
// Run lengths (0 overlong):
//          1 -   3592 |################################################################################
//          2 -   1157 |#########################
//          3 -    397 |########
//          4 -    186 |####
//          5 -     69 |#
//          6 -     32 |#
//          7 -     12 |#
//          8 -      4 |#
//          9 -      3 |#
//         10 -      2 |#
//         11 -      0 |
//         12 -      1 |#
static inline u32 strhash_crc(const byte* begin, const byte* end) noexcept
{
	const byte* curr = begin;

	u32 crc = 2166136261;

	while (curr + 7 < end)
	{
		const u64* const curr_u64 = reinterpret_cast<const u64*>(curr);

		crc = static_cast<u32>(_mm_crc32_u64(crc, *curr_u64));

		curr += sizeof(u64);
	}

	const u64* curr_u64 = reinterpret_cast<const u64*>(curr);

	const u64 tail_bits = 8 * (end - curr);

	const u64 tail_mask = ~((~static_cast<u64>(0)) << tail_bits);

	const u64 tail = *curr_u64 & tail_mask;

	return static_cast<u32>(_mm_crc32_u64(crc, tail));
}



static inline u32 strhash(const byte* begin, const byte* end) noexcept
{
	return strhash_crc(begin, end);
}

#endif // HASH_INCLUDE_GUARD
