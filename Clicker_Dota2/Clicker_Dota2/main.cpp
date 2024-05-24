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
std::string boots[] = { "BOOTS OF SPEED","PHASE BOOTS","ARCANE BOOTS", "AGHANIM SHARD","OBSER WARD","BLADE MAIL","TRANQUIL BOOTS","BOOTS OF TRAVEL","HELM OF THE" };
std::string maska[] = { "WRAITH", "VLADMIR" ,"DRUM OF ENDURANCE", "BLADE MAIL" ,"OBSER WARD" ,"SENTRY WARD","HELM OF IRON" ,"MASK OF MADNESS" };
//7
//14
std::string weapons[] = { "FALCON", "HEADDRESS","OBLI", "HAND","ARML","EUL","KAYA","FORCE" };
//14
//24
std::string amulets[] = { "BRACER", "DAGON","SANGE","NULL TALISMAN","ORB OF CORROSION","PERSEVERANCE" };
//24
//35
std::string power_item_skill[] = { "HARPOON","CRYSTOLYS","ECHO SABLE","METEOR HAMMER","SHADOW BLADE","SKULL","WIT","DESLATOR","YASHAND KAYA" };
//35
void OneEterationBot(int index)
{
	if (!IsDeBug()) {
		std::cout << "dbg___________start________________" << std::endl;
	}
	//random buy item
	if (bots[index].GetMyArrayTime(bots[index].GetMyIndexQueue()) == DeltaTime())
	{
		bots[index].SetShopItem("FALCON");
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
			randomBuyTime[0] = (Random(3,60) * Random(1,6));
			randomBuyTime[1] = (Random(10, 60) * Random(6, 9));
			randomBuyTime[2] = (Random(20, 60) * Random(9, 14));
			randomBuyTime[3] = (Random(30, 60) * Random(14, 20));
			randomBuyTime[4] = (Random(40, 60) * Random(20, 24));
			//std::string* nameItems = new std::string[buy_max_item];
			////500
			//nameItems[0] = "a";
			//nameItems[1] = "b";
			//nameItems[2] = "c";
			//nameItems[3] = "v";
			//nameItems[4] = "g";
			int random_item_boots = Random(0, 9);
			int random_item_maska = Random(0, 8);
			int random_item_weapon = Random(0, 8);
			int random_item_amullet = Random(0, 5);
			int random_item_power = Random(0, 9);
			int set_index_b = random_item_boots;
			int set_index_m = random_item_maska;
			int set_index_w = random_item_weapon;
			int set_index_a = random_item_amullet;
			int set_index_p = random_item_power;
			int size_item = 5;
			std::string* iteam = new std::string[size_item]{ maska[set_index_m],boots[set_index_b],weapons[set_index_w],amulets[set_index_a],power_item_skill[set_index_p] };;
			int random_select_save = Random(0, 6);
			if (0 == random_select_save)
			{
				iteam = new std::string[size_item]{ maska[set_index_m],boots[set_index_b],weapons[set_index_w],amulets[set_index_a],power_item_skill[set_index_p] };
			}
			else if (1 == random_select_save)
			{
				iteam = new std::string[size_item]{ boots[set_index_b] ,maska[set_index_m],weapons[set_index_w],amulets[set_index_a],power_item_skill[set_index_p] };
			}
			else if (2 == random_select_save)
			{
				iteam = new std::string[size_item]{ weapons[set_index_w] ,maska[set_index_m],boots[set_index_b],amulets[set_index_a],power_item_skill[set_index_p] };
			}
			else if (3 == random_select_save)
			{
				iteam = new std::string[size_item]{ weapons[set_index_w] ,amulets[set_index_a],boots[set_index_b],maska[set_index_m],power_item_skill[set_index_p] };
			}
			else if (4 == random_select_save)
			{
				iteam = new std::string[size_item]{ weapons[set_index_w] ,maska[set_index_m],amulets[set_index_a],boots[set_index_b],power_item_skill[set_index_p] };
			}
			else if (5 == random_select_save)
			{
				iteam = new std::string[size_item]{ maska[set_index_m] , weapons[set_index_w],boots[set_index_b],amulets[set_index_a],power_item_skill[set_index_p] };
			}

		

			int sd = 0;
			
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