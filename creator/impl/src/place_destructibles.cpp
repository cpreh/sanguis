#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/impl/place_destructibles.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_int.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/make_pos_ref_crange.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/distribution/basic.hpp>

sanguis::creator::destructible_container sanguis::creator::impl::place_destructibles(
    fcppt::reference<sanguis::creator::grid> const _grid,
    sanguis::creator::impl::random::generator &_generator)
{
  sanguis::creator::destructible_container result{};

  using uniform_int2 =
      fcppt::random::distribution::basic<sanguis::creator::impl::random::uniform_int<unsigned>>;

  auto roll_d8(fcppt::random::make_variate(
      fcppt::make_ref(_generator),
      uniform_int2{uniform_int2::param_type::min{1U}, uniform_int2::param_type::max{8U}}));

  auto place_stuff_random([&](unsigned _cutoff) -> bool { return roll_d8() <= _cutoff; });

  auto number_of_wall_neighbors(
      [&](sanguis::creator::pos const &_pos)
      {
        unsigned res = 0U;

        auto neighbors(fcppt::container::grid::neumann_neighbors(_pos));

        for (auto &n : neighbors)
        {
          if (FCPPT_ASSERT_OPTIONAL_ERROR(fcppt::container::grid::at_optional(_grid.get(), n))
                  .get() == sanguis::creator::tile::concrete_wall)
          {
            res++;
          }
        }

        return res;
      });

  for (auto const entry : fcppt::container::grid::make_pos_ref_crange(_grid.get()))
  {
    if (!sanguis::creator::tile_is_solid(entry.value()) &&
        place_stuff_random(number_of_wall_neighbors(entry.pos())))
    {
      result.push_back(sanguis::creator::destructible(
          sanguis::creator::destructible_pos(entry.pos()),
          sanguis::creator::destructible_type::barrel));
    }
  }

  return result;
}
