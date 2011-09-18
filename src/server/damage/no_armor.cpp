#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/all.hpp>

sanguis::server::damage::list const
sanguis::server::damage::no_armor()
{
	return
		damage::all(
			damage::unit(
				0
			)
		);
}
