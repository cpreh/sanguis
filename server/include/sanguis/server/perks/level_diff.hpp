#ifndef SANGUIS_SERVER_PERKS_LEVEL_DIFF_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_LEVEL_DIFF_HPP_INCLUDED

#include <sanguis/server/level.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::perks
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	std::make_signed_t<
		sanguis::server::level::value_type
	>,
	level_diff
);

}

#endif
