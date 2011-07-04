#include <iostream>
#include <vector>
#include "rng.h"

std::vector<int> _get_distinct_values(std::vector<int> values);

int main(int argc, const char **argv)
{
	// #values, #distinct values, range min, range max	
	RNG rng(100, 50, 1, 100);

	rng.generate();

	for(size_t i = 0; i < rng.generated_values.size(); ++i)
	{
		printf("%d\n", rng.generated_values[i]);
	}

	// check results

	printf("#values: %ld\n", rng.generated_values.size());
	printf("#distinct values: %ld\n", _get_distinct_values(rng.generated_values).size());
	printf("min value: %d\n", *min_element(rng.generated_values.begin(), rng.generated_values.end()));
	printf("max value: %d\n", *max_element(rng.generated_values.begin(), rng.generated_values.end()));

	return EXIT_SUCCESS;
}

std::vector<int> _get_distinct_values(std::vector<int> values)
{
	std::vector<int>::iterator it;
	sort(values.begin(), values.end());
	it = unique(values.begin(), values.end());
	values.resize(it - values.begin());
	return values;
}
