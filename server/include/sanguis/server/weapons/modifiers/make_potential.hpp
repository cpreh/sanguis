#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_MAKE_POTENTIAL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_MAKE_POTENTIAL_HPP_INCLUDED

#include <sanguis/server/weapons/modifiers/make.hpp>
#include <sanguis/server/weapons/modifiers/potential.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace modifiers
{

template<
	typename Parameters,
	typename... Args
>
sanguis::server::weapons::modifiers::potential<
	Parameters
>
make_potential(
	Args && ..._args
)
{
	return
		sanguis::server::weapons::modifiers::potential<
			Parameters
		>{
			sanguis::server::weapons::modifiers::make<
				Parameters
			>(
				std::forward<
					Args
				>(
					_args
				)...
			)
		};
}

}
}
}
}

#endif
