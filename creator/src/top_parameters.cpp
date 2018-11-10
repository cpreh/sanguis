#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <fcppt/log/context_fwd.hpp>


sanguis::creator::top_parameters::top_parameters(
	fcppt::log::context &_log_context,
	sanguis::creator::name const &_name,
	sanguis::creator::seed const _seed,
	sanguis::creator::opening_count_array const _opening_count_array,
	sanguis::creator::spawn_boss const _spawn_boss
)
:
	log_context_{
		_log_context
	},
	name_(
		_name
	),
	seed_(
		_seed
	),
	opening_count_array_(
		_opening_count_array
	),
	spawn_boss_{
		_spawn_boss
	}
{
}

fcppt::log::context &
sanguis::creator::top_parameters::log_context() const
{
	return
		log_context_.get();
}

sanguis::creator::name const &
sanguis::creator::top_parameters::name() const
{
	return
		name_;
}

sanguis::creator::seed
sanguis::creator::top_parameters::seed() const
{
	return
		seed_;
}

sanguis::creator::opening_count_array const &
sanguis::creator::top_parameters::opening_count_array() const
{
	return
		opening_count_array_;
}

sanguis::creator::spawn_boss
sanguis::creator::top_parameters::spawn_boss() const
{
	return
		spawn_boss_;
}
