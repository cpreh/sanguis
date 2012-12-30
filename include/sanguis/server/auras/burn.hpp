#ifndef SANGUIS_SERVER_AURAS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_BURN_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/buffs/provider.hpp>
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

class burn
:
	public sanguis::server::auras::aura
{
	FCPPT_NONCOPYABLE(
		burn
	);
public:
	burn(
		sanguis::diff_clock const &,
		sanguis::server::radius,
		sanguis::server::team,
		sanguis::server::damage::unit damage_per_pules,
		sanguis::duration const &pulse_diff,
		sanguis::server::damage::array const &
	);

	~burn();
private:
	void
	enter(
		sanguis::server::entities::with_body &
	);

	void
	leave(
		sanguis::server::entities::with_body &
	);

	sanguis::diff_clock const &diff_clock_;

	sanguis::duration const pulse_diff_;

	sanguis::server::damage::unit const damage_per_pulse_;

	sanguis::server::damage::array const damage_values_;

	sanguis::server::buffs::provider provider_;
};

}
}
}

#endif
