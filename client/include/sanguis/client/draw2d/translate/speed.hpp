#ifndef SANGUIS_CLIENT_DRAW2D_TRANSLATE_SPEED_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSLATE_SPEED_HPP_INCLUDED

#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/translate/vector_to_client.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <majutsu/get.hpp>


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
sanguis::client::draw2d::speed
speed(
	Message const &_message
)
{
	return
		sanguis::client::draw2d::speed(
			sanguis::client::draw2d::translate::vector_to_client(
				majutsu::get<
					sanguis::messages::roles::speed
				>(
					_message
				)
			)
		);
}

}
}
}
}

#endif
