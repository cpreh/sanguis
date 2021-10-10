#include <sanguis/messages/call/forward_to_default.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/call/result_variant.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::messages::call::result::result(boost::statechart::result _statechart_result)
    : variant_(std::move(_statechart_result))
{
}

sanguis::messages::call::result::result(sanguis::messages::call::forward_to_default const _forward)
    : variant_(_forward)
{
}

sanguis::messages::call::result_variant const &sanguis::messages::call::result::get() const
{
  return variant_;
}
