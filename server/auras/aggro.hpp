#ifndef SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED

#include "aura.hpp"
#include "../space_unit.hpp"
#include "../team.hpp"
#include "../update_target_function.hpp"
#include <sge/function/object.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class aggro
:
	public aura
{
public:
	aggro(
		space_unit radius,
		team::type,
		update_target_function const &add_target,
		update_target_function const &remove_target
	);
private:
	collision::group_vector const
	collision_groups() const;

	void
	enter(
		entities::base &target
	);

	void
	leave(
		entities::base &target
	);

	update_target_function const
		add_target_,
		remove_target_;
};


}
}
}

#endif
