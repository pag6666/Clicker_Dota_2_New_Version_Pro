#include "lib/source/include/include.h"
#include "lib/source/include/fun.h"
#include "lib/source/include/ItemBot.h"
const int buy_max_item = 5;
std::vector<Bot> bots;
std::vector<HWND> windows;
void StartAllThread() 
{
	std::thread* t1 = new std::thread(ThreadKeyBoard);
	std::thread* t2 = new std::thread(ThreadTime);
}
PointF base_light(353, 317);
PointF base_dark(394, 279);
//топ свет 348 282
//мид свет 370 301
//бот свет 395 316
// ///////////
//топ тьма 352 278
//мид тьма 374 296
//бот тьма 399 311
PointF cords_dark[] =
{
//top
PointF(352, 278),
//mid
PointF(374, 296),
//bottom
PointF(399, 311)
};
PointF cords_light[] =
{
//top
PointF(348, 282),
//mid
PointF(370, 301),
//bottom
PointF(395, 316)
};

PointF cords_lager_light[] = 
{ 
PointF(359,293), PointF(365,328),
PointF(365,313), PointF(380,328), 
PointF(374,306), PointF(390,328),
PointF(376,311), PointF(391,324),
PointF(384,309), PointF(388,317),
PointF(374,326), PointF(392,311) 
};
PointF cords_lager_dark[] =
{
PointF(384,266), PointF(356,281),
PointF(374,269), PointF(365,284),
PointF(368,267), PointF(369,278),
PointF(361,265), PointF(375,287),
PointF(358,268), PointF(379,281),
PointF(361,279), PointF(385,301)
};
/////////////////////////////////////////////////////////////
//7
//std::string items0[] = { "BOOTS OF SPEED","PHASE BOOTS","ARCANE BOOTS", "AGHANIM SHARD","OBSER WARD","BLADE MAIL","TRANQUIL BOOTS","BOOTS OF TRAVEL","HELM OF THE" };
//std::string items1[] = { "WRAITH", "VLADMIR" ,"DRUM OF ENDURANCE", "BLADE MAIL" ,"OBSER WARD" ,"SENTRY WARD","HELM OF IRON" ,"MASK OF MADNESS" };
////7
////14
//std::string items2[] = { "FALCON", "HEADDRESS","OBLI", "HAND","ARML","EUL","KAYA","FORCE" };
////14
////24
//std::string items3[] = { "BRACER", "DAGON","SANGE","NULL TALISMAN","ORB OF CORROSION","PERSEVERANCE" };
////24
////35
//std::string items4[] = { "HARPOON","CRYSTOLYS","ECHO SABLE","METEOR HAMMER","SHADOW BLADE","SKULL","WIT","DESLATOR","YASHAND KAYA" };
////35
//7
std::string items0[] = {"QUELLING BLADE","ORB OF VENOM","HEADDRESS","BUCKLER","MAGIC WAND","BRACER","NULL TALISMAN"};
std::string items1[] = {"RING OF BASILIUS","TRANQUIL BOOTS","PHASE BOOTS","BOOTS OF SPEED","POWER TREADS"};
std::string items2[] = {"FALCON BLADE","MASK OF MADNESS","MEKANSM","DRUM OF ENDURANCE","URN OF SHADOWS","SOUL RING","VOODOO MASK","MORBID MASK","JAVELIN","BLITZ KNUCKLES","HELM OF IRON WILL"};
std::string items3[] = { "WITCH BLADE","BLADE MAIL","VLADMIR OFFERING","DRAGON LANCE","FORCE STAFF","VEIL OF DISCORD","CRYSTALYS","ECHO SABRE","SANGE","YASHA","KAYA","DIFFUSAL BLADE","MAELSTROM","GLIMMER CAPE","ARMLET OF MORDIGGIAN" };
std::string items4[] = { "DESOLATOR", "KAYA AND SANGE", "SANGE AND YASHA", "YASHA AND KAYA", "SHADOW BLADE", "MAGE SLAYER", "METEOR HAMMER", "EULS SCEPTER" };

