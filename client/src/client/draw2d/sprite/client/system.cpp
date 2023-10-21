#include <sanguis/client/draw2d/sprite/system_impl.hpp>
#include <sanguis/client/draw2d/sprite/client/category.hpp>
#include <sanguis/client/draw2d/sprite/client/choices.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp> // NOLINT(misc-include-cleaner)

template class sanguis::client::draw2d::sprite::system<
    sanguis::client::draw2d::sprite::client::choices,
    sanguis::client::draw2d::sprite::client::category>;
