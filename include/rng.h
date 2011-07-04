#include <vector>
#include <boost/random/mersenne_twister.hpp>

class UVG // Unique Values Generator
{
	size_t _nr_of_values;
	int _min_value;
	int _max_value;

	typedef boost::mt19937 engine_type;
	engine_type *_engine;

public:

	std::vector<int> generated_values;

	UVG(size_t nr_of_values, int min_value, int max_value);
	virtual ~UVG();

	void generate();
};

class RNG // Random Numbers Generator
{
	size_t _nr_of_values;
	size_t _nr_of_distinct_values;
	int _min_value;
	int _max_value;

	std::vector<bool> _assigned_values;

	UVG *_uvg;

	typedef boost::mt19937 engine_type;
	engine_type *_engine;
	
	void _distribute_distinct_values_once();
	void _distribute_remaining_values();	

public:

	std::vector<int> generated_values;

	RNG(size_t nr_of_values, size_t nr_of_distinct_values, int min_value, int max_value);
	virtual ~RNG();

	void generate();
};
