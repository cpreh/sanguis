#ifndef SANGUIS_CLIENT_DRAW2D_INSERT_OWN_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_INSERT_OWN_CALLBACK_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

typedef std::function<
	sanguis::client::draw2d::entities::own &(
		sanguis::client::draw2d::entities::own_unique_ptr
	)
> insert_own_callback;

}
}
}

#endif
