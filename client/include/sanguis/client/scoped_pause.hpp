#ifndef SANGUIS_CLIENT_SCOPED_PAUSE_HPP_INCLUDED
#define SANGUIS_CLIENT_SCOPED_PAUSE_HPP_INCLUDED

#include <sanguis/client/send_callback.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client
{

class scoped_pause
{
	FCPPT_NONMOVABLE(
		scoped_pause
	);
public:
	explicit
	scoped_pause(
		sanguis::client::send_callback &&
	);

	~scoped_pause();
private:
	sanguis::client::send_callback const send_;
};

}

#endif
