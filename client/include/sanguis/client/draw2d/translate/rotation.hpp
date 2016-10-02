#ifndef SANGUIS_CLIENT_DRAW2D_TRANSLATE_ROTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSLATE_ROTATION_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <alda/message/get.hpp>


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
sanguis::client::draw2d::sprite::rotation
rotation(
	Message const &_message
)
{
	return
		sanguis::client::draw2d::sprite::rotation{
			alda::message::get<
				sanguis::messages::roles::angle
			>(
				_message
			)
		};
}

}
}
}
}

#endif
