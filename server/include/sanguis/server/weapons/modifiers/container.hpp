#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_CONTAINER_HPP_INCLUDED

#include <sanguis/server/weapons/modifiers/callback.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::weapons::modifiers
{

template<
	typename Parameters
>
using
container
=
std::vector<
	sanguis::server::weapons::modifiers::callback<
		Parameters
	>
>;

}

#endif
