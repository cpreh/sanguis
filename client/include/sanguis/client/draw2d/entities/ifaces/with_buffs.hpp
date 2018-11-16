#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_BUFFS_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace ifaces
{

class with_buffs
{
	FCPPT_NONCOPYABLE(
		with_buffs
	);
protected:
	with_buffs();

	virtual
	~with_buffs();
public:
	virtual
	void
	add_buff(
		sanguis::buff_type
	) = 0;

	virtual
	void
	remove_buff(
		sanguis::buff_type
	) = 0;
};

}
}
}
}
}

#endif
