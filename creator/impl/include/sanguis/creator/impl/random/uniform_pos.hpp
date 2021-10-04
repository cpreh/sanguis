#ifndef SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_POS_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_POS_HPP_INCLUDED

#include <sanguis/creator/dim_fwd.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <sanguis/creator/impl/random/uniform_pos_fwd.hpp>
#include <sanguis/creator/impl/random/uniform_size_variate.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sanguis::creator::impl::random
{

class uniform_pos
{
public:
	uniform_pos(
		fcppt::reference<
			sanguis::creator::impl::random::generator
		>,
		sanguis::creator::dim const &
	);

	[[nodiscard]]
	sanguis::creator::pos
	operator()();
private:
	sanguis::creator::impl::random::uniform_size_variate random_x_;

	sanguis::creator::impl::random::uniform_size_variate random_y_;
};

}

#endif
