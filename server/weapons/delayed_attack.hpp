#ifndef SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED

#include "../team.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../environment/object_ptr.hpp"
#include "../environment/load_context_ptr.hpp"
#include <sge/math/vector/basic_decl.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class delayed_attack {
public:
	delayed_attack(
		pos_type const &spawn_point,
		space_unit angle,
		server::team::type,
		server::environment::object_ptr,
		server::environment::load_context_ptr,
		pos_type const &dest
	);

	pos_type const &
	spawn_point() const;
	
	space_unit
	angle() const;
	
	server::team::type
	team() const;
	
	server::environment::object_ptr const
	environment() const;
	
	server::environment::load_context_ptr const
	load_context() const;

	pos_type const &
	dest() const;
private:
	pos_type spawn_point_;
	space_unit angle_;
	server::team::type team_;
	server::environment::object_ptr environment_;
	server::environment::load_context_ptr load_context_;
	pos_type dest_;
};

}
}
}

#endif
