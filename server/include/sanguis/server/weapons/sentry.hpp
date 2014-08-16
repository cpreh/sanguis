#ifndef SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/sentry_parameters_fwd.hpp>
#include <sanguis/server/weapons/sentry_weapon.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/health.hpp>
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
		sanguis::random_generator &,
		sanguis::server::weapons::sentry_weapon const &,
		sanguis::server::weapons::sentry_parameters const &
	);

	~sentry()
	override;
private:
	sanguis::server::weapons::attack_result
	do_attack(
		sanguis::server::weapons::attack const &
	)
	override;

	sanguis::weapon_attribute_vector
	attributes() const
	override;

	sanguis::server::weapons::attributes::health const health_;

	sanguis::server::weapons::sentry_weapon const sentry_weapon_;

	sanguis::weapon_attribute_vector const attributes_;
};

}
}
}

#endif
