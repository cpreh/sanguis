#ifndef SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_DELAYED_ATTACK_HPP_INCLUDED

#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/weapons/target.hpp>
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
		sanguis::server::center spawn_point,
		sanguis::server::angle,
		sanguis::server::team,
		sanguis::server::environment::object &,
		sanguis::server::weapons::target
	);

	sanguis::server::center const &
	spawn_point() const;

	sanguis::server::angle const
	angle() const;

	sanguis::server::team
	team() const;

	sanguis::server::environment::object &
	environment() const;

	sanguis::server::weapons::target const &
	target() const;
private:
	sanguis::server::center spawn_point_;

	sanguis::server::angle angle_;

	sanguis::server::team team_;

	sanguis::server::environment::object &environment_;

	sanguis::server::weapons::target target_;
};

}
}
}

#endif
