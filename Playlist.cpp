#include"Playlist.h"
#include<iostream>
#include<string>

Playlist::Playlist(std::string name)
{
	this->name = name;
}

void Playlist::add(Song aSong)
{
	collection.push_back(aSong);
}

std::string Playlist::getNameOfPLayList() const
{
	return this->name;
}

void Playlist::printSongsInPLaylist() const
{
	for (Song s : collection)
	{
		s.print();
	}
	
}

bool Playlist::checkSong(std::string aSong)
{
	for (Song s : collection)
	{		
		if (s.get_namesong() == aSong)
		{			
			return true;
	    }
	}
	
	std::cout << "This song does not exist" << std::endl;
	return false;
}





