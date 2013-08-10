#ifndef SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/create_function.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class sentry
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONCOPYABLE(
		sentry
	);
public:
	sentry(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::reload_time,
		sanguis::server::weapons::range,
		sanguis::server::weapons::create_function const &sentry_weapon
	);

	~sentry();
private:
	void
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	);

	sanguis::random_generator &random_generator_;

	sanguis::server::weapons::create_function const sentry_weapon_;
};

}
}
}

#endif
