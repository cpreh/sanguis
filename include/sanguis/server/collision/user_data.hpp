#ifndef SANGUIS_SERVER_COLLISION_USER_DATA_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_USER_DATA_HPP_INCLUDED

#include <sanguis/server/collision/user_data_fwd.hpp>
#include <sanguis/server/collision/body_base_fwd.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class user_data
{
	FCPPT_NONASSIGNABLE(
		user_data
	);
public:
	explicit user_data(
		collision::body_base &
	);

	collision::body_base &
	get() const;
private:
	collision::body_base &data_;
};

}
}
}

#endif
