#ifndef SANGUIS_CLIENT_DRAW2D_TRANSLATE_ROTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSLATE_ROTATION_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <alda/message/object.hpp>
#include <fcppt/record/get.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace translate
{

template<
	typename Id,
	typename Type
>
inline
sanguis::client::draw2d::sprite::rotation
rotation(
	alda::message::object<
		Id,
		Type
	> const &_message
)
{
	return
		sanguis::client::draw2d::sprite::rotation{
			fcppt::record::get<
				sanguis::messages::roles::angle
			>(
				_message.get()
			)
		};
}

}
}
}
}

#endif
