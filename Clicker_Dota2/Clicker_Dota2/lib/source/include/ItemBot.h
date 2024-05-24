#pragma once
#include "include.h"
#include "fun.h"
class Bot
{
private:
	int timerStraf = 0;
	bool straf = false;
	bool is_farm = false;
	int _myIndexSucessBuyItem = 0;
	int* _myArrayTimeBuy;
	SideBot _mySide;
	PointF _tempPointFarm;
	PointF _point;
	PointF _temp;
	HWND _myWindows;
	std::string _itemShop;
	std::string* _nameItems;
	void Start()
	{

	}
	void Stop()
	{

	}
public:
	Bot(PointF point, HWND hwnd, SideBot side, int * arrayTimeBuy, std::string* nameItems)
	{
		this->_nameItems = nameItems;
		this->_myArrayTimeBuy = arrayTimeBuy;
		this->_mySide = side;
		this->_myWindows = hwnd;
		this->_point = point;
		this->_temp = point;
		Start();
	}
	bool IsFarm() 
	{
		return is_farm;
	}
	void SetTimerStraf(int timer) { timerStraf = timer; }
	int GetTimerStraf() { return timerStraf; }
	bool GetSf() { return straf; }
	void SetSf(bool farmSd) { straf = farmSd; }
	void SetIsFarm(bool farmState)
	{
		is_farm = farmState;
	}
	PointF GetSavePointFarm() 
	{
		return _tempPointFarm;
	}
	void SetSavePointFarm(PointF point) 
	{
		_tempPointFarm = point;
	}
	std::string GetNameItemOfIndex(int index)
	{
		return _nameItems[index];
	}
	int GetMyArrayTime(int index) 
	{	
			return _myArrayTimeBuy[index];
	}
	int GetMyIndexQueue() 
	{
		return _myIndexSucessBuyItem;
	}
	void SetMyIndexQueue(int index) 
	{
		this->_myIndexSucessBuyItem = index;
	}
	HWND GetMyWindows() 
	{
		return _myWindows; 
	}
	void SetCord(PointF point) 
	{
		_point = point; 
	}
	void DefultCord() 
	{ 
		this->_point = _temp; 
	}
	void SetShopItem(std::string nameItem) 
	{ 
		this->_itemShop = nameItem; 
	}
	void ClearShopItem() 
	{ 
		this->_itemShop = "null"; 
	}
	SideBot GetMySide() 
	{ 
		return _mySide; 
	}
	void LoopOnCircle(int index)
	{
		MoveTargetPersonal(_point, _myWindows);

		if (_itemShop != "null")
		{
			ShopItem(_itemShop);
			ClearShopItem();
		}
	}
	PointF GetPoint() { return _point; }
	~Bot() 
	{
		Stop();
	}
};