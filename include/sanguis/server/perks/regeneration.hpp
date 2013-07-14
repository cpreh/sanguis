#ifndef SANGUIS_SERVER_PERKS_REGENERATION_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_REGENERATION_HPP_INCLUDED

#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

class regeneration
:
	public sanguis::server::perks::perk
{
	FCPPT_NONCOPYABLE(
		regeneration
	);
public:
	regeneration();

	~regeneration();
private:
	void
	change(
		sanguis::server::entities::with_perks &,
		sanguis::server::perks::level_diff
	);
};

}
}
}

#endif
