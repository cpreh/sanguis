#include <sanguis/client/draw2d/entities/with_auras_model.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/draw2d/entities/with_buffs_impl.hpp>

template class sanguis::client::draw2d::entities::with_buffs<
    sanguis::client::draw2d::entities::with_auras_model>;
