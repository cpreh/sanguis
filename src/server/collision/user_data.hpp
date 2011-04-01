#ifndef SANGUIS_SERVER_COLLISION_USER_DATA_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_USER_DATA_HPP_INCLUDED

#include "base_fwd.hpp"
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
		collision::base &
	);

	collision::base &
	get() const;
private:
	collision::base &data_;
};

}
}
}

#endif
