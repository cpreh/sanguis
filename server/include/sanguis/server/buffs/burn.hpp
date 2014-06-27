#ifndef SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

class burn
:
	public sanguis::server::buffs::buff
{
	FCPPT_NONCOPYABLE(
		burn
	);
public:
	burn(
		sanguis::server::entities::with_health &,
		sanguis::server::buffs::burn_interval,
		sanguis::server::damage::unit,
		sanguis::server::damage::modified_array const &
	);

	~burn()
	override;
private:
	sanguis::buff_type
	type() const
	override;

	void
	update()
	override;

	bool
	greater(
		sanguis::server::buffs::buff const &
	) const
	override;

	sanguis::server::entities::with_health &entity_;

	sanguis::diff_timer interval_timer_;

	sanguis::server::damage::unit const damage_;

	sanguis::server::damage::modified_array const damage_values_;
};

}
}
}

#endif
