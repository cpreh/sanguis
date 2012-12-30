#include <sanguis/server/damage/all.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/unit.hpp>


sanguis::server::damage::list const
sanguis::server::damage::all(
	sanguis::server::damage::unit const _value
)
{
	return
		sanguis::server::damage::list(
			_value
		);
}
