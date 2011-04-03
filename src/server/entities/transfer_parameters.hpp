#ifndef SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_TRANSFER_PARAMETERS_HPP_INCLUDED

#include "transfer_parameters_fwd.hpp"
#include "../collision/create_parameters.hpp"
#include "../angle.hpp"
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class transfer_parameters
{
	FCPPT_NONASSIGNABLE(
		transfer_parameters
	);
public:
	transfer_parameters(
		collision::create_parameters const &,
		server::angle
	);

	collision::create_parameters const &
	create_parameters() const;

	server::angle const
	angle() const;
private:
	collision::create_parameters const create_parameters_;

	server::angle const angle_;
};

}
}
}

#endif
