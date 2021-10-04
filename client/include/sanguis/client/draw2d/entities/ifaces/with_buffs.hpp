#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_BUFFS_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::entities::ifaces
{

class with_buffs
{
	FCPPT_NONMOVABLE(
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

#endif
