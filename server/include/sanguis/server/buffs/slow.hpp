#ifndef SANGUIS_SERVER_BUFFS_SLOW_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_SLOW_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>
#include <sanguis/server/entities/with_velocity_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

class slow
:
	public sanguis::server::buffs::buff
{
	FCPPT_NONMOVABLE(
		slow
	);
public:
	slow(
		sanguis::server::entities::with_velocity_ref,
		sanguis::server::buffs::slow_factor
	);

	~slow()
	override;
private:
	[[nodiscard]]
	sanguis::buff_type
	type() const
	override;

	void
	apply(
		sanguis::server::buffs::buff::added
	)
	override;

	[[nodiscard]]
	bool
	greater(
		sanguis::server::buffs::buff const &
	) const
	override;

	sanguis::server::entities::with_velocity_ref const entity_;

	sanguis::server::buffs::slow_factor const factor_;
};

}
}
}

#endif
