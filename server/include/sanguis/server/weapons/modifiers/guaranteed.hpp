#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_GUARANTEED_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_GUARANTEED_HPP_INCLUDED

#include <sanguis/server/weapons/modifiers/container.hpp>
#include <sanguis/server/weapons/modifiers/guaranteed_tag.hpp>
#include <fcppt/strong_typedef_impl.hpp>

namespace sanguis::server::weapons::modifiers
{

template <typename Parameters>
using guaranteed = fcppt::strong_typedef<
    sanguis::server::weapons::modifiers::container<Parameters>,
    sanguis::server::weapons::modifiers::guaranteed_tag>;

}

#endif
