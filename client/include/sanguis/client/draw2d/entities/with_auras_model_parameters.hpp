#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_MODEL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_MODEL_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/with_auras_model_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/with_auras_parameters_decl.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

extern
template
class
sanguis::client::draw2d::entities::with_auras_parameters<
	sanguis::client::draw2d::entities::model::parameters
>;

FCPPT_PP_POP_WARNING

#endif
