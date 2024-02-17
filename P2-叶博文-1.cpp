#include <iostream>
#include<vector>
#include <string>
#include<map>

using namespace std;

void action(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act);

//判断我方死亡宠物数量并且返回这个数量值
int my_dead(vector<int> vec_hp, vector<int> my_ch)
{
    int a = 0;
    if(vec_hp[my_ch[0] - 1] <= 0)
    {
        a += 1;
    }
    if(vec_hp[my_ch[1] - 1] <= 0)
    {
        a += 1;
    }
    if(vec_hp[my_ch[2] - 1] <= 0)
    {
        a += 1;
    }
    return a;
}

//检查敌方死亡情况
void ene_beaten(ostream& os, int& enemy_cho, vector<int> vec_hp)
{
    if(enemy_cho == 1 && vec_hp[5] <= 0)
    {
        os << "Enemy's D is beaten" << endl;
    }
    if(enemy_cho == 2 && vec_hp[6] <= 0)
    {
        os << "Enemy's W is beaten" << endl;
    }
    if(enemy_cho == 3 && vec_hp[7] <= 0)
    {
        os << "Enemy's L is beaten" << endl;
    }
}

//检查我方死亡
void ene_beaten(ostream& os, int& my_cho, vector<int> vec_hp, map<int, string> me, vector<int>& my_ch)
{
    if(my_cho == 1 && vec_hp[my_ch[0] - 1] <= 0)
    {
        os << "Your" <<  me[my_ch[0]] << "is beaten" << endl;
    }
    if(my_cho == 2 && vec_hp[my_ch[1] - 1] <= 0)
    {
        os << "Your" <<  me[my_ch[1]] << "is beaten" << endl;
    }
    if(my_cho == 3 && vec_hp[my_ch[2] - 1] <= 0)
    {
        os << "Your" <<  me[my_ch[2]] << "is beaten" << endl;
    }
}

//敌方死亡后改变宠物（唯一情况）
void enemy_change(int& enemy_cho, vector<int> vec_hp, ostream& os)
{
    if(enemy_cho == 1)
    {
        os << "Enemy's D is beaten" << endl;
    }
    else if(enemy_cho == 2)
    {
        os << "Enemy's W is beaten" << endl;
    }
    else if(enemy_cho == 3)
    {
        os << "Enemy's L is beaten" << endl;
    }
    if(vec_hp[5] <= 0 && vec_hp[6] >= 55)
    {
        os << "Enemy sends W" << endl;
        enemy_cho = 2;
    }
    else if(vec_hp[6] < 55 && vec_hp[7] > 0)
    {
        os << "Enemy sends L" << endl;
        enemy_cho = 3;
    }
    else if(vec_hp[7] <= 0 && vec_hp[6] > 0)
    {
        os << "Enemy sends W" << endl;
        enemy_cho = 2;
    }
}

//我方选择宠物(死亡后）
void my_change(istream& is, ostream& os, int& my_cho, vector<int> vec_hp, map<int, string> me, vector<int>& my_ch)
{
    my_cho = 0;
    os << "Your " << me[my_ch[my_cho - 1]] << " is beaten" << endl;
    if(vec_hp[my_ch[0] - 1] > 0 && vec_hp[my_ch[1] - 1] > 0)
    {
        os << "Select your next pet (1 for "<< me[my_ch[0]] << " -HP" << vec_hp[my_ch[0] - 1] << ", 2 for " << me[my_ch[1]] << " -HP" << vec_hp[my_ch[1] - 1] << "):";
        while(my_cho != 1 && my_cho != 2)
        {
            os << "Select your next pet (1 for " << me[my_ch[0]] << " -HP" << vec_hp[my_ch[0] - 1] << ", 2 for " << me[my_ch[1]] << " -HP" << vec_hp[my_ch[1] - 1] << "):";
            is >> my_cho;
        }
    }
    else if(vec_hp[my_ch[0] - 1] > 0 && vec_hp[my_ch[2] - 1] > 0)
    {
        os << "Select your next pet (1 for " << me[my_ch[0]] << " -HP" << vec_hp[my_ch[0] - 1] << ", 3 for " << me[my_ch[2]] << " -HP" << vec_hp[my_ch[2] - 1] << "):";
        while(my_cho != 1 && my_cho != 2)
        {
            os << "Select your next pet (1 for " << me[my_ch[0]] << " -HP" << vec_hp[my_ch[0] - 1] << ", 3 for " << me[my_ch[2]] << " -HP" << vec_hp[my_ch[2] - 1] << "):";
            is >> my_cho;
        }
    }
    else if(vec_hp[my_ch[2] - 1] > 0 && vec_hp[my_ch[1] - 1] > 0)
    {
        os << "Select your next pet (2 for " << me[my_ch[1]] << " -HP" << vec_hp[my_ch[1] - 1] << ", 3 for " << me[my_ch[2]] << " -HP" << vec_hp[my_ch[2] - 1] << "):";
        while(my_cho != 1 && my_cho != 2)
        {
            os << "Select your next pet (2 for " << me[my_ch[1]] << " -HP" << vec_hp[my_ch[1] - 1] << ", 3 for " << me[my_ch[2]] << " -HP" << vec_hp[my_ch[2] - 1] << "):";
            is >> my_cho;
        }
    }
    else if(vec_hp[my_ch[0] - 1] > 0)
    {
        os << "Select your next pet (1 for " << me[my_ch[0]] << " -HP" << vec_hp[my_ch[0] - 1] << "):";
        while(my_cho != 1)
        {
            os << "Select your next pet (1 for " << me[my_ch[0]] << " -HP" << vec_hp[my_ch[0] - 1] << "):";
            is >> my_cho;
        }
    }
    else if(vec_hp[my_ch[1] - 1] > 0)
    {
        os << "Select your next pet (2 for " << me[my_ch[1]] << " -HP" << vec_hp[my_ch[1] - 1] << "):";
        while(my_cho != 1)
        {
            os << "Select your next pet (2 for " << me[my_ch[1]] << " -HP" << vec_hp[my_ch[1] - 1] << "):";
            is >> my_cho;
        }
    }
    else if(vec_hp[my_ch[2] - 1] > 0)
    {
        os << "Select your next pet (3 for " << me[my_ch[2]] << " -HP" << vec_hp[my_ch[2] - 1] << "):";
        while(my_cho != 1)
        {
            os << "Select your next pet (3 for " << me[my_ch[2]] << " -HP" << vec_hp[my_ch[2] - 1] << "):";
            is >> my_cho;
        }
    }
}

//死亡后改变敌我宠物
bool dead_echange(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int> vec_hp, map<int, string> me, vector<int>& my_ch)
{
    if(vec_hp[my_cho - 1] <= 0)
    {
        my_change(is, os, my_cho, vec_hp, me, my_ch);
        return true;
    }
    if(vec_hp[enemy_cho + 4] <= 0)
    {
        enemy_change(enemy_cho, vec_hp, os);
        return true;
    }
    return false;
}

//程序开始的输出
void start(ostream& os, int me)
{
    switch(me)
    {
    case 1:
        os << "You start with W" <<  endl;
        break;
    case 2:
        os << "You start with L" << endl;
        break;
    case 3:
        os << "You start with G" << endl;
        break;
    case 4:
        os << "You start with Q" << endl;
        break;
    case 5:
        os << "You start with D" << endl;
    default:
        break;
    }
    os << "Enemy starts with D" << endl;
}

//判断胜负情况
bool win(ostream& os, vector<int>& my_ch, vector<int> vec_hp, int round)
{
    if((vec_hp[5] <= 0 && vec_hp[6] <= 0 && vec_hp[7] <= 0 && vec_hp[my_ch[0]] <= 0 && vec_hp[my_ch[1]] <= 0 && vec_hp[my_ch[2]] <= 0) || round == 100)
    {
        os << "Draw" ;
        return true;
    }
    else if(vec_hp[my_ch[0]] <= 0 && vec_hp[my_ch[1]] <= 0 && vec_hp[my_ch[2]] <= 0)
    {
        os << "You lose";
        return true;
    }
    else if(vec_hp[5] <= 0 && vec_hp[6] <= 0 && vec_hp[7] <= 0)
    {
        os << "You win" ;
        return true;
    }
    return false;
}

//展示敌我HP值 or 判断胜负
void show_hp(ostream& os,int& enemy_cho, vector<int>& my_ch, map<int, string> me, vector<int> vec_hp, int my_cho, int& round)
{
    if(win(os, my_ch, vec_hp, round))
    {
       my_cho = my_cho;
    }
    else
    {
      os << "Your " << me[my_ch[my_cho - 1]] << ": HP " << vec_hp[my_ch[my_cho - 1] - 1] << " || " ;
        switch(enemy_cho)
        {
        case 1:
            os << "Enemy's D: HP " << vec_hp[5] << endl;
            break;
        case 2:
            os << "Enemy's W: HP " << vec_hp[6] << endl;
            break;
        case 3:
            os << "Enemy's L: HP " << vec_hp[7] << endl;
            break;
        default:
            break;
        }
    }
}

