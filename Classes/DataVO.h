#pragma once

class DataVO 
{
public:
	DataVO() {
		m_pValue = 100;
	}
	~DataVO();
	void showValue();

	void setValue(int i);
private:
	int m_pValue;
};