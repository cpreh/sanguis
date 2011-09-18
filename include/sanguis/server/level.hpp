#ifndef SANGUIS_SERVER_LEVEL_HPP_INCLUDED
#define SANGUIS_SERVER_LEVEL_HPP_INCLUDED

#include <sanguis/messages/types/level.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace server
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::messages::types::level,
	level
);

}
}

#endif
