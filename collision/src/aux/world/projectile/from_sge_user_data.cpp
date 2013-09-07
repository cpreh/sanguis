#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/aux/world/projectile/from_sge_user_data.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/any.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::collision::world::body_base &
sanguis::collision::aux::world::projectile::from_sge_user_data(
	boost::any const &_any
)
{
	return
		*boost::any_cast<
			sanguis::collision::world::body_base *
		>(
			_any
		);
}
