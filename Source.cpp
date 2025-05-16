#include <iostream>
using namespace std;

class GeneralGameState {
protected:
    int state[100];
    int size;     

public:
    GeneralGameState(int s) : size(s) {
        for (int i = 0; i < size; i++) {
            state[i] = 0;
        }
    }

    virtual void inputState() = 0;      
    virtual bool isTerminal() = 0;    
    virtual int heuristic() = 0;          
    virtual void bfs() = 0;              
    virtual void dfs(int depth = 0) = 0;  
    virtual int minimax(int depth, int alpha, int beta, bool isMax) = 0; 
    virtual int monteCarlo(int simulations) = 0;
};

class anyGame : public GeneralGameState {
public:
    anyGame(int s) : GeneralGameState(s) {}
    void inputState() override {
        cout << "Enter the initial state (0 for empty, 1 for MAX, -1 for MIN)"<< endl;
        for (int i = 0; i < size; i++) {
            cin >> state[i];
        }
    }

    bool isTerminal() override {
        for (int i = 0; i < size; i++) {
            if (state[i] == 0) return false;
        }
        return true;
    }

    int heuristic() override {
        int score = 0;
        for (int i = 0; i < size; i++) {
            score += state[i];
        }
        return score;
    }

    void bfs() override {
        cout << "BFS Search: ";
        for (int i = 0; i < size; i++) {
            if (state[i] == 0) {
                cout << " -> State[" << i << "]";
            }
        }
        cout << endl;
    }

    void dfs(int depth = 0) override {
        if (depth >= size) return;
        if (state[depth] == 0) {
            cout << " -> State[" << depth << "]";
        }
        dfs(depth + 1);
    }

    int minimax(int depth, int alpha, int beta, bool isMax) override {
        if (isTerminal() || depth == 0) {
            return heuristic();
        }

        if (isMax) {
            int maxEval = -10000;
            for (int i = 0; i < size; i++) {
                if (state[i] == 0) {
                    state[i] = 1;
                    int eval = minimax(depth - 1, alpha, beta, false);
                    state[i] = 0;
                    if (eval > maxEval) maxEval = eval;
                    if (eval > alpha) alpha = eval;
                    if (beta <= alpha) break;
                }
            }
            return maxEval;
        }
        else {
            int minEval = 10000;
            for (int i = 0; i < size; i++) {
                if (state[i] == 0) {
                    state[i] = -1; 
                    int eval = minimax(depth - 1, alpha, beta, true);
                    state[i] = 0;
                    if (eval < minEval) minEval = eval;
                    if (eval < beta) beta = eval;
                    if (beta <= alpha) break;
                }
            }
            return minEval;
        }
    }

   
    int monteCarlo(int simulations) override {
        int winCount = 0;
        for (int s = 0; s < simulations; s++) {
            int simState[100];
            for (int i = 0; i < size; i++) simState[i] = state[i];

        
            for (int i = 0; i < size; i++) {
                if (simState[i] == 0) {
                    simState[i] = (s % 2 == 0) ? 1 : -1; 
                }
            }
            if (heuristic() > 0) winCount++; 
        }
        return winCount;
    }
};

int main() {
    int size;
    cout << "Enter the size of your game state: "<<endl;
    cin >> size;

    anyGame game(size);

    game.inputState();

    cout << "Graph Search Algorithms:"<<endl;
    game.bfs();
    cout << "BFS Search: ";
    game.dfs();
    cout << "DFS Search: " << endl;

    int depth;
    cout << "Enter the search depth for Minimax: "<<endl;
    cin >> depth;
    int bestScore = game.minimax(depth, -10000, 10000, true);
    cout << "Minimax Best Score using Alpha-Beta Pruning: " << bestScore << endl;

    int simulations;
    cout << "Enter the number of Monte Carlo simulations: ";
    cin >> simulations;
    int mcResult = game.monteCarlo(simulations);
    cout << "Monte Carlo Win Estimate for MAX: " << mcResult << " / " << simulations << endl;

    return 0;
}
