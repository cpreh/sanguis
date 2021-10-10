#ifndef SANGUIS_TILES_PAIR_STD_HASH_HPP_INCLUDED
#define SANGUIS_TILES_PAIR_STD_HASH_HPP_INCLUDED

#include <sanguis/creator/is_tile.hpp>
#include <sanguis/tiles/pair_fwd.hpp>
#if defined(FCPPT_CONFIG_CLANG_COMPILER)
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#endif
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <functional>
#include <fcppt/config/external_end.hpp>

namespace std
{

#if defined(FCPPT_CONFIG_CLANG_COMPILER)
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmismatched-tags)
#endif

template <typename Tile>
struct hash<sanguis::tiles::pair<Tile>>
{
  static_assert(sanguis::creator::is_tile<Tile>::value, "Tile must be a tile type");

  std::size_t operator()(sanguis::tiles::pair<Tile>) const;
};

#if defined(FCPPT_CONFIG_CLANG_COMPILER)
FCPPT_PP_POP_WARNING
#endif

}

#endif
