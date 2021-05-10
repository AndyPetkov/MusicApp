#include<iostream>
#include<string>
#include <sstream>
#include<fstream>
#pragma once

class Song
{
private:
	std::string nameSong;
	std::string nameSinger;
	std::string janr;
	std::string album;
	int year;
	float rating;
	int votes;
public:
	Song(std::string, std::string, std::string, std::string, int,float,int);

	std::string get_namesong()const;
	std::string get_namesinger()const;
	std::string get_album()const;
	std::string get_janr()const;
	int get_year()const;
	float get_rating()const;
	int get_votes()const;
	void updateVotes();
	void updateRating(float);
	
	friend std::ostream& operator <<(std::ostream& os,  Song s);
	void print()const;
};
