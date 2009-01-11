#include "tree.hpp"
#include "../../exception.hpp"
#include <sge/container/tree_impl.hpp>
#include <sge/container/traversal.hpp>
#include <sge/text.hpp>

namespace
{

struct perk_equal {
	explicit perk_equal(
		sanguis::perk_type::type);
	
	bool operator()(
		sanguis::server::perks::tree::tree_type const &) const;
private:
	sanguis::perk_type::type p;
};

}

sanguis::server::perks::tree::tree()
:
	impl(
		status(
			perk_type::size,
			true))
{
}

sanguis::server::perks::tree::~tree()
{}

bool
sanguis::server::perks::tree::choosable(
	perk_type::type const p) const
{
	typedef 
	sge::container::traversal<
		tree_type const
	> traversal;
	
	traversal trav(
		impl);
	
	traversal::iterator const it = std::find_if(
		trav.begin(),
		trav.end(),
		perk_equal(
			p));
	
	if(it == trav.end())
		return false;

	for(
		tree_type::const_iterator tree_it(
			it.internal());
		tree_it->has_parent();
		tree_it = tree_it->child_position()
	)
		if(!(*it).value().chosen())
			return false;
	return true;
}

void
sanguis::server::perks::tree::take(
	perk_type::type const p)
{
	typedef 
	sge::container::traversal<
		tree_type
	> traversal;
	
	traversal trav(
		impl);
	
	traversal::iterator const it = std::find_if(
		trav.begin(),
		trav.end(),
		perk_equal(
			p));
	
	if(it == trav.end())
		throw exception(
			SGE_TEXT("Perk von found in the tree!"));
	
	// TODO: check for chosen, maybe increment the perk's level instead?
	(*it).value().choose();
}

sanguis::server::perks::list const
sanguis::server::perks::tree::choosables() const
{
	// TODO: very wasteful but easy
	list ret;

	for(unsigned i = 0; i < perk_type::size; ++i)
	{
		perk_type::type const pt(
			static_cast<
				perk_type::type
			>(
				i));
		if(choosable(pt))
			ret.push_back(pt);
	}
	return ret;
}

namespace
{

perk_equal::perk_equal(
	sanguis::perk_type::type const p)
:
	p(p)
{}
	
bool
perk_equal::operator()(
	sanguis::server::perks::tree::tree_type const &t
) const
{
	return t.value().type() == p;
}

}

