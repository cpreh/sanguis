#ifndef SANGUIS_RANDOM_GENERATOR_REF_HPP_INCLUDED
#define SANGUIS_RANDOM_GENERATOR_REF_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{

using
random_generator_ref
=
fcppt::reference<
	sanguis::random_generator
>;

}

#endif
