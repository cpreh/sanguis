#ifndef SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED

#include "base.hpp"
#include "../auras/aura_fwd.hpp"
#include "../auras/auto_ptr.hpp"
#include "../collision/global_groups_fwd.hpp"
#include "../collision/create_parameters_fwd.hpp"
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_auras
:
	public virtual base
{
public:
	void
	add_aura(
		auras::auto_ptr
	);
protected:
	with_auras();

	~with_auras();

	void
	on_update(
		time_type
	);
private:
	void
	on_center(
		pos_type const &
	);

	void
	on_destroy();

	void
	on_transfer(
		collision::global_groups const &,
		collision::create_parameters const &
	);

	typedef boost::ptr_list<
		auras::aura
	> aura_container;

	aura_container auras_;
};

}
}
}

#endif
