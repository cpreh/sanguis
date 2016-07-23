#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


sanguis::creator::impl::parameters::parameters(
	fcppt::log::object &_log,
	sanguis::creator::impl::random::generator &_randgen,
	sanguis::creator::spawn_boss const _spawn_boss,
	sanguis::creator::opening_count_array const _opening_count_array
)
:
	log_{
		_log
	},
	randgen_(
		_randgen
	),
	spawn_boss_{
		_spawn_boss
	},
	opening_count_array_(
		_opening_count_array
	)
{
}

fcppt::log::object &
sanguis::creator::impl::parameters::log() const
{
	return
		log_;
}

sanguis::creator::impl::random::generator &
sanguis::creator::impl::parameters::randgen() const
{
	return
		randgen_;
}

sanguis::creator::spawn_boss
sanguis::creator::impl::parameters::spawn_boss() const
{
	return
		spawn_boss_;
}

sanguis::creator::opening_count_array const &
sanguis::creator::impl::parameters::opening_count_array() const
{
	return
		opening_count_array_;
}
