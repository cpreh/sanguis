#include "ghost.hpp"
#include "from_sge_user_data.hpp"
#include "ghost_parameters.hpp"
#include "make_groups.hpp"
#include "user_data.hpp"
#include "to_sge_dim.hpp"
#include "to_sge_vector.hpp"
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/ghost/parameters.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::collision::ghost::ghost(
	collision::ghost_parameters const &_params,
	server::pos const &_pos,
	server::dim const &_size
)
:
	ghost_(
		fcppt::make_unique_ptr<
			sge::projectile::ghost::object
		>(
			sge::projectile::ghost::parameters(
				_params.world(),
				sge::projectile::ghost::position(
					collision::to_sge_vector(
						_pos.get()
					)
				),
				sge::projectile::ghost::size(
					collision::to_sge_dim(
						_size
					)
				),
				collision::make_groups(
					_params.groups(),
					_params.global_groups()
				),
				sge::projectile::ghost::user_data()
			)
		)
	),
	collision_begin_connection_(
		ghost_->body_enter(
			std::tr1::bind(
				&ghost::body_enter,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	collision_end_connection_(
		ghost_->body_exit(
			std::tr1::bind(
				&ghost::body_exit,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}

sanguis::server::collision::ghost::~ghost()
{
}

void
sanguis::server::collision::ghost::body_enter(
	sge::projectile::body::object const &_body
)
{
	this->on_body_enter(
		collision::from_sge_user_data(
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
		collision::from_sge_user_data(
			_body.user_data()
		).get()
	);
}
