#include<iostream>
#include<vector>
#include<algorithm>   
#include"User.h"
#pragma once
class Server
{
private:
	std::vector<User> users;
	std::vector<Song> songs;
	std::vector<Playlist> AllPlaylists;

	bool flag = false;
	bool secondflag = false;
	bool thirdflag = false;
	bool fourthflag = false;
	void writeUserToFile(User newUser);
public:
	
	Server();

	std::string convert(std::string);

	void readSongsFromFile();

	void addPlaylistToMainPlaylistVector(std::string);
	bool registration(User);
	bool login(User);
	void writeSongsToFile(std::string, std::string, std::string, std::string, int, float,int );
	void deleteSongsInfile();
	void readAllPlaylists();
	
	bool DoesPlaylistNameExistInData(std::string);
	bool IsThisNameFree(User newUser);
	bool IsThisUserFree(User newUser);
	bool IsThisSongFree(Song newSong);

	void writeVectorOfSongsToFile();
	void UpdateRatingOfSong(std::string,float, std::string, std::string);
	void SortSongsByRating();
	void sortSongsByJanr(std::string);
	void ReadandDeleteSongsFromFile();
	void readclientsfromFile();

	Song DoesSongExist(std::string);
	void PrintSongs();
	void Printusers();
	void PrintSongsInVector(std::vector<Song>);
	
};

