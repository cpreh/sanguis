#ifndef SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED

#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class delayed_attack
{
	FCPPT_NONASSIGNABLE(
		delayed_attack
	);
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
