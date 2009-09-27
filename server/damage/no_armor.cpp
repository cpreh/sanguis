#include "no_armor.hpp"
#include "list.hpp"
#include "all.hpp"

sanguis::server::damage::list const
sanguis::server::damage::no_armor()
{
	return
		all(
			unit(
				0
			)
		);
}