//判定是否使用逃跑
void run(ostream& os, int& round, int action)
{
    if(action == 0)
    {
        os << "You escape" ;
        round = 100;
    }
}

//判断是否更换宠物,主动更换宠物
bool changeall(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act, int& before)
{
    before = my_cho;
    vector<int> vec = {0};
    int pact = -1;
    while(pact < 0 || pact >= 4 || pact == my_cho)
    {
        os << "Select your next pet(0 for back";
        for(int i = 1; i <= 3; i++)
        {
            if(i != my_cho && vec_hp[my_ch[i - 1] - 1] > 0)
            {
                os << ", " <<  i << " for " << me[my_ch[i - 1]] << "-HP" << vec_hp[my_ch[i - 1] - 1];
                vec.push_back(i);
            }
        }
        os << "): ";
        is >> pact;
        int a = 0;
        for(int i = 0; i < vec.size(); i++)
        {
            if(pact == vec[i])
            {
                a += 1;
            }
        }
        if(a == 0)
        {
            pact = -1;
            vec = {0};
        }
    }
    if(pact != 0)
    {
        my_cho = pact;
        os << "You send " << me[my_ch[my_cho - 1]] << endl;
        return true;
    }
    return false;
}

//敌方主动更换宠物
bool change_ene(ostream& os, vector<int>& vec_hp, int& enemy_cho)
{
    if(vec_hp[6] < 55 && vec_hp[7] > 0)
    {
        return true;
    }
    return false;
}

//宠物数量大于等于2的acion
void act2(istream& is, ostream& os, int& act)
{
    while(act < 0 || act >= 3)
    {
        os << "Select your action (0 for escape, 1 for skill, 2 for change): " ;
        is >> act;
    }
}

//宠物数量等于1的acion
void act1(istream& is, ostream& os, int& act)
{
    while(act < 0 || act >= 2)
    {
        os << "Select your action (0 for escape, 1 for skill): " ;
        is >> act;
    }
}

//单纯我方的攻击
bool my_attack(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act)
{
    act = -1;
    if(my_ch[my_cho - 1] == 1)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Tackle, 2 for Leaf, 3 for Synthesis): " ;
            is >> act;
        }
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else if(act == 1)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 2] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 2)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 3)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[0] == 0)
            {
                os << "Your " << me[my_ch[my_cho - 1]] << " uses Synthesis! Recovery: 33" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] += 33;
            }
            else if(condition[0] < 0)
            {
               os << "Your " << me[my_ch[my_cho - 1]] << " uses Synthesis! Recovery: 22" << endl;
               vec_hp[my_ch[my_cho - 1] - 1] += 22;
            }
            else
            {
               os << "Your " << me[my_ch[my_cho - 1]] << " uses Synthesis! Recovery: 44" << endl; \
               vec_hp[my_ch[my_cho - 1] - 1] += 44;
            }
            if(vec_hp[my_ch[my_cho - 1] - 1] > 110)
            {
                vec_hp[my_ch[my_cho - 1] - 1] = 110;
            }
        }
    }
    else if(my_ch[my_cho - 1] == 2)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Claw, 2 for Flame, 3 for Sunny): " ;
            is >> act;
        }
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else if(act == 1)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 23" << endl;
                    vec_hp[enemy_cho + 4] -= 23;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 18" << endl;
                    vec_hp[enemy_cho + 4] -= 18;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 23" << endl;
                    vec_hp[enemy_cho + 4] -= 23;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's D wakes up" << endl;
                    }
                    condition[enemy_cho + 6] = 0;
                    time[enemy_cho + 3] = 0;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 18" << endl;
                    vec_hp[enemy_cho + 4] -= 18;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 45" << endl;
                    vec_hp[enemy_cho + 4] -= 45;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 45" << endl;
                    vec_hp[enemy_cho + 4] -= 45;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's D wakes up" << endl;
                    }
                    condition[enemy_cho + 6] = 0;
                    time[enemy_cho + 3] = 0;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 2)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 30" << endl;
                       vec_hp[enemy_cho + 4] -= 30;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 12" << endl;
                        vec_hp[enemy_cho + 4] -= 12;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 15" << endl;
                       vec_hp[enemy_cho + 4] -= 15;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                       vec_hp[enemy_cho + 4] -= 24;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 6" << endl;
                        vec_hp[enemy_cho + 4] -= 6;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 45" << endl;
                       vec_hp[enemy_cho + 4] -= 45;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                       vec_hp[enemy_cho + 4] -= 72;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 18" << endl;
                        vec_hp[enemy_cho + 4] -= 18;
                   }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 30" << endl;
                       vec_hp[enemy_cho + 4] -= 30;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 12" << endl;
                        vec_hp[enemy_cho + 4] -= 12;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 15" << endl;
                       vec_hp[enemy_cho + 4] -= 15;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                       vec_hp[enemy_cho + 4] -= 24;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 6" << endl;
                        vec_hp[enemy_cho + 4] -= 6;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 45" << endl;
                       vec_hp[enemy_cho + 4] -= 45;
                    }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                       vec_hp[enemy_cho + 4] -= 72;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 18" << endl;
                        vec_hp[enemy_cho + 4] -= 18;
                   }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                    }
                }
                condition[enemy_cho + 6] = 0;
                time[enemy_cho + 3] = 0;
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 60" << endl;
                       vec_hp[enemy_cho + 4] -= 60;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 96" << endl;
                       vec_hp[enemy_cho + 4] -= 96;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                        vec_hp[enemy_cho + 4] -= 24;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 30" << endl;
                       vec_hp[enemy_cho + 4] -= 30;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 12" << endl;
                        vec_hp[enemy_cho + 4] -= 12;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 90" << endl;
                       vec_hp[enemy_cho + 4] -= 90;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 144" << endl;
                       vec_hp[enemy_cho + 4] -= 144;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 36" << endl;
                        vec_hp[enemy_cho + 4] -= 36;
                   }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
               if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 60" << endl;
                       vec_hp[enemy_cho + 4] -= 60;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 96" << endl;
                       vec_hp[enemy_cho + 4] -= 96;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                        vec_hp[enemy_cho + 4] -= 24;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 30" << endl;
                       vec_hp[enemy_cho + 4] -= 30;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 12" << endl;
                        vec_hp[enemy_cho + 4] -= 12;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 90" << endl;
                       vec_hp[enemy_cho + 4] -= 90;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 144" << endl;
                       vec_hp[enemy_cho + 4] -= 144;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 36" << endl;
                        vec_hp[enemy_cho + 4] -= 36;
                   }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                    }
                }
                condition[enemy_cho + 6] = 0;
                time[enemy_cho + 3] = 0;
            }
        }
        else if(act == 3)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            os << "Your " << me[my_ch[my_cho - 1]] << " uses Sunny! Weather becomes sunny" << endl;
            condition[0] = 1;
            time[0] = 5;
        }
    }
    else if(my_ch[my_cho - 1] == 3)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Tackle, 2 for Stream, 3 for Rainy): " ;
            is >> act;
        }
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else if(act == 1)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else
                {
                    os << "20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else
                {
                    os << "20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                else
                {
                    os << "40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                else
                {
                    os << "40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 13" << endl;
                        vec_hp[enemy_cho + 4] -= 13;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 5" << endl;
                        vec_hp[enemy_cho + 4] -= 5;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 38" << endl;
                        vec_hp[enemy_cho + 4] -= 38;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 15" << endl;
                        vec_hp[enemy_cho + 4] -= 15;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 60" << endl;
                        vec_hp[enemy_cho + 4] -= 60;
                    }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 13" << endl;
                        vec_hp[enemy_cho + 4] -= 13;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 5" << endl;
                        vec_hp[enemy_cho + 4] -= 5;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 38" << endl;
                        vec_hp[enemy_cho + 4] -= 38;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 15" << endl;
                        vec_hp[enemy_cho + 4] -= 15;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 60" << endl;
                        vec_hp[enemy_cho + 4] -= 60;
                    }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 80" << endl;
                        vec_hp[enemy_cho + 4] -= 80;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 75" << endl;
                        vec_hp[enemy_cho + 4] -= 75;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 30" << endl;
                        vec_hp[enemy_cho + 4] -= 30;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 120" << endl;
                        vec_hp[enemy_cho + 4] -= 120;
                    }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 80" << endl;
                        vec_hp[enemy_cho + 4] -= 80;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 75" << endl;
                        vec_hp[enemy_cho + 4] -= 75;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 30" << endl;
                        vec_hp[enemy_cho + 4] -= 30;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 120" << endl;
                        vec_hp[enemy_cho + 4] -= 120;
                    }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 3)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            os << "Your G uses Rainy! Weather becomes rainy" << endl;
            condition[0] = -1;
            time[0] = 5;
        }
    }
    else if(my_ch[my_cho - 1] == 4)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Quick, 2 for Volt, 3 for Thunder): " ;
            is >> act;
        }
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else if(act == 1)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                else
                {
                    os << "15" << endl;
                    vec_hp[enemy_cho + 4] -= 15;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                else
                {
                    os << "15" << endl;
                    vec_hp[enemy_cho + 4] -= 15;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
                else
                {
                    os << "30" << endl;
                    vec_hp[enemy_cho + 4] -= 30;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
                else
                {
                    os << "30" << endl;
                    vec_hp[enemy_cho + 4] -= 30;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "30" << endl;
                    vec_hp[enemy_cho + 4] -= 30;
                }
                else if(enemy_cho == 2)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                else if(enemy_cho == 3)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "30" << endl;
                    vec_hp[enemy_cho + 4] -= 30;
                }
                else if(enemy_cho == 2)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                else if(enemy_cho == 3)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "60" << endl;
                    vec_hp[enemy_cho + 4] -= 60;
                }
                else if(enemy_cho == 2)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else if(enemy_cho == 3)
                {
                    os << "50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "60" << endl;
                    vec_hp[enemy_cho + 4] -= 60;
                }
                else if(enemy_cho == 2)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else if(enemy_cho == 3)
                {
                    os << "50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 3)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[0] == -1)
            {
                if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "63" << endl;
                        vec_hp[enemy_cho + 4] -= 63;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                }
                else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "63" << endl;
                        vec_hp[enemy_cho + 4] -= 63;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's D wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 3)
                        {
                            os << "Enemy's L wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                    }
                }
                else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "125" << endl;
                        vec_hp[enemy_cho + 4] -= 125;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "100" << endl;
                        vec_hp[enemy_cho + 4] -= 100;
                    }
                }
                else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "125" << endl;
                        vec_hp[enemy_cho + 4] -= 125;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "100" << endl;
                        vec_hp[enemy_cho + 4] -= 100;
                    }
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's D wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 3)
                        {
                            os << "Enemy's L wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                    }
                }
            }
            else
            {
                os << "Your Q uses Thunder! Failure" << endl;
            }
        }
    }
    else if(my_ch[my_cho - 1] == 5)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Slap, 2 for Sing, 3 for Paint): " ;
            is >> act;
        }
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else if(act == 1)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "17" << endl;
                    vec_hp[enemy_cho + 4] -= 17;
                }
                else
                {
                    os << "14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "17" << endl;
                    vec_hp[enemy_cho + 4] -= 17;
                }
                else
                {
                    os << "14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "34" << endl;
                    vec_hp[enemy_cho + 4] -= 34;
                }
                else
                {
                    os << "27" << endl;
                    vec_hp[enemy_cho + 4] -= 27;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "34" << endl;
                    vec_hp[enemy_cho + 4] -= 34;
                }
                else
                {
                    os << "27" << endl;
                    vec_hp[enemy_cho + 4] -= 27;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            os << "Your D uses Sing!";
            if(condition[enemy_cho + 6] != 0)
            {
                os << "Waste" << endl;
            }
            else
            {
                if(enemy_cho == 1)
                {
                    os << " Enemy's D falls asleep" << endl;
                }
                if(enemy_cho == 2)
                {
                    os << " Enemy's W falls asleep" << endl;
                }
                if(enemy_cho == 3)
                {
                    os << " Enemy's L falls asleep" << endl;
                }
                condition[enemy_cho + 6] = 1;
                time[enemy_cho + 3] = 3;
            }
        }
        else if(act == 3)
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            os << "Your D uses Paint! Enemy's " ;
            if(enemy_cho == 1)
            {
                os << "D is painted" << endl;
            }
            else if(enemy_cho == 2)
            {
                os << "W is painted" << endl;
            }
            else if(enemy_cho == 3)
            {
                os << "L is painted" << endl;
            }
            condition[enemy_cho + 9] = 1;
        }
    }
    return true;
}

