#ifndef SANGUIS_CLIENT_SOUND_MANAGER_HPP_INCLUDED
#define SANGUIS_CLIENT_SOUND_MANAGER_HPP_INCLUDED

#include <sanguis/client/sound_manager_fwd.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

class sound_manager
{
	FCPPT_NONCOPYABLE(
		sound_manager
	);
public:
	sound_manager();

	~sound_manager();

	void
	add(
		sge::audio::sound::base_unique_ptr &&
	);

	void
	pause(
		bool
	);

	void
	update();
private:
	typedef
	std::list<
		sge::audio::sound::base_unique_ptr
	>
	sound_list;

	sound_list sounds_;
};

}
}

#endif
