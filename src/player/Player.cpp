#include <player/Player.hpp>
#include <app/Config.hpp>

Player::Player() : balance(100.0f), savings(900.f), name("Null"), debt(0.f)
{
	status = WealthStatus::POOR;
}
		
void Player::setBalance(float f)
{
	balance = f;
}

void Player::ChangeBalance(float value)
{
    balance += value;
}
		
void Player::setName(const std::string& inString)
{
	name = inString;
}

float Player::getBalance() const
{
	return balance;
}

void Player::UpdateStatus()
{
    float net = netWorth();
    if (net > 40000.f)
        status = WealthStatus::WEALTHY;
    else if (net > 20000.f)
        status = WealthStatus::COMFORTABLE;
    else if (net > 10000.f)
        status = WealthStatus::AVERAGE;
    else if (net < 1000.f)
        status = WealthStatus::POOR;
    else if (net < 500.f)
        status = WealthStatus::NO_DISPOSABLE;
    else if (net < 100.f)
        status = WealthStatus::BROKE;
    else if (net < debt)
        status = WealthStatus::DEBT;
}

void Player::Withdraw(float amount)
{
    balance += amount;
    savings -= amount;
}

void Player::Deposit(float amount)
{
    balance -= amount;
    savings += amount;
}

float Player::netWorth() const
{
    return balance + savings;
}
		
const std::string& Player::getName() const
{
	return name;
}
		
void Player::write_form(std::ostream& stream)
{
	stream << "<Name> " << name << '\n' << "<Balance> " << balance;
	stream << "<Savings> " << savings << '\n' << "<Debt> " << debt;
}
		
void Player::read_form(std::istream& stream)
{
    stream.ignore(256, ' ');
	stream >> name;
    stream.ignore(256, ' ');
	stream >> balance;
    stream.ignore(256, ' ');
	stream >> savings;
    stream.ignore(256, ' ');
	stream >> debt;
	UpdateStatus();
}
        
void Player::write_binary(std::ostream& stream)
{
    game::write_binary(stream, name);
	stream.write((char*)&balance, sizeof(float)); 
	stream.write((char*)&savings, sizeof(float)); 
	stream.write((char*)&debt, sizeof(float)); 

}
        
void Player::read_binary(std::istream& stream)
{
    game::read_binary(stream, name);
	stream.read((char*)&balance, sizeof(float)); //Save size to file
	stream.read((char*)&savings, sizeof(float)); 
	stream.read((char*)&debt, sizeof(float)); 
	UpdateStatus();
}