//单纯敌方的攻击
void enemy_attack(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act)
{
    if(enemy_cho == 1)
    {
        int max_hp = 0;
        if(my_ch[my_cho - 1] == 1)
        {
            max_hp = 37;
        }
        else if(my_ch[my_cho - 1] == 2)
        {
            max_hp = 34;
        }
        else if(my_ch[my_cho - 1] == 3)
        {
            max_hp = 34;
        }
        else if(my_ch[my_cho - 1] == 4)
        {
            max_hp = 30;
        }
        else if(my_ch[my_cho - 1] == 5)
        {
            max_hp = 40;
        }
        if(vec_hp[my_ch[my_cho - 1] - 1] < max_hp && (time[my_cho] != 0 || condition[my_cho + 3] != 0))
        {
            if(my_ch[my_cho - 1] == 1 || my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 4)
            {
                os << "Enemy's D uses Slap! Damage: 27" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 27;
            }
            else if(my_ch[my_cho - 1] == 3)
            {
                os << "Enemy's D uses Slap! Damage: 19" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 19;
            }
            else if(my_ch[my_cho - 1] == 5)
            {
                os << "Enemy's D uses Slap! Damage: 34" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 34;
            }
        }
        else if(condition[my_cho] == 0)
        {
            os << "Enemy's D uses Sing! Your " << me[my_ch[my_cho - 1]] << " falls asleep" << endl;
            condition[my_cho] = 1;
            time[my_cho] = 3;
        }
        else if(condition[my_cho] != 0 && condition[my_cho + 3] == 0)
        {
            os << "Enemy's D uses Paint! Your " << me[my_ch[my_cho - 1]] << " is painted" << endl;
            condition[my_cho + 3] = 1;
        }
        else if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
        {
            if(my_ch[my_cho - 1] == 1 || my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 4)
            {
                os << "Enemy's D uses Slap! Damage: 27" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 27;
            }
            else if(my_ch[my_cho - 1] == 3)
            {
                os << "Enemy's D uses Slap! Damage: 19" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 19;
            }
            else if(my_ch[my_cho - 1] == 5)
            {
                os << "Enemy's D uses Slap! Damage: 34" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 34;
            }
            if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
            {
                os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                time[my_cho] = 0;
                condition[my_cho] = 0;
            }
        }
    }
    else if(enemy_cho == 3)
    {
        int max_hp = 0;
        if(my_ch[my_cho - 1] == 1)
        {
            max_hp = 22;
        }
        else if(my_ch[my_cho - 1] == 2)
        {
            max_hp = 20;
        }
        else if(my_ch[my_cho - 1] == 3)
        {
            max_hp = 20;
        }
        else if(my_ch[my_cho - 1] == 4)
        {
            max_hp = 18;
        }
        else if(my_ch[my_cho - 1] == 5)
        {
            max_hp = 24;
        }
        if(vec_hp[my_ch[my_cho - 1] - 1] < max_hp && (my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 3))
        {
            if(my_ch[my_cho - 1] == 1 || my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 4)
            {
                os << "Enemy's L uses Claw! Damage: 36" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 36;
            }
            else if(my_ch[my_cho - 1] == 3)
            {
                os << "Enemy's L uses Claw! Damage: 25" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 25;
            }
            else if(my_ch[my_cho - 1] == 5)
            {
                os << "Enemy's L uses Claw! Damage: 45" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 45;
            }
        }
        else if(condition[0] > 0)
        {
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                if(my_ch[my_cho - 1] == 1)
                {
                    os << "Enemy's L uses Flame! Damage: 72" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 72;
                }
                else if(my_ch[my_cho - 1] == 2)
                {
                    os << "Enemy's L uses Flame! Damage: 18" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 18;
                }
                else if(my_ch[my_cho - 1] == 3)
                {
                    os << "Enemy's L uses Flame! Damage: 13" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 13;
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    os << "Enemy's L uses Flame! Damage: 36" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 36;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "Enemy's L uses Flame! Damage: 45" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 45;
                }
            }
            else if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
            {
                if(my_ch[my_cho - 1] == 1)
                {
                    os << "Enemy's L uses Flame! Damage: 72" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 72;
                }
                else if(my_ch[my_cho - 1] == 2)
                {
                    os << "Enemy's L uses Flame! Damage: 18" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 18;
                }
                else if(my_ch[my_cho - 1] == 3)
                {
                    os << "Enemy's L uses Flame! Damage: 13" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 13;
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    os << "Enemy's L uses Flame! Damage: 36" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 36;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "Enemy's L uses Flame! Damage: 45" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 45;
                }
                if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                    time[my_cho] = 0;
                    condition[my_cho] = 0;
                }
            }
            else if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                {
                    os << "Enemy's L uses Flame! Damage: 144" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 144;
                }
                else if(my_ch[my_cho - 1] == 2)
                {
                    os << "Enemy's L uses Flame! Damage: 36" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 36;
                }
                else if(my_ch[my_cho - 1] == 3)
                {
                    os << "Enemy's L uses Flame! Damage: 26" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 26;
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    os << "Enemy's L uses Flame! Damage: 72" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 72;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "Enemy's L uses Flame! Damage: 90" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 90;
                }
            }
            else if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                {
                    os << "Enemy's L uses Flame! Damage: 144" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 144;
                }
                else if(my_ch[my_cho - 1] == 2)
                {
                    os << "Enemy's L uses Flame! Damage: 36" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 36;
                }
                else if(my_ch[my_cho - 1] == 3)
                {
                    os << "Enemy's L uses Flame! Damage: 26" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 26;
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    os << "Enemy's L uses Flame! Damage: 72" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 72;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "Enemy's L uses Flame! Damage: 90" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 90;
                }
                if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                    time[my_cho] = 0;
                    condition[my_cho] = 0;
                }
            }
        }
        else
        {
            os << "Enemy's L uses Sunny! Weather becomes sunny" << endl;
            condition[0] = 1;
            time[0] = 5;
        }
    }
    else if(enemy_cho == 2)
    {
        if(vec_hp[enemy_cho + 4] >= 55 || (vec_hp[enemy_cho + 4] > vec_hp[my_ch[my_cho - 1] - 1]) && vec_hp[5] <= 0 && vec_hp[7] <=0)
        {
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                if(my_ch[my_cho - 1] == 3)
                {
                    if(condition[0] < 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 43" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 43;
                    }
                    else if(condition[0] == 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 29" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 29;
                    }
                    else if(condition[0] > 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 14" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 14;
                    }
                }
                else
                {
                    if(my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's W uses Tackle! Damage: 20" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 20;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's W uses Tackle! Damage: 25" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 25;
                    }
                    else
                    {
                        os << "Enemy's W uses Tackle! Damage: 20" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 20;
                    }
                }
            }
            else if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
            {
               if(my_ch[my_cho - 1] == 3)
                {
                    if(condition[0] < 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 43" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 43;
                    }
                    else if(condition[0] == 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 29" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 29;
                    }
                    else if(condition[0] > 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 14" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 14;
                    }
                }
                else
                {
                    if(my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's W uses Tackle! Damage: 20" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 20;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's W uses Tackle! Damage: 25" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 25;
                    }
                    else
                    {
                        os << "Enemy's W uses Tackle! Damage: 20" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 20;
                    }
                }
                if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                    time[my_cho] = 0;
                    condition[my_cho] = 0;
                }
            }
            else if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 3)
                {
                    if(condition[0] < 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 86" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 86;
                    }
                    else if(condition[0] == 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 57" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 57;
                    }
                    else if(condition[0] > 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 29" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 29;
                    }
                }
                else
                {
                    if(my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's W uses Tackle! Damage: 40" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 40;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's W uses Tackle! Damage: 50" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 50;
                    }
                    else
                    {
                        os << "Enemy's W uses Tackle! Damage: 40" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 40;
                    }
                }
            }
            else if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                 if(my_ch[my_cho - 1] == 3)
                {
                    if(condition[0] < 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 86" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 86;
                    }
                    else if(condition[0] == 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 57" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 57;
                    }
                    else if(condition[0] > 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 29" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 29;
                    }
                }
                else
                {
                    if(my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's W uses Tackle! Damage: 40" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 40;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's W uses Tackle! Damage: 50" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 50;
                    }
                    else
                    {
                        os << "Enemy's W uses Tackle! Damage: 40" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 40;
                    }
                }
                if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                    time[my_cho] = 0;
                    condition[my_cho] = 0;
                }
            }
        }
        else
        {
            if(condition[0] == 0)
            {
                os << "Enemy’s W uses Synthesis! Recovery: 33" << endl;
                vec_hp[enemy_cho + 4] += 33;
                if(vec_hp[enemy_cho + 4] > 110)
                {
                   vec_hp[enemy_cho + 4] = 110;
                }
            }
            else if(condition[0] == 1)
            {
                os << "Enemy’s W uses Synthesis! Recovery: 44" << endl;
                vec_hp[enemy_cho + 4] += 44;
                if(vec_hp[enemy_cho + 4] > 110)
                {
                   vec_hp[enemy_cho + 4] = 110;
                }
            }
            else if(condition[0] == -1)
            {
                os << "Enemy’s W uses Synthesis! Recovery: 22" << endl;
                vec_hp[enemy_cho + 4] += 22;
                if(vec_hp[enemy_cho + 4] > 110)
                {
                   vec_hp[enemy_cho + 4] = 110;
                }
            }
        }
    }
}

