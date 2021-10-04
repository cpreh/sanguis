#ifndef SANGUIS_SERVER_AURAS_AOE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AOE_DAMAGE_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/server/aoe_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/influence_fwd.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::auras
{

class aoe_damage
:
	public sanguis::server::auras::aura
{
	FCPPT_NONMOVABLE(
		aoe_damage
	);
public:
	aoe_damage(
		sanguis::server::team,
		sanguis::server::aoe,
		sanguis::server::auras::influence,
		sanguis::server::damage::unit,
		sanguis::server::damage::modified_array const &
	);

	~aoe_damage()
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

	sanguis::server::damage::unit const damage_;

	sanguis::server::damage::modified_array const damage_values_;
};

}

#endif
