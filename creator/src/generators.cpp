#include <sanguis/creator/generator_vector.hpp>
#include <sanguis/creator/generators.hpp>
#include <sanguis/creator/impl/graveyard_name.hpp>
#include <sanguis/creator/impl/maze_name.hpp>
#include <sanguis/creator/impl/rooms_name.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sanguis::creator::generator_vector const global_generators{
    sanguis::creator::impl::graveyard_name(),
    //	sanguis::creator::impl::maze_name(),
    sanguis::creator::impl::rooms_name()};

FCPPT_PP_POP_WARNING

}

sanguis::creator::generator_vector const &sanguis::creator::generators()
{
  return global_generators;
}
