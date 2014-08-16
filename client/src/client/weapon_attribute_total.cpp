#include <sanguis/weapon_attribute_base.hpp>
#include <sanguis/weapon_attribute_extra.hpp>
#include <sanguis/weapon_attribute_value.hpp>
#include <sanguis/client/weapon_attribute_total.hpp>


sanguis::weapon_attribute_value
sanguis::client::weapon_attribute_total(
	sanguis::weapon_attribute_base const _base,
	sanguis::weapon_attribute_extra const _extra
)
{
	return
		_extra.get()
		?
			_base.get()
			+
			*_extra.get()
		:
			_base.get()
		;
}
