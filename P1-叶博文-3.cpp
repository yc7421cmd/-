#include <iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include <string>

using namespace std;

void change_G(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& before_me, int& att_pot, int& round);
void change_L(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& before_me, int& att_pot, int& round);
void change_W(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& before_me, int& att_pot, int& round);
void W_change(istream& is, ostream& os, int choose, int& my_cho, int& before_me);
void L_change(istream& is, ostream& os, int choose, int& my_cho, int& before_me);
void G_change(istream& is, ostream& os, int choose, int& my_cho, int& before_me);
void num_echange(ostream& os, int& death, int& my_cho, int& enemy_cho, vector<int>& vec_hp);
int dam(int& my_cho, int& enemy_cho, int& cho_att);

//贪心敌方换宠物
bool ene_greed(ostream& os, int& my_cho, int& enemy_cho, vector<int> vec_hp, int number)
{
    if(number == 0)
    {
        if(my_cho == 1 && enemy_cho != 2 && vec_hp[4] > 0)
        {
            enemy_cho = 2;
            os << "Enemy sends L" << endl;
            return true;
        }
        if(my_cho == 2 && enemy_cho != 3 && vec_hp[5] > 0)
        {
            enemy_cho = 3;
            os << "Enemy sends G" << endl;
            return true;
        }
        if(my_cho == 3 && enemy_cho != 1 && vec_hp[3] > 0)
        {
            enemy_cho = 1;
            os << "Enemy sends W" << endl;
            return true;
        }
        if(my_cho == 1 && enemy_cho == 3 && vec_hp[3] > 0)
        {
            enemy_cho = 1;
            os << "Enemy sends W" << endl;
            return true;
        }
        if(my_cho == 2 && enemy_cho == 1 && vec_hp[4] > 0)
        {
            enemy_cho = 2;
            os << "Enemy sends L" << endl;
            return true;
        }
        if(my_cho == 3 && enemy_cho == 2 && vec_hp[5] > 0)
        {
            enemy_cho = 3;
            os << "Enemy sends G" << endl;
            return true;
        }
    }
    return false;
}

//使用加强药
bool attack(ostream& os, int& att_pot, int before_me, int enemy_cho, int& number)
{
    if(att_pot != 0 && number == 0)
    {
        if(before_me == 1 && enemy_cho == 2)
        {
            number = 1;
            att_pot -= 1;
            os << "Enemy uses Attack Potion on L" << endl;
            return true;
        }
        else if(before_me == 1 && enemy_cho == 1)
        {
            number = 1;
            att_pot -= 1;
            os << "Enemy uses Attack Potion on W" << endl;
            return true;
        }
        else if(before_me == 2 && enemy_cho == 3)
        {
            number = 1;
            att_pot -= 1;
            os << "Enemy uses Attack Potion on G" << endl;
            return true;
        }
        else if(before_me == 2 && enemy_cho == 2)
        {
            number = 1;
            att_pot -= 1;
            os << "Enemy uses Attack Potion on L" << endl;
            return true;
        }
        else if(before_me == 3 && enemy_cho == 1)
        {
            number = 1;
            att_pot -= 1;
            os << "Enemy uses Attack Potion on W" << endl;
            return true;
        }
        else if(before_me == 3 && enemy_cho == 3)
        {
            number = 1;
            att_pot -= 1;
            os << "Enemy uses Attack Potion on G" << endl;
            return true;
        }
    }
    return false;
}
//使用复苏药
bool revival(ostream& os, vector<int>& vec_hp, int& pot, int enemy_cho)
{
    if(pot == 1)
    {
        if(vec_hp[3] <= 0 && enemy_cho != 1)
        {
            vec_hp[3] = 55;
            os << "Enemy uses Revival Potion on W" << endl;
            pot = 0;
            return true;
        }
        else if(vec_hp[4] <= 0 && enemy_cho != 2)
        {
            vec_hp[4] = 50;
            os << "Enemy uses Revival Potion on L" << endl;
            pot = 0;
            return true;
        }
        else if(vec_hp[5] <= 0 && enemy_cho != 3)
        {
            vec_hp[5] = 50;
            os << "Enemy uses Revival Potion on G" << endl;
            pot = 0;
            return true;
        }
    }
    return false;
}

