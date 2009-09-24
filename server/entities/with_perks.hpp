#ifndef SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_PERKS_HPP_INCLUDED

namespace sanguis
{
namespace server
{
namespace entities
{

class with_perks
:
	public virtual base
{
protected:
	explicit with_perks(
		base_parameters const &
	);
private:
	typedef boost::ptr_map<
		perk_type::type,
		perks::perk
	> perk_container;

	perk_container perks_;
};

}
}
}

#endif
