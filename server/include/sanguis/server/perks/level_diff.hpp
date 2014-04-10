#ifndef SANGUIS_SERVER_PERKS_LEVEL_DIFF_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_LEVEL_DIFF_HPP_INCLUDED

#include <sanguis/server/level.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

FCPPT_MAKE_STRONG_TYPEDEF(
	std::make_signed<
		sanguis::server::level::value_type
	>::type,
	level_diff
);

}
}
}

#endif
