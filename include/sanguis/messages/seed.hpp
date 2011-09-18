#ifndef SANGUIS_MESSAGES_SEED_HPP_INCLUDED
#define SANGUIS_MESSAGES_SEED_HPP_INCLUDED

#include <sanguis/messages/bindings/fundamental_strong.hpp>
#include <sanguis/creator/generator/seed.hpp>

namespace sanguis
{
namespace messages
{

typedef bindings::fundamental_strong<
	sanguis::creator::generator::seed
> seed;

}
}

#endif
