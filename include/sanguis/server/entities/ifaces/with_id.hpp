#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_ID_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_ID_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <fcppt/noncopyable.hpp>


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
	FCPPT_NONCOPYABLE(
		with_id
	);
protected:
	with_id();
public:
	virtual
	sanguis::entity_id const
	id() const = 0;

	virtual
	~with_id() = 0;
};

}
}
}
}

#endif
