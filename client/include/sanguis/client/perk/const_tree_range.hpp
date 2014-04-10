#ifndef SANGUIS_CLIENT_PERK_CONST_TREE_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CONST_TREE_RANGE_HPP_INCLUDED

#include <sanguis/client/perk/const_tree_range_fwd.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

class const_tree_range
{
public:
	const_tree_range(
		sanguis::client::perk::tree::const_iterator,
		sanguis::client::perk::tree::const_iterator
	);

	typedef
	std::pair<
		sanguis::client::perk::tree::const_iterator,
		sanguis::client::perk::tree::const_iterator
	>
	pair;

	explicit
	const_tree_range(
		pair const &
	);

	sanguis::client::perk::tree::const_iterator
	begin() const;

	sanguis::client::perk::tree::const_iterator
	end() const;

	bool
	empty() const;
private:
	sanguis::client::perk::tree::const_iterator begin_;

	sanguis::client::perk::tree::const_iterator end_;
};

}
}
}

#endif
