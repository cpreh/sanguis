#ifndef SANGUIS_CREATOR_TOP_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_TOP_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/symbol.hpp>
#include <sanguis/creator/top_parameters_fwd.hpp>
#include <fcppt/log/context_reference.hpp>


namespace sanguis::creator
{

class top_parameters
{
public:
	SANGUIS_CREATOR_SYMBOL
	top_parameters(
		fcppt::log::context_reference,
		sanguis::creator::name,
		sanguis::creator::seed,
		sanguis::creator::opening_count_array,
		sanguis::creator::spawn_boss
	);

	[[nodiscard]]
	fcppt::log::context_reference
	log_context() const;

	[[nodiscard]]
	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::name const &
	name() const;

	[[nodiscard]]
	sanguis::creator::seed
	seed() const;

	[[nodiscard]]
	sanguis::creator::opening_count_array const &
	opening_count_array() const;

	[[nodiscard]]
	sanguis::creator::spawn_boss
	spawn_boss() const;
private:
	fcppt::log::context_reference log_context_;

	sanguis::creator::name name_;

	sanguis::creator::seed seed_;

	sanguis::creator::opening_count_array opening_count_array_;

	sanguis::creator::spawn_boss spawn_boss_;
};

}

#endif
