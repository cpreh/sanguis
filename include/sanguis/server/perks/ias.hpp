#ifndef SANGUIS_SERVER_PERKS_IAS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IAS_HPP_INCLUDED

#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

class ias
:
	public sanguis::server::perks::perk
{
	FCPPT_NONCOPYABLE(
		ias
	);
public:
	ias();

	~ias();
private:
	void
	change(
		sanguis::server::entities::base &,
		sanguis::server::perks::level_diff
	);
};

}
}
}

#endif
