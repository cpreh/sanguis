#ifndef SANGUIS_CLIENT_LEVEL_HPP_INCLUDED
#define SANGUIS_CLIENT_LEVEL_HPP_INCLUDED

#include "../messages/types/level.hpp"
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace client
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::messages::types::level,
	level
);

}
}

#endif
