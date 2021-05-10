#include "User.h"
#include<string>

User::User()
{
	this->name = "";
	this->password = "";
	this->vote = "";
	this->playlists.clear();
}
User::User(std::string name,std::string password,std::string vote)
{
	this->name=name;
	this->password = password;
	this->vote = vote;
}

std::string User::getName() const
{
	return this->name;
}

std::string User::getPass() const
{
	return this->password;
}

std::string User::getVote() const
{
	return this->vote;
}

void User::setName(std::string name)
{
	this->name = name;
}
void User::setPass(std::string password)
{
	this->password = password;
}

void User::setVote(std::string vote)
{
	this->vote = vote;
}

void User::ReadMyPlaylistFromFile()
{
	try
	{
		std::string line;
		std::string nameOfPlaylist;
		std::ifstream f(name + "Playlist.txt");
		while (std::getline(f, line))
		{
			std::istringstream is(line);
			is >> nameOfPlaylist;
			playlists.push_back(Playlist(nameOfPlaylist));
		}
	}
	catch (std::exception const& e)
	{
		std::cout << "There was an error" << e.what() << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out,  User aUser)
{
	out << aUser.getName() << " " << aUser.getPass()<<" "<<aUser.getVote();
	return out;
}
void User::WritePlaylistTofile(Playlist playlist)
{
	try
	{
		std::ofstream g(name + "PLaylist.txt", std::ios::app);
		g << playlist.getNameOfPLayList() << std::endl;
		g.close();
	}
	catch (std::exception const& e)
	{
		std::cout << "There was error" << e.what() << std::endl;
	}
}
void User::WritePlaylistToFileOfAllPlaylists(Playlist playlist)
{
	try
	{
		std::ofstream g("PLaylists.txt", std::ios::app);
		g << playlist.getNameOfPLayList() << std::endl;
		g.close();
	}
	catch (std::exception const& e)
	{
		std::cout << "There was error" << e.what() << std::endl;
	}
}
void User::CreateFileOfPlaylist(std::string filename)
{
	try
	{
		std::ofstream f(filename + ".txt", std::ios::app);
		f.close();
	}
	catch (std::exception const& e)
	{
		std::cout << "There was error" << e.what() << std::endl;
	}
}
bool User::createNewPLaylist(std::string nameOfPlaylist)
{
	
	Playlist newplaylist(nameOfPlaylist);
	if (!DoesPlaylistExist(newplaylist))
	{
		CreateFileOfPlaylist(nameOfPlaylist);
		playlists.push_back(newplaylist);
		WritePlaylistTofile(newplaylist);
		WritePlaylistToFileOfAllPlaylists(newplaylist);
		std::cout << "PLaylist has been created" << std::endl;
		return true;
	}
	return false;
}
void User::PrintMyPLaylists()
{
	for (Playlist& p : playlists)
	{
		std::cout << p.getNameOfPLayList() << std::endl;
	}
}



bool User::DoesPlaylistExist(Playlist newPlaylist)
{
	for (Playlist& p : playlists)
	{
		if (p.getNameOfPLayList() == newPlaylist.getNameOfPLayList())
		{
			return true;
		}
	}
	return false;
}
void User::printSongsInPlaylist(std::string& playlistName)
{
	for (Playlist& p : playlists)
	{
		if (p.getNameOfPLayList() == playlistName)
		{
			p.printSongsInPLaylist();
		}
	}
}
void User::AddSongToPlaylist(std::string nameOfPlaylist, Song& newSong)
{
	for (Playlist& p : playlists)
	{
		if (p.getNameOfPLayList() == nameOfPlaylist)
		{
			AddSongToFilePlaylist(nameOfPlaylist, newSong);
			p.add(newSong);
			return;
		}
	}
}
void User::AddSongToFilePlaylist(std::string nameOfPlaylist, Song newSong)
{
	try
	{
		std::ofstream g(nameOfPlaylist+".txt",std::ios::app);
		g << newSong;
		g.close();
	}
	catch (std::exception const& e)
	{
		std::cout << "There was an error" << e.what() << std::endl;
	}
}
void User::readSongsFromPlaylistsFile()
{
	for (Playlist& p : playlists)
	{
		try
		{
			std::string line;
			std::string songName;
			std::string singer;
			std::string janr;
			std::string album;
			int year;
			float rating;
			int votes;
			std::ifstream f(p.getNameOfPLayList() + ".txt");
			while (std::getline(f, line))
			{
				std::istringstream is(line);
				is >> songName >> singer >> janr >> album>>year>>rating>>votes;
				p.add(Song(songName, singer, janr, album, year, rating,votes));
			}
		}
		catch (std::exception const& e)
		{
			std::cout << "There was an error" << e.what() << std::endl;
		}
	}
}
bool User::DoesSongExistInPlaylist(std::string nameOfPlaylist, std::string nameOfSong)
{
	for (Playlist &p : playlists)
	{
		if (p.getNameOfPLayList() == nameOfPlaylist)
		{		
			if (p.checkSong(nameOfSong) == true)
			{
				return true;
			}
		}
	}

	std::cout << "Playlist have not been found" << std::endl;
	return false;
}
void User::readData()
{
	ReadMyPlaylistFromFile();
	readSongsFromPlaylistsFile();
}
void User::print() const
{
	std::cout << name <<std::endl;
}


