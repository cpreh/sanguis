#ifndef SANGUIS_SERVER_WEAPONS_ATTACK_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTACK_HPP_INCLUDED

#include <sanguis/server/angle.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class attack
{
public:
	attack(
		sanguis::server::angle,
		sanguis::server::environment::object &,
		sanguis::server::weapons::target
	);

	sanguis::server::angle
	angle() const;

	sanguis::server::environment::object &
	environment() const;

	sanguis::server::weapons::target const &
	target() const;
private:
	sanguis::server::angle angle_;

	fcppt::reference<
		sanguis::server::environment::object
	> environment_;

	sanguis::server::weapons::target target_;
};

}
}
}

#endif
