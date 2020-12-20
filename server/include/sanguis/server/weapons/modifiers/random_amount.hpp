#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_RANDOM_AMOUNT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_RANDOM_AMOUNT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/random/amount.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace modifiers
{

sanguis::server::random::amount
random_amount(
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::server::random::amount
);

}
}
}
}

#endif
