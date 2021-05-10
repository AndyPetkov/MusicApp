#include "Song.h"
using namespace std;
Song::Song(std::string nameOfSong, std::string nameOfSinger, std::string nameofJanr, std::string namealbum, int nameofyear,float numberofrating,int NumberOfVotes)
{
	nameSong = nameOfSong;
	nameSinger = nameOfSinger;
	janr = nameofJanr;
	album = namealbum;
	year = nameofyear;
	rating = numberofrating;
	votes = NumberOfVotes;
}

std::string Song::get_namesong()const
{
	return nameSong;
}

std::string Song::get_namesinger()const
{
	return nameSinger;
}

std::string Song::get_album() const
{
	return album;
}

std::string Song::get_janr()const
{
	return janr;
}

int Song::get_year()const
{
	return year;
}

float Song::get_rating()const
{
	return rating;
}
int Song::get_votes()const
{
	return votes;
}
void Song::updateVotes()
{
	++votes;
}
void Song::updateRating(float ratingOfUser)
{
	updateVotes();
	rating=(rating*votes+ratingOfUser)/(votes+1);
}

void Song::print()const
{
	std::cout << nameSong << " " << nameSinger << " " << janr << " " << album << " " << year << " " << rating << " " << votes<< std::endl;
}

ostream& operator<<(std::ostream& os,  Song s)
{
	os << s.get_namesong() << " " << s.get_namesinger() << " " << s.get_janr() << " " <<s.get_album()<< " " << s.get_year() << " " << s.get_rating()<<" "<<s.get_votes();
	return os;
}
