#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/destructible_pos.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/interior_range.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/parameters_fwd.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <sanguis/creator/impl/generators/start.hpp>
#include <sanguis/creator/impl/random/generator.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/creator/impl/random/uniform_int.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::creator::impl::result
sanguis::creator::impl::generators::start(sanguis::creator::impl::parameters const &_parameters)
{
  if (_parameters.opening_count_array()[sanguis::creator::opening_type::entry] >
          sanguis::creator::opening_count{1U} ||
      _parameters.opening_count_array()[sanguis::creator::opening_type::exit] >
          sanguis::creator::opening_count{1U})
  {
    throw sanguis::creator::exception{
        FCPPT_TEXT("The start level can only deal with 0 or 1 opening each.")};
  }

  sanguis::creator::dim const grid_size{fcppt::math::dim::fill<sanguis::creator::dim>(10)};

  sanguis::creator::grid grid{grid_size, sanguis::creator::tile::concrete_wall};

  for (auto const pos : sanguis::creator::impl::interior_range(fcppt::make_ref(grid)))
  {
    pos.value() = sanguis::creator::tile::nothing;
  }

  sanguis::creator::opening const start_portal{sanguis::creator::pos{1U, grid_size.h() / 2U}};

  sanguis::creator::opening const exit_portal{
      sanguis::creator::pos{grid_size.w() - 2U, grid_size.h() / 2U}};

  sanguis::creator::background_grid bg_grid{grid_size, sanguis::creator::background_tile::dirt};

  using uniform_int2 =
      fcppt::random::distribution::basic<sanguis::creator::impl::random::uniform_int<unsigned>>;

  auto random_dirt_grass(fcppt::random::make_variate(
      fcppt::make_ref(_parameters.randgen()),
      uniform_int2{uniform_int2::param_type::min{0U}, uniform_int2::param_type::max{1U}}));

  for (auto const pos : sanguis::creator::impl::interior_range(fcppt::make_ref(bg_grid)))
  {
    pos.value() = random_dirt_grass() != 0U ? sanguis::creator::background_tile::dirt
                                            : sanguis::creator::background_tile::grass;
  }

  fcppt::optional::to_exception(
      fcppt::container::grid::at_optional(grid, exit_portal.get()),
      [] { return sanguis::creator::exception{FCPPT_TEXT("Exit portal out of range!")}; })
      .get() = sanguis::creator::tile::stairs;

  return sanguis::creator::impl::result{
      std::move(grid),
      std::move(bg_grid),
      fcppt::enum_::array_init<sanguis::creator::opening_container_array>(
          [&_parameters, start_portal, exit_portal](
              sanguis::creator::opening_type const _opening_type)
          {
            if (_parameters.opening_count_array()[_opening_type] ==
                sanguis::creator::opening_count{0U})
            {
              return sanguis::creator::opening_container{};
            }

            FCPPT_PP_PUSH_WARNING
            FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
            switch (_opening_type)
            {
            case sanguis::creator::opening_type::entry:
              return sanguis::creator::opening_container{start_portal};
            case sanguis::creator::opening_type::exit:
              return sanguis::creator::opening_container{exit_portal};
            }

            FCPPT_PP_POP_WARNING

            throw fcppt::enum_::make_invalid(_opening_type);
          }),
      sanguis::creator::spawn_container(),
      sanguis::creator::destructible_container{sanguis::creator::destructible(
          sanguis::creator::destructible_pos(sanguis::creator::pos(2U, 2U)),
          sanguis::creator::destructible_type::barrel)}};
}
