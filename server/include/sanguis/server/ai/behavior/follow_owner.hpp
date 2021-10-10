#ifndef SANGUIS_SERVER_AI_BEHAVIOR_FOLLOW_OWNER_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_FOLLOW_OWNER_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::ai::behavior
{

class follow_owner : public sanguis::server::ai::behavior::base
{
  FCPPT_NONMOVABLE(follow_owner);

public:
  follow_owner(sanguis::server::ai::context_ref, sanguis::server::entities::spawn_owner);

  ~follow_owner() override;

  [[nodiscard]] bool start() override;

  [[nodiscard]] sanguis::server::ai::status update(sanguis::duration) override;

private:
  sanguis::server::entities::spawn_owner const spawn_owner_;
};

}

#endif
