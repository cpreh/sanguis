#ifndef SANGUIS_SERVER_AURAS_WEAPON_PICKUP_CANDIDATES_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_WEAPON_PICKUP_CANDIDATES_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/collision/world/group_field_fwd.hpp>
#include <sanguis/server/add_weapon_pickup_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_weapon_pickup_callback.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

class weapon_pickup_candidates
:
	public sanguis::server::auras::aura
{
	FCPPT_NONCOPYABLE(
		weapon_pickup_candidates
	);
public:
	weapon_pickup_candidates(
		sanguis::server::radius,
		sanguis::server::add_weapon_pickup_callback const &,
		sanguis::server::remove_weapon_pickup_callback const &
	);

	~weapon_pickup_candidates()
	override;
private:
	sanguis::optional_aura_type const
	type() const
	override;

	sanguis::collision::world::group_field const
	collision_groups() const
	override;

	void
	enter(
		sanguis::server::entities::with_body &
	)
	override;

	void
	leave(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::server::add_weapon_pickup_callback const add_;

	sanguis::server::remove_weapon_pickup_callback const remove_;
};

}
}
}

#endif
