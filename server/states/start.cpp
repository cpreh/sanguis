#include "start.hpp"
#include "waiting.hpp"
#include "../../log_headers.hpp"
#include <sge/iconv.hpp>
#include <ostream>

sanguis::server::states::start::start()
{}

boost::statechart::result
sanguis::server::states::start::react(
	message_event const &m)
{
	// FIXME: handle this once and not in every state!
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("server: got unexpected message: ")
			<< sge::iconv(typeid(*m.message).name()));
	return forward_event();
}

boost::statechart::result
sanguis::server::states::start::react(
	tick_event const &)
{
	context<machine>().listen();
	return transit<waiting>(); 
}
