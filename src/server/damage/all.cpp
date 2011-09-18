#include <sanguis/server/damage/all.hpp>
#include <sanguis/server/damage/list.hpp>

sanguis::server::damage::list const
sanguis::server::damage::all(
	damage::unit const _value
)
{
	return
		damage::list(
			_value
		);
}
