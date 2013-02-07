#include <sanguis/server/center.hpp>
#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/from_sge_user_data.hpp>
#include <sanguis/server/collision/make_groups.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/collision/user_data.hpp>
#include <sanguis/server/collision/to_sge_dim.hpp>
#include <sanguis/server/collision/to_sge_vector.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/ghost/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::collision::ghost::ghost(
	sanguis::server::collision::group_vector const &_groups,
	sanguis::server::dim const &_size
)
:
	groups_(
		_groups
	),
	ghost_(
		fcppt::make_unique_ptr<
			sge::projectile::ghost::object
		>(
			sge::projectile::ghost::parameters(
				sge::projectile::ghost::position(
					sge::projectile::vector2::null()
				),
				sge::projectile::ghost::size(
					sanguis::server::collision::to_sge_dim(
						_size
					)
				)
			)
		)
	),
	collision_begin_connection_(
		ghost_->body_enter(
			std::bind(
				&sanguis::server::collision::ghost::body_enter,
				this,
				std::placeholders::_1
			)
		)
	),
	collision_end_connection_(
		ghost_->body_exit(
			std::bind(
				&sanguis::server::collision::ghost::body_exit,
				this,
				std::placeholders::_1
			)
		)
	)
{
}

sanguis::server::collision::ghost::~ghost()
{
}

void
sanguis::server::collision::ghost::center(
	sanguis::server::center const &_center
)
{
	ghost_->position(
		sanguis::server::collision::to_sge_vector(
			_center.get()
		)
	);
}

sanguis::server::collision::group_vector const &
sanguis::server::collision::ghost::groups() const
{
	return groups_;
}

sge::projectile::ghost::object &
sanguis::server::collision::ghost::get()
{
	return *ghost_;
}

void
sanguis::server::collision::ghost::body_enter(
	sge::projectile::body::object const &_body
)
{
	this->on_body_enter(
		sanguis::server::collision::from_sge_user_data(
			_body.user_data()
		).get()
	);
}

void
sanguis::server::collision::ghost::body_exit(
	sge::projectile::body::object const &_body
)
{
	this->on_body_exit(
		sanguis::server::collision::from_sge_user_data(
			_body.user_data()
		).get()
	);
}
