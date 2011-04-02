#ifndef SANGUIS_ENTITY_ID_HPP_INCLUDED
#define SANGUIS_ENTITY_ID_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <boost/cstdint.hpp>

namespace sanguis
{

FCPPT_MAKE_STRONG_TYPEDEF(
	boost::uint32_t,
	entity_id
);

}

#endif
