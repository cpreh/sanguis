#ifndef SANGUIS_CLIENT_PERK_COMPARE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_COMPARE_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/tree.hpp>


namespace sanguis::client::perk
{

class compare
{
public:
	explicit
	compare(
		sanguis::perk_type
	);

	bool
	operator()(
		sanguis::client::perk::tree const &
	) const;
private:
	sanguis::perk_type type_;
};

}

#endif
