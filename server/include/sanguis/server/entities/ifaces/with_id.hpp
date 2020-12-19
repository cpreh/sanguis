#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_ID_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_ID_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace ifaces
{

class with_id
{
	FCPPT_NONMOVABLE(
		with_id
	);
protected:
	with_id();
public:
	[[nodiscard]]
	virtual
	sanguis::entity_id
	id() const = 0;

	virtual
	~with_id();
};

}
}
}
}

#endif
