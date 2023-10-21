#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/sprite/system_impl.hpp>
#include <sanguis/client/draw2d/sprite/normal/choices.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp> // NOLINT(misc-include-cleaner)

template class sanguis::client::draw2d::sprite::
    system<sanguis::client::draw2d::sprite::normal::choices, sanguis::client::draw2d::z_ordering>;
