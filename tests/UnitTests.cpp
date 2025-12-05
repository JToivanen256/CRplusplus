#include <gtest/gtest.h>
#include "../src/entities/Unit.hpp"
#include "../assets/Cards and Decks/decks.hpp"  // For default Deck
#include "../src/game/Match.hpp"

TEST(UnitTest, Attack) {
  // Create two players
  Player player1("Player1", defaultDeck);
  Player player2("Player2", defaultDeck);

  // Create two units
  Unit unit1(0.0f, 0.0f, 100, 20, 1.0f, 30.0f, 50.0f, 100.0f, &player1, "Unit1", false);
  Unit unit2(10.0f, 0.0f, 100, 15, 1.0f, 30.0f, 50.0f, 100.0f, &player2, "Unit2", false);

  // Ensure unit1 can attack unit2
  EXPECT_TRUE(unit1.canAttack());

  // Perform attack
  unit1.attack(unit2);

  // Check that unit2's health has decreased
  EXPECT_EQ(unit2.getHealth(), 80);

  // Ensure unit1 cannot attack again immediately
  EXPECT_FALSE(unit1.canAttack());
}

TEST(PlayerTest, PlayCard) {
  Player player("TestPlayer", defaultDeck);

  // Initial elixir should be 0
  EXPECT_EQ(player.getElixir(), 0);

  auto& card = player.getHand().getCards().at(0);

  // Simulate elixir regeneration
  player.update(card->getCost() - 1); // Assume regen rate is 1 elixir per second
  EXPECT_EQ(player.getElixir(), card->getCost() - 1);

  // Try to play a card that costs more elixir than available
  bool result = player.playCard(card);
  EXPECT_FALSE(result); // Should fail

  // Regenerate enough elixir to play the card
  player.update(1.0f); // Regenerate 2 more elixir
  EXPECT_EQ(player.getElixir(), card->getCost());
  bool result2 = player.playCard(card);
  EXPECT_TRUE(result2); // Should succeed
}

TEST(MatchTest, AllEntities) {
  Player player1("Player1", defaultDeck);
  Player player2("Player2", defaultDeck);
  Match match(player1, player2);

  // Initially, there should be only towers
  auto entities = match.allEntities();
  int towerCount = 0;
  for (const auto& entity : entities) {
    if (dynamic_cast<Tower*>(entity)) {
      towerCount++;
    }
  }
  EXPECT_EQ(towerCount, 6); // 3 towers per player

  // Add a unit and a building
  auto& card = player1.getDeck().getCards().at(0);
  match.createUnitFromCard(
      *std::dynamic_pointer_cast<UnitCard>(card), 10, 10, player1);

  // Re-fetch entities
  entities = match.allEntities();
  int unitCount = 0;
  for (const auto& entity : entities) {
    if (dynamic_cast<Unit*>(entity)) {
      unitCount++;
    }
  }
  EXPECT_EQ(unitCount, 1); // One unit added
}