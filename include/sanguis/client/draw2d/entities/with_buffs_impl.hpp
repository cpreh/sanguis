#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_IMPL_HPP_INCLUDED

#include <sanguis/buff_type.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_decl.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_parameters_decl.hpp>


template<
	typename Base
>
sanguis::client::draw2d::entities::with_buffs<
	Base
>::with_buffs(
	parameters_type const &_parameters
)
:
	Base(
		_parameters.base()
	)
{
}

template<
	typename Base
>
sanguis::client::draw2d::entities::with_buffs<
	Base
>::~with_buffs()
{
}

template<
	typename Base
>
void
sanguis::client::draw2d::entities::with_buffs<
	Base
>::add_buff(
	sanguis::buff_type const _type
)
{
}

template<
	typename Base
>
void
sanguis::client::draw2d::entities::with_buffs<
	Base
>::remove_buff(
	sanguis::buff_type const _type
)
{
}

#endif
