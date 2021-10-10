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
#include <alda/message/object.hpp>
#include <fcppt/record/get.hpp>

namespace sanguis::client
{

template <typename Id, typename Type>
sanguis::weapon_description
weapon_description_from_message(alda::message::object<Id, Type> const &_message)
{
  return sanguis::weapon_description(
      fcppt::record::get<sanguis::messages::roles::weapon_type>(_message.get()),
      sanguis::magazine_size(
          fcppt::record::get<sanguis::messages::roles::magazine_base_size>(_message.get())),
      sanguis::magazine_extra(
          fcppt::record::get<sanguis::messages::roles::magazine_extra_size>(_message.get())),
      sanguis::magazine_remaining(
          fcppt::record::get<sanguis::messages::roles::magazine_remaining>(_message.get())),
      sanguis::reload_time(
          fcppt::record::get<sanguis::messages::roles::reload_time>(_message.get())),
      sanguis::messages::convert::from_weapon_attribute_vector(
          fcppt::record::get<sanguis::messages::roles::weapon_attribute_container>(
              _message.get())));
}

}

#endif
