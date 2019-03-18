/*
 * AI for texas holdem. Dictates betting patterns and response to other AIs betting.
 *
 * Totally random AI would be a fun experiment, but wouldn't help the player get better at poker
 * and could be easily exploited by only betting made hands.
 * 
 * AI that only bets the strength of its hand can be exploited again by bluffing. A good poker player
 * considers ranges and probabilities and bets accordingly. A good player is elastic to the bets of others
 * and adjusts frequencies based on the information they have.
 *
 * Passive players can be exploited by betting more frequently to pick up pots for cheap.
 * Aggressive players can be exploited by betting strong hands or inducing bluffs.
 *
 * A good AI system requires good situational analysis: player stats, board texture etc.
 */

#pragma once


class AI
{
    public:

        float aggression;
        float tightness;
};
