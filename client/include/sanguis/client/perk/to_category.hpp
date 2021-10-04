#ifndef SANGUIS_CLIENT_PERK_TO_CATEGORY_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TO_CATEGORY_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/client/perk/category_fwd.hpp>


namespace sanguis::client::perk
{

sanguis::client::perk::category
to_category(
	sanguis::perk_type
);

}

#endif
