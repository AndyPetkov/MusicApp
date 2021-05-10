#include "Input.h"


std::wstring Input::StartSong(const std::string& songName)
{
	int len;
	int slength = (int)songName.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, songName.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, songName.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void Input::Identification() const
{
	std::cout << "*************Welcome to the Music player*************" << std::endl;
	std::cout << "1.Login"<<std::endl;
	std::cout << "2.Registration"<<std::endl;	
	
}

void Input::MusicMenu() const
{
	std::cout << "*************Music player menu*************" << std::endl;
	std::cout << "1.See all songs " << std::endl;
	std::cout << "2.See songs by rating " << std::endl;
	std::cout << "3.See all songs with this janr " << std::endl;
	std::cout << "4.Create new playlist " << std::endl;
	std::cout << "5.See my playlist " << std::endl;
	std::cout << "6.Add new song to playlist " << std::endl;
	std::cout << "7.See my songs in playlist " << std::endl;
	std::cout << "8.Play Song " << std::endl;
	std::cout << "9.Clear screen " << std::endl;
	std::cout << "10.Rate a song " << std::endl;
	std::cout << "11.Exit " << std::endl;
}

void Input::registration()
{
	do
	{
		std::cout << "Enter your name" << std::endl;
		std::string name;
		std::cin >> name;
		std::cout  << "Enter your password" << std::endl;
		std::string password;
		std::cin >> password;
		std::string vote = "No";
		std::string Convertedpassword=server.convert(password);
		newUser.setName(name);		
		newUser.setPass(Convertedpassword);
		newUser.setVote(vote);
		server.registration(newUser);
	} while (server.registration(newUser) == true);
}

void Input::loginUser()
{
	do
	{
		std::cout << "Enter your name" << std::endl;
		std::string name;
		std::cin >> name;
		std::cout << "Enter your password" << std::endl;
		std::string password;
		std::cin >> password;
		std::string Convertedpassword = server.convert(password);
		newUser.setName(name);
		newUser.setPass(Convertedpassword);
	} while (server.login(newUser) == false);
}

void Input::printSongByjanr()
{
	std::string janr;
	std::cout << "Type your janr here: ";
	std::cin >> janr;
	server.sortSongsByJanr(janr);
}
void Input::CreateNewPlayListForUser()
{
	std::string nameNewPlaylist;
	std::cout << "Enter the name of your new playlist ";
	std::cin >> nameNewPlaylist;
	if (server.DoesPlaylistNameExistInData(nameNewPlaylist) == false)
	{
         newUser.createNewPLaylist(nameNewPlaylist);	
		// server.addPlaylistToMainPlaylistVector(nameNewPlaylist);
    }
}
void Input::addSongtoPLaylistForUser()
{
	std::string nameOfSong;
	std::string nameOfPlaylist;
	std::cout << "Name of new song ";
	std::cin >> nameOfSong;
	std::cout<<std::endl;
	std::cout << "Playlist name ";
	std::cin >> nameOfPlaylist;
	Song s = server.DoesSongExist(nameOfSong);
	newUser.AddSongToPlaylist(nameOfPlaylist, s);
}
void Input::seeSongsInUSerPlaylist()
{
	std::string nameOfPlaylist;
	std::cout << "Playlist name ";
	std::cin >> nameOfPlaylist;
	if (newUser.DoesPlaylistExist(nameOfPlaylist))
	{
		newUser.printSongsInPlaylist(nameOfPlaylist);
	}
	else
	{
		std::cout << "This playlist does not exist" << std::endl;
	}
}
void Input::playSong()
{
	std::string nameOfPlaylist;
	std::cout << "Name of playlist" << std::endl;
	std::cin >> nameOfPlaylist;
	std::cout << std::endl;
	std::string nameOfSong;
	std::cout << "Name of song" << std::endl;
	std::cin >> nameOfSong;
	if (newUser.DoesSongExistInPlaylist(nameOfPlaylist, nameOfSong)==true)
	{
		//server.UpdateRatingOfSong(nameOfSong);
		std::wstring stemp = StartSong(nameOfSong);
		LPCWSTR result = stemp.c_str();
		PlaySound((result), NULL, SND_FILENAME);
    }
}
void Input::BetterUpdate()
{
	std::cout << "Name of song: " << std::endl;
	std::string nameofsong;
	std::cin >> nameofsong;
	std::cout << "Your rating for the song " << std::endl;
	float ratingNum;
	std::cin >> ratingNum;
	std::string name = newUser.getName();
	std::string vote = newUser.getVote();
	server.UpdateRatingOfSong(nameofsong, ratingNum,name,vote);
}
void Input::start()
{
	Identification();
	server.readclientsfromFile();
	int IdentificationChoice;	
	bool isValidated = false;
	do
	{
		std::cout << "Input yor choice: ";
		std::cin >> IdentificationChoice;
		if (IdentificationChoice == 1 || IdentificationChoice == 2)
		{
			isValidated = true;
		}

		else
		{
			std::cout << "Wrong input, try again" << std::endl;
		}
	} while (isValidated!=true);
		switch (IdentificationChoice)
		{
		case 1: 
		{
			loginUser();
			break;
		}
		case 2:
		{
			registration();
			break;
		}
		}

		MusicMenu();
		server.ReadandDeleteSongsFromFile();
		server.readAllPlaylists();
		newUser.readData();
		int UserChoice;
		do
		{
			std::cout << "Enter your choice: ";
			std::cin >> UserChoice;
			switch (UserChoice)
			{
			case 1:{
				server.PrintSongs();
				break;
			}
			case 2: {
				server.SortSongsByRating();
				break;
			}
			case 3: {
				printSongByjanr();
				break;
			}
			case 4: {
				CreateNewPlayListForUser();
				break;
			}
			case 5: {
				newUser.PrintMyPLaylists();
				break;
			}
			case 6: {
				addSongtoPLaylistForUser();
				break;
			}
			case 7: {
				seeSongsInUSerPlaylist();
				break;
			}
			case 8: {
				playSong();
				break;
			}
			case 9: {
				system("cls");
				MusicMenu();
				break;
			}
			case 10:
			{
				BetterUpdate();
				break;
			}
			}
		} while (UserChoice !=11);
		server.writeVectorOfSongsToFile();
}