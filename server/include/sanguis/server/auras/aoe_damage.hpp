#ifndef SANGUIS_SERVER_AURAS_AOE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AOE_DAMAGE_HPP_INCLUDED

#include <sanguis/optional_aura_type_fwd.hpp>
#include <sanguis/server/aoe_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

class aoe_damage
:
	public sanguis::server::auras::aura
{
	FCPPT_NONCOPYABLE(
		aoe_damage
	);
public:
	aoe_damage(
		sanguis::server::team,
		sanguis::server::aoe,
		sanguis::server::damage::unit,
		sanguis::server::damage::array const &
	);

	~aoe_damage()
	override;
private:
	sanguis::optional_aura_type const
	type() const
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

	sanguis::server::damage::unit const damage_;

	sanguis::server::damage::array const damage_values_;
};

}
}
}

#endif
