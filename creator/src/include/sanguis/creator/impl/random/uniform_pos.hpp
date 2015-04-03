#ifndef SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_POS_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_POS_HPP_INCLUDED

#include <sanguis/creator/dim_fwd.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <sanguis/creator/impl/random/uniform_pos_fwd.hpp>
#include <sanguis/creator/impl/random/uniform_size_variate.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{
namespace random
{

// TODO: Try to generalize this in fcppt
class uniform_pos
{
public:
	// TODO: More constructors for different ranges?
	uniform_pos(
		sanguis::creator::impl::random::generator &,
		sanguis::creator::dim
	);

	sanguis::creator::pos
	operator()();
private:
	sanguis::creator::impl::random::uniform_size_variate random_x_;

	sanguis::creator::impl::random::uniform_size_variate random_y_;
};

}
}
}
}

#endif
