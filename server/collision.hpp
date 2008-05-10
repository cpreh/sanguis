#ifndef SANGUIS_SERVER_COLLISSION_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISSION_HPP_INCLUDED

namespace sanguis
{
namespace server
{
namespace entities
{
class entity;
}

bool collides(
	entities::entity const&,
	entities::entity const&);

}
}

#endif
