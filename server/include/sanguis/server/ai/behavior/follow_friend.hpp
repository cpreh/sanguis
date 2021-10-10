#ifndef SANGUIS_SERVER_AI_BEHAVIOR_FOLLOW_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_FOLLOW_FRIEND_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/optional_with_body_ref_fwd.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::ai::behavior
{

class follow_friend : public sanguis::server::ai::behavior::base
{
  FCPPT_NONMOVABLE(follow_friend);

public:
  follow_friend(sanguis::server::ai::context_ref, sanguis::server::ai::sight_range);

  ~follow_friend() override;

  [[nodiscard]] sanguis::server::entities::transfer_result transfer() override;

  [[nodiscard]] bool start() override;

  [[nodiscard]] sanguis::server::ai::status update(sanguis::duration) override;

private:
  void target_enters(sanguis::server::entities::with_body_ref);

  void target_leaves(sanguis::server::entities::with_body & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  [[nodiscard]] sanguis::server::entities::optional_with_body_ref first_target() const;

  sanguis::server::ai::sight_range const sight_range_;

  sanguis::server::ai::entity_set potential_targets_;

  sanguis::server::entities::auto_weak_link target_;
};

}

#endif
