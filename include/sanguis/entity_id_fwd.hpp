#ifndef SANGUIS_ENTITY_ID_FWD_HPP_INCLUDED
#define SANGUIS_ENTITY_ID_FWD_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{

FCPPT_MAKE_STRONG_TYPEDEF(
	std::uint32_t,
	entity_id
);

}

#endif