//检查敌方死亡情况,并且取消攻击翻倍
void ene_beaten(ostream& os, int& enemy_cho, int& number)
{
    if(enemy_cho == 1)
    {
        os << "Enemy's W is beaten" << endl;
        number = 0;
    }
    if(enemy_cho == 2)
    {
        os << "Enemy's L is beaten" << endl;
        number = 0;
    }
    if(enemy_cho == 3)
    {
        os << "Enemy's G is beaten" << endl;
        number = 0;
    }
}

//根据death来改变程序运行，改变death
void deat(int& death, vector<int> vec_hp)
{
    if(vec_hp[0] <=0 && vec_hp[1] <= 0 && vec_hp[2] <= 0)
    {
        death = 7;
    }
    else if(vec_hp[0] <=0 && vec_hp[1] <= 0)
    {
        death = 4;
    }
    else if(vec_hp[0] <=0 && vec_hp[2] <= 0)
    {
        death = 5;
    }
    else if(vec_hp[1] <= 0 && vec_hp[2] <= 0 && vec_hp[0] > 0)
    {
        death = 6;
    }
    else if(vec_hp[0] <= 0)
    {
        death = 1;
    }
    else if(vec_hp[1] <= 0)
    {
        death = 2;
    }
    else if(vec_hp[2] <= 0)
    {
        death = 3;
    }
}

//我方选择宠物(死亡后选择）
void my_change(istream& is, ostream& os, vector<int> vec_hp, int& my_cho)
{
    int choose = 0;
    if(vec_hp[0] <= 0 && vec_hp[1] <= 0 && vec_hp[2] <= 0)
    {
        my_cho = my_cho;
    }
    else if(vec_hp[0] <= 0 && vec_hp[1] <= 0)
    {
        while(choose != 3)
        {
            os << "Select your next pet(3 for G):";
            is >> choose;
        }
        os << "You send G" << endl;
        my_cho = choose;
    }
    else if(vec_hp[1] <= 0 && vec_hp[2] <= 0)
    {
        while(choose != 1)
        {
            os << "Select your next pet(1 for W):";
            is >> choose;
        }
        os << "You send W" << endl;
        my_cho = choose;
    }
    else if(vec_hp[2] <= 0 && vec_hp[0] <= 0)
    {
        while(choose != 2)
        {
            os << "Select your next pet(2 for L):";
            is >> choose;
        }
        os << "You send L" << endl;
        my_cho = choose;
    }
    else if(vec_hp[0] <=0 )
    {
        while(choose != 2 && choose != 3)
        {
            os << "Select your next pet(2 for L, 3 for G):";
            is >> choose;
        }
        if(choose == 2)
        {
            os << "You send L" << endl;
        }
        else
        {
            os << "You send G" << endl;
        }
        my_cho = choose;
    }
    else if(vec_hp[1] <=0 )
    {
        while(choose != 1 && choose != 3)
        {
            os << "Select your next pet(1 for W, 3 for G):";
            is >> choose;
        }
        if(choose == 1)
        {
            os << "You send W" << endl;
        }
        else
        {
            os << "You send G" << endl;
        }
        my_cho = choose;
    }
    else if(vec_hp[2] <=0 )
    {
        while(choose != 1 && choose != 2)
        {
            os << "Select your next pet(1 for W, 2 for L):";
            is >> choose;
        }
        if(choose == 1)
        {
            os << "You send W" << endl;
        }
        else
        {
            os << "You send L" << endl;
        }
        my_cho = choose;
    }
}

