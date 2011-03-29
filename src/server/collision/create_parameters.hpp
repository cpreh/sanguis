#ifndef SANGUIS_SERVER_COLLISION_CREATE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CREATE_PARAMETERS_HPP_INCLUDED

#include "create_parameters_fwd.hpp"
#include "../pos.hpp"
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class create_parameters
{
	FCPPT_NONASSIGNABLE(
		create_parameters
	);
public:
	create_parameters(
		server::pos const &center,
		server::pos const &speed
	);

	server::pos const
	center() const;

	server::pos const
	speed() const;
private:
	server::pos const
		center_,
		speed_;
};

}
}
}

#endif
