#include <sanguis/duration.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/tree/basic_sequence.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <sanguis/server/ai/tree/sequence.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::tree::sequence::sequence(
	sanguis::server::ai::tree::container &&_children
)
:
	sanguis::server::ai::tree::basic_sequence(
		std::move(
			_children
		)
	),
	current_{
		this->get().begin()
	}
{
}

sanguis::server::ai::tree::sequence::~sequence()
{
}

sanguis::server::ai::status
sanguis::server::ai::tree::sequence::run(
	sanguis::duration const _duration
)
{
	if(
		current_
		==
		this->get().end()
	)
	{
		current_ =
			this->get().begin();

		return
			sanguis::server::ai::status::success;
	}

	switch(
		(*current_)->run(
			_duration
		)
	)
	{
	case sanguis::server::ai::status::failure:
		current_ =
			this->get().begin();

		return
			sanguis::server::ai::status::failure;
	case sanguis::server::ai::status::success:
		current_ =
			std::next(
				current_
			);

		return
			sanguis::server::ai::status::running;
	case sanguis::server::ai::status::running:
		return
			sanguis::server::ai::status::running;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
