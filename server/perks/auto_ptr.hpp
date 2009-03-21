#ifndef SANGUIS_SERVER_PERKS_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_AUTO_PTR_HPP_INCLUDED

#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

class perk;

typedef sge::auto_ptr<perk> auto_ptr;

}
}
}

#endif
