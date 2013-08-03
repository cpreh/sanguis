#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SCALE_DIFFICULTY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SCALE_DIFFICULTY_HPP_INCLUDED

#include <sanguis/server/difficulty.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

template<
	typename Arg
>
Arg
scale_difficulty(
	Arg const _base,
	sanguis::server::difficulty const _difficulty
)
{
	return
		_base
		*
		static_cast<
			Arg
		>(
			_difficulty.get()
		);
}

}
}
}
}

#endif
