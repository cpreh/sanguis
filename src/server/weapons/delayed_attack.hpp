#ifndef SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED

#include "../angle.hpp"
#include "../center.hpp"
#include "../team.hpp"
#include "../vector.hpp"
#include "../environment/object_fwd.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class delayed_attack
{
public:
	delayed_attack(
		server::center const &spawn_point,
		server::angle,
		server::team::type,
		server::environment::object &,
		server::vector const &dest
	);

	server::center const &
	spawn_point() const;
	
	server::angle const
	angle() const;
	
	server::team::type
	team() const;
	
	server::environment::object &
	environment() const;
	
	server::vector const &
	dest() const;
private:
	server::center spawn_point_;

	server::angle angle_;

	server::team::type team_;

	server::environment::object &environment_;

	server::vector dest_;
};

}
}
}

#endif
