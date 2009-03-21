#ifndef SANGUIS_SERVER_AURAS_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AUTO_PTR_HPP_INCLUDED

#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class aura;

typedef sge::auto_ptr<
	aura
> auto_ptr;

}
}
}

#endif
