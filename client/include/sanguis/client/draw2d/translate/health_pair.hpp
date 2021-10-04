#ifndef SANGUIS_CLIENT_DRAW2D_TRANSLATE_HEALTH_PAIR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSLATE_HEALTH_PAIR_HPP_INCLUDED

#include <sanguis/client/health.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <alda/message/object.hpp>
#include <fcppt/record/get.hpp>


namespace sanguis::client::draw2d::translate
{

template<
	typename Id,
	typename Type
>
sanguis::client::health_pair
health_pair(
	alda::message::object<
		Id,
		Type
	> const &_message
)
{
	return
		sanguis::client::health_pair(
			sanguis::client::health(
				fcppt::record::get<
					sanguis::messages::roles::health
				>(
					_message.get()
				)
			),
			sanguis::client::max_health(
				fcppt::record::get<
					sanguis::messages::roles::max_health
				>(
					_message.get()
				)
			)
		);
}

}

#endif
