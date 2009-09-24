#ifndef SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AURAS_HPP_INCLUDED

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
