#include <sanguis/weapon_attribute_base.hpp>
#include <sanguis/weapon_attribute_extra.hpp>
#include <sanguis/weapon_attribute_value.hpp>
#include <sanguis/client/weapon_attribute_total.hpp>
#include <fcppt/maybe.hpp>


sanguis::weapon_attribute_value
sanguis::client::weapon_attribute_total(
	sanguis::weapon_attribute_base const _base,
	sanguis::weapon_attribute_extra const _opt_extra
)
{
	return
		fcppt::maybe(
			_opt_extra.get(),
			[
				_base
			]{
				return
					_base.get();
			},
			[
				_base
			](
				sanguis::weapon_attribute_value const _extra
			)
			{
				return
					_base.get()
					+
					_extra;
			}
		);
}
