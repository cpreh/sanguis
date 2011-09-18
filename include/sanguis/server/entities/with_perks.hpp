#ifndef SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED

#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/perks/perk_fwd.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>
#include <sanguis/perk_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_perks
:
	public virtual base
{
	FCPPT_NONCOPYABLE(
		with_perks
	);
public:
	void
	add_perk(
		perks::unique_ptr
	);
protected:
	with_perks();

	~with_perks();

	void
	on_update();
private:
	typedef boost::ptr_map<
		perk_type::type,
		perks::perk
	> perk_container;

	perk_container perks_;
};

}
}
}

#endif
