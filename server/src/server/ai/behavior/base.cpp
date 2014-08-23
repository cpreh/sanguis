#include <sanguis/server/ai/behavior/base.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::server::ai::behavior::base::base()
:
	started_{
		false
	}
{
}

sanguis::server::ai::behavior::base::~base()
{
}

bool
sanguis::server::ai::behavior::base::is_started() const
{
	return
		started_;
}

bool
sanguis::server::ai::behavior::base::start()
{
	FCPPT_ASSERT_PRE(
		!started_
	);

	started_ =
		this->do_start();

	return
		started_;
}

void
sanguis::server::ai::behavior::base::stop()
{
	FCPPT_ASSERT_PRE(
		started_
	);

	this->do_stop();

	started_ =
		false;
}
