#ifndef SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED

#include "with_body.hpp"
#include "../auras/aura_fwd.hpp"
#include "../auras/unique_ptr.hpp"
#include "../collision/global_groups_fwd.hpp"
#include <sge/collision/shapes/container.hpp>
#include <sge/collision/world_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_auras
:
	public virtual with_body
{
	FCPPT_NONCOPYABLE(
		with_auras
	);
public:
	void
	add_aura(
		auras::unique_ptr
	);
protected:
	with_auras();

	~with_auras();

	void
	on_update(
		time_type
	);

	void
	recreate_ghosts(
		collision::ghost_parameters const &
	);
private:
	typedef boost::ptr_list<
		auras::aura
	> aura_container;

	aura_container auras_;
};

}
}
}

#endif