//输出宠物死亡情况并且改变敌我宠物
void num_echange(istream& is, ostream& os, int& death, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& number)
{
    if(vec_hp[my_cho- 1] <= 0 && vec_hp[enemy_cho + 2] <= 0)
    {
        ene_beaten(os, enemy_cho, number);
        if(my_cho == 1)
        {
            os << "Your W is beaten" << endl;
            my_change(is, os, vec_hp, my_cho);
            if(vec_hp[5] > 0)
            {
                enemy_cho = 3;
                os << "Enemy sends G" << endl;
            }
            else if(vec_hp[3] > 0)
            {
            enemy_cho = 1;
            os << "Enemy sends W" << endl;
            }
            else if(vec_hp[4] > 0)
            {
            enemy_cho = 2;
            os << "Enemy sends L" << endl;
            }
        }
        else if(my_cho == 2)
        {
            os << "Your L is beaten" << endl;
            my_change(is, os, vec_hp, my_cho);
            if(vec_hp[3] > 0)
            {
                enemy_cho = 1;
                os << "Enemy sends W" << endl;
            }
            else if(vec_hp[4] > 0)
            {
                enemy_cho = 2;
                os << "Enemy sends L" << endl;
            }
            else if(vec_hp[5] > 0)
            {
                enemy_cho = 3;
                os << "Enemy sends G" << endl;
            }
        }
        else if(my_cho == 3)
        {
            os << "Your G is beaten" << endl;
            my_change(is, os, vec_hp, my_cho);
            if(vec_hp[4] > 0)
            {
                enemy_cho = 2;
                os << "Enemy sends L" << endl;
            }
            else if(vec_hp[5] > 0)
            {
                enemy_cho = 3;
                os << "Enemy sends G" << endl;
            }
            else if(vec_hp[3] > 0)
            {
                enemy_cho = 1;
                os << "Enemy sends W" << endl;
            }
        }
    }
    else if(vec_hp[enemy_cho + 2] <= 0 && vec_hp[my_cho- 1] > 0)
    {
        ene_beaten(os, enemy_cho, number);
        if(my_cho == 1 && vec_hp[4] > 0)
        {
            enemy_cho = 2;
            os << "Enemy sends L" << endl;
        }
        else if(my_cho == 1 && vec_hp[3] > 0)
        {
            enemy_cho = 1;
            os << "Enemy sends W" << endl;
        }
        else if(my_cho == 1 && vec_hp[5] > 0)
        {
            enemy_cho = 3;
            os << "Enemy sends G" << endl;
        }
        if(my_cho == 2 && vec_hp[5] > 0)
        {
            enemy_cho = 3;
            os << "Enemy sends G" << endl;
        }
        else if(my_cho == 2 && vec_hp[4] > 0)
        {
            enemy_cho = 2;
            os << "Enemy sends L" << endl;
        }
        else if(my_cho == 2 && vec_hp[3] > 0)
        {
            enemy_cho = 1;
            os << "Enemy sends W" << endl;
        }
        if(my_cho == 3 && vec_hp[3] > 0)
        {
            enemy_cho = 1;
            os << "Enemy sends W" << endl;
        }
        else if(my_cho == 3 && vec_hp[5] > 0)
        {
            enemy_cho = 3;
            os << "Enemy sends G" << endl;
        }
        else if(my_cho == 3 && vec_hp[4] > 0)
        {
            enemy_cho = 2;
            os << "Enemy sends L" << endl;
        }
    }
    else if(vec_hp[my_cho- 1] <= 0 && vec_hp[enemy_cho + 2] > 0)
    {
        if(my_cho == 1)
        {
            os << "Your W is beaten" << endl;
        }
        else if(my_cho == 2)
        {
            os << "Your L is beaten" << endl;
        }
        else if(my_cho == 3)
        {
            os << "Your G is beaten" << endl;
        }
        my_change(is, os, vec_hp, my_cho);
    }
}

//程序开始的输出
void start(ostream& os, int me, int enemy)
{
    switch(me)
    {
    case 1:
        os << "You start with W" << endl;
        break;
    case 2:
        os << "You start with L" << endl;
        break;
    case 3:
        os << "You start with G" << endl;
        break;
    default:
        break;
    }

    switch(enemy)
    {
    case 1:
        os << "Enemy starts with W" << endl;
        break;
    case 2:
        os << "Enemy starts with L" << endl;
        break;
    case 3:
        os << "Enemy starts with G" << endl;
        break;
    default:
        break;
    }
}

//判断胜负情况
void win(ostream& os, vector<int> vec_hp, int& death, int& round)
{
    if((vec_hp[0] <= 0 && vec_hp[1] <= 0 && vec_hp[2] <= 0 && vec_hp[3] <= 0 && vec_hp[4] <= 0 && vec_hp[5] <= 0) || round == 100)
    {
        os << "Draw" ;
        death = 7;
    }
    else if(vec_hp[0] <= 0 && vec_hp[1] <= 0 && vec_hp[2] <= 0)
    {
        os << "You lose";
        death = 7;
    }
    else if(vec_hp[3] <= 0 && vec_hp[4] <= 0 && vec_hp[5] <= 0)
    {
        os << "You win" ;
        death = 7;
    }
}

