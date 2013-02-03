#include <sanguis/server/collision/from_sge_user_data.hpp>
#include <sanguis/server/collision/user_data.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/any.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::collision::user_data const
sanguis::server::collision::from_sge_user_data(
	boost::any const &_any
)
{
	return
		sanguis::server::collision::user_data(
			*boost::any_cast<
				sanguis::server::collision::body_base *
			>(
				_any
			)
		);
}
