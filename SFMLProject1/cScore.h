// cScore.h
#pragma once

class cScore {
private:
    int score;

public:
    cScore() : score(0) {}

    void addPoints(int points) {
        score += points;
    }

    int getScore() const {
        return score;
    }

    void reset() {
        score = 0;
    }
};
