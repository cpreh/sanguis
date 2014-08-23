#include <sanguis/duration.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <sanguis/server/ai/tree/priority_sequence.hpp>
#include <sanguis/server/ai/tree/status.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::tree::priority_sequence::priority_sequence(
	sanguis::server::ai::tree::container &&_children
)
:
	children_(
		std::move(
			_children
		)
	)
{
}

sanguis::server::ai::tree::priority_sequence::~priority_sequence()
{
}

sanguis::server::ai::tree::status
sanguis::server::ai::tree::priority_sequence::run(
	sanguis::duration const _duration
)
{
	for(
		auto it(
			children_.begin()
		);
		it != children_.end();
		++it
	)
	{
		switch(
			(*it)->run(
				_duration
			)
		)
		{
		case sanguis::server::ai::tree::status::started:
			for(
				auto &elem
				:
				boost::make_iterator_range(
					std::next(
						it
					),
					children_.end()
				)
			)
				elem->clear();

			return
				sanguis::server::ai::tree::status::started;
		case sanguis::server::ai::tree::status::ended_failure:
			continue;
		case sanguis::server::ai::tree::status::ended_success:
			return
				sanguis::server::ai::tree::status::ended_success;
		case sanguis::server::ai::tree::status::running:
			return
				sanguis::server::ai::tree::status::running;
		}
	}

	return
		sanguis::server::ai::tree::status::ended_failure;
}

void
sanguis::server::ai::tree::priority_sequence::clear()
{
	for(
		auto const &child
		:
		children_
	)
		child->clear();
}
