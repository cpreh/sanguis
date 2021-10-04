#ifndef SANGUIS_CLIENT_DRAW2D_TRANSLATE_SPEED_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSLATE_SPEED_HPP_INCLUDED

#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/translate/vector_to_client.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <alda/message/object.hpp>
#include <fcppt/record/get.hpp>


namespace sanguis::client::draw2d::translate
{

template<
	typename Id,
	typename Type
>
inline
sanguis::client::draw2d::speed
speed(
	alda::message::object<
		Id,
		Type
	> const &_message
)
{
	return
		sanguis::client::draw2d::speed(
			sanguis::client::draw2d::translate::vector_to_client(
				fcppt::record::get<
					sanguis::messages::roles::speed
				>(
					_message.get()
				)
			)
		);
}

}

#endif
