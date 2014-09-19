#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_MAKE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_MAKE_HPP_INCLUDED

#include <sanguis/server/weapons/modifiers/container.hpp>
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
	typename Parameters
>
sanguis::server::weapons::modifiers::container<
	Parameters
>
make()
{
	return
		sanguis::server::weapons::modifiers::container<
			Parameters
		>{};
}

template<
	typename Parameters,
	typename Arg,
	typename... Args
>
sanguis::server::weapons::modifiers::container<
	Parameters
>
make(
	Arg const &,
	Args && ..._args
)
{
	sanguis::server::weapons::modifiers::container<
		Parameters
	> res{
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

	res.push_back(
		&Arg:: template make<
			Parameters
		>
	);

	return
		res;
}

}
}
}
}

#endif
