#pragma once
#include<iostream>
#include<sstream>
#include<Windows.h>
#include<mmsystem.h>
#include"Server.h"
class Input
{
private:
	User newUser;
	Server server;
	
	std::wstring StartSong(const std::string&);
	void Identification()const;
	void MusicMenu()const;
	void registration();
	void loginUser();
	void printSongByjanr();
	void CreateNewPlayListForUser();
	void addSongtoPLaylistForUser();
	void seeSongsInUSerPlaylist();
	void playSong();
	void BetterUpdate();
public:
	void start();
};

