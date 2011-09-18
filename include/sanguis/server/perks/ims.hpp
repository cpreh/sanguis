#ifndef SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED

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

class ims
:
	public perk
{
	FCPPT_NONCOPYABLE(
		ims
	);
public:
	ims();

	~ims();
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
