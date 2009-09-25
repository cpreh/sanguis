#ifndef SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED

#include "base.hpp"
#include "base_parameters_fwd.hpp"
#include "../auras/aura.hpp"
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
protected:
	explicit with_auras(
		base_parameters const &
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
