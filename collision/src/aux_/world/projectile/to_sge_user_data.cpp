#include <sanguis/collision/aux_/world/projectile/to_sge_user_data.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/any.hpp>
#include <fcppt/config/external_end.hpp>


boost::any const
sanguis::collision::aux_::world::projectile::to_sge_user_data(
	sanguis::collision::world::body_base &_user_data
)
{
	return
		boost::any(
			&_user_data
		);
}
