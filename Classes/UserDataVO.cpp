#include "UserDataVO.h"

UserDataVO::UserDataVO() {

}

UserDataVO::~UserDataVO() {

}

bool UserDataVO::init() {
	return true;
}

UserDataVO& UserDataVO::operator= (const UserDataVO& other)
{
	return *this;
}

UserDataVO& UserDataVO::operator= (UserDataVO&& other)
{
	return *this;
}

UserDataVO* UserDataVO::create() {
	UserDataVO* data = new UserDataVO();
	do
	{
		if (!data->init()) {
			break;
		}
		return data;
	} while (0);
	delete data;
	return nullptr;
}
