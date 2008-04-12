#ifndef SANGUIS_SERVER_COLLISSION_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISSION_HPP_INCLUDED

namespace sanguis
{
namespace server
{

class entity;

bool collides(entity const&, entity const&);

}
}

#endif