//敌方进行攻击
void enemy_damage(ostream& os, int my_cho, int enemy_cho, vector<int>& vec_hp, int& death, int number)
{
    if(my_cho == 1 && enemy_cho == 1)
    {
        if(number == 0)
        {
            vec_hp[0] -= 20;
            os << "Enemy's W use Tackle! Damage: 20" << endl;
        }
        else if(number == 1)
        {
            vec_hp[0] -= 40;
            os << "Enemy's W use Tackle! Damage: 40" << endl;
        }
    }
    if(my_cho == 1 && enemy_cho == 2)
    {
        if(number == 0)
        {
            vec_hp[0] -= 40;
            os << "Enemy's L use Flame! Damage: 40" << endl;
        }
        else
        {
            vec_hp[0] -= 80;
            os << "Enemy's L use Flame! Damage: 80" << endl;
        }
    }
    if(my_cho == 1 && enemy_cho == 3)
    {
        if(number == 0)
        {
            vec_hp[0] -= 20;
            os << "Enemy's G use Tackle! Damage: 20" << endl;
        }
        else
        {
            vec_hp[0] -= 40;
            os << "Enemy's G use Tackle! Damage: 40" << endl;
        }
    }
     if(my_cho == 2 && enemy_cho == 1)
    {
        if(number == 0)
        {
            vec_hp[1] -= 20;
            os << "Enemy's W use Tackle! Damage: 20" << endl;
        }
        else
        {
            vec_hp[1] -= 40;
            os << "Enemy's W use Tackle! Damage: 40" << endl;
        }
    }
    if(my_cho == 2 && enemy_cho == 2)
    {
        if(number == 0)
        {
            vec_hp[1] -= 22;
            os << "Enemy's L use Tackle! Damage: 22" << endl;
        }
        else
        {
            vec_hp[1] -= 44;
            os << "Enemy's L use Tackle! Damage: 44" << endl;
        }
    }
    if(my_cho == 2 && enemy_cho == 3)
    {
        if(number == 0)
        {
           vec_hp[1] -= 40;
            os << "Enemy's G use Stream! Damage: 40" << endl;
        }
        else
        {
            vec_hp[1] -= 80;
            os << "Enemy's G use Stream! Damage: 80" << endl;
        }
    }
    if(my_cho == 3 && enemy_cho == 1)
    {
        if(number == 0)
        {
            vec_hp[2] -= 36;
            os << "Enemy's W use Leaf! Damage: 36" << endl;
        }
        else
        {
            vec_hp[2] -= 72;
            os << "Enemy's W use Leaf! Damage: 72" << endl;
        }
    }
    if(my_cho == 3 && enemy_cho == 2)
    {
        if(number == 0)
        {
            vec_hp[2] -= 20;
            os << "Enemy's L use Tackle! Damage: 20" << endl;
        }
        else
        {
            vec_hp[2] -= 40;
            os << "Enemy's L use Tackle! Damage: 40" << endl;
        }
    }
    if(my_cho == 3 && enemy_cho == 3)
    {
        if(number == 0)
        {
            vec_hp[2] -= 18;
            os << "Enemy's G use Tackle! Damage: 18" << endl;
        }
        else
        {
            vec_hp[2] -= 36;
            os << "Enemy's G use Tackle! Damage: 36" << endl;
        }
    }
}

//展示敌我HP值
void show_hp(ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp)
{
    if(my_cho == 1 && enemy_cho == 1)
    {
        os << "Your W: HP " << vec_hp[0] <<" || " << "Enemy's W: HP " << vec_hp[3] << endl;
    }
    if(my_cho == 1 && enemy_cho == 2)
    {
        os << "Your W: HP " << vec_hp[0] <<" || " << "Enemy's L: HP " << vec_hp[4] << endl;
    }
    if(my_cho == 1 && enemy_cho == 3)
    {
        os << "Your W: HP " << vec_hp[0] <<" || " << "Enemy's G: HP " << vec_hp[5] << endl;
    }
     if(my_cho == 2 && enemy_cho == 1)
    {
        os << "Your L: HP " << vec_hp[1] <<" || " << "Enemy's W: HP " << vec_hp[3] << endl;
    }
    if(my_cho == 2 && enemy_cho == 2)
    {
        os << "Your L: HP " << vec_hp[1] <<" || " << "Enemy's L: HP " << vec_hp[4] << endl;
    }
    if(my_cho == 2 && enemy_cho == 3)
    {
        os << "Your L: HP " << vec_hp[1] <<" || " << "Enemy's G: HP " << vec_hp[5] << endl;
    }
    if(my_cho == 3 && enemy_cho == 1)
    {
        os << "Your G: HP " << vec_hp[2] <<" || " << "Enemy's W: HP " << vec_hp[3] << endl;
    }
    if(my_cho == 3 && enemy_cho == 2)
    {
        os << "Your G: HP " << vec_hp[2] <<" || " << "Enemy's L: HP " << vec_hp[4] << endl;
    }
    if(my_cho == 3 && enemy_cho == 3)
    {
        os << "Your G: HP " << vec_hp[2] <<" || " << "Enemy's G: HP " << vec_hp[5] << endl;
    }
}

