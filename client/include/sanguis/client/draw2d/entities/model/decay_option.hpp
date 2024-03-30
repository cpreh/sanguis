#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_DECAY_OPTION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_DECAY_OPTION_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/model/decay_option_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::draw2d::entities::model
{

enum class decay_option : std::uint8_t
{
  immediate,
  delayed
};

}

#endif
