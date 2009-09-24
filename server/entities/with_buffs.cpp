	buffs_(),
void
sanguis::server::entities::with_buffs::add_buff(
	buffs::auto_ptr b
)
{
	buffs_.push_back(b);
}

void
sanguis::server::entities::with_buffs::update(
	time_type const time
)
{
	for(
		buff_container::iterator it(buffs_.begin());
		it != buffs_.end();
	)
	{
		it->update(
			*this,
			time
		);

		if(it->expired())
			it = buffs_.erase(it);
		else
			++it;
	}
}
