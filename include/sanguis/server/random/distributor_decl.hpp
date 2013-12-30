#ifndef SANGUIS_SERVER_RANDOM_DISTRIBUTOR_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_DISTRIBUTOR_DECL_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/random/distributor_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <type_traits>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace random
{

template<
	typename Value,
	typename State
>
class distributor
{
	FCPPT_NONCOPYABLE(
		distributor
	);
public:
	typedef
	std::pair<
		Value,
		State
	>
	value_state_pair;

	typedef
	std::vector<
		value_state_pair
	>
	vector;

	explicit
	distributor(
		vector const &
	);

	~distributor();

	State const &
	execute(
		sanguis::random_generator &
	);
private:
	typedef
	typename
	boost::mpl::if_<
		std::is_floating_point<
			typename Value::value_type
		>,
		fcppt::random::distribution::parameters::uniform_real<
			Value
		>,
		fcppt::random::distribution::parameters::uniform_int<
			Value
		>
	>::type
	distribution_parameters;

	typedef
	fcppt::random::distribution::basic<
		distribution_parameters
	>
	distribution;

	vector const values_;

	distribution distribution_;
};

}
}
}

#endif
