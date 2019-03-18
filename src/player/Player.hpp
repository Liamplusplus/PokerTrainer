/*
 *
 *
 */

// Add different statuses of wealth and random scenarios for when
// you go broke e.g suicide, begging, prostitution. This will create incentive to win hands
//
// Add ability to withdraw saving or get loans
//
// Only one save per game, a character must die in order to start another
//
// A stats screen showing networth would enhance player experience

#pragma once
#include <string>
#include <iostream>


enum WealthStatus 
{ 
    DEBT,           // No savings, and owing money
    BROKE,          // No savings. Under $500 net worth
    NO_DISPOSABLE,  // Down to final savings pool (random amount)
    POOR,           // Under $2500
    AVERAGE, 
    COMFORTABLE, 
    WEALTHY 
};


// Extremes that one may resort to after losing too much money to play
//
// Give the player the option on how much money to take in
// Savings could be boosted from players opting to take in less


class Player
{

    public:

        Player();

		// High level
        // 
		void ChangeBalance(float value);
        void Withdraw(float amount);
        void Deposit(float amount);

		// Getters / Setters
		//
		void setBalance(float f);
		void setName(const std::string& inString);
		
		float getBalance() 	const;
		float getSavings() 	const;
		float getDebt() 	const;


        // Seperating net-worth into savings and balance will give the player the ability
        // to save or lose all their money
        float netWorth() const;


		const std::string& getName() const;

		void write_form(std::ostream& stream);
		void read_form(std::istream& stream);

        void write_binary(std::ostream& stream);
        void read_binary(std::istream& stream);
        void UpdateStatus();

	protected:
    
		std::string name;
        float balance;
        float savings;
        float debt;
        WealthStatus status;
};
