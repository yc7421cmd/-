#include <iostream>
#include<vector>
#include <string>
#include<map>
#include<cstdlib>
#include<ctime>

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

//敌方用药
bool revival(ostream& os, int& enemy_cho, vector<int>& vec_hp, int& number)
{
    if(number == 1 && enemy_cho != 2)
    {
        if(vec_hp[6] <= 0 &&(vec_hp[5] > 0 || vec_hp[7] > 0))
        {
            os << "Enemy uses Revival Potion on G" << endl;
            vec_hp[6] = 50;
            return true;
        }
    }
    return false;
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

//敌方死亡后改变宠物
void enemy_change(int& enemy_cho, vector<int> vec_hp, ostream& os)
{
    if(enemy_cho == 1)
    {
        os << "Enemy's W is beaten" << endl;
    }
    if(enemy_cho == 2)
    {
        os << "Enemy's G is beaten" << endl;
    }
    if(enemy_cho == 3)
    {
        os << "Enemy's Q is beaten" << endl;
    }
    if((vec_hp[5] <= 0 || vec_hp[7] <= 0) && vec_hp[6] > 0)
    {
        os << "Enemy sends G" << endl;
        enemy_cho = 2;
    }
    else if(vec_hp[6] <= 0 && vec_hp[5] > 0)
    {
        os << "Enemy sends W" << endl;
        enemy_cho = 1;
    }
    else
    {
        if(vec_hp[5] > 0)
        {
            os << "Enemy sends W" << endl;
            enemy_cho = 1;
        }
        else if(vec_hp[6] > 0)
        {
            os << "Enemy sends G" << endl;
            enemy_cho = 2;
        }
        else if(vec_hp[7] > 0)
        {
            os << "Enemy sends Q" << endl;
            enemy_cho = 3;
        }
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
void start(ostream& os, int me, int enemy_cho)
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
    switch(enemy_cho)
    {
    case 1:
        os << "Enemy starts with W" <<  endl;
        break;
    case 2:
        os << "Enemy starts with G" << endl;
        break;
    case 3:
        os << "Enemy starts with Q" << endl;
        break;
    default:
        break;
    }
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
            os << "Enemy's W: HP " << vec_hp[5] << endl;
            break;
        case 2:
            os << "Enemy's G: HP " << vec_hp[6] << endl;
            break;
        case 3:
            os << "Enemy's Q: HP " << vec_hp[7] << endl;
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
bool change_ene(ostream& os, vector<int>& vec_hp, int& enemy_cho, vector<int>& my_ch, int& my_cho, vector<int>& condition)
{
    if(enemy_cho == 2)
    {
        if(vec_hp[5] >= 0 && (my_ch[my_cho - 1] == 4 || (my_ch[my_cho - 1] == 2 && condition[0] == -1)))
        {
            enemy_cho = 1;
            return true;
        }
        else if(vec_hp[5] == 0 && condition[0] == -1 && vec_hp[7] >= 0)
        {
            enemy_cho = 3;
            return true;
        }
    }
    else if(enemy_cho == 3)
    {
        if(my_ch[my_cho - 1] == 2 && vec_hp[6] >= 0)
        {
            enemy_cho = 2;
            return true;
        }
        else if(my_ch[my_cho - 1] != 2 && condition[0] >= 0 && vec_hp[5] >= 0)
        {
            enemy_cho = 1;
            return true;
        }
    }
    return false;
}

//敌方主动更换宠物的输出
void output(ostream& os, int& enemy_cho)
{
    if(enemy_cho == 1)
    {
        os << "Enemy sends W" << endl;
    }
    else if(enemy_cho == 2)
    {
        os << "Enemy sends G" << endl;
    }
    else if(enemy_cho == 3)
    {
        os << "Enemy sends Q" << endl;
    }
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's G wakes up" << endl;
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
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's Q wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 29" << endl;
                    vec_hp[enemy_cho + 4] -= 29;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 29" << endl;
                    vec_hp[enemy_cho + 4] -= 29;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's G wakes up" << endl;
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
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's Q wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
                }
                else if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 7" << endl;
                    vec_hp[enemy_cho + 4] -= 7;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 10" << endl;
                    os << "Enemy's W wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
                }
                else if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 7" << endl;
                    os << "Enemy's G wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 7;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    os << "Enemy's Q wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                else if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    os << "Enemy's W wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                else if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 14" << endl;
                    os << "Enemy's G wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 40" << endl;
                    os << "Enemy's Q wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 13" << endl;
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
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's G wakes up" << endl;
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
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's Q wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 26" << endl;
                    vec_hp[enemy_cho + 4] -= 26;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 26" << endl;
                    vec_hp[enemy_cho + 4] -= 26;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's G wakes up" << endl;
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
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's Q wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 9" << endl;
                       vec_hp[enemy_cho + 4] -= 9;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                       vec_hp[enemy_cho + 4] -= 24;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 5" << endl;
                       vec_hp[enemy_cho + 4] -= 5;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                       vec_hp[enemy_cho + 4] -= 72;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 26" << endl;
                       vec_hp[enemy_cho + 4] -= 26;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 36" << endl;
                        vec_hp[enemy_cho + 4] -= 36;
                   }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 9" << endl;
                       vec_hp[enemy_cho + 4] -= 9;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                       vec_hp[enemy_cho + 4] -= 24;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 5" << endl;
                       vec_hp[enemy_cho + 4] -= 5;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                       vec_hp[enemy_cho + 4] -= 72;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 26" << endl;
                       vec_hp[enemy_cho + 4] -= 26;
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
                        os << "Enemy's W wakes up" << endl;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 96" << endl;
                       vec_hp[enemy_cho + 4] -= 96;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 17" << endl;
                       vec_hp[enemy_cho + 4] -= 17;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                        vec_hp[enemy_cho + 4] -= 48;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 9" << endl;
                       vec_hp[enemy_cho + 4] -= 9;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                        vec_hp[enemy_cho + 4] -= 24;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 144" << endl;
                       vec_hp[enemy_cho + 4] -= 144;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 53" << endl;
                       vec_hp[enemy_cho + 4] -= 53;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                        vec_hp[enemy_cho + 4] -= 72;
                   }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
               if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 96" << endl;
                       vec_hp[enemy_cho + 4] -= 96;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 17" << endl;
                       vec_hp[enemy_cho + 4] -= 17;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                        vec_hp[enemy_cho + 4] -= 48;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 9" << endl;
                       vec_hp[enemy_cho + 4] -= 9;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                        vec_hp[enemy_cho + 4] -= 24;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 144" << endl;
                       vec_hp[enemy_cho + 4] -= 144;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 53" << endl;
                       vec_hp[enemy_cho + 4] -= 53;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                        vec_hp[enemy_cho + 4] -= 72;
                   }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's W wakes up" << endl;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                    }
                }
                condition[enemy_cho + 6] = 0;
                time[enemy_cho + 3] = 0;
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
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
                if(enemy_cho == 2)
                {
                    os << "14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "29" << endl;
                    vec_hp[enemy_cho + 4] -= 29;
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
                if(enemy_cho == 2)
                {
                    os << "29" << endl;
                    vec_hp[enemy_cho + 4] -= 29;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 7" << endl;
                        vec_hp[enemy_cho + 4] -= 7;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 5" << endl;
                        vec_hp[enemy_cho + 4] -= 13;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 4" << endl;
                        vec_hp[enemy_cho + 4] -= 5;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 15" << endl;
                        vec_hp[enemy_cho + 4] -= 15;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 11" << endl;
                        vec_hp[enemy_cho + 4] -= 11;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 30" << endl;
                        vec_hp[enemy_cho + 4] -= 30;
                    }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 7" << endl;
                        vec_hp[enemy_cho + 4] -= 7;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 5" << endl;
                        vec_hp[enemy_cho + 4] -= 13;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 4" << endl;
                        vec_hp[enemy_cho + 4] -= 5;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 15" << endl;
                        vec_hp[enemy_cho + 4] -= 15;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 11" << endl;
                        vec_hp[enemy_cho + 4] -= 11;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 30" << endl;
                        vec_hp[enemy_cho + 4] -= 30;
                    }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
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
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 14" << endl;
                        vec_hp[enemy_cho + 4] -= 14;
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
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 7" << endl;
                        vec_hp[enemy_cho + 4] -= 7;
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
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 29" << endl;
                        vec_hp[enemy_cho + 4] -= 29;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 80" << endl;
                        vec_hp[enemy_cho + 4] -= 80;
                    }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 14" << endl;
                        vec_hp[enemy_cho + 4] -= 14;
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
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 7" << endl;
                        vec_hp[enemy_cho + 4] -= 7;
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
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 29" << endl;
                        vec_hp[enemy_cho + 4] -= 29;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 80" << endl;
                        vec_hp[enemy_cho + 4] -= 80;
                    }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "11" << endl;
                    vec_hp[enemy_cho + 4] -= 11;
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
                if(enemy_cho == 2)
                {
                    os << "11" << endl;
                    vec_hp[enemy_cho + 4] -= 11;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "21" << endl;
                    vec_hp[enemy_cho + 4] -= 21;
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
                if(enemy_cho == 2)
                {
                    os << "21" << endl;
                    vec_hp[enemy_cho + 4] -= 21;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                else if(enemy_cho == 2)
                {
                    os << "36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                }
                else if(enemy_cho == 3)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                else if(enemy_cho == 2)
                {
                    os << "36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                }
                else if(enemy_cho == 3)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
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
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else if(enemy_cho == 2)
                {
                    os << "71" << endl;
                    vec_hp[enemy_cho + 4] -= 71;
                }
                else if(enemy_cho == 3)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else if(enemy_cho == 2)
                {
                    os << "71" << endl;
                    vec_hp[enemy_cho + 4] -= 71;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
            if(condition[0] == -1)
            {
                if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "71" << endl;
                        vec_hp[enemy_cho + 4] -= 71;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                }
                else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "71" << endl;
                        vec_hp[enemy_cho + 4] -= 71;
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
                            os << "Enemy's W wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 2)
                        {
                            os << "Enemy's G wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 3)
                        {
                            os << "Enemy's Q wakes up" << endl;
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
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "143" << endl;
                        vec_hp[enemy_cho + 4] -= 143;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                }
                else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "143" << endl;
                        vec_hp[enemy_cho + 4] -= 143;
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
                            os << "Enemy's W wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 2)
                        {
                            os << "Enemy's G wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 3)
                        {
                            os << "Enemy's Q wakes up" << endl;
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
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
                if(enemy_cho == 2)
                {
                    os << "10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "19" << endl;
                    vec_hp[enemy_cho + 4] -= 19;
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
                if(enemy_cho == 2)
                {
                    os << "19" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            os << "Your D uses Sing!";
            if(condition[enemy_cho + 6] != 0)
            {
                os << "Waste" << endl;
            }
            else
            {
                if(enemy_cho == 1)
                {
                    os << " Enemy's W falls asleep" << endl;
                }
                if(enemy_cho == 2)
                {
                    os << " Enemy's G falls asleep" << endl;
                }
                if(enemy_cho == 3)
                {
                    os << " Enemy's Q falls asleep" << endl;
                }
                condition[enemy_cho + 6] = 1;
                time[enemy_cho + 3] = 3;
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
            os << "Your D uses Paint! Enemy's " ;
            if(enemy_cho == 1)
            {
                os << "W is painted" << endl;
            }
            else if(enemy_cho == 2)
            {
                os << "G is painted" << endl;
            }
            else if(enemy_cho == 3)
            {
                os << "Q is painted" << endl;
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
        if(my_ch[my_cho - 1] == 2 && vec_hp[6] <= 0)
        {
            if(vec_hp[5] <= 36)
            {
                os << "Enemy's W uses  Synthesis! Recovery: " ;
                if(condition[0] == 0)
                {
                    os << "33" << endl;
                    vec_hp[5] += 33;
                }
                if(condition[0] == -1)
                {
                    os << "22" << endl;
                    vec_hp[5] += 22;
                }
                if(condition[0] == 1)
                {
                    os << "44" << endl;
                    vec_hp[5] += 44;
                }
            }
            else
            {
                os << "Enemy's W uses Tackle! Damage: ";
                if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else
                    {
                        os << "20" << endl;
                        vec_hp[4] -= 20;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else
                    {
                        os << "20" << endl;
                        vec_hp[4] -= 20;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
                if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "27" << endl;
                        vec_hp[2] -= 27;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else
                    {
                        os << "40" << endl;
                        vec_hp[4] -= 40;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "27" << endl;
                        vec_hp[2] -= 27;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else
                    {
                        os << "40" << endl;
                        vec_hp[4] -= 40;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            }
        }
        else if(my_ch[my_cho - 1] == 1)
        {
            if(vec_hp[5] >= 55)
            {
                os << "Enemy's W uses Tackle! Damage: ";
                if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else
                    {
                        os << "20" << endl;
                        vec_hp[4] -= 20;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else
                    {
                        os << "20" << endl;
                        vec_hp[4] -= 20;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
                if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "27" << endl;
                        vec_hp[2] -= 27;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else
                    {
                        os << "40" << endl;
                        vec_hp[4] -= 40;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "27" << endl;
                        vec_hp[2] -= 27;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else
                    {
                        os << "40" << endl;
                        vec_hp[4] -= 40;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            }
            else
            {
                    os << "Enemy's W uses  Synthesis! Recovery: " ;
                    if(condition[0] == 0)
                    {
                        os << "33" << endl;
                        vec_hp[5] += 33;
                    }
                    if(condition[0] == -1)
                    {
                        os << "22" << endl;
                        vec_hp[5] += 22;
                    }
                    if(condition[0] == 1)
                    {
                        os << "44" << endl;
                        vec_hp[5] += 44;
                    }
            }
        }
        else
        {
            if(vec_hp[5] >= 55 || vec_hp[my_ch[my_cho - 1] - 1] < max_hp)
            {
                os << "Enemy's W uses Leaf! Damage: ";
                if(condition[0] == 0)
                {
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                      if(my_ch[my_cho] == 1)
                      {
                          os << "10" << endl;
                          vec_hp[0] -= 10;
                      }
                      if(my_ch[my_cho] == 2)
                      {
                          os << "10" << endl;
                          vec_hp[0] -= 10;
                      }
                      if(my_ch[my_cho] == 3)
                      {
                          os << "29" << endl;
                          vec_hp[0] -= 29;
                      }
                      if(my_ch[my_cho] == 5)
                      {
                          os << "25" << endl;
                          vec_hp[0] -= 25;
                      }
                      if(my_ch[my_cho] == 4)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho] == 1)
                      {
                          os << "10" << endl;
                          vec_hp[0] -= 10;
                      }
                      if(my_ch[my_cho] == 2)
                      {
                          os << "10" << endl;
                          vec_hp[0] -= 10;
                      }
                      if(my_ch[my_cho] == 3)
                      {
                          os << "29" << endl;
                          vec_hp[0] -= 29;
                      }
                      if(my_ch[my_cho] == 5)
                      {
                          os << "25" << endl;
                          vec_hp[0] -= 25;
                      }
                      if(my_ch[my_cho] == 4)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                    }
                    if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                    {
                        if(my_ch[my_cho] == 1)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      if(my_ch[my_cho] == 2)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      if(my_ch[my_cho] == 3)
                      {
                          os << "57" << endl;
                          vec_hp[0] -= 57;
                      }
                      if(my_ch[my_cho] == 4)
                      {
                          os << "40" << endl;
                          vec_hp[0] -= 40;
                      }
                      if(my_ch[my_cho] == 5)
                      {
                          os << "50" << endl;
                          vec_hp[0] -= 50;
                      }
                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                    {
                        if(my_ch[my_cho] == 1)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      if(my_ch[my_cho] == 2)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      if(my_ch[my_cho] == 3)
                      {
                          os << "57" << endl;
                          vec_hp[0] -= 57;
                      }
                      if(my_ch[my_cho] == 4)
                      {
                          os << "40" << endl;
                          vec_hp[0] -= 40;
                      }
                      if(my_ch[my_cho] == 5)
                      {
                          os << "50" << endl;
                          vec_hp[0] -= 50;
                      }
                       os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                    }

                }
                else if(condition[0] == 1)
                {
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {

                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                    {

                    }
                    if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                    {

                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                    {

                    }
                }
                else if(condition[0] == -1)
                {
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {

                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                    {

                    }
                    if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                    {

                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                    {

                    }
                }
            }
            else
            {
               os << "Enemy's W uses  Synthesis! Recovery: " ;
                if(condition[0] == 0)
                {
                    os << "33" << endl;
                    vec_hp[5] += 33;
                }
                if(condition[0] == -1)
                {
                    os << "22" << endl;
                    vec_hp[5] += 22;
                }
                if(condition[0] == 1)
                {
                    os << "44" << endl;
                    vec_hp[5] += 44;
                }
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
        if(vec_hp[my_ch[my_cho - 1] - 1] < max_hp)
        {
            os << "Enemy's Q uses Quick";
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "11" << endl;
                        vec_hp[2] -= 11;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "19" << endl;
                        vec_hp[4] -= 19;
                    }
                    else
                    {
                        os << "15" << endl;
                        vec_hp[4] -= 15;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "11" << endl;
                        vec_hp[2] -= 11;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "19" << endl;
                        vec_hp[4] -= 19;
                    }
                    else
                    {
                        os << "15" << endl;
                        vec_hp[4] -= 15;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 3)
                {
                    os << "21" << endl;
                    vec_hp[2] -= 21;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "37" << endl;
                    vec_hp[4] -= 37;
                }
                else
                {
                    os << "30" << endl;
                    vec_hp[4] -= 30;
                }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 3)
                {
                    os << "21" << endl;
                    vec_hp[2] -= 21;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "37" << endl;
                    vec_hp[4] -= 37;
                }
                else
                {
                    os << "30" << endl;
                    vec_hp[4] -= 30;
                }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
        }
        else if(my_ch[my_cho - 1] == 2 && vec_hp[6] <= 0)
        {
            os << "Enemy's Q uses Volt! Damage: ";
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "13" << endl;
                        vec_hp[2] -= 13;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "36" << endl;
                        vec_hp[4] -= 36;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "13" << endl;
                        vec_hp[4] -= 13;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "31" << endl;
                        vec_hp[4] -= 31;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "13" << endl;
                        vec_hp[2] -= 13;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "36" << endl;
                        vec_hp[4] -= 36;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "13" << endl;
                        vec_hp[4] -= 13;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "31" << endl;
                        vec_hp[4] -= 31;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "25" << endl;
                        vec_hp[2] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "25" << endl;
                        vec_hp[2] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
        }
        else if(my_ch[my_cho - 1] != 2 && condition[0] >= 0 && vec_hp[5] <= 0)
        {
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "15" << endl;
                        vec_hp[2] -= 15;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "36" << endl;
                        vec_hp[4] -= 36;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "15" << endl;
                        vec_hp[2] -= 15;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "31" << endl;
                        vec_hp[4] -= 31;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "15" << endl;
                        vec_hp[2] -= 15;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "36" << endl;
                        vec_hp[4] -= 36;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "15" << endl;
                        vec_hp[2] -= 15;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "31" << endl;
                        vec_hp[4] -= 31;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "30" << endl;
                        vec_hp[2] -= 30;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "30" << endl;
                        vec_hp[2] -= 30;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "30" << endl;
                        vec_hp[2] -= 30;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "30" << endl;
                        vec_hp[2] -= 30;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
        }
        else if(my_ch[my_cho - 1] != 2 && condition[0] < 0)
        {
            os << "Enemy's Q uses Thunder! Damage: ";
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "25" << endl;
                        vec_hp[2] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "25" << endl;
                        vec_hp[2] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "50" << endl;
                        vec_hp[2] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "100" << endl;
                        vec_hp[4] -= 100;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "143" << endl;
                        vec_hp[4] -= 143;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "125" << endl;
                        vec_hp[4] -= 125;
                    }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "50" << endl;
                        vec_hp[2] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "100" << endl;
                        vec_hp[4] -= 100;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "143" << endl;
                        vec_hp[4] -= 143;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "125" << endl;
                        vec_hp[4] -= 125;
                    }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
        }
    }
    else if(enemy_cho == 2)
    {
        if(condition[0] == 1)
        {
            os << "Enemy's G uses Rainy!Weather becomes rainy" << endl;
            time[0] = 5;
            condition[0] = -1;
        }
        else
        {
            if(my_ch[my_cho - 1] == 3)
            {
               os << "Enemy's G uses Tackle! Damage: " ;
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    os << "14" << endl;
                        vec_hp[2] -= 14;
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                os << "29" << endl;
                        vec_hp[2] -= 29;
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                os << "29" << endl;
                        vec_hp[2] -= 29;
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
            }
            else if((my_ch[my_cho - 1] == 5 || (my_ch[my_cho - 1] == 1 && condition[0] == -1)) && vec_hp[5] <= 0)
            {
               if(condition[0] == -1)
                {
                    os << "Enemy's G uses Stream! Damage: ";
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho - 1] == 1)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "11" << endl;
                            vec_hp[2] -=11;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "38" << endl;
                            vec_hp[2] -= 39;
                        }
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "11" << endl;
                            vec_hp[2] -=11;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "38" << endl;
                            vec_hp[2] -= 39;
                        }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "120" << endl;
                            vec_hp[2] -= 120;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "21" << endl;
                            vec_hp[2] -=21;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "75" << endl;
                            vec_hp[2] -= 75;
                        }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "120" << endl;
                            vec_hp[2] -= 120;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "21" << endl;
                            vec_hp[2] -=21;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "75" << endl;
                            vec_hp[2] -= 75;
                        }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
                }
                if(condition[0] == 0)
                {
                    os << "Enemy's G uses Stream! Damage: ";
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho - 1] == 1)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "7" << endl;
                            vec_hp[2] -=7;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "25" << endl;
                            vec_hp[2] -= 25;
                        }
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "7" << endl;
                            vec_hp[2] -=7;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "25" << endl;
                            vec_hp[2] -= 25;
                        }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "14" << endl;
                            vec_hp[2] -=14;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "40" << endl;
                            vec_hp[2] -= 40;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "50" << endl;
                            vec_hp[2] -= 50;
                        }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                 if(my_ch[my_cho - 1] == 1)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "14" << endl;
                            vec_hp[2] -=14;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "40" << endl;
                            vec_hp[2] -= 40;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "50" << endl;
                            vec_hp[2] -= 50;
                        }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
                }

                if(condition[0] == 1)
                {
                    os << "Enemy's G uses Stream! Damage: ";
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho - 1] == 1)
                        {
                            os << "5" << endl;
                            vec_hp[2] -= 5;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "4" << endl;
                            vec_hp[2] -=4;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "13" << endl;
                            vec_hp[2] -= 13;
                        }
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                        {
                            os << "5" << endl;
                            vec_hp[2] -= 5;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "4" << endl;
                            vec_hp[2] -=4;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "13" << endl;
                            vec_hp[2] -= 13;
                        }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "7" << endl;
                            vec_hp[2] -=7;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "25" << endl;
                            vec_hp[2] -= 25;
                        }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                 if(my_ch[my_cho - 1] == 1)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "7" << endl;
                            vec_hp[2] -=7;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "25" << endl;
                            vec_hp[2] -= 25;
                        }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
                }


            }
            else
            {
                if(condition[0] == -1)
                {
                    os << "Enemy's G uses Stream! Damage: ";
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho - 1] == 1)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "11" << endl;
                            vec_hp[2] -=11;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "38" << endl;
                            vec_hp[2] -= 39;
                        }
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "11" << endl;
                            vec_hp[2] -=11;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "38" << endl;
                            vec_hp[2] -= 39;
                        }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "120" << endl;
                            vec_hp[2] -= 120;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "21" << endl;
                            vec_hp[2] -=21;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "75" << endl;
                            vec_hp[2] -= 75;
                        }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "120" << endl;
                            vec_hp[2] -= 120;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "21" << endl;
                            vec_hp[2] -=21;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "75" << endl;
                            vec_hp[2] -= 75;
                        }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
                }
                else
                {
                    os << "Enemy's G uses Rainy!Weather becomes rainy" << endl;
                    time[0] = 5;
                    condition[0] = -1;
                }
            }
        }
    }
}

