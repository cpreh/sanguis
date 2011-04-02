#ifndef SANGUIS_SERVER_PERKS_LEVEL_DIFF_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_LEVEL_DIFF_HPP_INCLUDED

#include "../level.hpp"
#include <fcppt/strong_typedef.hpp>
#include <boost/type_traits/make_signed.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

FCPPT_MAKE_STRONG_TYPEDEF(
	boost::make_signed<
		server::level::value_type
	>::type,
	level_diff
);

}
}
}

#endif
