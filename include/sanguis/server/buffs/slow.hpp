#ifndef SANGUIS_SERVER_BUFFS_SLOW_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_SLOW_HPP_INCLUDED

#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>


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
	FCPPT_NONCOPYABLE(
		slow
	);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		sanguis::server::entities::property::value,
		factor
	);

	explicit
	slow(
		sanguis::server::buffs::slow::factor
	);

	~slow();
private:
	void
	add(
		sanguis::server::entities::base &
	)
	override;

	void
	remove(
		sanguis::server::entities::base &
	)
	override;

	bool
	less(
		sanguis::server::buffs::buff const &
	) const
	override;

	sanguis::server::buffs::slow::factor const factor_;
};

}
}
}

#endif
