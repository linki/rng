#include <gtest/gtest.h>
#include "rng.h"

// helper
std::vector<int> _get_distinct_values(std::vector<int> values);

TEST(RNG, Generate)
{
	// #values, #distinct values, range min, range max
	RNG rng(100, 10, 1, 1000);

	rng.generate();

	EXPECT_EQ(100, rng.generated_values.size());
	EXPECT_EQ( 10, _get_distinct_values(rng.generated_values).size());

	EXPECT_LE(1, *min_element(rng.generated_values.begin(), rng.generated_values.end()));
	EXPECT_GE(1000, *max_element(rng.generated_values.begin(), rng.generated_values.end()));
}

TEST(UVG, Generate)
{
	// 10 unique values in the range of 1 and 100 (inclusive)
	UVG uvg(10, 1, 100);

	uvg.generate();

	EXPECT_EQ(10, uvg.generated_values.size());
	EXPECT_EQ(10, _get_distinct_values(uvg.generated_values).size());

	EXPECT_LE(1, *min_element(uvg.generated_values.begin(), uvg.generated_values.end()));
	EXPECT_GE(100, *max_element(uvg.generated_values.begin(), uvg.generated_values.end()));
}

// helper

std::vector<int> _get_distinct_values(std::vector<int> values)
{
	std::vector<int>::iterator it;
	sort(values.begin(), values.end());
	it = unique(values.begin(), values.end());
	values.resize(it - values.begin());
	return values;
}

TEST(RNG, _GetDistinctValuesHelper)
{
	int numbers[] = { 1, 1, 4, -1, 5, 5, 1000, 50, 50, 1000 };

	std::vector<int> values(numbers, numbers + 10);
	std::vector<int> distinct_values = _get_distinct_values(values);

	EXPECT_EQ( 6, distinct_values.size());

	EXPECT_EQ(-1, distinct_values[0]);
	EXPECT_EQ( 1, distinct_values[1]);
	EXPECT_EQ( 4, distinct_values[2]);
	EXPECT_EQ( 5, distinct_values[3]);
	EXPECT_EQ(50, distinct_values[4]);
	EXPECT_EQ(1000, distinct_values[5]);
}