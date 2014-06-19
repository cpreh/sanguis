#ifndef SANGUIS_SERVER_WEAPONS_ATTACK_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTACK_HPP_INCLUDED

#include <sanguis/server/angle.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class attack
{
	FCPPT_NONASSIGNABLE(
		attack
	);
public:
	attack(
		sanguis::server::angle,
		sanguis::server::environment::object &,
		sanguis::server::weapons::target
	);

	sanguis::server::angle const
	angle() const;

	sanguis::server::environment::object &
	environment() const;

	sanguis::server::weapons::target const &
	target() const;
private:
	sanguis::server::angle angle_;

	sanguis::server::environment::object &environment_;

	sanguis::server::weapons::target target_;
};

}
}
}

#endif
