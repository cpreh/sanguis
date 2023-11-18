#include <sanguis/collision/impl/world/body_ghost_group_pair_body.hpp>
#include <sanguis/collision/impl/world/body_ghost_group_pair_ghost.hpp>
#include <sanguis/collision/impl/world/body_ghost_group_relation.hpp>
#include <sanguis/collision/impl/world/body_group_container.hpp>
#include <sanguis/collision/impl/world/body_groups_for_ghost_group.hpp>
#include <sanguis/collision/impl/world/make_groups.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/if.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/fold.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/mpl/list/push_back.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace
{

template <sanguis::collision::world::ghost_group Group>
using ghost_body_groups_static = fcppt::mpl::list::fold<
    sanguis::collision::impl::world::body_ghost_group_relation,
    fcppt::mpl::bind<
        fcppt::mpl::lambda<fcppt::mpl::if_>,
        fcppt::mpl::bind<
            fcppt::mpl::lambda<std::is_same>,
            fcppt::mpl::constant<
                std::integral_constant<sanguis::collision::world::ghost_group, Group>>,
            fcppt::mpl::bind<
                fcppt::mpl::lambda<sanguis::collision::impl::world::body_ghost_group_pair_ghost>,
                fcppt::mpl::arg<1>>>,
        fcppt::mpl::bind<
            fcppt::mpl::lambda<fcppt::mpl::list::push_back>,
            fcppt::mpl::arg<2>,
            fcppt::mpl::bind<
                fcppt::mpl::lambda<sanguis::collision::impl::world::body_ghost_group_pair_body>,
                fcppt::mpl::arg<1>>>,
        fcppt::mpl::arg<2>>,
    fcppt::mpl::list::object<>>;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(cert-err58-cpp)
auto const groups{sanguis::collision::impl::world::make_groups<
                  sanguis::collision::world::ghost_group,
                  sanguis::collision::world::body_group,
                  ghost_body_groups_static>::make()};

FCPPT_PP_POP_WARNING

}

sanguis::collision::impl::world::body_group_container const &
sanguis::collision::impl::world::body_groups_for_ghost_group(
    sanguis::collision::world::ghost_group const _group)
{
  return groups[_group];
}
