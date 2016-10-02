#ifndef SANGUIS_CLIENT_DRAW2D_TRANSLATE_CENTER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSLATE_CENTER_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/translate/vector_to_client.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <alda/message/get.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace translate
{

template<
	typename Message
>
inline
sanguis::client::draw2d::sprite::center
center(
	Message const &_message
)
{
	return
		sanguis::client::draw2d::sprite::center{
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::sprite::point,
				fcppt::cast::float_to_int_fun
			>(
				sanguis::client::draw2d::translate::vector_to_client(
					alda::message::get<
						sanguis::messages::roles::center
					>(
						_message
					)
				)
			)
		};
}

}
}
}
}

#endif
