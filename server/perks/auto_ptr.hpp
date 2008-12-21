#ifndef SANGUIS_SERVER_PERKS_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_AUTO_PTR_HPP_INCLUDED

#include <memory>

namespace sanguis
{
namespace server
{
namespace perks
{

class perk;

typedef std::auto_ptr<perk> auto_ptr;

}
}
}

#endif
