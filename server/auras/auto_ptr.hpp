#ifndef SANGUIS_SERVER_AURAS_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AUTO_PTR_HPP_INCLUDED

#include "aura_fwd.hpp"
#include <fcppt/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

typedef sge::auto_ptr<
	aura
> auto_ptr;

}
}
}

#endif
