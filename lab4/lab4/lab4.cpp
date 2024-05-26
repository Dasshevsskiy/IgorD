#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Player {
    string name; 
    vector<int> predictions; 
};

void readDataFromFile(vector<Player>& players, vector<int>& winningNumbers, double& prizePool) {
    ifstream inputFile("lottery_data.txt");
    if (!inputFile) {
        cerr << "File opening error!" << endl;
        exit(1);
    }

    int numPlayers;
    inputFile >> numPlayers;

    for (int i = 0; i < numPlayers; ++i) {
        Player player;
        inputFile >> player.name;
        for (int j = 0; j < 6; ++j) {
            int prediction;
            inputFile >> prediction;
            player.predictions.push_back(prediction);
        }
        players.push_back(player);
    }

    for (int i = 0; i < 6; ++i) {
        int number;
        inputFile >> number;
        winningNumbers.push_back(number);
    }

    inputFile >> prizePool;
    inputFile.close();
}

double calculateWinnings(const vector<Player>& players, const vector<int>& winningNumbers) {
    double totalWinnings = 0.0;
    for (const auto& player : players) {
        int correctPredictions = 0;
        for (int prediction : player.predictions) {
            if (find(winningNumbers.begin(), winningNumbers.end(), prediction) != winningNumbers.end()) {
                correctPredictions++;
            }
        }
        double playerWinnings = 0.0;
        switch (correctPredictions) {
        case 0:
        case 1:
        case 2:
            playerWinnings = 0.0;
            break;
        case 3:
            playerWinnings = 100.0;
            break;
        case 4:
            playerWinnings = 1000.0;
            break;
        case 5:
            playerWinnings = 10000.0;
            break;
        case 6:
            playerWinnings = 1000000.0;
            break;
        }
        totalWinnings += playerWinnings;
        cout << "Player: " << player.name << ", win: " << playerWinnings << endl;
    }
    return totalWinnings;
}

int main() {
    vector<Player> players;
    vector<int> winningNumbers;
    double prizePool;

    readDataFromFile(players, winningNumbers, prizePool);

    cout << "Prize Pool Amount: " << prizePool << endl;

    double totalWinnings = calculateWinnings(players, winningNumbers);

    cout << "Total winnings: " << totalWinnings << endl;

    return 0;
}