void enemy_attack2(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act, int& before)
{
    if(enemy_cho == 1)
    {
        int max_hp = 0;
        if(my_ch[my_cho - 1] == 1)
        {
            max_hp = 37;
        }
        else if(my_ch[my_cho - 1] == 2)
        {
            max_hp = 34;
        }
        else if(my_ch[my_cho - 1] == 3)
        {
            max_hp = 34;
        }
        else if(my_ch[my_cho - 1] == 4)
        {
            max_hp = 30;
        }
        else if(my_ch[my_cho - 1] == 5)
        {
            max_hp = 40;
        }
        if(vec_hp[my_ch[before] - 1] < max_hp && (time[before] != 0 || condition[before + 3] != 0))
        {
            if(my_ch[my_cho - 1] == 1 || my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 4)
            {
                os << "Enemy's D uses Slap! Damage: 27" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 27;
            }
            else if(my_ch[my_cho - 1] == 3)
            {
                os << "Enemy's D uses Slap! Damage: 19" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 19;
            }
            else if(my_ch[my_cho - 1] == 5)
            {
                os << "Enemy's D uses Slap! Damage: 34" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 34;
            }
        }
        else if(condition[before] == 0)
        {
            if(condition[my_cho] == 0)
            {
                os << "Enemy's D uses Sing! Your " << me[my_ch[my_cho - 1]] << " falls asleep" << endl;
                condition[my_cho] = 1;
                time[my_cho] = 3;

            }
            else
            {
                os << "Enemy's D uses Sing! Waste " <<  endl;
            }
        }
        else if(condition[before] != 0 && condition[before + 3] == 0)
        {
            os << "Enemy's D uses Paint! Your " << me[my_ch[my_cho - 1]] << " is painted" << endl;
            condition[my_cho + 3] = 1;
        }
        else if(time[before] != 0 && condition[before + 3] != 0)
        {
            if(my_ch[my_cho - 1] == 1 || my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 4)
            {
                os << "Enemy's D uses Slap! Damage: 27" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 27;
            }
            else if(my_ch[my_cho - 1] == 3)
            {
                os << "Enemy's D uses Slap! Damage: 19" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 19;
            }
            else if(my_ch[my_cho - 1] == 5)
            {
                os << "Enemy's D uses Slap! Damage: 34" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 34;
            }
            if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
            {
                os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                time[my_cho] = 0;
                condition[my_cho] = 0;
            }
        }
    }
    else if(enemy_cho == 3)
    {
        int max_hp = 0;
        if(my_ch[my_cho - 1] == 1)
        {
            max_hp = 22;
        }
        else if(my_ch[my_cho - 1] == 2)
        {
            max_hp = 20;
        }
        else if(my_ch[my_cho - 1] == 3)
        {
            max_hp = 20;
        }
        else if(my_ch[my_cho - 1] == 4)
        {
            max_hp = 18;
        }
        else if(my_ch[my_cho - 1] == 5)
        {
            max_hp = 24;
        }
        if(vec_hp[my_ch[before - 1] - 1] < max_hp && (my_ch[before - 1] == 2 || my_ch[before - 1] == 3))
        {
            if(my_ch[my_cho - 1] == 1 || my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 4)
            {
                os << "Enemy's L uses Claw! Damage: 36" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 36;
            }
            else if(my_ch[my_cho - 1] == 3)
            {
                os << "Enemy's L uses Claw! Damage: 25" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 25;
            }
            else if(my_ch[my_cho - 1] == 5)
            {
                os << "Enemy's L uses Claw! Damage: 45" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] -= 45;
            }
        }
        else if(condition[0] > 0)
        {
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                if(my_ch[my_cho - 1] == 1)
                {
                    os << "Enemy's L uses Flame! Damage: 72" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 72;
                }
                else if(my_ch[my_cho - 1] == 2)
                {
                    os << "Enemy's L uses Flame! Damage: 18" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 18;
                }
                else if(my_ch[my_cho - 1] == 3)
                {
                    os << "Enemy's L uses Flame! Damage: 13" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 13;
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    os << "Enemy's L uses Flame! Damage: 36" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 36;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "Enemy's L uses Flame! Damage: 45" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 45;
                }
            }
            else if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
            {
                if(my_ch[my_cho - 1] == 1)
                {
                    os << "Enemy's L uses Flame! Damage: 72" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 72;
                }
                else if(my_ch[my_cho - 1] == 2)
                {
                    os << "Enemy's L uses Flame! Damage: 18" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 18;
                }
                else if(my_ch[my_cho - 1] == 3)
                {
                    os << "Enemy's L uses Flame! Damage: 13" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 13;
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    os << "Enemy's L uses Flame! Damage: 36" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 36;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "Enemy's L uses Flame! Damage: 45" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 45;
                }
                if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                    time[my_cho] = 0;
                    condition[my_cho] = 0;
                }
            }
            else if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                {
                    os << "Enemy's L uses Flame! Damage: 144" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 144;
                }
                else if(my_ch[my_cho - 1] == 2)
                {
                    os << "Enemy's L uses Flame! Damage: 36" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 36;
                }
                else if(my_ch[my_cho - 1] == 3)
                {
                    os << "Enemy's L uses Flame! Damage: 26" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 26;
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    os << "Enemy's L uses Flame! Damage: 72" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 72;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "Enemy's L uses Flame! Damage: 90" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 90;
                }
            }
            else if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                {
                    os << "Enemy's L uses Flame! Damage: 144" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 144;
                }
                else if(my_ch[my_cho - 1] == 2)
                {
                    os << "Enemy's L uses Flame! Damage: 36" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 36;
                }
                else if(my_ch[my_cho - 1] == 3)
                {
                    os << "Enemy's L uses Flame! Damage: 26" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 26;
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    os << "Enemy's L uses Flame! Damage: 72" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 72;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "Enemy's L uses Flame! Damage: 90" << endl;
                    vec_hp[my_ch[my_cho - 1] - 1] -= 90;
                }
                if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                    time[my_cho] = 0;
                    condition[my_cho] = 0;
                }
            }
        }
        else
        {
            os << "Enemy's L uses Sunny! Weather becomes sunny" << endl;
            condition[0] = 1;
            time[0] = 5;
        }
    }
    else if(enemy_cho == 2)
    {
        if(vec_hp[enemy_cho + 4] >= 55 || (vec_hp[enemy_cho + 4] > vec_hp[my_ch[before - 1] - 1]) && vec_hp[5] <= 0 && vec_hp[7] <=0)
        {
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                if(my_ch[my_cho - 1] == 3)
                {
                    if(condition[0] < 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 43" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 43;
                    }
                    else if(condition[0] == 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 29" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 29;
                    }
                    else if(condition[0] > 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 14" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 14;
                    }
                }
                else
                {
                    if(my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's W uses Tackle! Damage: 20" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 20;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's W uses Tackle! Damage: 25" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 25;
                    }
                    else
                    {
                        os << "Enemy's W uses Tackle! Damage: 20" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 20;
                    }
                }
            }
            else if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
            {
               if(my_ch[my_cho - 1] == 3)
                {
                    if(condition[0] < 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 43" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 43;
                    }
                    else if(condition[0] == 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 29" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 29;
                    }
                    else if(condition[0] > 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 14" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 14;
                    }
                }
                else
                {
                    if(my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's W uses Tackle! Damage: 20" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 20;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's W uses Tackle! Damage: 25" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 25;
                    }
                    else
                    {
                        os << "Enemy's W uses Tackle! Damage: 20" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 20;
                    }
                }
                if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                    time[my_cho] = 0;
                    condition[my_cho] = 0;
                }
            }
            else if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 3)
                {
                    if(condition[0] < 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 86" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 86;
                    }
                    else if(condition[0] == 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 57" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 57;
                    }
                    else if(condition[0] > 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 29" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 29;
                    }
                }
                else
                {
                    if(my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's W uses Tackle! Damage: 40" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 40;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's W uses Tackle! Damage: 50" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 50;
                    }
                    else
                    {
                        os << "Enemy's W uses Tackle! Damage: 40" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 40;
                    }
                }
            }
            else if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                 if(my_ch[my_cho - 1] == 3)
                {
                    if(condition[0] < 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 86" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 86;
                    }
                    else if(condition[0] == 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 57" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 57;
                    }
                    else if(condition[0] > 0)
                    {
                        os << "Enemy's W uses Leaf! Damage: 29" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 29;
                    }
                }
                else
                {
                    if(my_ch[my_cho - 1] == 2 || my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's W uses Tackle! Damage: 40" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 40;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's W uses Tackle! Damage: 50" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 50;
                    }
                    else
                    {
                        os << "Enemy's W uses Tackle! Damage: 40" << endl;
                        vec_hp[my_ch[my_cho - 1] - 1] -= 40;
                    }
                }
                if(vec_hp[my_ch[my_cho - 1] - 1] > 0)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
                    time[my_cho] = 0;
                    condition[my_cho] = 0;
                }
            }
        }
        else
        {
            if(condition[0] == 0)
            {
                os << "Enemy’s W uses Synthesis! Recovery: 33" << endl;
                vec_hp[enemy_cho + 4] += 33;
                if(vec_hp[enemy_cho + 4] > 110)
                {
                   vec_hp[enemy_cho + 4] = 110;
                }
            }
            else if(condition[0] == 1)
            {
                os << "Enemy’s W uses Synthesis! Recovery: 44" << endl;
                vec_hp[enemy_cho + 4] += 44;
                if(vec_hp[enemy_cho + 4] > 110)
                {
                   vec_hp[enemy_cho + 4] = 110;
                }
            }
            else if(condition[0] == -1)
            {
                os << "Enemy’s W uses Synthesis! Recovery: 22" << endl;
                vec_hp[enemy_cho + 4] += 22;
                if(vec_hp[enemy_cho + 4] > 110)
                {
                   vec_hp[enemy_cho + 4] = 110;
                }
            }
        }
    }
    before = my_cho;
}

