#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_AURAS_MODEL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_AURAS_MODEL_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/with_auras_model.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model_fwd.hpp> // IWYU pragma: export
#include <sanguis/client/draw2d/entities/with_buffs_auras_model_parameters.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_decl.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

extern template class sanguis::client::draw2d::entities::with_buffs<
    sanguis::client::draw2d::entities::with_auras_model>;

FCPPT_PP_POP_WARNING

#endif
