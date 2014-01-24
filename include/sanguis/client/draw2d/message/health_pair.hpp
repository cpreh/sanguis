#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_HEALTH_PAIR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_HEALTH_PAIR_HPP_INCLUDED

#include <sanguis/client/health.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <majutsu/get.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace message
{

template<
	typename Message
>
sanguis::client::health_pair const
health_pair(
	Message const &_message
)
{
	return
		sanguis::client::health_pair(
			sanguis::client::health(
				majutsu::get<
					sanguis::messages::roles::health
				>(
					_message
				)
			),
			sanguis::client::max_health(
				majutsu::get<
					sanguis::messages::roles::max_health
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
