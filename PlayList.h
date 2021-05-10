#pragma once
#include<fstream>
#include<iostream>
#include <string>
#include<vector>
#include <sstream>
#include"Song.h"
class Playlist
{
public:
	Playlist(std::string);
	void add(Song);
	
	std::string getNameOfPLayList()const;
	void printSongsInPLaylist()const;
	bool checkSong(std::string);
private:
	std::string name;
	std::vector<Song> collection;
 
};