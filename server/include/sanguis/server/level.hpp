#ifndef SANGUIS_SERVER_LEVEL_HPP_INCLUDED
#define SANGUIS_SERVER_LEVEL_HPP_INCLUDED

#include <sanguis/messages/types/level.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::messages::types::level,
	level
);

}

#endif
