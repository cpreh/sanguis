#ifndef SANGUIS_SERVER_COLLISION_CREATE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_CREATE_PARAMETERS_HPP_INCLUDED

#include "create_parameters_fwd.hpp"
#include "user_data.hpp"
#include "../center.hpp"
#include "../speed.hpp"
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
		server::center const &,
		server::speed const &,
		collision::user_data const &
	);

	server::center const
	center() const;

	server::speed const
	speed() const;

	collision::user_data const &
	user_data() const;
private:
	server::center const center_;

	server::speed const speed_;
	
	collision::user_data const user_data_;
};

}
}
}

#endif
