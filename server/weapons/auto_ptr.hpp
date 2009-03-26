#ifndef SANGUIS_SERVER_WEAPONS_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_AUTO_PTR_HPP_INCLUDED

#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class weapon;

typedef sge::auto_ptr<weapon> auto_ptr;

}
}
}

#endif