//判断敌方小D是否使用Sing
bool sing(int& enemy_cho, ostream& os, int& my_cho, int& act, vector<int>& my_ch, vector<int>& condition, vector<int>& time, vector<int>& vec_hp, map<int, string> me)
{
    int max_hp = 0;
    if(enemy_cho == 1)
    {
        if(my_ch[my_cho - 1] == 1)
        {
            max_hp = 37;
        }
        else if(my_ch[my_cho - 1] == 2)
        {
            max_hp = 34;
        }
        else if(my_ch[my_cho - 1] == 3)
        {
            max_hp = 34;
        }
        else if(my_ch[my_cho - 1] == 4)
        {
            max_hp = 30;
        }
        else if(my_ch[my_cho - 1] == 5)
        {
            max_hp = 40;
        }
    }
    if(enemy_cho == 1 && (time[my_cho] != 0 && time[my_cho + 3] == 0))
    {
        if(my_ch[my_cho - 1] == 4 && act == 3 && condition[0] >= 0)
        {
            os << "Enemy's D uses Paint! Your " << me[my_ch[my_cho - 1]] << " is painted" << endl;
            condition[my_cho + 3] = 1;
            return true;
        }
        else
        {
            os << "Enemy's D uses Paint! Failure" << endl;
            return true;
        }
    }
    else
    {
        return false;
    }
}

