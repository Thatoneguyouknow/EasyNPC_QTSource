#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <string>
#include <map>

using namespace std;

static const map<int, string> belief = {pair<int, string>(0, "Lawful "), pair<int, string>(1, "Neutral "), pair<int, string>(2, "Chaotic ")};
static const map<int, string> moral = {pair<int, string>(0, "Good "), pair<int, string>(1, "Neutral "), pair<int, string>(2, "Evil ")};

#endif // ALIGNMENT_H
