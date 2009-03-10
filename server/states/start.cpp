#include "start.hpp"
#include "waiting.hpp"
#include "../log.hpp"
#include <sge/log/headers.hpp>
#include <sge/iconv.hpp>
#include <sge/text.hpp>
#include <ostream>

sanguis::server::states::start::start()
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("constructor"));
}

boost::statechart::result
sanguis::server::states::start::react(
	message_event const &m)
{
	// FIXME: handle this once and not in every state!
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("got unexpected message: ")
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

sge::log::logger &
sanguis::server::states::start::log()
{
	static sge::log::logger log_(
		server::log(),
		SGE_TEXT("start: "),
		true
	);
	return log_;
}
