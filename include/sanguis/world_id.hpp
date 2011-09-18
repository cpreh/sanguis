#ifndef SANGUIS_WORLD_ID_HPP_INCLUDED
#define SANGUIS_WORLD_ID_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

FCPPT_MAKE_STRONG_TYPEDEF(
	boost::uint32_t,
	world_id
);

}

#endif
