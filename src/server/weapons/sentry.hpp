#ifndef SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED

#include "weapon.hpp"
#include "delayed_attack_fwd.hpp"
#include "base_cooldown.hpp"
#include "cast_point.hpp"
#include "reload_time.hpp"
#include "create_function.hpp"
#include "../../diff_clock_fwd.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class sentry
:
	public weapon
{
	FCPPT_NONCOPYABLE(
		sentry
	);
public:
	sentry(
		sanguis::diff_clock const &,
		weapon_type::type,
		weapons::base_cooldown,
		weapons::cast_point,
		weapons::reload_time,
		create_function const &sentry_weapon
	);

	~sentry();
private:
	void
	do_attack(
		delayed_attack const &
	);

	create_function const sentry_weapon_;
};

}
}
}

#endif
