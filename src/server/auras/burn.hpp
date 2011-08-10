#ifndef SANGUIS_SERVER_AURAS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_BURN_HPP_INCLUDED

#include "aura.hpp"
#include "../buffs/provider.hpp"
#include "../damage/array.hpp"
#include "../damage/unit.hpp"
#include "../entities/with_body_fwd.hpp"
#include "../radius.hpp"
#include "../../diff_clock_fwd.hpp"
#include "../../duration.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class burn
:
	public aura
{
	FCPPT_NONCOPYABLE(
		burn
	);
public:
	burn(
		sanguis::diff_clock const &,
		server::radius,
		server::team::type team,
		damage::unit damage_per_pules,
		sanguis::duration const &pulse_diff,
		damage::array const &
	);

	~burn();
private:
	void
	enter(
		entities::with_body &
	);

	void
	leave(
		entities::with_body &
	);

	sanguis::diff_clock const &diff_clock_;

	sanguis::duration const pulse_diff_;

	damage::unit const damage_per_pulse_;

	damage::array const damage_values_;

	buffs::provider provider_;
};

}
}
}

#endif
