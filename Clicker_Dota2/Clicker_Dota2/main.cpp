#include "lib/source/include/include.h"
#include "lib/source/include/fun.h"
#include "lib/source/include/ItemBot.h"
const int buy_max_item = 6;
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

PointF cords_lager_dark[] = 
{ 
PointF(378,281), PointF(375,287),
PointF(369,277), PointF(364,284), 
PointF(361,279), PointF(356,285),
PointF(360,284), PointF(357,269),
PointF(368,266), PointF(375,268),
PointF(384,266), PointF(386,302) 
};
PointF cords_lager_light[] =
{
PointF(366,313), PointF(365,328),
PointF(374,305), PointF(373,326),
PointF(376,311), PointF(381,326),
PointF(385,309), PointF(389,328),
PointF(392,311), PointF(392,325),
PointF(388,317), PointF(359,293)
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
std::string items0[] = {"OBSERVER WARD","CLARITY","ENCHANTED MANGO","MAGIC WAND","RING OF BASILIUS"};
std::string items1[] = {"SENTRY WARD", "NULL TALISMAN","SENTRY WARD","BOOTS OF SPEED", "WRAITH BAND","BRACER","HEADD RESS"};
std::string items2[] = {"SOUL RING","ORB OF CORROSION","BOTTLE","UM OF SHADOWS","BOOTS OF SPEED" };
std::string items3[] = {"FALCON BLADE","ARCANE BOOTS","PERSEVERANCE","AGHANIM SHARD","PAVISE","POWER TREADS","PHASE BOOTS","DRUM OF ENDURANCE","PHASE BOOTS"};
std::string items4[] = {"OBLIVION STAFF","AGHANIM SHARD","VEIL OF DISCORD","MASK OF MADNESS","DRAGON LANCE"};
std::string items5[] = {"CRYSTALYS","SANGE","YASHA","KAYA","BOOTS OF TRAVEL","HELM OF THE DOMINATOR","SKULL BASHER","SHADOW BLADE","DESOLATOR","KAYA AND SANGE","SANGE AND YASHA","YASHA AND KAYA"};
void OneEterationBot(int index)
{
	
	if (!IsDeBug()) {
		std::cout << "dbg___________start_________index windwos = "<<index<<"_______" << std::endl;
	}
	//random buy item
	if (bots[index].GetMyArrayTime(bots[index].GetMyIndexQueue()) == DeltaTime())
	{
		bots[index].SetShopItem(bots[index].GetNameItemOfIndex(bots[index].GetMyIndexQueue()));
		if (bots[index].GetMyIndexQueue() < buy_max_item) {
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
		
	int randomTimeFarm = (Random(45, 60) * Random(1, 3));
	if (!IsDeBug()) 
	{
		std::cout << "random farm time = " << randomTimeFarm << std::endl;
		std::cout << "farm state = " << bots[index].IsFarm() << std::endl;
	}

	//farm
	if (TwoMinutsTimer() >= randomTimeFarm && !bots[index].IsFarm())
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
		}
		else 
		{
			if (FarmTime() > bots[index].GetSf());
			{
				bots[index].SetSf(0);
			}
		}
	}
	if (bots[index].IsFarm())
	{
		bots[index].SetCord(bots[index].GetSavePointFarm());
		if (FarmTime() >= Random(14, 17))
		{
			bots[index].SetIsFarm(false);
			bots[index].SetSf(Random(12, 14));
		}
		
	}
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
			randomBuyTime[0] = (Random(1,50) * Random(1,5));
			randomBuyTime[1] = (Random(20, 60) * Random(5, 11));
			randomBuyTime[2] = (Random(40, 60) * Random(11, 16));
			randomBuyTime[3] = (Random(50, 60) * Random(16, 25));
			randomBuyTime[4] = (Random(45, 60) * Random(25, 29));
			randomBuyTime[5] = (Random(50, 60) * Random(30, 36));
			//std::string* nameItems = new std::string[buy_max_item];
			////500
			//nameItems[0] = "a";
			//nameItems[1] = "b";
			//nameItems[2] = "c";
			//nameItems[3] = "v";
			//nameItems[4] = "g";
			
			int random_item_time0	=	Random(0, (sizeof(items0) / sizeof(std::string)));
			int random_item_time1	=	Random(0, (sizeof(items1) / sizeof(std::string)));
			int random_item_time2	=	Random(0, (sizeof(items2) / sizeof(std::string)));
			int random_item_time3	=	Random(0, (sizeof(items3) / sizeof(std::string)));
			int random_item_time4	=	Random(0, (sizeof(items4) / sizeof(std::string)));
			int random_item_time5	=	Random(0, (sizeof(items5) / sizeof(std::string)));
			int set_index_0 = random_item_time0;
			int set_index_1 = random_item_time1;
			int set_index_2 = random_item_time2;
			int set_index_3 = random_item_time3;
			int set_index_4 = random_item_time4;
			int set_index_5 = random_item_time5;
			std::string* iteam = new std::string[buy_max_item]{ 
				items0[set_index_0],
				items1[set_index_1],
				items2[set_index_2],
				items3[set_index_3],
				items4[set_index_4],
				items5[set_index_5]};
				
				
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
					}
				}
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