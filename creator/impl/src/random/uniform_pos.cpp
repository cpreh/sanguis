#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <sanguis/creator/impl/random/uniform_pos.hpp>
#include <sanguis/creator/impl/random/uniform_pos_parameters.hpp>
#include <fcppt/reference_impl.hpp>

sanguis::creator::impl::random::uniform_pos::uniform_pos(
    fcppt::reference<sanguis::creator::impl::random::generator> const _generator,
    sanguis::creator::dim const &_dim)
    : random_x_(_generator, sanguis::creator::impl::random::uniform_pos_parameters(_dim.w())),
      random_y_(_generator, sanguis::creator::impl::random::uniform_pos_parameters(_dim.h()))
{
}

sanguis::creator::pos sanguis::creator::impl::random::uniform_pos::operator()()
{
  sanguis::creator::size_type const pos_x(random_x_());

  sanguis::creator::size_type const pos_y(random_y_());

  return sanguis::creator::pos(pos_x, pos_y);
}
