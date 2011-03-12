#include "initial_max.hpp"
#include "initial.hpp"
#include "value.hpp"

sanguis::server::entities::property::initial const
sanguis::server::entities::property::initial_max(
	value  const base_
)
{
	return
		initial(
			base_,
			base_
		);
}
