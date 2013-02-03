#include <sanguis/server/collision/body_base_fwd.hpp>
#include <sanguis/server/collision/user_data.hpp>


sanguis::server::collision::user_data::user_data(
	sanguis::server::collision::body_base &_data
)
:
	data_(
		_data
	)
{
}

sanguis::server::collision::body_base &
sanguis::server::collision::user_data::get() const
{
	return data_;
}
