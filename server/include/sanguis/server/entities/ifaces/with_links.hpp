#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_LINKS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_LINKS_HPP_INCLUDED

#include <sanguis/server/entities/auto_weak_link_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_links_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace ifaces
{

class with_links
{
	FCPPT_NONCOPYABLE(
		with_links
	);
protected:
	with_links();
public:
	virtual
	~with_links() = 0;

	virtual
	sanguis::server::entities::auto_weak_link
	link() = 0;
protected:
	virtual
	void
	reset_links() = 0;
};

}
}
}
}

#endif
