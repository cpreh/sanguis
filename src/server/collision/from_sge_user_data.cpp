#include <sanguis/server/collision/from_sge_user_data.hpp>
#include <sanguis/server/collision/user_data.hpp>

sanguis::server::collision::user_data const
sanguis::server::collision::from_sge_user_data(
	boost::any const &_any
)
{
	return
		collision::user_data(
			*boost::any_cast<
				collision::body_base *
			>(
				_any
			)
		);
}
