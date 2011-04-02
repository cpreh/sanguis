#ifndef SANGUIS_SERVER_PERKS_IRS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IRS_HPP_INCLUDED

#include "perk.hpp"
#include "level_diff.hpp"
#include "../entities/base_fwd.hpp"
#include "../level.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

class irs
:
	public perk
{
	FCPPT_NONCOPYABLE(
		irs
	);
public:
	irs();

	~irs();
private:
	void
	change(
		entities::base &,
		level_diff
	);

	server::level const
	max_level() const;
};

}
}
}

#endif
