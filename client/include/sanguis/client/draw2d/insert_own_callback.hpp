#ifndef SANGUIS_CLIENT_DRAW2D_INSERT_OWN_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_INSERT_OWN_CALLBACK_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

using
insert_own_callback
=
fcppt::function<
	sanguis::client::draw2d::entities::own &(
		sanguis::client::draw2d::entities::own_unique_ptr
	)
>;

}
}
}

#endif
