#ifndef SANGUIS_SERVER_PERKS_TREE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_HPP_INCLUDED

#include "status.hpp"
#include "list.hpp"
#include "../../perk_type.hpp"
#include <sge/container/tree_decl.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace perks
{

class tree {
	SGE_NONCOPYABLE(tree)
public:
	tree();
	~tree();

	bool choosable(
		perk_type::type) const;
	void take(
		perk_type::type);
	
	list const
	choosables() const;

	// public for helper functions
	typedef sge::container::tree<
		status
	> tree_type;
private:
	tree_type impl;
};

}
}
}

#endif
