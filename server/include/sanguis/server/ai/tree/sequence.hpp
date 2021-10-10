#ifndef SANGUIS_SERVER_AI_TREE_SEQUENCE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_TREE_SEQUENCE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/tree/basic_sequence.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::ai::tree
{

class sequence : public sanguis::server::ai::tree::basic_sequence
{
  FCPPT_NONMOVABLE(sequence);

public:
  explicit sequence(sanguis::server::ai::tree::container &&);

  ~sequence() override;

private:
  [[nodiscard]] sanguis::server::ai::status run(sanguis::duration) override;

  sanguis::server::ai::tree::container::iterator current_;
};

}

#endif
