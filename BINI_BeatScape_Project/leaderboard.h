#pragma once
class Leaderboard
{
private:
	struct Node {
		int score, maxCombo;
		Node* next;
		Node();
	};

	Node* head = NULL;

public:
	bool init();
};

