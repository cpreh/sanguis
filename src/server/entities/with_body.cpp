#include "with_body.hpp"
#include "collision_groups.hpp"
#include "solidity.hpp"
#include "../collision/body.hpp"
#include "../collision/create_parameters.hpp"
#include "../collision/user_data.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::entities::with_body::with_body()
:
	collision_body_()	
{
}

sanguis::server::entities::with_body::~with_body()
{
}

sanguis::server::center const
sanguis::server::entities::with_body::center() const
{
	return
		collision_body_->center();
}

void
sanguis::server::entities::with_body::center(
	server::center const &_center
)
{
	collision_body_->center(
		_center
	);
}

void
sanguis::server::entities::with_body::on_transfer(
	collision::create_parameters const &_params
)
{
	collision_body_.take(
		fcppt::make_unique_ptr<
			collision::body
		>(
			_params,
			entities::collision_groups(
				this->type(),
				this->team()
			),
			this->recreate_shape(),
			entities::solidity(
				this->type()
			),
			collision::user_data(
				*this
			),
			std::tr1::bind(
				&with_body::on_position_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	with_ghosts::on_transfer(
		_params
	);
}

void
sanguis::server::entities::with_body::on_position_change(
	server::center const &_center
)
{
	with_ghosts::update_center(
		_center
	);
}
