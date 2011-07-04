#include <vector>
#include <set>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/generator_iterator.hpp>
#include "rng.h"

UVG::UVG(size_t nr_of_values, int min_value, int max_value) :
	_nr_of_values(nr_of_values),
	_min_value(min_value),
	_max_value(max_value),
	_engine(new boost::mt19937(std::time(0)))
{
	// empty
}

UVG::~UVG()
{
	delete _engine;
}

void UVG::generate()
{
	if (_nr_of_values > (size_t) _max_value - _min_value + 1)
	{
		throw;
	}
	
	typedef boost::uniform_int<> distribution_type;
	typedef boost::variate_generator<engine_type&, distribution_type> generator_type;
	typedef boost::generator_iterator<generator_type> iterator_type;

	distribution_type dist(_min_value, _max_value);
	generator_type generator(*_engine, dist);
	iterator_type iterator(&generator);

	std::set<int> values;

	while (values.size() < _nr_of_values)
	{
		values.insert(*iterator++);
	}

	generated_values.assign(values.begin(), values.end());
}

RNG::RNG(size_t nr_of_values, size_t nr_of_distinct_values, int min_value, int max_value) :
	_nr_of_values(nr_of_values),
	_nr_of_distinct_values(nr_of_distinct_values),
	_min_value(min_value),
	_max_value(max_value),
	_uvg(new UVG(nr_of_distinct_values, min_value, max_value)),
	_engine(new boost::mt19937(std::time(0)))
{
	// empty
}

RNG::~RNG()
{
	delete _uvg;
	delete _engine;
}

void RNG::generate()
{
	_uvg->generate();

	generated_values.clear();
	generated_values.resize(_nr_of_values);

	_assigned_values.assign(_nr_of_values, 0);

	_distribute_distinct_values_once();
	_distribute_remaining_values();
}

void RNG::_distribute_distinct_values_once()
{
	typedef boost::uniform_int<> distribution_type;
	typedef boost::variate_generator<engine_type&, distribution_type> generator_type;
	typedef boost::generator_iterator<generator_type> iterator_type;
	
	distribution_type dist(0, _nr_of_values - 1);
	generator_type generator(*_engine, dist);
	iterator_type iterator(&generator);

	int index;

	for (size_t i = 0; i < _nr_of_distinct_values; ++i)
	{
		do
		{
			index = *iterator++;
		}
		while (_assigned_values[index]);

		generated_values[index] = _uvg->generated_values[i];
		_assigned_values[index] = 1;
	}
}

void RNG::_distribute_remaining_values()
{
	typedef boost::uniform_int<> distribution_type;
	typedef boost::variate_generator<engine_type&, distribution_type> generator_type;
	typedef boost::generator_iterator<generator_type> iterator_type;
	
	distribution_type dist(0, _nr_of_distinct_values - 1);
	generator_type generator(*_engine, dist);
	iterator_type iterator(&generator);

	for (size_t i = 0; i < _nr_of_values; ++i)
	{
		if (!_assigned_values[i])
		{
			generated_values[i] = _uvg->generated_values[*iterator++];
		}
	}
}



// int main()
// {
//  //typedef boost::mt19937 integer_generator_type;
//  //typedef boost::normal_distribution<int> distribution_type;
//
//  //typedef boost::variate_generator<boost::mt19937&, boost::normal_distribution<int>> generator_type;
//
//   boost::mt11213b mt(time(0));
//   boost::normal_distribution<float> wurstbrotverteilung(0, 3);
//
//   boost::variate_generator<boost::mt11213b&, boost::normal_distribution<float> >
//              generator(mt, wurstbrotverteilung);
//
//   for(size_t i = 0; i < 100; ++i)
//   {
//     cout << round(abs(generator())) << ":" << round(abs(generator())) << endl;
//   }
//
//
//     //
//     //
//     //
//     // // Create a Mersenne twister random number generator
//     // // that is seeded once with #seconds since 1970
//     // mt19937 rng(static_cast<unsigned int> (time(NULL)));
//     //
//     // // select Gaussian probability distribution
//     // boost::math::normal_distribution<double> norm_dist(1,3);
//     //
//     // // bind random number generator to distribution, forming a function
//     // variate_generator<mt19937&, boost::math::normal_distribution<double> > normal_sampler(rng, norm_dist);
//     //
//     // // sample from the distribution
//     // cout << normal_sampler();
//
//  return 0;
// }