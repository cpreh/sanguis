#ifndef SANGUIS_SERVER_AURAS_WEAPON_PICKUP_CANDIDATES_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_WEAPON_PICKUP_CANDIDATES_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/server/add_weapon_pickup_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_weapon_pickup_callback.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::auras
{

class weapon_pickup_candidates
:
	public sanguis::server::auras::aura
{
	FCPPT_NONMOVABLE(
		weapon_pickup_candidates
	);
public:
	weapon_pickup_candidates(
		sanguis::server::radius,
		sanguis::server::add_weapon_pickup_callback &&,
		sanguis::server::remove_weapon_pickup_callback &&
	);

	~weapon_pickup_candidates()
	override;
private:
	[[nodiscard]]
	sanguis::optional_aura_type
	type() const
	override;

	void
	enter(
		sanguis::server::entities::with_body_ref,
		sanguis::collision::world::created
	)
	override;

	void
	leave(
		sanguis::server::entities::with_body & // NOLINT(google-runtime-references)
	) // NOLINT(google-runtime-references)
	override;

	sanguis::server::add_weapon_pickup_callback const add_;

	sanguis::server::remove_weapon_pickup_callback const remove_;
};

}

#endif
