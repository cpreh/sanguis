#ifndef SANGUIS_SERVER_PERKS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_HEALTH_HPP_INCLUDED

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

class health
:
	public perk
{
	FCPPT_NONCOPYABLE(
		health
	);
public:
	health();

	~health();
private:
	void
	change(
		entities::base &,
		perks::level_diff
	);
};

}
}
}

#endif
