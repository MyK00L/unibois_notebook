/*
To calculate the Grundy value of a given state you need to:
- Get all possible transitions from this state
- Each transition can lead to a sum of independent games (one game in the degenerate case). Calculate the Grundy value for each independent game and xor-sum them.
- After we calculated Grundy values for each transition we find the state's value as the MEX of these numbers.
If the value is zero, then the current state is losing, otherwise it is winning.
*/