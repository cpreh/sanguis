#include <sanguis/magazine_extra.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/magazine_size.hpp>
#include <sanguis/reload_time.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::weapon_description::weapon_description(
	sanguis::weapon_type const &_weapon_type,
	sanguis::magazine_size const _magazine_size,
	sanguis::magazine_extra const _magazine_extra,
	sanguis::magazine_remaining const _magazine_remaining,
	sanguis::reload_time const _reload_time,
	sanguis::weapon_attribute_vector &&_attributes
)
:
	weapon_type_(
		_weapon_type
	),
	magazine_size_(
		_magazine_size
	),
	magazine_extra_(
		_magazine_extra
	),
	magazine_remaining_(
		_magazine_remaining
	),
	reload_time_(
		_reload_time
	),
	attributes_(
		std::move(
			_attributes
		)
	)
{
}

sanguis::weapon_type const &
sanguis::weapon_description::weapon_type() const
{
	return
		weapon_type_;
}

sanguis::magazine_size
sanguis::weapon_description::magazine_size() const
{
	return
		magazine_size_;
}

sanguis::magazine_extra
sanguis::weapon_description::magazine_extra() const
{
	return
		magazine_extra_;
}

sanguis::magazine_remaining
sanguis::weapon_description::magazine_remaining() const
{
	return
		magazine_remaining_;
}

sanguis::reload_time
sanguis::weapon_description::reload_time() const
{
	return
		reload_time_;
}

sanguis::weapon_attribute_vector const &
sanguis::weapon_description::attributes() const
{
	return
		attributes_;
}
