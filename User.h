#pragma once
#include <ostream>
#include<fstream>
#include <string>
#include <sstream>
#include <vector>
#include "PlayList.h"

class User {

public:
	User();
	User(std::string,std::string,std::string);

	std::string getName()const;
	std::string getPass()const;
	std::string getVote()const;

	void setName(std::string name);
	void setPass(std::string password);
	void setVote(std::string vote);

	void ReadMyPlaylistFromFile();
	void WritePlaylistTofile(Playlist);
	void WritePlaylistToFileOfAllPlaylists(Playlist);
	void CreateFileOfPlaylist(std::string);
	bool createNewPLaylist(std::string);
	void PrintMyPLaylists();
	

	bool DoesPlaylistExist(Playlist);
	void printSongsInPlaylist(std::string&);
	void AddSongToPlaylist(std::string, Song&);
	void AddSongToFilePlaylist(std::string, Song);
	void readSongsFromPlaylistsFile();
	bool DoesSongExistInPlaylist(std::string, std::string);
	void readData();
	void print()const;
	
	friend std::ostream& operator<<(std::ostream& out, User aUser);
    
private:

	std::string name;
	std::string password;
	std::string vote;
	std::vector<Playlist> playlists;
};


