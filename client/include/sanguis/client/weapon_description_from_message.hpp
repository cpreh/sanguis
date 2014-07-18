#ifndef SANGUIS_CLIENT_WEAPON_DESCRIPTION_FROM_MESSAGE_HPP_INCLUDED
#define SANGUIS_CLIENT_WEAPON_DESCRIPTION_FROM_MESSAGE_HPP_INCLUDED

#include <sanguis/magazine_extra.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/magazine_size.hpp>
#include <sanguis/reload_time.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/messages/convert/from_weapon_attribute_vector.hpp>
#include <sanguis/messages/roles/magazine_base_size.hpp>
#include <sanguis/messages/roles/magazine_extra_size.hpp>
#include <sanguis/messages/roles/magazine_remaining.hpp>
#include <sanguis/messages/roles/reload_time.hpp>
#include <sanguis/messages/roles/weapon_attribute_container.hpp>
#include <sanguis/messages/roles/weapon_type.hpp>
#include <majutsu/get.hpp>


namespace sanguis
{
namespace client
{

template<
	typename Message
>
sanguis::weapon_description
weapon_description_from_message(
	Message const &_message
)
{
	return
		sanguis::weapon_description(
			majutsu::get<
				sanguis::messages::roles::weapon_type
			>(
				_message
			),
			sanguis::magazine_size(
				majutsu::get<
					sanguis::messages::roles::magazine_base_size
				>(
					_message
				)
			),
			sanguis::magazine_extra(
				majutsu::get<
					sanguis::messages::roles::magazine_extra_size
				>(
					_message
				)
			),
			sanguis::magazine_remaining(
				majutsu::get<
					sanguis::messages::roles::magazine_remaining
				>(
					_message
				)
			),
			sanguis::reload_time(
				majutsu::get<
					sanguis::messages::roles::reload_time
				>(
					_message
				)
			),
			sanguis::messages::convert::from_weapon_attribute_vector(
				majutsu::get<
					sanguis::messages::roles::weapon_attribute_container
				>(
					_message
				)
			)
		);
}

}
}

#endif
