#pragma once
#include <vector>
#include <algorithm>
#include <card/Card.hpp>
#include <ctk/random/RandomGenerator.hpp>
#include <poker/Hand.hpp>

void CalculateEquity(std::vector<Hand>& hands, std::vector<int>& counts, ctk::RandomGenerator& rand_gen, int sample_size = 100);

int Straight(std::vector<Card>& cards);
int StraightFlush(std::vector<Card>& cards, int suit);
std::pair<int, int> Flush(std::vector<Card>& cards);

// pair<0> = number of occurence
// pair<1> = value of card
std::pair<int, int> NSame(std::vector<Card>& cards, int ignore  = -1);

// Takes vector of cards sorted from highest to lowest and returns n highest values, ignoring list 
void getHighestCards(std::vector<int>& src, std::vector<Card>& cards, int n, std::initializer_list<int> ignore);