void OneEterationBot(int index)
{
	Sleep(150);
	if (!IsDeBug()) {
		std::cout << "dbg___________start_________index windwos = "<< index + 1 <<"_______" << std::endl;
	}
	//random buy item
	//22 > 30
	if (DeltaTime() > bots[index].GetMyArrayTime(bots[index].GetMyIndexQueue()))
	{
		
		if (bots[index].GetMyIndexQueue() < buy_max_item) {
			bots[index].SetShopItem(bots[index].GetNameItemOfIndex(bots[index].GetMyIndexQueue()));
			bots[index].SetMyIndexQueue((bots[index].GetMyIndexQueue() + 1));
		}
		if (!IsDeBug()) {
			std::cout << "Sucess Shop Item" << std::endl;
		}
	}
	
	if (!IsDeBug()) {
		std::cout << "Now time = " << DeltaTime() << "s" << std::endl;
		
		for (int i = 0; i < buy_max_item; i++) 
		{
			std::cout << "time"<<i<<" = " << bots[index].GetMyArrayTime(i) << std::endl;
		}
	}
		
	int randomTimeFarm = (Random(45, 59) * 13);
	if (!IsDeBug()) 
	{
		std::cout << "random farm time = " << randomTimeFarm << std::endl;
		std::cout << "farm state = " << bots[index].IsFarm() << std::endl;
	}

	//farm


	if (nineMinutsTimer() >= randomTimeFarm && !bots[index].IsFarm())
	{
		if (bots[index].GetSf() == 0) {
			bots[index].SetIsFarm(true);
			if (bots[index].GetMySide() == SideBot::dark)
			{
				bots[index].SetSavePointFarm(cords_lager_dark[Random(0, 12)]);
			}
			else if (bots[index].GetMySide() == SideBot::light)
			{
				bots[index].SetSavePointFarm(cords_lager_light[Random(0, 12)]);
			}
			bots[index].SetSf(5);
		}
		
	}
	if (bots[index].GetSf() == 5 && bots[index].IsFarm())
	{
		bots[index].SetCord(bots[index].GetSavePointFarm());
		if (FarmTime() >= Random(24, 27))
		{
			bots[index].SetSf(6);
			if (bots[index].GetMySide() == SideBot::dark)
			{
				bots[index].SetSavePointFarm(cords_lager_dark[Random(0, 12)]);
			}
			else if (bots[index].GetMySide() == SideBot::light)
			{
				bots[index].SetSavePointFarm(cords_lager_light[Random(0, 12)]);
			}
		}
	}
	if (bots[index].GetSf() == 6 && bots[index].IsFarm())
	{
		if (FarmTime() >= Random(24, 27))
		{
			bots[index].SetSf(0);
		}
		bots[index].SetIsFarm(false);
	}

	/*if (bots[index].IsFarm())
	{
		bots[index].SetCord(bots[index].GetSavePointFarm());
		if (FarmTime() >= Random(24, 27))
		{
			
			
		}

	}*/

	//end farm
	
	if (TwoMinutsTimer() >= (60)*Random(0,3))
	{
		KeyDown(VK_CONTROL);
		int random_up = Random(0, 4);
		if (random_up == 0) {
			InputKey('Q');
		}
		else if (random_up == 1) {
			InputKey('W');
		}
		else if (random_up == 2) {
			InputKey('E');
		}
		else if (random_up == 3)
		{
			InputKey('R');
		}
		KeyUp(VK_CONTROL);
		for (int i = 0; i < 2; i++) {
			int random_down = Random(0, 4);
			if (random_down == 0) {
				InputKey('Q');
			}
			else if (random_down == 1) {
				InputKey('W');
			}
			else if (random_down == 2) {
				InputKey('E');
			}
			else if (random_down == 3)
			{
				InputKey('R');
			}
		}
	}
	if ((TwoMinutsTimer()/2) >= (30) * Random(0, 2))
	{
		int random = Random(0, 2);
		if (random == 0) {
			InputKey('Z');
			InputKey('X');
			InputKey('C');
		}
		else {
			InputKey('V');
			InputKey('B');
			InputKey('N');
		}
	}
	//press 9 dk or press 8 lt
	if (bots[index].GetMySide() == SideBot::dark)
	{
		if (GetRashenSpawnLight()) 
		{
			// spawn light cord
			bots[index].SetCord(base_light);
			print("dark rashen light");
		}
	}
	else if (bots[index].GetMySide() == SideBot::light)
	{
		if (GetRashenSpawnDark()) 
		{
			// spawn dark cord;
			bots[index].SetCord(base_dark);
			print("light rashen dark");
		}
	}

	bots[index].LoopOnCircle(index);
	PrintCords(bots[index].GetPoint());
	std::cout << "my side = " << bots[index].GetMySide() << std::endl;
	//clear or set defult parametors
	if (!bots[index].IsFarm()) {
		bots[index].DefultCord();
	}
	if (!IsDeBug()) {
		std::cout << "dbg___________end________________" << std::endl;
	}
}
////////////////////////////////////////////////////////////////////
int main() 
{
	srand(time(0));
	SerchWindwos(windows);
	if (windows.size() > 0) 
	{
		SideBot side = SideBot::null;
		int getInputUserSide = 0;
		bool setUpWindwos = false;
		while (1)
		{
			std::cout << "how many found windwos = " << windows.size() << std::endl;
			print("Input 6 for Dark or Input 7 for Light or Input -1 for defult windows.(size/2)");
			std::cin >> getInputUserSide;
			if (getInputUserSide == -1)
			{
				side = SideBot::null;
				setUpWindwos = true;
			}
			else if (getInputUserSide == 7)
			{
				side = SideBot::light;
				setUpWindwos = true;
			}
			else if (getInputUserSide == 6)
			{
				side = SideBot::dark;
				setUpWindwos = true;
			}
			if (setUpWindwos)
			{
				break;
			}
		}
		int howManyWindwosSelectFirst = 0;
		if (side != SideBot::null) {
			while (1)
			{
				print("how many windwos for this is side ?");
				std::cin >> howManyWindwosSelectFirst;
				if (howManyWindwosSelectFirst <= windows.size())
				{
					break;
				}
			}
		}
		int formulaSelectSide = 0;
		if (side == SideBot::null) 
		{
			formulaSelectSide = (windows.size() / 2);
		}
		else if (side == SideBot::dark) 
		{
			formulaSelectSide = howManyWindwosSelectFirst;
		}
		else if (side == SideBot::light) 
		{
			formulaSelectSide = howManyWindwosSelectFirst;
		}
		for (int i = 0; i < windows.size(); i++)
		{		
			int* randomBuyTime = new int [buy_max_item];
			randomBuyTime[0] = (Random(3, 28) * Random(1, 1));
			randomBuyTime[1] = (Random(45, 60) * Random(7, 9));
			randomBuyTime[2] = (Random(43, 60) * Random(14, 16));
			randomBuyTime[3] = (Random(56, 60) * Random(25, 27));
			randomBuyTime[4] = (Random(23, 60) * Random(34, 36));
			randomBuyTime[5] = (Random(35, 60) * Random(40, 42));
			//std::string* nameItems = new std::string[buy_max_item];
			////500
			//nameItems[0] = "a";
			//nameItems[1] = "b";
			//nameItems[2] = "c";
			//nameItems[3] = "v";
			//nameItems[4] = "g";
			int random_item_time0 = Random(0, (sizeof(items0) / sizeof(std::string)));
			int random_item_time1 = Random(0, (sizeof(items1) / sizeof(std::string)));
			int random_item_time2 = Random(0, (sizeof(items2) / sizeof(std::string)));
			int random_item_time3 = Random(0, (sizeof(items3) / sizeof(std::string)));
			int random_item_time4 = Random(0, (sizeof(items4) / sizeof(std::string)));
			
			//std::cout << "random select item windwos = " << i <<" ri0 = "<<random_item_time0<< std::endl;
			int set_index_0 = random_item_time0;
			int set_index_1 = random_item_time1;
			int set_index_2 = random_item_time2;
			int set_index_3 = random_item_time3;
			int set_index_4 = random_item_time4;
			std::string* iteam = new std::string[buy_max_item]{
				items0[set_index_0],
				items1[set_index_1],
				items2[set_index_2],
				items3[set_index_3],
				items4[set_index_4],
			};
				
				
				if (side == SideBot::dark) {
					if (i < formulaSelectSide)
					{
						int selected = 0;
						bool sucessSelect = false;
						statePoint defultPoint = statePoint::null_st;
						//dark
						while (1)
						{
							print("|DARK|Input 0 for top| Input 1 for midd| Input 2 for bottom");
							std::cin >> selected;
							if (selected == statePoint::top)
							{
								defultPoint = statePoint::top;
								sucessSelect = true;
							}
							else if (selected == statePoint::midd)
							{
								defultPoint = statePoint::midd;
								sucessSelect = true;
							}
							else if (selected == statePoint::bottom)
							{
								defultPoint = statePoint::bottom;
								sucessSelect = true;
							}
							if (sucessSelect == true)
							{
								break;
							}
						}
						bots.push_back(Bot(cords_dark[defultPoint], windows[i], SideBot::dark, randomBuyTime, iteam));
					}
					else if (i >= formulaSelectSide)
					{
						//light
						int selected = 0;
						bool sucessSelect = false;
						statePoint defultPoint = statePoint::null_st;
						//light
						while (1)
						{
							print("|Light|Input 0 for top| Input 1 for midd| Input 2 for bottom");
							std::cin >> selected;
							if (selected == statePoint::top)
							{
								defultPoint = statePoint::top;
								sucessSelect = true;
							}
							else if (selected == statePoint::midd)
							{
								defultPoint = statePoint::midd;
								sucessSelect = true;
							}
							else if (selected == statePoint::bottom)
							{
								defultPoint = statePoint::bottom;
								sucessSelect = true;
							}
							if (sucessSelect == true)
							{
								break;
							}
						}
						bots.push_back(Bot(cords_light[defultPoint], windows[i], SideBot::light, randomBuyTime, iteam));
					}
				}
				else if (side == SideBot::light)
				{
					if (i < formulaSelectSide) {

						int selected = 0;
						bool sucessSelect = false;
						statePoint defultPoint = statePoint::null_st;
						//light
						while (1)
						{
							print("|Light|Input 0 for top| Input 1 for midd| Input 2 for bottom");
							std::cin >> selected;
							if (selected == statePoint::top)
							{
								defultPoint = statePoint::top;
								sucessSelect = true;
							}
							else if (selected == statePoint::midd)
							{
								defultPoint = statePoint::midd;
								sucessSelect = true;
							}
							else if (selected == statePoint::bottom)
							{
								defultPoint = statePoint::bottom;
								sucessSelect = true;
							}
							if (sucessSelect == true)
							{
								break;
							}
						}
						bots.push_back(Bot(cords_light[defultPoint], windows[i], SideBot::light, randomBuyTime, iteam));
					}
					else if (i >= formulaSelectSide)
					{
						int selected = 0;
						bool sucessSelect = false;
						statePoint defultPoint = statePoint::null_st;
						//dark
						while (1)
						{
							print("|DARK|Input 0 for top| Input 1 for midd| Input 2 for bottom");
							std::cin >> selected;
							if (selected == statePoint::top)
							{
								defultPoint = statePoint::top;
								sucessSelect = true;
							}
							else if (selected == statePoint::midd)
							{
								defultPoint = statePoint::midd;
								sucessSelect = true;
							}
							else if (selected == statePoint::bottom)
							{
								defultPoint = statePoint::bottom;
								sucessSelect = true;
							}
							if (sucessSelect == true)
							{
								break;
							}
						}
						bots.push_back(Bot(cords_dark[defultPoint], windows[i], SideBot::dark, randomBuyTime, iteam));
					}
				}
			
			
		}
		StartAllThread();
		std::cout << " CloseWindows = " << !CloseWindows() << std::endl;
		std::cout << " GetPause = " << !GetPause() << std::endl;
		while (!CloseWindows())
		{
			if (!GetPause()) {
				if (bots.size() > 0) {
					for (int i = 0; i < bots.size(); i++)
					{
						if (!GetPause()) {
							OneEterationBot(i);
						}
						else 
						{
							Sleep(500);
						}
					}
				}
			}
			else
			{
				Sleep(500);
			}
		}
	}
	else 
	{
		
		MessageBoxA(NULL,"бро где dota 2 ?","ошибка окна", MB_ICONWARNING);
	}
	std::cout << "Clicker closed" << std::endl;
	return 0;
}