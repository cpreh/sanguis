#ifndef SANGUIS_CLIENT_LEVEL_HPP_INCLUDED
#define SANGUIS_CLIENT_LEVEL_HPP_INCLUDED

#include <sanguis/messages/types/level.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::client
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::messages::types::level,
	level
);

}

#endif
