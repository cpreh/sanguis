#ifndef SANGUIS_SERVER_COLLISSION_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISSION_HPP_INCLUDED

#include "../messages/types.hpp"

namespace sanguis
{
namespace server
{

class entity;

bool collides(entity const&, entity const&);

}
}

#endif
