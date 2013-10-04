#ifndef SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/create_function.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
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
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::range,
		sanguis::server::weapons::magazine_size,
		sanguis::server::weapons::create_function const &sentry_weapon
	);

	~sentry();
private:
	bool
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	)
	override;

	sanguis::string_vector
	attributes() const
	override;

	sanguis::server::weapons::create_function const sentry_weapon_;
};

}
}
}

#endif
