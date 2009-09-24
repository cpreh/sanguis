#ifndef SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BUFFS_HPP_INCLUDED

namespace sanguis
{
namespace server
{
namespace entities
{

class with_buffs
:
	public virtual base
{
protected:

private:
	void
	damage(
		space_unit,
		damage::array const &
	);

	typedef boost::ptr_list<
		buffs::buff
	> buff_container;

	buff_container buffs_;
};

}
}
}

#endif
