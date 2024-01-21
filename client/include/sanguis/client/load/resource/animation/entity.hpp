#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_ENTITY_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_ENTITY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/load/resource/animation/entity_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis::client::load::resource::animation
{

class entity
{
  FCPPT_NONCOPYABLE(entity);

public:
  entity(sanguis::duration, sge::texture::const_part_unique_ptr &&);

  entity(entity &&) noexcept;

  entity &operator=(entity &&) noexcept;

  ~entity();

  [[nodiscard]] sanguis::duration delay() const;

  [[nodiscard]] sge::texture::part const &texture() const;

  [[nodiscard]] sge::renderer::dim2 dim() const;

private:
  sanguis::duration delay_;

  sge::texture::const_part_unique_ptr texture_;
};

}

#endif
