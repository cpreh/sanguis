#ifndef SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED

namespace sanguis
{
namespace server
{
namespace auras
{

class aggro
:
	public aura
{
public:
	aggro(
	);
private:
	void
	do_effect(
		entities::entity %target
	);
};


}
}
}

#endif
