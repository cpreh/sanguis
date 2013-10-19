#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_IMPL_HPP_INCLUDED

#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_parameters_decl.hpp>


template<
	typename Base
>
sanguis::client::draw2d::entities::with_buffs_parameters<
	Base
>::with_buffs_parameters(
	sanguis::buff_type_vector const &_buffs,
	Base const &_base
)
:
	buffs_(
		_buffs
	),
	base_(
		_base
	)
{
}

template<
	typename Base
>
sanguis::buff_type_vector const &
sanguis::client::draw2d::entities::with_buffs_parameters<
	Base
>::buffs() const
{
	return
		buffs_;
}

template<
	typename Base
>
Base const &
sanguis::client::draw2d::entities::with_buffs_parameters<
	Base
>::base() const
{
	return
		base_;
}

#endif
