#ifndef SANGUIS_SERVER_RANDOM_DISTRIBUTOR_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_DISTRIBUTOR_DECL_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/random/distributor_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::random
{

template<
	typename Value,
	typename State
>
class distributor
{
	FCPPT_NONMOVABLE(
		distributor
	);
public:
	using
	value_state_pair
	=
	std::pair<
		Value,
		State
	>;

	using
	vector
	=
	std::vector<
		value_state_pair
	>;

	explicit
	distributor(
		vector const &
	);

	~distributor();

	[[nodiscard]]
	State const &
	execute(
		sanguis::random_generator & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)
private:
	using
	distribution_parameters
	=
	std::conditional_t<
		std::is_floating_point_v<
			typename Value::value_type
		>,
		fcppt::random::distribution::parameters::uniform_real<
			Value
		>,
		fcppt::random::distribution::parameters::uniform_int<
			Value
		>
	>;

	using
	distribution
	=
	fcppt::random::distribution::basic<
		distribution_parameters
	>;

	vector const values_;

	distribution distribution_;
};

}

#endif
