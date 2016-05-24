#pragma once

class UserDataVO {
public:
	UserDataVO();
	~UserDataVO();
	bool init();
	static UserDataVO* create();

	/**
	* Overroads of operator=.
	*/
	UserDataVO& operator= (const UserDataVO& other);

	/**
	* Overroads of operator=.
	*/
	UserDataVO& operator= (UserDataVO&& other);
};