#ifndef SANGUIS_CLIENT_SOUND_MANAGER_HPP_INCLUDED
#define SANGUIS_CLIENT_SOUND_MANAGER_HPP_INCLUDED

#include <sanguis/client/sound_manager_fwd.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client
{

class sound_manager
{
  FCPPT_NONMOVABLE(sound_manager);

public:
  sound_manager();

  ~sound_manager();

  void add(sge::audio::sound::base_unique_ptr &&);

  void pause(bool);

  void update();

private:
  using sound_list = std::list<sge::audio::sound::base_unique_ptr>;

  sound_list sounds_;
};

}

#endif
