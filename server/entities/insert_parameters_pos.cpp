#include "insert_parameters_pos.hpp"
#include "insert_parameters.hpp"
#include "../space_unit.hpp"

sanguis::server::entities::insert_parameters const
sanguis::server::entities::insert_parameters_pos(
	pos_type const &pos_
)
{
	return
		insert_parameters(
			pos_,
			static_cast<space_unit>(0)
		);
}
