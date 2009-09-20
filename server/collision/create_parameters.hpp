#ifndef SANGUIS_SERVER_COLLISION_CREATE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CREATE_PARAMETERS_HPP_INCLUDED

#include "create_parameters_fwd.hpp"
#include "../pos_type.hpp"
#include <sge/math/vector/basic_decl.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class create_parameters {
public:
	create_parameters(
		pos_type const &center,
		pos_type const &speed
	);

	pos_type const
	center() const;

	pos_type const
	speed() const;
private:
	pos_type const
		center_,
		speed_;
};

}
}
}

#endif