//双方进攻的主要过程(我方扣血，地方扣血，死亡后更换宠物，改变death，判断胜负，展示血量
void show_poc(istream& is, ostream& os, int& my_cho, int& enemy_cho, int cho_att, vector<int>& vec_hp, int& death, int& pot, int& att_pot, int& number, int& before_me, int& round)
{
    int damage = 0;
    if(my_cho == 1 && enemy_cho == 1 && cho_att == 1)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 20;
            vec_hp[3] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 20;
            vec_hp[3] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
        }
        else
        {
            damage = 20;
            vec_hp[3] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 1 && enemy_cho == 1 && cho_att == 2)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 10;
            vec_hp[3] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 10;
            vec_hp[3] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
        }
        else
        {
            damage = 10;
            vec_hp[3] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 1 && enemy_cho == 2 && cho_att == 1)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 20;
            vec_hp[4] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;

        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 20;
            vec_hp[4] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
        }
        else
        {
            damage = 20;
            vec_hp[4] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 1 && enemy_cho == 2 && cho_att == 2)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 10;
            vec_hp[4] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 10;
            vec_hp[4] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
        }
        else
        {
            damage = 10;
            vec_hp[4] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 1 && enemy_cho == 3 && cho_att == 1)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 18;
            vec_hp[5] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 18;
            vec_hp[5] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
        }
        else
        {
            damage = 18;
            vec_hp[5] -= damage;
            os << "Your W use Tackle! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);

        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 1 && enemy_cho == 3 && cho_att == 2)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 36;
            vec_hp[5] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 36;
            vec_hp[5] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
        }
        else
        {
            damage = 36;
            vec_hp[5] -= damage;
            os << "Your W use Leaf! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 2 && enemy_cho == 1 && cho_att == 1)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 22;
            vec_hp[3] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 22;
            vec_hp[3] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
        }
        else
        {
            damage = 22;
            vec_hp[3] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 2 && enemy_cho == 1 && cho_att == 2)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 44;
            vec_hp[3] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 44;
            vec_hp[3] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
        }
        else
        {
            damage = 44;
            vec_hp[3] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 2 && enemy_cho == 2 && cho_att == 1)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 22;
            vec_hp[4] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 22;
            vec_hp[4] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
        }
        else
        {
            damage = 22;
            vec_hp[4] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 2 && enemy_cho == 2 && cho_att == 2)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 11;
            vec_hp[4] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 11;
            vec_hp[4] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
        }
        else
        {
            damage = 11;
            vec_hp[4] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 2 && enemy_cho == 3 && cho_att == 1)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 20;
            vec_hp[5] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;

        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 20;
            vec_hp[5] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
        }
        else
        {
            damage = 20;
            vec_hp[5] -= damage;
            os << "Your L use Tackle! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 2 && enemy_cho == 3 && cho_att == 2)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 10;
            vec_hp[5] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 10;
            vec_hp[5] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
        }
        else
        {
            damage = 10;
            vec_hp[5] -= damage;
            os << "Your L use Flame! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 3 && enemy_cho == 1 && cho_att == 1)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 20;
            vec_hp[3] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 20;
            vec_hp[3] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
        }
        else
        {
            damage = 20;
            vec_hp[3] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 3 && enemy_cho == 1 && cho_att == 2)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 10;
            vec_hp[3] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 10;
            vec_hp[3] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
        }
        else
        {
            damage = 10;
            vec_hp[3] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 3 && enemy_cho == 2 && cho_att == 1)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 20;
            vec_hp[4] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 20;
            vec_hp[4] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
        }
        else
        {
            damage = 20;
            vec_hp[4] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 3 && enemy_cho == 2 && cho_att == 2)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 40;
            vec_hp[4] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;

        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 40;
            vec_hp[4] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
        }
        else
        {
            damage = 40;
            vec_hp[4] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 3 && enemy_cho == 3 && cho_att == 1)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 18;
            vec_hp[5] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 18;
            vec_hp[5] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
        }
        else
        {
            damage = 18;
            vec_hp[5] -= damage;
            os << "Your G use Tackle! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(my_cho == 3 && enemy_cho == 3 && cho_att == 2)
    {
        if(revival(os, vec_hp, pot, enemy_cho))
        {
            damage = 9;
            vec_hp[5] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;

        }
        else if(attack(os, att_pot, before_me, enemy_cho, number))
        {
            damage = 9;
            vec_hp[5] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
        }
        else if(!revival(os, vec_hp, pot, enemy_cho) && ene_greed(os, my_cho, enemy_cho, vec_hp, number))
        {
            int damage = dam(my_cho, enemy_cho, cho_att);
            vec_hp[enemy_cho + 2] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
        }
        else
        {
            damage = 9;
            vec_hp[5] -= damage;
            os << "Your G use Stream! Damage: " << damage << endl;
            enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        }
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
}

//返回我方对敌伤害
int dam(int& my_cho, int& enemy_cho, int& cho_att)
{
    int damage = 0;
    if(my_cho == 1 && enemy_cho == 1 && cho_att == 1)
    {
        damage = 20;
    }
    if(my_cho == 1 && enemy_cho == 1 && cho_att == 2)
    {
        damage = 10;
    }
    if(my_cho == 1 && enemy_cho == 2 && cho_att == 1)
    {
        damage = 20;
    }
    if(my_cho == 1 && enemy_cho == 2 && cho_att == 2)
    {
        damage = 10;
    }
    if(my_cho == 1 && enemy_cho == 3 && cho_att == 1)
    {
        damage = 18;
    }
    if(my_cho == 1 && enemy_cho == 3 && cho_att == 2)
    {
        damage = 36;
    }
    if(my_cho == 2 && enemy_cho == 1 && cho_att == 1)
    {
        damage = 22;
    }
     if(my_cho == 2 && enemy_cho == 1 && cho_att == 2)
    {
        damage = 44;
    }
    if(my_cho == 2 && enemy_cho == 2 && cho_att == 1)
    {
        damage = 22;
    }
    if(my_cho == 2 && enemy_cho == 2 && cho_att == 2)
    {
        damage = 11;
    }
    if(my_cho == 2 && enemy_cho == 3 && cho_att == 1)
    {
        damage = 20;
    }
    if(my_cho == 2 && enemy_cho == 3 && cho_att == 2)
    {
        damage = 10;
    }
    if(my_cho == 3 && enemy_cho == 1 && cho_att == 1)
    {
        damage = 20;
    }
    if(my_cho == 3 && enemy_cho == 1 && cho_att == 2)
    {
        damage = 10;
    }
    if(my_cho == 3 && enemy_cho == 2 && cho_att == 1)
    {
        damage = 20;
    }
    if(my_cho == 3 && enemy_cho == 2 && cho_att == 2)
    {
        damage = 40;
    }
    if(my_cho == 3 && enemy_cho == 3 && cho_att == 1)
    {
        damage = 18;
    }
    if(my_cho == 3 && enemy_cho == 3 && cho_att == 2)
    {
        damage = 9;
    }
    return damage;
}

//展示W的进攻和show_poc
void W_attack(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& pot, int& att_pot, int& number, int& before_me, int& round)
{
    int cho_att = 0;
    while(cho_att !=1 && cho_att != 2)
    {
        os << "Select the skill(1 for Tackle, 2 for Leaf):";
        is >> cho_att;
    }
    show_poc(is, os, my_cho, enemy_cho, cho_att, vec_hp, death, pot, att_pot, number, before_me, round);
}

void L_attack(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& pot, int& att_pot, int& number, int& before_me, int& round)
{
    int cho_att = 0;
    while(cho_att !=1 && cho_att != 2)
    {
        os << "Select the skill(1 for Tackle, 2 for Flame):";
        is >> cho_att;
    }
    show_poc(is, os, my_cho, enemy_cho, cho_att, vec_hp, death, pot, att_pot, number, before_me, round);
}

void G_attack(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& pot, int& att_pot, int& number, int& before_me, int& round)
{
    int cho_att = 0;
    while(cho_att !=1 && cho_att != 2)
    {
        os << "Select the skill(1 for Tackle, 2 for Stream):";
        is >> cho_att;
    }
    show_poc(is, os, my_cho, enemy_cho, cho_att, vec_hp, death, pot, att_pot, number, before_me, round);
}

//W活着的时候进行换宠物
void W_change(istream& is, ostream& os, int choose, int& my_cho, int& before_me)
{
    while(choose != 2 && choose != 3)
        {
            os << "Select your next pet(2 for L, 3 for G):";
            is >> choose;
        }
        if(choose == 2)
        {
            os << "You send L" << endl;
        }
        else
        {
            os << "You send G" << endl;
        }
        before_me = my_cho;
        my_cho = choose;
}

void L_change(istream& is, ostream& os, int choose, int& my_cho, int& before_me)
{
    while(choose != 1 && choose != 3)
        {
            os << "Select your next pet(1 for W, 3 for G):";
            is >> choose;
        }
        if(choose == 1)
        {
            os << "You send W" << endl;
        }
        else
        {
            os << "You send G" << endl;
        }
        before_me = my_cho;
        my_cho = choose;
}

void G_change(istream& is, ostream& os, int choose, int& my_cho, int& before_me)
{
    while(choose != 1 && choose != 2)
    {
        os << "Select your next pet(1 for W, 2 for L):";
        is >> choose;
    }
    if(choose == 1)
    {
        os << "You send W" << endl;
    }
    else
    {
        os << "You send L" << endl;
    }
    before_me = my_cho;
    my_cho = choose;
}

//我方三只宠物都没死的时候换宠物
void changeall(istream& is, ostream& os, int& my_cho, int& before_me)
{
    int choose = 0;
    switch(my_cho)
    {
    case 1:
        W_change(is, os, choose, my_cho, before_me);
        break;
    case 2:
        L_change(is, os, choose, my_cho, before_me);
        break;
    case 3:
        G_change(is, os, choose, my_cho, before_me);
        break;
    default:
        break;
    }
}

//当W已经死亡的时候的我方换宠物
void change_W(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& number, int& pot, int& before_me, int& att_pot, int& round)
{
    int choose = 0;
    if(my_cho == 2)
    {
        while(choose != 3)
        {
            os << "Select your next pet(3 for G):";
            is >> choose;
        }
        os << "You send G" << endl;
        before_me = my_cho;
        my_cho = choose;
    }
    else
    {
        while(choose != 2)
        {
            os << "Select your next pet(2 for L):";
            is >> choose;
        }
        os << "You send L" << endl;
        before_me = my_cho;
        my_cho = choose;
    }
    if(revival(os, vec_hp, pot, enemy_cho))
    {
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(attack(os, att_pot, before_me, enemy_cho, number))
    {
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else
    {
        enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
}

void change_L(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& number, int& pot, int& before_me, int& att_pot, int& round)
{
    int choose = 0;
    if(my_cho == 1)
    {
        while(choose != 3)
        {
            os << "Select your next pet(3 for G):";
            is >> choose;
        }
        os << "You send G" << endl;
        before_me = my_cho;
        my_cho = choose;
    }
    else
    {
        while(choose != 1)
        {
            os << "Select your next pet(1 for W):";
            is >> choose;
        }
        os << "You send W" << endl;
        before_me = my_cho;
        my_cho = choose;
    }
    if(revival(os, vec_hp, pot, enemy_cho))
    {
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(attack(os, att_pot, before_me, enemy_cho, number))
    {
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else
    {
        enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
}

void change_G(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& number, int& pot, int& before_me, int& att_pot, int& round)
{
    int choose = 0;
    if(my_cho == 1)
    {
        while(choose != 2)
        {
            os << "Select your next pet(2 for L):";
            is >> choose;
        }
        os << "You send L" << endl;
        before_me = my_cho;
        my_cho = choose;
    }
    else
    {
        while(choose != 1)
        {
            os << "Select your next pet(1 for W):";
            is >> choose;
        }
        os << "You send W" << endl;
        before_me = my_cho;
        my_cho = choose;
    }
    if(revival(os, vec_hp, pot, enemy_cho))
    {
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else if(attack(os, att_pot, before_me, enemy_cho, number))
    {
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
    else
    {
        enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
        num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
        deat(death, vec_hp);
        win(os, vec_hp, death, round);
        if(death != 7)
        {
            show_hp(os, my_cho, enemy_cho, vec_hp);
        }
    }
}

//进行宠物对决
void action(istream& is, ostream& os, int& my_cho, int& enemy_cho, vector<int>& vec_hp, int& death, int& pot, int& att_pot, int& number, int& round)
{
    int my_act = 4;
    int before_me = my_cho;
    if(death == 4 || death == 5 || death == 6)
    {
        while(my_act != 1)
        {
            os << "Select your action(1 for skill):";
            is >> my_act;
        }
        switch(my_cho)
        {
        case 1:
            W_attack(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, before_me, round);
            break;
        case 2:
            L_attack(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, before_me, round);
            break;
        case 3:
            G_attack(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, before_me, round);
            break;
        default:
            break;
        }
    }
    else if(death == 1 || death ==2 || death == 3)
    {
        while(my_act != 1 && my_act != 0)
        {
            os << "Select your action(0 for change, 1 for skill):";
            is >> my_act;
        }
            if(my_act == 0)
            {
                switch(death)
                {
                case 1:
                    change_W(is, os, my_cho, enemy_cho, vec_hp, death, number, pot, before_me, att_pot, round);
                    break;
                case 2:
                    change_L(is, os, my_cho, enemy_cho, vec_hp, death, number, pot, before_me, att_pot, round);
                    break;
                case 3:
                    change_G(is, os, my_cho, enemy_cho, vec_hp, death, number, pot, before_me, att_pot, round);
                    break;
                default:
                    break;
                }
            }
            else
            {
                switch(my_cho)
                {
                case 1:
                    W_attack(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, before_me, round);
                    break;
                case 2:
                    L_attack(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, before_me, round);
                    break;
                case 3:
                    G_attack(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, before_me, round);
                    break;
                default:
                    break;
                }
            }
        }
    else if(death == 0)
    {
        while(my_act != 1 && my_act != 0)
        {
            os << "Select your action(0 for change, 1 for skill):";
            is >> my_act;
        }
        if(my_act == 0)
        {
            changeall(is, os, my_cho, before_me);
            if(revival(os, vec_hp, pot, enemy_cho))
            {
                num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
                deat(death, vec_hp);
                win(os, vec_hp, death, round);
                if(death != 7)
                {
                    show_hp(os, my_cho, enemy_cho, vec_hp);
                }
            }
            else if(attack(os, att_pot, before_me, enemy_cho, number))
            {
                num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
                deat(death, vec_hp);
                win(os, vec_hp, death, round);
                if(death != 7)
                {
                    show_hp(os, my_cho, enemy_cho, vec_hp);
                }
            }
            else
            {
                enemy_damage(os, my_cho, enemy_cho, vec_hp, death, number);
                num_echange(is, os, death,my_cho, enemy_cho, vec_hp, number);
                deat(death, vec_hp);
                win(os, vec_hp, death, round);
                if(death != 7)
                {
                    show_hp(os, my_cho, enemy_cho, vec_hp);
                }
            }
        }
        else if(my_act == 1)
        {
            switch(my_cho)
            {
            case 1:
                W_attack(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, before_me, round);
                break;
            case 2:
                L_attack(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, before_me, round);
                break;
            case 3:
                G_attack(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, before_me, round);
                break;
            default:
                break;
            }
        }
    }
}

//回合的进行
void play(istream& is, ostream& os)
{
    os << "Welcome to Battle of Pets!" << endl;
    os << "You have W, L and G. So does Enemy." << endl;
    vector<int> vec_hp = {110, 100, 100, 110, 100, 100};
    srand(time(0));
    int enemy_cho = rand() % 3 + 1;
    int my_cho = 0;
    int death = 0;
    int pot = 1, att_pot = 2, number = 0;
    while(my_cho <= 0 || my_cho >= 4)
    {
        os << "Select your starting pet(1 for W, 2 for L, 3 for G):";
        is >> my_cho;
    }
    start(os, my_cho, enemy_cho);
    show_hp(os, my_cho, enemy_cho, vec_hp);
    os << "Battle starts!" << endl;
    int round = 1;
    while(round <= 100 && death != 7)
    {
        os << "-------------------------------------------------" << endl;
        os << "Round " << round << endl;
        action(is, os, my_cho, enemy_cho, vec_hp, death, pot, att_pot, number, round);
        round += 1;
    }
}

int main()
{
    play(cin, cout);
    return 0;
}

