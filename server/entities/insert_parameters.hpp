#ifndef SANGUIS_SERVER_ENTITIES_INSERT_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_INSERT_PARAMETERS_HPP_INCLUDED

#include "insert_parameters_fwd.hpp"
#include "../space_unit.hpp"
#include "../pos_type.hpp"
#include <fcppt/math/vector/basic_decl.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class insert_parameters {
public:
	insert_parameters(
		pos_type const &,
		space_unit angle
	);

	pos_type const &
	center() const;

	space_unit
	angle() const;
private:
	pos_type const center_;
	space_unit const angle_;
};

}
}
}

#endif