bool enemy_attack2(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act)
{
    if(enemy_cho == 1)
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
        if(my_ch[my_cho - 1] == 2 && vec_hp[6] <= 0)
        {
            if(vec_hp[5] <= 36)
            {
                os << "Enemy's W uses  Synthesis! Recovery: " ;
                if(condition[0] == 0)
                {
                    os << "33" << endl;
                    vec_hp[5] += 33;
                }
                if(condition[0] == -1)
                {
                    os << "22" << endl;
                    vec_hp[5] += 22;
                }
                if(condition[0] == 1)
                {
                    os << "44" << endl;
                    vec_hp[5] += 44;
                }
            }
            else
            {
                os << "Enemy's W uses Tackle! Damage: ";
                if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else
                    {
                        os << "20" << endl;
                        vec_hp[4] -= 20;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else
                    {
                        os << "20" << endl;
                        vec_hp[4] -= 20;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
                if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "27" << endl;
                        vec_hp[2] -= 27;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else
                    {
                        os << "40" << endl;
                        vec_hp[4] -= 40;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "27" << endl;
                        vec_hp[2] -= 27;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else
                    {
                        os << "40" << endl;
                        vec_hp[4] -= 40;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            }
        }
        else if(my_ch[my_cho - 1] == 1)
        {
            if(vec_hp[5] >= 55)
            {
                os << "Enemy's W uses Tackle! Damage: ";
                if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else
                    {
                        os << "20" << endl;
                        vec_hp[4] -= 20;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else
                    {
                        os << "20" << endl;
                        vec_hp[4] -= 20;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
                if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "27" << endl;
                        vec_hp[2] -= 27;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else
                    {
                        os << "40" << endl;
                        vec_hp[4] -= 40;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "27" << endl;
                        vec_hp[2] -= 27;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else
                    {
                        os << "40" << endl;
                        vec_hp[4] -= 40;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            }
            else
            {
                    os << "Enemy's W uses  Synthesis! Recovery: " ;
                    if(condition[0] == 0)
                    {
                        os << "33" << endl;
                        vec_hp[5] += 33;
                    }
                    if(condition[0] == -1)
                    {
                        os << "22" << endl;
                        vec_hp[5] += 22;
                    }
                    if(condition[0] == 1)
                    {
                        os << "44" << endl;
                        vec_hp[5] += 44;
                    }
            }
        }
        else
        {
            if(vec_hp[5] >= 55 || vec_hp[my_ch[my_cho - 1] - 1] < max_hp)
            {
                os << "Enemy's W uses Leaf! Damage: ";
                if(condition[0] == 0)
                {
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                      if(my_ch[my_cho] == 1)
                      {
                          os << "10" << endl;
                          vec_hp[0] -= 10;
                      }
                      if(my_ch[my_cho] == 2)
                      {
                          os << "10" << endl;
                          vec_hp[0] -= 10;
                      }
                      if(my_ch[my_cho] == 3)
                      {
                          os << "29" << endl;
                          vec_hp[0] -= 29;
                      }
                      if(my_ch[my_cho] == 5)
                      {
                          os << "25" << endl;
                          vec_hp[0] -= 25;
                      }
                      if(my_ch[my_cho] == 4)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho] == 1)
                      {
                          os << "10" << endl;
                          vec_hp[0] -= 10;
                      }
                      if(my_ch[my_cho] == 2)
                      {
                          os << "10" << endl;
                          vec_hp[0] -= 10;
                      }
                      if(my_ch[my_cho] == 3)
                      {
                          os << "29" << endl;
                          vec_hp[0] -= 29;
                      }
                      if(my_ch[my_cho] == 5)
                      {
                          os << "25" << endl;
                          vec_hp[0] -= 25;
                      }
                      if(my_ch[my_cho] == 4)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                    }
                    if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                    {
                        if(my_ch[my_cho] == 1)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      if(my_ch[my_cho] == 2)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      if(my_ch[my_cho] == 3)
                      {
                          os << "57" << endl;
                          vec_hp[0] -= 57;
                      }
                      if(my_ch[my_cho] == 4)
                      {
                          os << "40" << endl;
                          vec_hp[0] -= 40;
                      }
                      if(my_ch[my_cho] == 5)
                      {
                          os << "50" << endl;
                          vec_hp[0] -= 50;
                      }
                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                    {
                        if(my_ch[my_cho] == 1)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      if(my_ch[my_cho] == 2)
                      {
                          os << "20" << endl;
                          vec_hp[0] -= 20;
                      }
                      if(my_ch[my_cho] == 3)
                      {
                          os << "57" << endl;
                          vec_hp[0] -= 57;
                      }
                      if(my_ch[my_cho] == 4)
                      {
                          os << "40" << endl;
                          vec_hp[0] -= 40;
                      }
                      if(my_ch[my_cho] == 5)
                      {
                          os << "50" << endl;
                          vec_hp[0] -= 50;
                      }
                       os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                    }

                }
                else if(condition[0] == 1)
                {
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {

                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                    {

                    }
                    if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                    {

                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                    {

                    }
                }
                else if(condition[0] == -1)
                {
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {

                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                    {

                    }
                    if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
                    {

                    }
                    if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
                    {

                    }
                }
            }
            else
            {
               os << "Enemy's W uses  Synthesis! Recovery: " ;
                if(condition[0] == 0)
                {
                    os << "33" << endl;
                    vec_hp[5] += 33;
                }
                if(condition[0] == -1)
                {
                    os << "22" << endl;
                    vec_hp[5] += 22;
                }
                if(condition[0] == 1)
                {
                    os << "44" << endl;
                    vec_hp[5] += 44;
                }
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
        if(vec_hp[my_ch[my_cho - 1] - 1] < max_hp)
        {
            os << "Enemy's Q uses Quick";
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "11" << endl;
                        vec_hp[2] -= 11;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "19" << endl;
                        vec_hp[4] -= 19;
                    }
                    else
                    {
                        os << "15" << endl;
                        vec_hp[4] -= 15;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 3)
                    {
                        os << "11" << endl;
                        vec_hp[2] -= 11;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "19" << endl;
                        vec_hp[4] -= 19;
                    }
                    else
                    {
                        os << "15" << endl;
                        vec_hp[4] -= 15;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 3)
                {
                    os << "21" << endl;
                    vec_hp[2] -= 21;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "37" << endl;
                    vec_hp[4] -= 37;
                }
                else
                {
                    os << "30" << endl;
                    vec_hp[4] -= 30;
                }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 3)
                {
                    os << "21" << endl;
                    vec_hp[2] -= 21;
                }
                else if(my_ch[my_cho - 1] == 5)
                {
                    os << "37" << endl;
                    vec_hp[4] -= 37;
                }
                else
                {
                    os << "30" << endl;
                    vec_hp[4] -= 30;
                }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
            return true;
        }
        else if(my_ch[my_cho - 1] == 2 && vec_hp[6] <= 0)
        {
            os << "Enemy's Q uses Volt! Damage: ";
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "13" << endl;
                        vec_hp[2] -= 13;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "36" << endl;
                        vec_hp[4] -= 36;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "13" << endl;
                        vec_hp[4] -= 13;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "31" << endl;
                        vec_hp[4] -= 31;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "13" << endl;
                        vec_hp[2] -= 13;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "36" << endl;
                        vec_hp[4] -= 36;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "13" << endl;
                        vec_hp[4] -= 13;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "31" << endl;
                        vec_hp[4] -= 31;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "25" << endl;
                        vec_hp[2] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "25" << endl;
                        vec_hp[2] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
        }
        else if(my_ch[my_cho - 1] != 2 && condition[0] >= 0 && vec_hp[5] <= 0)
        {
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "15" << endl;
                        vec_hp[2] -= 15;
                        return true;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "36" << endl;
                        vec_hp[4] -= 36;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "15" << endl;
                        vec_hp[2] -= 15;
                        return true;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "31" << endl;
                        vec_hp[4] -= 31;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "15" << endl;
                        vec_hp[2] -= 15;
                        return true;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "36" << endl;
                        vec_hp[4] -= 36;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "15" << endl;
                        vec_hp[2] -= 15;
                        return true;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "31" << endl;
                        vec_hp[4] -= 31;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "30" << endl;
                        vec_hp[2] -= 30;
                        return true;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "30" << endl;
                        vec_hp[2] -= 30;
                        return true;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "30" << endl;
                        vec_hp[2] -= 30;
                        return true;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "Enemy's Q uses Quick! Damage: ";
                        os << "30" << endl;
                        vec_hp[2] -= 30;
                        return true;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "Enemy's Q uses Volt! Damage: ";
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
        }
        else if(my_ch[my_cho - 1] != 2 && condition[0] < 0)
        {
            os << "Enemy's Q uses Thunder! Damage: ";
            if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
            {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "25" << endl;
                        vec_hp[2] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
                }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                    {
                        os << "25" << endl;
                        vec_hp[2] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "71" << endl;
                        vec_hp[4] -= 71;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "25" << endl;
                        vec_hp[4] -= 25;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "63" << endl;
                        vec_hp[4] -= 63;
                    }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "50" << endl;
                        vec_hp[2] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "100" << endl;
                        vec_hp[4] -= 100;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "143" << endl;
                        vec_hp[4] -= 143;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "125" << endl;
                        vec_hp[4] -= 125;
                    }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                    {
                        os << "50" << endl;
                        vec_hp[2] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 2)
                    {
                        os << "100" << endl;
                        vec_hp[4] -= 100;
                    }
                    else if(my_ch[my_cho - 1] == 3)
                    {
                        os << "143" << endl;
                        vec_hp[4] -= 143;
                    }
                    else if(my_ch[my_cho - 1] == 4)
                    {
                        os << "50" << endl;
                        vec_hp[4] -= 50;
                    }
                    else if(my_ch[my_cho - 1] == 5)
                    {
                        os << "125" << endl;
                        vec_hp[4] -= 125;
                    }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
        }
    }
    else if(enemy_cho == 2)
    {
        if(condition[0] == 1)
        {
            os << "Enemy's G uses Rainy!Weather becomes rainy" << endl;
            time[0] = 5;
            condition[0] = -1;
            return true;
        }
        else
        {
            if(my_ch[my_cho - 1] == 3)
            {
               os << "Enemy's G uses Tackle! Damage: " ;
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        os << "14" << endl;
                        vec_hp[2] -= 14;
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    os << "14" << endl;
                        vec_hp[2] -= 14;
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                os << "29" << endl;
                        vec_hp[2] -= 29;
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                os << "29" << endl;
                        vec_hp[2] -= 29;
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
            }
            else if((my_ch[my_cho - 1] == 5 || (my_ch[my_cho - 1] == 1 && condition[0] == -1)) && vec_hp[5] <= 0)
            {
               if(condition[0] == -1)
                {
                    os << "Enemy's G uses Stream! Damage: ";
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho - 1] == 1)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "11" << endl;
                            vec_hp[2] -=11;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "38" << endl;
                            vec_hp[2] -= 39;
                        }
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "11" << endl;
                            vec_hp[2] -=11;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "38" << endl;
                            vec_hp[2] -= 39;
                        }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "120" << endl;
                            vec_hp[2] -= 120;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "21" << endl;
                            vec_hp[2] -=21;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "75" << endl;
                            vec_hp[2] -= 75;
                        }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "120" << endl;
                            vec_hp[2] -= 120;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "21" << endl;
                            vec_hp[2] -=21;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "75" << endl;
                            vec_hp[2] -= 75;
                        }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
                }
                if(condition[0] == 0)
                {
                    os << "Enemy's G uses Stream! Damage: ";
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho - 1] == 1)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "7" << endl;
                            vec_hp[2] -=7;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "25" << endl;
                            vec_hp[2] -= 25;
                        }
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "7" << endl;
                            vec_hp[2] -=7;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "25" << endl;
                            vec_hp[2] -= 25;
                        }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "14" << endl;
                            vec_hp[2] -=14;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "40" << endl;
                            vec_hp[2] -= 40;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "50" << endl;
                            vec_hp[2] -= 50;
                        }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                 if(my_ch[my_cho - 1] == 1)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "14" << endl;
                            vec_hp[2] -=14;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "40" << endl;
                            vec_hp[2] -= 40;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "50" << endl;
                            vec_hp[2] -= 50;
                        }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
                }

                if(condition[0] == 1)
                {
                    os << "Enemy's G uses Stream! Damage: ";
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho - 1] == 1)
                        {
                            os << "5" << endl;
                            vec_hp[2] -= 5;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "4" << endl;
                            vec_hp[2] -=4;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "13" << endl;
                            vec_hp[2] -= 13;
                        }
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                        {
                            os << "5" << endl;
                            vec_hp[2] -= 5;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "4" << endl;
                            vec_hp[2] -=4;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "13" << endl;
                            vec_hp[2] -= 13;
                        }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "7" << endl;
                            vec_hp[2] -=7;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "25" << endl;
                            vec_hp[2] -= 25;
                        }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                 if(my_ch[my_cho - 1] == 1)
                        {
                            os << "10" << endl;
                            vec_hp[2] -= 10;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "7" << endl;
                            vec_hp[2] -=7;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "20" << endl;
                            vec_hp[2] -= 20;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "25" << endl;
                            vec_hp[2] -= 25;
                        }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
                }


            }
            else
            {
                if(condition[0] == -1)
                {
                    os << "Enemy's G uses Stream! Damage: ";
                    if(time[my_cho] == 0 && condition[my_cho + 3] == 0)
                    {
                        if(my_ch[my_cho - 1] == 1)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "11" << endl;
                            vec_hp[2] -=11;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "38" << endl;
                            vec_hp[2] -= 39;
                        }
                    }
                if(time[my_cho] != 0 && condition[my_cho + 3] == 0)
                {
                    if(my_ch[my_cho - 1] == 1)
                        {
                            os << "15" << endl;
                            vec_hp[2] -= 15;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "11" << endl;
                            vec_hp[2] -=11;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "38" << endl;
                            vec_hp[2] -= 39;
                        }
                    os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
                }
            if(time[my_cho] == 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "120" << endl;
                            vec_hp[2] -= 120;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "21" << endl;
                            vec_hp[2] -=21;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "75" << endl;
                            vec_hp[2] -= 75;
                        }
            }
            if(time[my_cho] != 0 && condition[my_cho + 3] != 0)
            {
                if(my_ch[my_cho - 1] == 1)
                        {
                            os << "30" << endl;
                            vec_hp[2] -= 30;
                        }
                        if(my_ch[my_cho - 1] == 2)
                        {
                            os << "120" << endl;
                            vec_hp[2] -= 120;
                        }
                        if(my_ch[my_cho - 1] == 3)
                        {
                            os << "21" << endl;
                            vec_hp[2] -=21;
                        }
                        if(my_ch[my_cho - 1] == 4)
                        {
                            os << "60" << endl;
                            vec_hp[2] -= 60;
                        }
                        if(my_ch[my_cho - 1] == 5)
                        {
                            os << "75" << endl;
                            vec_hp[2] -= 75;
                        }
                os << "Your " << me[my_ch[my_cho - 1] - 1] << " wakes up" << endl;
            }
                }
                else
                {
                    os << "Enemy's G uses Rainy!Weather becomes rainy" << endl;
                    time[0] = 5;
                    condition[0] = -1;
                    return true;
                }
            }
        }
    }
    return false;
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's G wakes up" << endl;
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
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's Q wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 29" << endl;
                    vec_hp[enemy_cho + 4] -= 29;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Tackle! Damage: 29" << endl;
                    vec_hp[enemy_cho + 4] -= 29;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's G wakes up" << endl;
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
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's Q wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
                }
                else if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 7" << endl;
                    vec_hp[enemy_cho + 4] -= 7;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 10" << endl;
                    os << "Enemy's W wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
                }
                else if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 7" << endl;
                    os << "Enemy's G wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 7;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    os << "Enemy's Q wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                else if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 40" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 1)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 20" << endl;
                    os << "Enemy's W wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 20;
                }
                else if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 14" << endl;
                    os << "Enemy's G wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Leaf! Damage: 40" << endl;
                    os << "Enemy's Q wakes up" << endl;
                    vec_hp[enemy_cho + 4] -= 40;
                }
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 13" << endl;
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
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's G wakes up" << endl;
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
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's Q wakes up" << endl;
                        }
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 26" << endl;
                    vec_hp[enemy_cho + 4] -= 26;
                }
                else
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(enemy_cho == 2)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " uses Claw! Damage: 26" << endl;
                    vec_hp[enemy_cho + 4] -= 26;
                    if(vec_hp[enemy_cho + 4] > 0)
                    {
                       os << "Enemy's G wakes up" << endl;
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
                        if(enemy_cho == 1)
                        {
                            os << "Enemy's W wakes up" << endl;
                        }
                        else
                        {
                            os << "Enemy's Q wakes up" << endl;
                        }
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 9" << endl;
                       vec_hp[enemy_cho + 4] -= 9;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                       vec_hp[enemy_cho + 4] -= 24;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 5" << endl;
                       vec_hp[enemy_cho + 4] -= 5;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                       vec_hp[enemy_cho + 4] -= 72;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 26" << endl;
                       vec_hp[enemy_cho + 4] -= 26;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 36" << endl;
                        vec_hp[enemy_cho + 4] -= 36;
                   }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 9" << endl;
                       vec_hp[enemy_cho + 4] -= 9;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                       vec_hp[enemy_cho + 4] -= 24;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 5" << endl;
                       vec_hp[enemy_cho + 4] -= 5;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                       vec_hp[enemy_cho + 4] -= 72;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 26" << endl;
                       vec_hp[enemy_cho + 4] -= 26;
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
                        os << "Enemy's W wakes up" << endl;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
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
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 96" << endl;
                       vec_hp[enemy_cho + 4] -= 96;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 17" << endl;
                       vec_hp[enemy_cho + 4] -= 17;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                        vec_hp[enemy_cho + 4] -= 48;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 9" << endl;
                       vec_hp[enemy_cho + 4] -= 9;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                        vec_hp[enemy_cho + 4] -= 24;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 144" << endl;
                       vec_hp[enemy_cho + 4] -= 144;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 53" << endl;
                       vec_hp[enemy_cho + 4] -= 53;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                        vec_hp[enemy_cho + 4] -= 72;
                   }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
               if(condition[0] == 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 96" << endl;
                       vec_hp[enemy_cho + 4] -= 96;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 17" << endl;
                       vec_hp[enemy_cho + 4] -= 17;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                        vec_hp[enemy_cho + 4] -= 48;
                   }
                }
                else if(condition[0] < 0)
                {
                   if(enemy_cho == 1)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 48" << endl;
                       vec_hp[enemy_cho + 4] -= 48;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 9" << endl;
                       vec_hp[enemy_cho + 4] -= 9;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 24" << endl;
                        vec_hp[enemy_cho + 4] -= 24;
                   }
                }
                else if(condition[0] > 0)
                {
                    if(enemy_cho == 1)
                    {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 144" << endl;
                       vec_hp[enemy_cho + 4] -= 144;
                   }
                   else if(enemy_cho == 2)
                   {
                       os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 53" << endl;
                       vec_hp[enemy_cho + 4] -= 53;
                   }
                   else if(enemy_cho == 3)
                   {
                        os << "Your " << me[my_ch[my_cho - 1]] << " uses Flame!Damage: 72" << endl;
                        vec_hp[enemy_cho + 4] -= 72;
                   }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's W wakes up" << endl;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                    }
                }
                condition[enemy_cho + 6] = 0;
                time[enemy_cho + 3] = 0;
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
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
                if(enemy_cho == 2)
                {
                    os << "14" << endl;
                    vec_hp[enemy_cho + 4] -= 14;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your G uses Tackle!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "29" << endl;
                    vec_hp[enemy_cho + 4] -= 29;
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
                if(enemy_cho == 2)
                {
                    os << "29" << endl;
                    vec_hp[enemy_cho + 4] -= 29;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 7" << endl;
                        vec_hp[enemy_cho + 4] -= 7;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 5" << endl;
                        vec_hp[enemy_cho + 4] -= 13;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 4" << endl;
                        vec_hp[enemy_cho + 4] -= 5;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 15" << endl;
                        vec_hp[enemy_cho + 4] -= 15;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 11" << endl;
                        vec_hp[enemy_cho + 4] -= 11;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 30" << endl;
                        vec_hp[enemy_cho + 4] -= 30;
                    }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 7" << endl;
                        vec_hp[enemy_cho + 4] -= 7;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                }
                else if(condition[0] == 1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 5" << endl;
                        vec_hp[enemy_cho + 4] -= 13;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 4" << endl;
                        vec_hp[enemy_cho + 4] -= 5;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                }
                else if(condition[0] == -1)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 15" << endl;
                        vec_hp[enemy_cho + 4] -= 15;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 11" << endl;
                        vec_hp[enemy_cho + 4] -= 11;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 30" << endl;
                        vec_hp[enemy_cho + 4] -= 30;
                    }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
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
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 14" << endl;
                        vec_hp[enemy_cho + 4] -= 14;
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
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 7" << endl;
                        vec_hp[enemy_cho + 4] -= 7;
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
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 29" << endl;
                        vec_hp[enemy_cho + 4] -= 29;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 80" << endl;
                        vec_hp[enemy_cho + 4] -= 80;
                    }
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                if(condition[0] == 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Your G uses Stream!Damage: 20" << endl;
                        vec_hp[enemy_cho + 4] -= 20;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 14" << endl;
                        vec_hp[enemy_cho + 4] -= 14;
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
                        os << "Your G uses Stream!Damage: 10" << endl;
                        vec_hp[enemy_cho + 4] -= 10;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 7" << endl;
                        vec_hp[enemy_cho + 4] -= 7;
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
                        os << "Your G uses Stream!Damage: 40" << endl;
                        vec_hp[enemy_cho + 4] -= 40;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Your G uses Stream!Damage: 29" << endl;
                        vec_hp[enemy_cho + 4] -= 29;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Your G uses Stream!Damage: 80" << endl;
                        vec_hp[enemy_cho + 4] -= 80;
                    }
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "11" << endl;
                    vec_hp[enemy_cho + 4] -= 11;
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
                if(enemy_cho == 2)
                {
                    os << "11" << endl;
                    vec_hp[enemy_cho + 4] -= 11;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Quick!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "21" << endl;
                    vec_hp[enemy_cho + 4] -= 21;
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
                if(enemy_cho == 2)
                {
                    os << "21" << endl;
                    vec_hp[enemy_cho + 4] -= 21;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                else if(enemy_cho == 2)
                {
                    os << "36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                }
                else if(enemy_cho == 3)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                else if(enemy_cho == 2)
                {
                    os << "36" << endl;
                    vec_hp[enemy_cho + 4] -= 36;
                }
                else if(enemy_cho == 3)
                {
                    os << "13" << endl;
                    vec_hp[enemy_cho + 4] -= 13;
                }
                if(vec_hp[enemy_cho + 4] > 0)
                {
                    if(enemy_cho == 1)
                    {
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
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
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else if(enemy_cho == 2)
                {
                    os << "71" << endl;
                    vec_hp[enemy_cho + 4] -= 71;
                }
                else if(enemy_cho == 3)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
            }
            else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your Q uses Volt!Damage: ";
                if(enemy_cho == 1)
                {
                    os << "25" << endl;
                    vec_hp[enemy_cho + 4] -= 25;
                }
                else if(enemy_cho == 2)
                {
                    os << "71" << endl;
                    vec_hp[enemy_cho + 4] -= 71;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
            if(condition[0] == -1)
            {
                if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "71" << endl;
                        vec_hp[enemy_cho + 4] -= 71;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                }
                else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] == 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "25" << endl;
                        vec_hp[enemy_cho + 4] -= 25;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "71" << endl;
                        vec_hp[enemy_cho + 4] -= 71;
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
                            os << "Enemy's W wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 2)
                        {
                            os << "Enemy's G wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 3)
                        {
                            os << "Enemy's Q wakes up" << endl;
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
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "143" << endl;
                        vec_hp[enemy_cho + 4] -= 143;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                }
                else if(condition[enemy_cho + 6] != 0 && condition[enemy_cho + 9] != 0)
                {
                    os << "Your Q uses Thunder!Damage: ";
                    if(enemy_cho == 1)
                    {
                        os << "50" << endl;
                        vec_hp[enemy_cho + 4] -= 50;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "143" << endl;
                        vec_hp[enemy_cho + 4] -= 143;
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
                            os << "Enemy's W wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 2)
                        {
                            os << "Enemy's G wakes up" << endl;
                            condition[enemy_cho + 6] = 0;
                            time[enemy_cho + 3] = 0;
                        }
                        else if(enemy_cho == 3)
                        {
                            os << "Enemy's Q wakes up" << endl;
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
            output(os, enemy_cho);
            if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] == 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
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
                if(enemy_cho == 2)
                {
                    os << "10" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
            else if(condition[enemy_cho + 6] == 0 && condition[enemy_cho + 9] != 0)
            {
                os << "Your D uses Slap!Damage: ";
                if(enemy_cho == 2)
                {
                    os << "19" << endl;
                    vec_hp[enemy_cho + 4] -= 19;
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
                if(enemy_cho == 2)
                {
                    os << "19" << endl;
                    vec_hp[enemy_cho + 4] -= 10;
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
                        os << "Enemy's W wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 2)
                    {
                        os << "Enemy's G wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                    else if(enemy_cho == 3)
                    {
                        os << "Enemy's Q wakes up" << endl;
                        condition[enemy_cho + 6] = 0;
                        time[enemy_cho + 3] = 0;
                    }
                }
            }
        }
        else if(act == 2)
        {
            output(os, enemy_cho);
            os << "Your D uses Sing!";
            if(condition[enemy_cho + 6] != 0)
            {
                os << "Waste" << endl;
            }
            else
            {
                if(enemy_cho == 1)
                {
                    os << " Enemy's W falls asleep" << endl;
                }
                if(enemy_cho == 2)
                {
                    os << " Enemy's G falls asleep" << endl;
                }
                if(enemy_cho == 3)
                {
                    os << " Enemy's Q falls asleep" << endl;
                }
                condition[enemy_cho + 6] = 1;
                time[enemy_cho + 3] = 3;
            }
        }
        else if(act == 3)
        {
            output(os, enemy_cho);
            os << "Your D uses Paint! Enemy's " ;
            if(enemy_cho == 1)
            {
                os << "W is painted" << endl;
            }
            else if(enemy_cho == 2)
            {
                os << "G is painted" << endl;
            }
            else if(enemy_cho == 3)
            {
                os << "Q is painted" << endl;
            }
            condition[enemy_cho + 9] = 1;
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
            if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                output(os, enemy_cho);
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else
        {
            if(enemy_cho != 2 || enemy_attack2(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
            {
                if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
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
                    output(os, enemy_cho);
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
            else
            {
                if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
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
                    output(os, enemy_cho);
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
            if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
               output(os, enemy_cho);
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else if(act != 3 && enemy_cho != 3 && !enemy_attack2(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
        {

                if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
                {
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                    else
                    {
                        enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        my_cho = my_cho;
                    }
                }
                else
                {
                    output(os, enemy_cho);
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
            else if(act == 3 && enemy_cho != 2 && !enemy_attack2(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
            {
                if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
                {
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
                    {
                        my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    }
                    else
                    {
                        enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        my_cho = my_cho;
                    }
                }
                else
                {
                    output(os, enemy_cho);
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
        else if(act == 3 && enemy_cho != 2 && enemy_attack2(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
        {
            if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
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
                    output(os, enemy_cho);
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
        }
        else if(act != 3 && enemy_cho == 2 && enemy_attack2(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
        {
            if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
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
                    output(os, enemy_cho);
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
        }
        else
        {
            if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
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
                    output(os, enemy_cho);
                    enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
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
            if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                output(os, enemy_cho);
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else
        {
           if(act == 3)
           {
               if(enemy_attack2(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
               {
                   if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
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
                    output(os, enemy_cho);
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
               }
               else
               {
                   if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
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
                    output(os, enemy_cho);
                    enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
               }
           }
           else
           {
               if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
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
                    output(os, enemy_cho);
                    enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
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
            if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                output(os, enemy_cho);
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        else if(act == 1)
        {
            if(enemy_cho == 3 && enemy_attack2(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
            {
                if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
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
                    output(os, enemy_cho);
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
            else
            {
               if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
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
                    output(os, enemy_cho);
                    enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
            }
        }
        else
        {
           if(enemy_attack2(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act) || enemy_cho == 3)
           {
               if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
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
                    output(os, enemy_cho);
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
           }
           else
           {
               if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
                {
                    my_att(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    if(!dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch))
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
                    output(os, enemy_cho);
                    enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                }
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
            if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
            {
                enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
            }
            else
            {
                output(os, enemy_cho);
            }
            return true;
        }
        if(act == 0)
        {
            return false;
        }
        if(!change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
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
            output(os, enemy_cho);
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
void action(istream& is, ostream& os, vector<int>& my_ch, map<int, string> me, vector<int>& vec_hp, int& enemy_cho, int& my_cho, int& round, vector<int>& condition, vector<int>& time, int& act, int& number)
{
    int before = my_cho;
    if(my_dead(vec_hp, my_ch) <= 1)
    {
        act2(is, os, act);
        run(os, round, act);
        if(act == 1)
        {
           if(change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
            {
                if(time[my_cho - 1] != 0)
                {
                    output(os, enemy_cho);
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
                        action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
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
                        action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
                    }
                    else
                    {
                        my_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                        dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                        show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                    }
                }
            }
            else if(revival(os, enemy_cho, vec_hp, number))
            {
                if(time[my_cho - 1] != 0)
                {
                    os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
                    dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                }
                else
                {
                    if(!my_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
                    {
                        act = -1;
                        action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
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
                    action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
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
                action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
            }
            else
            {
                if(change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
                {
                    output(os, enemy_cho);
                    dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                }
                else if(revival(os, enemy_cho, vec_hp, number))
                {
                    dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                }
                else
                {
                    if(time[enemy_cho + 3] == 0)
                    {
                        enemy_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
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
        if(change_ene(os, vec_hp, enemy_cho, my_ch, my_cho, condition))
        {
            if(time[my_cho - 1] != 0)
            {
                output(os, enemy_cho);
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
                    action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
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
                    action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
                }
                else
                {
                    my_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act);
                    dead_echange(is, os, my_cho, enemy_cho, vec_hp, me, my_ch);
                    show_hp(os, enemy_cho, my_ch, me, vec_hp, my_cho, round);
                }
            }
        }
        else if(revival(os, enemy_cho, vec_hp, number))
        {
            if(time[my_cho - 1] != 0)
            {
                os << "Your " << me[my_ch[my_cho - 1]] << " is sleeping" << endl;
            }
            else
            {
                if(!my_attack(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act))
                {
                    act = -1;
                    action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
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
                action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
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
    os << "Enemy has W, G and Q." << endl;
    os << "You can select three from five (1 for W, 2 for L, 3 for G, 4 for Q, 5 for D)." << endl;
    map<int, string> me = {{1, "W"}, {2, "L"}, {3, "G"}, {4, "Q"}, {5, "D"}};
    vector<int> vec_hp = {110, 100, 100, 90, 120, 110, 100, 90};
    srand(time(0));
    int enemy_cho = rand() % 3 + 1;
    int my_cho = 0;
    int number = 1;
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
    start(os, my_cho, enemy_cho);
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
        action(is, os, my_ch, me, vec_hp, enemy_cho, my_cho, round, condition, time, act, number);
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