//我方进攻简化
void my_att(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act)
{
    if(my_ch[my_cho - 1] == 1)
    {
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
        }
        if(act == 0)
        {
            act = 0;
        }
        else if(act == 1)
        {
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 2] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 2)
        {
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 3)
        {
            if(condition[0] == 0)
            {
                os << "Your " << me[my_ch[my_cho - 1]] << " uses Synthesis! Recovery: 33" << endl;
                vec_hp[my_ch[my_cho - 1] - 1] += 33;
            }
            else if(condition[0] < 0)
            {
               os << "Your " << me[my_ch[my_cho - 1]] << " uses Synthesis! Recovery: 22" << endl;
               vec_hp[my_ch[my_cho - 1] - 1] += 22;
            }
            else
            {
               os << "Your " << me[my_ch[my_cho - 1]] << " uses Synthesis! Recovery: 44" << endl; \
               vec_hp[my_ch[my_cho - 1] - 1] += 44;
            }
            if(vec_hp[my_ch[my_cho - 1] - 1] > 110)
            {
                vec_hp[my_ch[my_cho - 1] - 1] = 110;
            }
        }
    }
    else if(my_ch[my_cho - 1] == 2)
    {
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
        }
        if(act == 0)
        {
            act = 0;
        }
        else if(act == 1)
        {
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 23" << endl;
                    vec_hp[enemy_cho + 4] -= 23;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 18" << endl;
                    vec_hp[enemy_cho + 4] -= 18;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 23" << endl;
                    vec_hp[enemy_cho + 4] -= 23;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's D wakes up" << endl;
                    }
                    condition[enemy_cho + 6] = 0;
                    time[enemy_cho + 3] = 0;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 18" << endl;
                    vec_hp[enemy_cho + 4] -= 18;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 45" << endl;
                    vec_hp[enemy_cho + 4] -= 45;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 45" << endl;
                    vec_hp[enemy_cho + 4] -= 45;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's D wakes up" << endl;
                    }
                    condition[enemy_cho + 6] = 0;
                    time[enemy_cho + 3] = 0;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's L wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 2)
        {
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 30" << endl;
                       vec_hp[enemy_cho + 4] -= 30;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 12" << endl;
                        vec_hp[enemy_cho + 4] -= 12;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 15" << endl;
                       vec_hp[enemy_cho + 4] -= 15;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                       vec_hp[enemy_cho + 4] -= 24;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 6" << endl;
                        vec_hp[enemy_cho + 4] -= 6;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 45" << endl;
                       vec_hp[enemy_cho + 4] -= 45;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                       vec_hp[enemy_cho + 4] -= 72;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 18" << endl;
                        vec_hp[enemy_cho + 4] -= 18;
                   }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 30" << endl;
                       vec_hp[enemy_cho + 4] -= 30;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 12" << endl;
                        vec_hp[enemy_cho + 4] -= 12;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 15" << endl;
                       vec_hp[enemy_cho + 4] -= 15;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                       vec_hp[enemy_cho + 4] -= 24;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 6" << endl;
                        vec_hp[enemy_cho + 4] -= 6;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 45" << endl;
                       vec_hp[enemy_cho + 4] -= 45;
                    }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                       vec_hp[enemy_cho + 4] -= 72;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 18" << endl;
                        vec_hp[enemy_cho + 4] -= 18;
                   }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                    }
                }
                condition[enemy_cho + 6] = 0;
                time[enemy_cho + 3] = 0;
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 60" << endl;
                       vec_hp[enemy_cho + 4] -= 60;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 96" << endl;
                       vec_hp[enemy_cho + 4] -= 96;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                        vec_hp[enemy_cho + 4] -= 24;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 30" << endl;
                       vec_hp[enemy_cho + 4] -= 30;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 12" << endl;
                        vec_hp[enemy_cho + 4] -= 12;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 90" << endl;
                       vec_hp[enemy_cho + 4] -= 90;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 144" << endl;
                       vec_hp[enemy_cho + 4] -= 144;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 36" << endl;
                        vec_hp[enemy_cho + 4] -= 36;
                   }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
               if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 60" << endl;
                       vec_hp[enemy_cho + 4] -= 60;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 96" << endl;
                       vec_hp[enemy_cho + 4] -= 96;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                        vec_hp[enemy_cho + 4] -= 24;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 30" << endl;
                       vec_hp[enemy_cho + 4] -= 30;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 12" << endl;
                        vec_hp[enemy_cho + 4] -= 12;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 90" << endl;
                       vec_hp[enemy_cho + 4] -= 90;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 144" << endl;
                       vec_hp[enemy_cho + 4] -= 144;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 36" << endl;
                        vec_hp[enemy_cho + 4] -= 36;
                   }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                    }
                }
                condition[enemy_cho + 6] = 0;
                time[enemy_cho + 3] = 0;
            }
        }
        else if(act == 3)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " uses Sunny! Weather becomes sunny" << endl;
            condition[0] = 1;
            time[0] = 5;
        }
    }
    else if(my_ch[my_cho - 1] == 3)
    {
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
        }
        if(act == 0)
        {
            act = 0;
        }
        else if(act == 1)
        {
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else
                {
                    os << "20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else
                {
                    os << "20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                else
                {
                    os << "40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                else
                {
                    os << "40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 13" << endl;
                        vec_hp[enemy_cho + 4] -= 13;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 5" << endl;
                        vec_hp[enemy_cho + 4] -= 5;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 38" << endl;
                        vec_hp[enemy_cho + 4] -= 38;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 15" << endl;
                        vec_hp[enemy_cho + 4] -= 15;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 60" << endl;
                        vec_hp[enemy_cho + 4] -= 60;
                    }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 13" << endl;
                        vec_hp[enemy_cho + 4] -= 13;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 5" << endl;
                        vec_hp[enemy_cho + 4] -= 5;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 38" << endl;
                        vec_hp[enemy_cho + 4] -= 38;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 15" << endl;
                        vec_hp[enemy_cho + 4] -= 15;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 60" << endl;
                        vec_hp[enemy_cho + 4] -= 60;
                    }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 80" << endl;
                        vec_hp[enemy_cho + 4] -= 80;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 75" << endl;
                        vec_hp[enemy_cho + 4] -= 75;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 30" << endl;
                        vec_hp[enemy_cho + 4] -= 30;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 120" << endl;
                        vec_hp[enemy_cho + 4] -= 120;
                    }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 80" << endl;
                        vec_hp[enemy_cho + 4] -= 80;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 75" << endl;
                        vec_hp[enemy_cho + 4] -= 75;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 30" << endl;
                        vec_hp[enemy_cho + 4] -= 30;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 120" << endl;
                        vec_hp[enemy_cho + 4] -= 120;
                    }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 3)
        {
            os << "Your G uses Rainy! Weather becomes rainy" << endl;
            condition[0] = -1;
            time[0] = 5;
        }
    }
    else if(my_ch[my_cho - 1] == 4)
    {
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
        }
        if(act == 0)
        {
            act = 0;
        }
        else if(act == 1)
        {
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                else
                {
                    os << "15" << endl;
                    vec_hp[enemy_cho + 4] -= 15;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                else
                {
                    os << "15" << endl;
                    vec_hp[enemy_cho + 4] -= 15;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
                else
                {
                    os << "30" << endl;
                    vec_hp[enemy_cho + 4] -= 30;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
                else
                {
                    os << "30" << endl;
                    vec_hp[enemy_cho + 4] -= 30;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "30" << endl;
                    vec_hp[enemy_cho + 4] -= 30;
                }
                else if(enemy_cho == 2)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                else if(enemy_cho == 3)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "30" << endl;
                    vec_hp[enemy_cho + 4] -= 30;
                }
                else if(enemy_cho == 2)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                else if(enemy_cho == 3)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "60" << endl;
                    vec_hp[enemy_cho + 4] -= 60;
                }
                else if(enemy_cho == 2)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else if(enemy_cho == 3)
                {
                    os << "50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "60" << endl;
                    vec_hp[enemy_cho + 4] -= 60;
                }
                else if(enemy_cho == 2)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else if(enemy_cho == 3)
                {
                    os << "50" << endl;
                    vec_hp[enemy_cho + 4] -= 50;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 3)
        {
            if(condition[0] == -1)
            {
                if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "63" << endl;
                        vec_hp[enemy_cho + 4] -= 63;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                }
                else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "63" << endl;
                        vec_hp[enemy_cho + 4] -= 63;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's D wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 3)
                        {
                            os << "Enemy's L wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                    }
                }
                else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "125" << endl;
                        vec_hp[enemy_cho + 4] -= 125;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "100" << endl;
                        vec_hp[enemy_cho + 4] -= 100;
                    }
                }
                else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "125" << endl;
                        vec_hp[enemy_cho + 4] -= 125;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "100" << endl;
                        vec_hp[enemy_cho + 4] -= 100;
                    }
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's D wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 2)
                        {
                            os << "Enemy's W wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 3)
                        {
                            os << "Enemy's L wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                    }
                }
            }
            else
            {
                os << "Your Q uses Thunder! Failure" << endl;
            }
        }
    }
    else if(my_ch[my_cho - 1] == 5)
    {
        if(condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
        }
        if(act == 0)
        {
            act = 0;
        }
        else if(act == 1)
        {
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "17" << endl;
                    vec_hp[enemy_cho + 4] -= 17;
                }
                else
                {
                    os << "14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "17" << endl;
                    vec_hp[enemy_cho + 4] -= 17;
                }
                else
                {
                    os << "14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "34" << endl;
                    vec_hp[enemy_cho + 4] -= 34;
                }
                else
                {
                    os << "27" << endl;
                    vec_hp[enemy_cho + 4] -= 27;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "34" << endl;
                    vec_hp[enemy_cho + 4] -= 34;
                }
                else
                {
                    os << "27" << endl;
                    vec_hp[enemy_cho + 4] -= 27;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's D wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's L wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            os << "Your D uses Sing!";
            if(condition[enemy_cho + 6] != 0)
            {
                os << "Waste" << endl;
            }
            else
            {
                if(enemy_cho == 1)
                {
                    os << " Enemy's D is sleeping" << endl;
                }
                if(enemy_cho == 2)
                {
                    os << " Enemy's W is sleeping" << endl;
                }
                if(enemy_cho == 3)
                {
                    os << " Enemy's L is sleeping" << endl;
                }
                condition[enemy_cho + 6] = 1;
                time[enemy_cho + 3] = 3;
            }
        }
    }
}
//敌方和我方的攻击
bool attack(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act)
{
    act = -1;
    if(my_ch[my_cho - 1] == 1)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Tackle, 2 for Leaf, 3 for Synthesis): " ;
            is >> act;
        }
        if(condition[my_cho] != 0 && act != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            if(!change_ene(os, vec_hp, enemy_cho))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                os << "Enemy sends L" << endl;
                enemy_cho = 3;
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else
        {
            if(enemy_cho != 1)
            {
                if(!change_ene(os, vec_hp, enemy_cho))
                {
                    enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                    else
                    {
                        my_cho = my_cho;
                    }
                }
                else
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
            else
            {
                if(!change_ene(os, vec_hp, enemy_cho))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        if(!sing(enemy_cho, os, my_cho, act, my_ch, condition, time, vec_hp, me))
                        {
                            enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        }
                        else
                        {
                            my_cho = my_cho;
                        }
                    }
                    else
                    {
                        my_cho = my_cho;
                    }
                }
                else
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
        }
    }
    else if(my_ch[my_cho - 1] == 2)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Claw, 2 for Flame, 3 for Sunny): " ;
            is >> act;
        }
        if(condition[my_cho] != 0 && act != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            if(!change_ene(os, vec_hp, enemy_cho))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                os << "Enemy sends L" << endl;
                enemy_cho = 3;
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else if(act != 3 || enemy_cho != 3)
        {
            if(enemy_cho == 3)
            {
                if(!change_ene(os, vec_hp, enemy_cho))
                {
                    enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                    else
                    {
                        my_cho = my_cho;
                    }
                }
                else
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
            else
            {
                if(!change_ene(os, vec_hp, enemy_cho))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        if(!sing(enemy_cho, os, my_cho, act, my_ch, condition, time, vec_hp, me))
                        {
                            enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        }
                        else
                        {
                            my_cho = my_cho;
                        }
                    }
                    else
                    {
                        my_cho = my_cho;
                    }
                }
                else
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
        }
        else
        {
            if(condition[0] <= 0)
            {
                if(!change_ene(os, vec_hp, enemy_cho))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        if(!sing(enemy_cho, os, my_cho, act, my_ch, condition, time, vec_hp, me))
                        {
                            enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        }
                        else
                        {
                            my_cho = my_cho;
                        }
                    }
                    else
                    {
                        my_cho = my_cho;
                    }
                }
                else
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
            else
            {
                if(vec_hp[my_ch[my_cho - 1] - 1] >= 20)
                {
                    if(!change_ene(os, vec_hp, enemy_cho))
                    {
                        enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                        {
                            my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        }
                        else
                        {
                            my_cho = my_cho;
                        }
                    }
                    else
                    {
                        os << "Enemy sends L" << endl;
                        enemy_cho = 3;
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                }
                else
                {
                    if(!change_ene(os, vec_hp, enemy_cho))
                    {
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                        {
                            if(!sing(enemy_cho, os, my_cho, act, my_ch, condition, time, vec_hp, me))
                            {
                                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                            }
                            else
                            {
                                my_cho = my_cho;
                            }
                        }
                        else
                        {
                            my_cho = my_cho;
                        }
                    }
                    else
                    {
                        os << "Enemy sends L" << endl;
                        enemy_cho = 3;
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                }
            }
        }
    }
    else if(my_ch[my_cho - 1] == 3)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Tackle, 2 for Stream, 3 for Rainy): " ;
            is >> act;
        }
        if(condition[my_cho] != 0 && act != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            if(!change_ene(os, vec_hp, enemy_cho))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                os << "Enemy sends L" << endl;
                enemy_cho = 3;
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else
        {
            if(enemy_cho == 1)
            {
                if(!change_ene(os, vec_hp, enemy_cho))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        if(!sing(enemy_cho, os, my_cho, act, my_ch, condition, time, vec_hp, me))
                        {
                            enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        }
                        else
                        {
                            my_cho = my_cho;
                        }
                    }
                    else
                    {
                        my_cho = my_cho;
                    }
                }
                else
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
            else
            {
                if(act == 3 && enemy_cho == 3)
                {
                    if(vec_hp[my_ch[my_cho - 1] - 1] >= 20 && condition[0] <= 0)
                    {
                        if(!change_ene(os, vec_hp, enemy_cho))
                        {
                            enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                            if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                            {
                                my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                            }
                            else
                            {
                                my_cho = my_cho;
                            }
                        }
                        else
                        {
                            os << "Enemy sends L" << endl;
                            enemy_cho = 3;
                            my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        }
                    }
                    else
                    {
                       if(!change_ene(os, vec_hp, enemy_cho))
                        {
                            my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                            if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                            {
                                if(!sing(enemy_cho, os, my_cho, act, my_ch, condition, time, vec_hp, me))
                                {
                                    enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                                }
                                else
                                {
                                    my_cho = my_cho;
                                }
                            }
                            else
                            {
                                my_cho = my_cho;
                            }
                        }
                        else
                        {
                            os << "Enemy sends L" << endl;
                            enemy_cho = 3;
                            my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        }
                    }
                }
                else if(act == 3)
                {
                    if(!change_ene(os, vec_hp, enemy_cho))
                    {
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                        {
                            if(!sing(enemy_cho, os, my_cho, act, my_ch, condition, time, vec_hp, me))
                            {
                                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                            }
                            else
                            {
                                my_cho = my_cho;
                            }
                        }
                        else
                        {
                            my_cho = my_cho;
                        }
                    }
                    else
                    {
                        os << "Enemy sends L" << endl;
                        enemy_cho = 3;
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                }
                else
                {
                    if(!change_ene(os, vec_hp, enemy_cho))
                    {
                       enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                       if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                        {
                            my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        }
                        else
                        {
                            my_cho = my_cho;
                        }
                    }
                    else
                    {
                        os << "Enemy sends L" << endl;
                        enemy_cho = 3;
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                }
            }
        }
    }
    else if(my_ch[my_cho - 1] == 4)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Quick, 2 for Volt, 3 for Thunder): " ;
            is >> act;
        }
        if(condition[my_cho] != 0 && act != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            if(!change_ene(os, vec_hp, enemy_cho))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                os << "Enemy sends L" << endl;
                enemy_cho = 3;
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        if(enemy_cho == 3)
        {
            if(condition[0] <= 0 && vec_hp[my_ch[my_cho - 1] - 1] >= 18)
            {
                if(!change_ene(os, vec_hp, enemy_cho))
                {
                    enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                    else
                    {
                        my_cho = my_cho;
                    }
                }
                else
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
            else
            {
                if(!change_ene(os, vec_hp, enemy_cho))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        if(!sing(enemy_cho, os, my_cho, act, my_ch, condition, time, vec_hp, me))
                        {
                            enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        }
                        else
                        {
                            my_cho = my_cho;
                        }
                    }
                    else
                    {
                        my_cho = my_cho;
                    }
                }
                else
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
        }
        else
        {
            if(!change_ene(os, vec_hp, enemy_cho))
            {
                my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                {
                    if(!sing(enemy_cho, os, my_cho, act, my_ch, condition, time, vec_hp, me))
                    {
                        enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                    else
                    {
                        my_cho = my_cho;
                    }
                }
                else
                {
                    my_cho = my_cho;
                }
            }
            else
            {
                os << "Enemy sends L" << endl;
                enemy_cho = 3;
                my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
        }

    }
    else if(my_ch[my_cho - 1] == 5)
    {
        while(act < 0 || act >= 4)
        {
            os << "Select the skill (0 for back, 1 for Slap, 2 for Sing, 3 for Paint): " ;
            is >> act;
        }
        if(condition[my_cho] != 0 && act != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            if(!change_ene(os, vec_hp, enemy_cho))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                os << "Enemy sends L" << endl;
                enemy_cho = 3;
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        if(!change_ene(os, vec_hp, enemy_cho))
        {
            enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
            {
                my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                my_cho = my_cho;
            }
            if(act == 3)
            {
                os << "Your D uses Paint! Failure" << endl;
            }
        }
        else
        {
            os << "Enemy sends L" << endl;
            enemy_cho = 3;
            my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            if(act == 3)
            {
               if(enemy_cho == 1)
               {
                   os << "Your D use Paint! Enemy's D is painted" << endl;
                   condition[enemy_cho + 9] = 1;
               }
               else if(enemy_cho == 2)
                {
                   os << "Your D use Paint! Enemy's W is painted" << endl;
                   condition[enemy_cho + 9] = 1;
               }
               else if(enemy_cho == 3)
                {
                   os << "Your D use Paint! Enemy's L is painted" << endl;
                   condition[enemy_cho + 9] = 1;
               }
            }
        }
    }
    return true;
}

//进行宠物对决
void action(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act)
{
    int before = 0;
    if(my_dead(vec_hp, my_ch) <= 1)
    {
        act2(is, os, act);
        run(os, round, act);
        if(act == 1)
        {
           if(change_ene(os, vec_hp, enemy_cho))
            {
                if(time[my_cho - 1] != 0)
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    if(my_ch[my_cho - 1] == 1)
                    {
                        while(act < 0 || act >= 4)
                        {
                            os << "Select the skill (0 for back, 1 for Tackle, 2 for Leaf, 3 for Synthesis): " ;
                            is >> act;
                        }
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        while(act < 0 || act >= 4)
                        {
                            os << "Select the skill (0 for back, 1 for Claw, 2 for Flame, 3 for Sunny): " ;
                            is >> act;
                        }
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        while(act < 0 || act >= 4)
                        {
                            os << "Select the skill (0 for back, 1 for Tackle, 2 for Stream, 3 for Rainy): " ;
                            is >> act;
                        }
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        while(act < 0 || act >= 4)
                        {
                            os << "Select the skill (0 for back, 1 for Quick, 2 for Volt, 3 for Thunder): " ;
                            is >> act;
                        }
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        while(act < 0 || act >= 4)
                        {
                            os << "Select the skill (0 for back, 1 for Slap, 2 for Sing, 3 for Paint): " ;
                            is >> act;
                        }
                    }
                    if(act == 0)
                    {
                        act = -1;
                        action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                    else
                    {
                        act = -1;
                        os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
                        dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                        show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                    }
                }
                else
                {
                    if(!my_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
                    {
                        act = -1;
                        action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                    else
                    {
                        my_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                        show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                    }
                }
            }
            else
            {
                if(!attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
                {
                    act = -1;
                    action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
                else
                {
                    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                }
            }
        }
        else if(act == 2)
        {
            if(!changeall(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, before))
            {
                act = -1;   //很关键！
                action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                if(change_ene(os, vec_hp, enemy_cho))
                {
                    os << "Enemy sends L" << endl;
                    enemy_cho = 3;
                    dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                }
                else
                {
                    if(time[enemy_cho + 3] == 0)
                    {
                        enemy_attack2(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, before);
                    }
                    else
                    {
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's D is sleeping" << endl;
                        }
                        if(enemy_cho == 2)
                        {
                            os << "Enemy's W is sleeping" << endl;
                        }
                        if(enemy_cho == 3)
                        {
                            os << "Enemy's L is sleeping" << endl;
                        }
                    }
                    dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                }
            }
        }
    }
    else if(my_dead(vec_hp, my_ch) == 2)
    {
        act1(is, os, act);
        run(os, round, act);
        if(change_ene(os, vec_hp, enemy_cho))
        {
            if(time[my_cho - 1] != 0)
            {
                os << "Enemy sends L" << endl;
                enemy_cho = 3;
                if(my_ch[my_cho - 1] == 1)
                {
                    while(act < 0 || act >= 4)
                    {
                        os << "Select the skill (0 for back, 1 for Tackle, 2 for Leaf, 3 for Synthesis): " ;
                        is >> act;
                    }
                }
                else if(my_ch[my_cho - 1] == 2)
                {
                    while(act < 0 || act >= 4)
                    {
                        os << "Select the skill (0 for back, 1 for Claw, 2 for Flame, 3 for Sunny): " ;
                        is >> act;
                    }
                }
                else if(my_ch[my_cho - 1] == 3)
                {
                    while(act < 0 || act >= 4)
                    {
                        os << "Select the skill (0 for back, 1 for Tackle, 2 for Stream, 3 for Rainy): " ;
                        is >> act;
                    }
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    while(act < 0 || act >= 4)
                    {
                        os << "Select the skill (0 for back, 1 for Quick, 2 for Volt, 3 for Thunder): " ;
                        is >> act;
                    }
                }
                else if(my_ch[my_cho - 1] == 4)
                {
                    while(act < 0 || act >= 4)
                    {
                        os << "Select the skill (0 for back, 1 for Slap, 2 for Sing, 3 for Paint): " ;
                        is >> act;
                    }
                }
                if(act == 0)
                {
                    act = -1;
                    action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
                else
                {
                    act = -1;
                    os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
                    dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                }
            }
            else
            {
                if(!my_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
                {
                    act = -1;
                    action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
                else
                {
                    my_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                }
            }
        }
        else
        {
            if(!attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
            {
                act = -1;
                action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
            }
        }
    }
}

//回合的进行
void play(istream& is, ostream& os)
{
    os << "Welcome to Battle of Pets 2!" << endl;
    os << "Enemy has D, W and L." << endl;
    os << "You can select three from five (1 for W, 2 for L, 3 for G, 4 for Q, 5 for D)." << endl;
    map<int, string> me = {{1, "W"}, {2, "L"}, {3, "G"}, {4, "Q"}, {5, "D"}};
    vector<int> vec_hp = {110, 100, 100, 90, 120, 120, 110, 100};
    int enemy_cho = 1;
    int my_cho = 0;
    while(my_cho <= 0 || my_cho >= 6)
    {
        os << "Select your 1st pet: ";
        is >> my_cho;
    }
    int pmy_cho = 0;
    while((pmy_cho <= 0 || pmy_cho >= 6) || my_cho == pmy_cho)
    {
        os << "Select your 2nd pet: ";
        is >> pmy_cho;
    }
    int ppmy_cho = 0;
    while((ppmy_cho <= 0 || ppmy_cho >= 6) || my_cho == ppmy_cho || pmy_cho == ppmy_cho)
    {
        os << "Select your 3rd pet: ";
        is >> ppmy_cho;
    }
    os << "You have " << me[my_cho] << ", " << me[pmy_cho] << " and " << me[ppmy_cho] << "." << endl;
    start(os, my_cho);
    int round = 1;
    vector<int> my_ch;
    my_ch.push_back(my_cho);
    my_ch.push_back(pmy_cho);
    my_ch.push_back(ppmy_cho);
    my_cho = 1;
    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
    os << "Battle starts!" << endl;
    vector<int> condition = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 用来记录睡眠，涂鸦，和天气
    vector<int> time = {0, 0, 0, 0, 0, 0, 0}; // 用来记录回合数的
    while(round <= 100)
    {
        os << "-------------------------------------------------" << endl;
        if(condition[0] != 0 && time[0] == 0)
        {
            os << "Weather becomes normal" << endl;
            condition[0] = 0;
        }
        if(time[enemy_cho + 3] == 0 && condition[enemy_cho + 6] != 0)
        {
            if(enemy_cho == 1)
            {
                os << "Enemy's D wakes up" << endl;
            }
            if(enemy_cho == 2)
            {
                os << "Enemy's W wakes up" << endl;
            }
            if(enemy_cho == 3)
            {
                os << "Enemy's L wakes up" << endl;
            }
            condition[enemy_cho + 6] = 0;
        }
        if(time[my_cho] == 0 && condition[my_cho] != 0)
        {
            os << "Your " << me[my_ch[my_cho - 1]] << " wakes up" << endl;
            condition[my_cho] = 0;
        }
        int act = -1;
        os << "Round " << round << endl;
        action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
        if(time[0] > 0)
        {
            time[0] -= 1;
        }
        else if(time[0] < 0)
        {
            time[0] += 1;
        }
        if(time[enemy_cho + 3] != 0)
        {
            time[enemy_cho + 3] -= 1;
        }
        if(time[my_cho] != 0)
        {
            time[my_cho] -= 1;
        }
        round += 1;
    }
}

int main()
{
    play(cin, cout);
    return 0;
}

