#ifndef SANGUIS_SERVER_PERKS_REGENERATION_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_REGENERATION_HPP_INCLUDED

#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

class regeneration
:
	public perk
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
		entities::base &,
		level_diff
	);
};

}
}
}

#endif
