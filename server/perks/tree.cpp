#include "tree.hpp"
#include <sge/container/tree_impl.hpp>

sanguis::server::perks::tree::tree()
:
	impl(
		perk_type::ims)
{
}

sanguis::server::perks::tree::~tree()
{}


bool
sanguis::server::perks::tree::choosable(
	perk_type::type) const
{
	return false; // TODO:
}

void
sanguis::server::perks::tree::take(
	perk_type::type const p)
{
	// TODO
}

sanguis::server::perks::list const
sanguis::server::perks::tree::choosables() const
{
	return list(); // TODO:
}
