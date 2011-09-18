#include <sanguis/server/collision/to_sge_user_data.hpp>
#include <sanguis/server/collision/user_data.hpp>

boost::any const
sanguis::server::collision::to_sge_user_data(
	collision::user_data const &_user_data
)
{
	return
		boost::any(
			&_user_data.get()
		);
}
