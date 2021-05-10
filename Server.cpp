#include "Server.h"
void Server::writeUserToFile(User newUser)
{
	try
	{
		std::ofstream g("Users.txt", std::ios::app);
		g << newUser<<std::endl;
		g.close();
	}
	catch (std::exception const& e)
	{
		std::cout << "There was an error" << e.what() << std::endl;
	}		
}
std::string Server::convert(std::string pass)
{
	std::vector<int> ASCIIpass;
	for (int i = 0; i < pass.length(); i++)
	{
		int x = (int)pass[i];
		ASCIIpass.push_back(x);
	}
	
	std::stringstream ss;
	for (size_t i = 0; i < ASCIIpass.size(); ++i)
	{
		ss << ASCIIpass[i];
	}
	pass = ss.str();
	
	return pass;
}
Server::Server()
{
	users.clear();
	songs.clear();
}
void Server::readSongsFromFile()
{
	try
	{
		std::string line;
		std::string nameSong;
		std::string singer;
		std::string janr;
		std::string album;
		int year;
		float rating;
		int votes;
		std::ifstream f("Songs.txt");
		while (std::getline(f, line))
		{
			std::istringstream f(line);
			f >> nameSong >>  singer>>janr>>album>>year>>rating>>votes;
			songs.push_back(Song(nameSong, singer,janr,album,year,rating,votes));
		}
	}
	catch (std::exception const& e)
	{
		std::cout << "There was an error" << e.what() << std::endl;
	}
}

void Server::addPlaylistToMainPlaylistVector(std::string nameOfPLaylist)
{
	Playlist newplaylist(nameOfPLaylist);
	AllPlaylists.push_back(newplaylist);
}

bool Server::registration(User newUser)
{
		
		if (IsThisUserFree(newUser) == true)
		{
			if (IsThisNameFree(newUser) == false&& thirdflag == false)
			{
				std::cout << "this name already exist, choose another Username" << std::endl;
				thirdflag = true;
				return false;
            }
			users.push_back(newUser);
			writeUserToFile(newUser);
			flag = true;
			return true;
		}
		else if (flag == false && secondflag == false)
		{
			std::cout << "this user already exist" << std::endl;
			secondflag = true;
			return false;
		}	
}

bool Server::login(User newUser)
{
	if (!IsThisUserFree(newUser))
	{
		return true;
	}
	else
	{
		
		std::cout << "Not registered User" << std::endl;
		return false;
	}
}

void Server::writeSongsToFile(std::string songName, std::string singer, std::string janr, std::string album, int year, float rating,int votes)
{
	Song newSong(songName, singer, janr, album, year, rating,votes);
	try
	{
		std::ofstream g("Songs.txt", std::ios::app);
		g << newSong;
		g.close();
	}
	catch (std::exception const& e)
	{
		std::cout << "There was an error" << e.what() << std::endl;
	}
}

void Server::deleteSongsInfile()
{
	try
	{
		std::fstream f;
		f.open("Songs.txt", std::ios::out | std::ios::trunc);
		f.close();
	}
	catch (std::exception const& e)
	{
		std::cout << "There was an error" << e.what() << std::endl;
	}
}

void Server::readAllPlaylists()
{
	try
	{
		std::string line;
		std::string namePLaylist;
		std::ifstream f("Playlists.txt");
		while (std::getline(f, line))
		{
			std::istringstream f(line);
			f >> namePLaylist;
			AllPlaylists.push_back(Playlist(namePLaylist));
		}
	}
	catch (std::exception const& e)
	{
		std::cout << "There was an error" << e.what() << std::endl;
	}
}



bool Server::DoesPlaylistNameExistInData(std::string playlistname)
{
	for (Playlist& p : AllPlaylists)
	{
		if (p.getNameOfPLayList() == playlistname)
		{
			std::cout << "Playlist name you have set is already used by another User, please set another name " << std::endl;
			return true;
		}
	}
	return false;
}

bool Server::IsThisNameFree(User newUser)
{
	for (User u : users)
	{
		if (u.getName() == newUser.getName())
		{
			return false;
		}
	}
	return true;
}

bool Server::IsThisUserFree(User newUser)
{
	for (User u : users)
	{
		if (u.getName() == newUser.getName() && u.getPass() == newUser.getPass())
		{
			return false;			
		}
	}	
	return true;
	
}

bool Server::IsThisSongFree(Song newSong)
{
	for (Song s : songs)
	{
		if (s.get_namesong() == newSong.get_namesong() && s.get_namesinger() == newSong.get_namesinger())
		{
           return false;
		}
	}
	return true;
}

void Server::writeVectorOfSongsToFile()
{
	try
	{
		std::ofstream g("Songs.txt", std::ios::app);
		for (int i = 0; i < songs.size(); i++)
		{
			g<<songs[i]<<std::endl;
		}
		g.close();
	}
	catch (std::exception const& e)
	{
		std::cout << "There was an error" << e.what() << std::endl;
	}
}

void Server::UpdateRatingOfSong(std::string nameOfSong,float rating, std::string UserName, std::string vote)
{
	bool flag = true;
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].getName() == UserName)
		{
			if (users[i].getVote() == "Yes")
			{
				std::cout << "You have already vote" << std::endl;
				flag = false;
				break;
			}
				
		}
	}
	                                                      
	for (int i = 0; i < songs.size(); i++)
	{
		if (flag == false)
		{
			break;
		}
		if (songs[i].get_namesong() == nameOfSong)
		{
			songs[i].updateRating(rating);
			break;
		}		
	}
}

void Server::SortSongsByRating()
{
	std::vector<Song> copySongs;
	copySongs.insert(copySongs.begin(), songs.begin(), songs.end());
	std::sort(copySongs.begin(), copySongs.end(), [](const Song& lhs, const Song& rhs)
		{
			return lhs.get_rating() > rhs.get_rating();
		});
	PrintSongsInVector(copySongs);
}

void Server::sortSongsByJanr(std::string janr)
{
	std::vector<Song> songsByJanr;
	for (int i = 0; i < songs.size(); i++)
	{
		if (songs[i].get_janr() == janr)
		{
			songsByJanr.push_back(songs[i]);
		}
	}
	PrintSongsInVector(songsByJanr);
}
void Server::PrintSongsInVector(std::vector<Song> newSongsInVector)
{
	if (!newSongsInVector.empty())
	{
		for (Song s : newSongsInVector)
		{
			s.print();
		}
	}
	else
	{
		std::cout << "There are no songs with this janr" << std::endl;
	}
}

void Server::ReadandDeleteSongsFromFile()
{
	readSongsFromFile();
	deleteSongsInfile();
}

void Server::readclientsfromFile()
{
	try
	{
		std::string line;
		std::string newName;
		std::string newPassword;
		std::string vote;
		std::ifstream f("Users.txt");
		while (std::getline(f, line))
		{
			std::istringstream is(line);
			is >> newName >> newPassword >> vote;
			users.push_back(User(newName, newPassword,vote));
		}
	}
	catch (std::exception const& e)
	{
		std::cout << "There was an error" << e.what() << std::endl;
	}
}

Song Server::DoesSongExist(std::string nameOfSong)
{
	for (Song& s : songs)
	{
		if (s.get_namesong() == nameOfSong)
		{
			return s;
		}		
	}
	std::cout << "This song does not exist" << std::endl;
}

void Server::PrintSongs()
{
	for (Song s : songs)
	{
		s.print();
	}
}

void Server::Printusers()
{
	for (User u : users)
	{
		u.print();
	}
}
