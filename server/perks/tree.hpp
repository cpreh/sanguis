#ifndef SANGUIS_SERVER_PERKS_TREE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_HPP_INCLUDED

#include "status.hpp"
#include "list.hpp"
#include "../../perk_type.hpp"
#include "../level_type.hpp"
#include <fcppt/container/tree_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

class tree {
	FCPPT_NONCOPYABLE(tree)
public:
	tree();
	~tree();

	bool choosable(
		perk_type::type,
		server::level_type player_level) const;
	
	void take(
		perk_type::type);
	
	list const
	choosables(
		server::level_type player_level) const;

	// public for helper functions
	typedef fcppt::container::tree<
		status
	> tree_type;
private:
	tree_type impl;
};

}
}
}

#endif
