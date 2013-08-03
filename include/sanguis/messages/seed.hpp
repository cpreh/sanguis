#ifndef SANGUIS_MESSAGES_SEED_HPP_INCLUDED
#define SANGUIS_MESSAGES_SEED_HPP_INCLUDED

#include <sanguis/creator/seed.hpp>
#include <alda/bindings/fundamental_strong.hpp>


namespace sanguis
{
namespace messages
{

typedef
alda::bindings::fundamental_strong<
	sanguis::creator::seed
>
seed;

}
}

#endif
