#ifndef SANGUIS_SERVER_PERKS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_HEALTH_HPP_INCLUDED

#include "perk.hpp"
#include "level_type.hpp"
#include "level_diff.hpp"
#include "../entities/base_fwd.hpp"
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

	~healt();
private:
	void
	change(
		entities::base &,
		level_diff
	);

	level_type
	max_level() const;
};

}
}
}

#endif
